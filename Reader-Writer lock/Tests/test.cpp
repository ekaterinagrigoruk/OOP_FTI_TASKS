#include "pch.h"
#include "../Reader-Writer lock/rwlock.h"
#include "../Reader-Writer lock/reader_lock.h"
#include "../Reader-Writer lock/writer_lock.h"

TEST(ReadWriteLockTest, ReadLockTest) {
    rwlock rw;
    reader_lock lock(rw);
    ASSERT_TRUE(lock.is_locked());
    lock.unlock();
    ASSERT_FALSE(lock.is_locked());
}

TEST(ReadWriteLockTest, MultipleReadLockTest) {
    rwlock rw;
    reader_lock lock1(rw);
    reader_lock lock2(rw);
    ASSERT_TRUE(lock1.is_locked());
    ASSERT_FALSE(lock2.lock());
}

TEST(ReadWriteLockTest, WriteLockTest) {
    rwlock rw;
    writer_lock lock(rw);
    ASSERT_TRUE(lock.is_locked());
    lock.unlock();
    ASSERT_FALSE(lock.is_locked());
}

TEST(ReadWriteLockTest, MultipleWriteLockTest) {
    rwlock rw;
    writer_lock lock1(rw);
    writer_lock lock2(rw);
    ASSERT_TRUE(lock1.is_locked());
    ASSERT_FALSE(lock2.lock());
}