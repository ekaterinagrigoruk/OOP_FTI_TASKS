#include <thread>
#include <chrono>
#include <iostream>
#include <vector>
#include "pch.h"
#include "../Reader-Writer lock/rwlock.h"
#include "../Reader-Writer lock/reader_lock.h"
#include "../Reader-Writer lock/writer_lock.h"

class SharedData final {
private:
    rwlock& parent;
    std::string data;
public:
    SharedData(const std::string& data, rwlock& parent) : data(data), parent(parent) {}
    
    void write(const std::string& newdata, int64_t timeout) {
        writer_lock wl(parent, timeout);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        data = newdata;
    };

    std::string read(int64_t timeout) {
        reader_lock rl(parent, timeout);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        return data;
    };
};

void time_test_single_thread(int64_t timeout) {
    rwlock parent;
    SharedData Data("nodata", parent);

    auto start = std::chrono::steady_clock::now();
    Data.write("yesdata1", timeout);
    Data.write("yesdata2", timeout);
    Data.write("yesdata3", timeout);
    auto end = std::chrono::steady_clock::now();
    std::cout << "Elapsed time for writing in milliseconds: " <<
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
        << " ms" << std::endl;

    start = std::chrono::steady_clock::now();
    Data.read(timeout);
    Data.read(timeout);
    Data.read(timeout);
    end = std::chrono::steady_clock::now();
    std::cout << "Elapsed time for reading in milliseconds: " << 
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
        << " ms" << std::endl;
}

void time_test_multi_thread(int num_of_threads, int64_t timeout) {
    rwlock parent;
    SharedData Data("nodata", parent);

    std::vector<std::thread> threads;
    auto start = std::chrono::steady_clock::now();
    for (int counter_of_threads = 0; counter_of_threads < num_of_threads; counter_of_threads++) {
        threads.emplace_back([&Data, timeout]{
            Data.write("yesdata1", timeout);
            Data.write("yesdata2", timeout);
            Data.write("yesdata3", timeout);
            Data.read(timeout);
            Data.read(timeout);
            Data.read(timeout);
        });
    }
    for (auto& thread : threads) {
        thread.join();
    }
    auto end = std::chrono::steady_clock::now();
    std::cout << "Elapsed time for reading and for writing in milliseconds: " << 
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
        << " ms" << std::endl;
}

TEST(OneThreadTest, 10) {
    time_test_single_thread(10);
}

TEST(OneThreadTest, 100) {
    time_test_single_thread(100);
}

TEST(OneThreadTest, 1000) {
    time_test_single_thread(1000);
}

TEST(MultiThreadsTest, 5_10) {
    time_test_multi_thread(5, 10);
}

TEST(MultiThreadsTest, 10_10) {
    time_test_multi_thread(10, 10);
}

TEST(MultiThreadsTest, 10_100) {
    time_test_multi_thread(10, 100);
}

TEST(MultiThreadsTest, 10_1000) {
    time_test_multi_thread(10, 1000);
}

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