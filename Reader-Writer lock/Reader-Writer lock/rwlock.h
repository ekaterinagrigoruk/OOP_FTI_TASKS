#pragma once
#include <mutex>
#include <condition_variable>

class rwlock final {
private:
    std::mutex m;
    std::condition_variable cond_var;
    int readers;
    bool writer;

public:
    rwlock() : readers(0), writer(false) {}

    rwlock(const rwlock&) = delete;

    rwlock(rwlock&& other) noexcept {
        std::unique_lock<std::mutex> lock(other.m);
        readers = other.readers;
        writer = other.writer;
        other.readers = 0;
        other.writer = false;
    };

    rwlock& operator=(const rwlock& other) = delete;

    rwlock& operator=(rwlock&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        std::unique_lock<std::mutex> lock(m, std::defer_lock);
        std::unique_lock<std::mutex> lock_other(other.m, std::defer_lock);
        std::lock(lock, lock_other);
        readers = other.readers;
        writer = other.writer;
        other.readers = 0;
        other.writer = false;
        return *this;
    };

    ~rwlock() {
        std::unique_lock<std::mutex> lock(m);
        readers = 0;
        writer = false;
        cond_var.notify_all();
    };

    const int get_readers() {
        return readers;
    };

    const bool get_writer() {
        return writer;
    }

    const bool read_lock(int64_t timeOut = -1) {
        std::unique_lock<std::mutex> lock(m);
        if (writer) {
            if (timeOut < 0) {
                cond_var.wait(lock, [this] { return !writer; });
            }
            else {
                if (!cond_var.wait_for(lock, std::chrono::milliseconds(timeOut), [this] { return !writer; })) {
                    return false;
                }
            }
        }
        readers++;
        return true;
    };

    void read_unlock() {
        std::unique_lock<std::mutex> lock(m);
        readers--;
        if (readers == 0) {
            cond_var.notify_all();
        }
    };

    const bool write_lock(int64_t timeOut = -1) {
        std::unique_lock<std::mutex> lock(m);
        if (readers > 0 || writer) {
            if (timeOut < 0) {
                cond_var.wait(lock, [this] { return readers == 0 && !writer; });
            }
            else {
                if (!cond_var.wait_for(lock, std::chrono::milliseconds(timeOut), [this] { return readers == 0 && !writer; })) {
                    return false;
                }
            }
        }
        writer = true;
        return true;
    };

    void write_unlock() {
        std::unique_lock<std::mutex> lock(m);
        writer = false;
        cond_var.notify_all();
    };
};