/*饿汉模式*/
class Singleton1 {
public:
    Singleton1(const Singleton1* other) = delete;
    static Singleton1* Get() {
        return m_Instance;
    }
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
            Singleton2* m_Instance = new Singleton2();
        }
        return m_Instance;
    }
private:
    Singleton2() {}
    static Singleton2* m_Instance;
};

Singleton2* Singleton2::m_Instance = nullptr;

/*the chreno*/
class Singleton {
public:
    Singleton(const Singleton& other) = delete;
    static Singleton& Get() {
        static Singleton m_Instance;
        return m_Instance;
    }
    static int Int() {
        return Get().IntImpl();
    }
private:
    int IntImpl() { return 5; }
    Singleton() {}
};

int number = Singleton::Int();