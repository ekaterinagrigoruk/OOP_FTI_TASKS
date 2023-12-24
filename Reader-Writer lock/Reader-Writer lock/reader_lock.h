#pragma once
#include <mutex>
#include "rwlock.h"

class reader_lock final {
private:
    rwlock& parent;
    bool locked;

public:
    reader_lock() = delete;
    reader_lock(const rwlock&) = delete;
    reader_lock(rwlock&&) = delete;
    reader_lock& operator=(const rwlock&) = delete;
    reader_lock& operator=(rwlock&&) = delete;

    reader_lock(rwlock& parent, bool auto_lock = true, int64_t timeout = -1) : parent(parent) {
        locked = false;
        if (auto_lock) {
            lock(timeout);
        }
    };

    ~reader_lock() {
        if (locked) {
            unlock();
        }
    };

    const bool is_locked() {
        return locked;
    };

    bool lock(int64_t timeout = -1) {
        if (!locked) {
            locked = parent.read_lock(timeout);
            return locked;
        }
        return false;
    };

    void unlock() {
        if (locked) {
            parent.read_unlock();
            locked = false;
        }
    };
};