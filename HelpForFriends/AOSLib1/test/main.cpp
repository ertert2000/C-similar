#include <iostream>
#include <fcntl.h>
#include <liburing.h>
#include <unistd.h>
#include <sys/stat.h>
#include <vector>
#include <chrono>

constexpr int QUEUE_DEPTH = 16;
constexpr int CHUNK_SIZE = 1024 * 6; //меняем размер блока

struct IoTask {
    int fd;
    off_t offset;
    char *buffer;
};

void performFileCopy(const char* source, const char* destination, int opsCount) {
    int srcFd = open(source, O_RDONLY);
    int dstFd = open(destination, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (srcFd < 0 || dstFd < 0) {
        perror("Failed to open file");
        return;
    }

    io_uring ring;
    io_uring_queue_init(opsCount, &ring, 0);

    struct stat fileStat;
    fstat(srcFd, &fileStat);
    size_t totalSize = fileStat.st_size;

    auto start = std::chrono::high_resolution_clock::now();

    std::vector<IoTask> tasks(opsCount);
    for (int i = 0; i < opsCount; ++i) {
        tasks[i].fd = srcFd;
        tasks[i].offset = i * CHUNK_SIZE;
        tasks[i].buffer = new char[CHUNK_SIZE];
    }

    size_t copiedBytes = 0;
    while (copiedBytes < totalSize) {
        io_uring_sqe *sqe = io_uring_get_sqe(&ring);
        IoTask *task = &tasks[copiedBytes / CHUNK_SIZE % opsCount];
        io_uring_prep_read(sqe, task->fd, task->buffer, CHUNK_SIZE, task->offset);
        io_uring_sqe_set_data(sqe, task);
        io_uring_submit(&ring);

        io_uring_cqe *cqe;
        io_uring_wait_cqe(&ring, &cqe);
        IoTask *finishedTask = (IoTask*) io_uring_cqe_get_data(cqe);
        size_t bytesToWrite = std::min(static_cast<size_t>(CHUNK_SIZE), totalSize - copiedBytes);
        write(dstFd, finishedTask->buffer, bytesToWrite);
        copiedBytes += bytesToWrite;
        io_uring_cqe_seen(&ring, cqe);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Copy completed in: " << std::chrono::duration<double>(end - start).count() << " seconds\n";

    for (auto &task : tasks) delete[] task.buffer;
    io_uring_queue_exit(&ring);
    close(srcFd);
    close(dstFd);
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <source> <destination> <operations>\n";
        return EXIT_FAILURE;
    }
    performFileCopy(argv[1], argv[2], std::stoi(argv[3]));
    return EXIT_SUCCESS;
}
