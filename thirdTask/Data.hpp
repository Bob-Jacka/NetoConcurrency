#ifndef DATA_HPP
#define DATA_HPP

#include <mutex>
#include <utility>
#include <string>

class Data {
    int value;
    std::string name;
    mutable std::mutex mtx;

public:
    explicit Data(const int data_value = 0, std::string data_name = "") : value(data_value), name(std::move(data_name)) {
    }

    Data() = delete;

    int get_value() const {
        return value;
    }

    std::string get_name() const {
        return name;
    }

    void set_value(const int new_v) {
        value = new_v;
    }

    void set_name(const std::string &new_name) {
        name = new_name;
    }

    friend void swap_with_scoped_lock(Data &a, Data &b);

    friend void swap_with_unique_lock(Data &a, Data &b);

    friend void swap_with_lock(Data &a, Data &b);
};

inline void swap_with_lock(Data &a, Data &b) {
    std::lock(a.mtx, b.mtx);
    std::lock_guard lock_a(a.mtx, std::adopt_lock);
    std::lock_guard lock_b(b.mtx, std::adopt_lock);

    std::swap(a.value, b.value);
    std::swap(a.name, b.name);
}

inline void swap_with_scoped_lock(Data &a, Data &b) {
    std::scoped_lock lock(a.mtx, b.mtx);

    std::swap(a.value, b.value);
    std::swap(a.name, b.name);
}

inline void swap_with_unique_lock(Data &a, Data &b) {
    std::unique_lock lock_a(a.mtx, std::defer_lock);
    std::unique_lock lock_b(b.mtx, std::defer_lock);

    std::lock(lock_a, lock_b);

    std::swap(a.value, b.value);
    std::swap(a.name, b.name);
}

#endif
