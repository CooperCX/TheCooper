#include <mutex>

class Singleton {
public:
    static Singleton& Get() {
        static Singleton singleton;
        return singleton;
    }

    Singleton(const Singleton& other) = delete;
    Singleton& operator=(const Singleton& other) = delete;

    Singleton(Singleton&& other) = delete;
    Singleton& operator=(Singleton&& other) = delete;

private:
    Singleton() {}
    ~Singleton() {}
};

/*饿汉模式*/
class Singleton1 {
public:
    Singleton1(const Singleton1* other) = delete;
    static Singleton1* Get() { return m_Instance; }

private:
    Singleton1() {}
    static Singleton1* m_Instance;
};

Singleton1* Singleton1::m_Instance = new Singleton1();

/*懒汉模式*/
class Singleton2 {
public:
    Singleton2(const Singleton2* other) = delete;
    static Singleton2* Get() {
        if (m_Instance == nullptr) {
            std::lock_guard<std::mutex> locker(mutex);
            m_Instance = new Singleton2();
        }
        return m_Instance;
    }
    static std::mutex mutex;

private:
    Singleton2() {}
    static Singleton2* m_Instance;
};

Singleton2* Singleton2::m_Instance = nullptr;