#pragma once
#include <mutex>
#include "rwlock.h"

class writer_lock final {
private:
    rwlock& parent;
    bool locked;

public:
    writer_lock() = delete;
    writer_lock(const rwlock&) = delete;
    writer_lock(rwlock&&) = delete;
    writer_lock& operator=(const rwlock&) = delete;
    writer_lock& operator=(rwlock&&) = delete;

    writer_lock(rwlock& parent, bool auto_lock = true, int64_t timeout = -1) : parent(parent) {
        locked = false;
        if (auto_lock) {
            lock(timeout);
        }
    };

    ~writer_lock() {
        if (locked) {
            unlock();
        }
    };

    bool is_locked() {
        return locked;
    };

    bool lock(int64_t timeout = -1) {
        if (!locked && parent.write_lock(timeout)) {
            locked = true;
            return true;
        }
        return false;
    };

    void unlock() {
        if (locked) {
            parent.write_unlock();
            locked = false;
        }
    };
};