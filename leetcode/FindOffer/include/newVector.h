#include <cstddef>
#include <utility>
template <typename T>
class Vector {
public:
    Vector() { Realloc(2); }

    ~Vector() {
        Clear();

        ::operator delete(data_, sizeof(T) * capacity_);
    }

    Vector(const Vector& other) {
        size_ = other.size_;
        capacity_ = other.capacity_;

        data_ = static_cast<T*>(::operator new(sizeof(T) * capacity_));

        for (size_t i = 0; i < size_; ++i) {
            new (&data_[i]) T(other.data_[i]);
        }
    }

    Vector(Vector&& other) noexcept {
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    Vector& operator=(Vector other) noexcept {
        Swap(other);

        return *this;
    }

    void push_back(const T& data) {
        if (size_ >= capacity_) {
            Realloc(capacity_ == 0 ? 2 : capacity_ + capacity_ / 2);
        }

        new (&data_[size_++]) T(data);
    }

    void push_back(T&& data) {
        if (size_ >= capacity_) {
            Realloc(capacity_ == 0 ? 2 : capacity_ + capacity_ / 2);
        }

        new (&data_[size_++]) T(std::move(data));
    }

    template <typename... Args>
    void emplace_back(Args&&... args) {
        if (size_ >= capacity_) {
            Realloc(capacity_ == 0 ? 2 : capacity_ + capacity_ / 2);
        }

        new (&data_[size_++]) T(std::forward<Args>(args)...);
    }

    void pop_back() {
        if (size_ > 0) {
            data_[--size_].~T();
        }
    }

    constexpr size_t size() const { return size_; }

    constexpr size_t capacity() const { return capacity_; }

    T& operator[](size_t index) { return data_[index]; }

    const T& operator[](size_t index) const { return data_[index]; }

    void Clear() {
        for (size_t i = 0; i < size_; ++i) {
            data_[i].~T();
        }

        size_ = 0;
    }

    void Swap(Vector& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

private:
    void Realloc(size_t new_capacity) {
        T* new_data = static_cast<T*>(::operator new(sizeof(T) * new_capacity));

        size_t move_size = size_ < new_capacity ? size_ : new_capacity;

        for (size_t i = 0; i < move_size; ++i) {
            new (&new_data[i]) T(std::move(data_[i]));
        }

        for (size_t i = 0; i < size_; ++i) {
            data_[i].~T();
        }

        ::operator delete(data_, sizeof(T) * capacity_);

        data_ = new_data;
        size_ = move_size;
        capacity_ = new_capacity;
    }

private:
    T* data_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;
};