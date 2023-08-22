#include <iostream>
#include <atomic>
#include <thread>
#include <mutex>

int a;
std::atomic<int> b;
std::mutex mutex;

void* SumByMutex(void*) {
    for (volatile int i = 0; i < 10000000; i++) {
        std::lock_guard<std::mutex> locker(mutex);
        a++;
    }
}

void* SumByAtomic(void*) {
    for (volatile int i = 0; i < 10000000; i++) {
        b++;
    }
}

void TestByMutex() {
    a = 0;
    pthread_t t1, t2;
    pthread_create(&t1, nullptr, SumByMutex, nullptr);
    pthread_create(&t2, nullptr, SumByMutex, nullptr);

    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);
    std::cout << a << std::endl;
}

void TestByAtomic() {
    b = 0;
    pthread_t t1, t2;
    pthread_create(&t1, nullptr, SumByAtomic, nullptr);
    pthread_create(&t2, nullptr, SumByAtomic, nullptr);

    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);
    std::cout << b << std::endl;
}

int main() {
    TestByMutex();
    TestByAtomic();
}