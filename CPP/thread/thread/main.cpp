#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

int main()
{
    std::mutex m1;
    std::mutex m2;

    auto f1 = [&m1, &m2]() {
        std::scoped_lock lg(m1, m2);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        };

    auto f2 = [&m1, &m2]() {
        std::scoped_lock lg(m1, m2);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        };

    std::thread thread1([&f1, &f2]() {
        f1();
        });

    std::thread thread2([&f1, &f2]() {
        f2();
        });

    thread1.join();
    thread2.join();

    return 0;
}