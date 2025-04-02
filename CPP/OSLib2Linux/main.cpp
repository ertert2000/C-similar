#include <iostream>
#include <fstream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

#define FILENAME "shared_memory_file"
#define FILESIZE 1024

void server()
{
    int fd = open(FILENAME, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1)
    {
        perror("open");
        return;
    }
    ftruncate(fd, FILESIZE);

    void* ptr = mmap(NULL, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED)
    {
        perror("mmap");
        close(fd);
        return;
    }

    bool running = true;
    while (running)
    {
        std::cout << "Server Menu:\n1. Perform \n2. Record data \n3. Complete the work \n Select: ";
        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice)
        {
        case 1:
            std::cout << "The file is projected in memory.\n";
            break;
        case 2:
            std::cout << "Enter the data: ";
            std::cin.getline((char*)ptr, FILESIZE);
            break;
        case 3:
            running = false;
            break;
        default:
            std::cout << "The wrong choice.\n";
        }
    }

    munmap(ptr, FILESIZE);
    close(fd);
    unlink(FILENAME);
}

void client()
{
    int fd = open(FILENAME, O_RDWR);
    if (fd == -1)
    {
        perror("open");
        return;
    }

    void* ptr = mmap(NULL, FILESIZE, PROT_READ, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED)
    {
        perror("mmap");
        close(fd);
        return;
    }

    bool running = true;
    while (running)
    {
        std::cout << "Client Menu:\n1. Perform \n2. Read data \n3. Complete the work \n Select: ";
        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice)
        {
        case 1:
            std::cout << "The file is projected in memory.\n";
            break;
        case 2:
            std::cout << "Read data: " << (char*)ptr << "\n";
            break;
        case 3:
            running = false;
            break;
        default:
            std::cout << "The wrong choice.\n";
        }
    }

    munmap(ptr, FILESIZE);
    close(fd);
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <server|client>\n";
        return 1;
    }

    std::string mode = argv[1];
    if (mode == "server")
        server();
    else if (mode == "client")
        client();
    else
    {
        std::cerr << "Unknown mode: " << mode << "\n";
        return 1;
    }

    return 0;
}
