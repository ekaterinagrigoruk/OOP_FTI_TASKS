#include "gtest/gtest.h"

#include <algorithm>
#include <vector>
#include <list>
#include <forward_list>
#include <set>
#include "../FilterIterator/filteriterator.h"

using namespace FilterIterator;
using namespace CreatingFilterIterator;

struct Positivity {
    bool operator()(int x) const {
        return x > 0;
    }
};

struct Parity {
    bool operator()(int x) const {
        return x % 2 == 0;
    }
};

TEST(TestCaseName, TestName) {
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}

TEST(FilterIteratorTest, ParityNumbersVector) {
    std::vector<int> test = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    filter_iterator<Parity, std::vector<int>::iterator> end = make_filter_iterator(Parity(), test.end(), test.end());
    filter_iterator<Parity, std::vector<int>::iterator> it = make_filter_iterator(Parity(), test.begin(), test.end());
    std::vector<int> result;
    while (it != end) {
        result.push_back(*it);
        ++it;
    }
    std::vector<int> expection = { 2, 4, 6, 8, 10 };
    EXPECT_TRUE(result == expection);
}

TEST(FilterIteratorTest, PositiveNumbersVector) {
    std::vector<int> test = { 1, -2, 3, -4, 5, 6, 7, 8, -9, 10 };

    filter_iterator<Positivity, std::vector<int>::iterator> end = make_filter_iterator(Positivity(), test.end(), test.end());
    filter_iterator<Positivity, std::vector<int>::iterator> it = make_filter_iterator(Positivity(), test.begin(), test.end());
    std::vector<int> result;
    while (it != end) {
        result.push_back(*it);
        ++it;
    }
    std::vector<int> expection = { 1, 3, 5, 6, 7, 8, 10 };
    EXPECT_TRUE(result == expection);
}

TEST(FilterIteratorTest, EmptyVector) {
    std::vector<int> test;

    filter_iterator<Positivity, std::vector<int>::iterator> end = make_filter_iterator(Positivity(), test.end(), test.end());
    filter_iterator<Positivity, std::vector<int>::iterator> it = make_filter_iterator(Positivity(), test.begin(), test.end());
    std::vector<int> result;
    while (it != end) {
        result.push_back(*it);
        ++it;
    }
    std::vector<int> expection = {};
    EXPECT_TRUE(result == expection);
}

TEST(FilterIteratorTest, ParityNumbersSet) {
    std::set<int> test = { 1, -2, 3, -4, 5, 6, 7, 8, -9, 10 };

    filter_iterator<Parity, std::set<int>::iterator> end = make_filter_iterator(Parity(), test.end(), test.end());
    filter_iterator<Parity, std::set<int>::iterator> it = make_filter_iterator(Parity(), test.begin(), test.end());
    std::vector<int> result;
    while (it != end) {
        result.push_back(*it);
        ++it;
    }
    std::vector<int> expection = { -4, -2, 6, 8, 10 };
    EXPECT_EQ(result, expection);
}

TEST(FilterIteratorTest, PositiveNumbersSet) {
    std::set<int> test = { 1, -2, 3, -4, 5, 6, 7, 8, -9, 10 };

    filter_iterator<Positivity, std::set<int>::iterator> end = make_filter_iterator(Positivity(), test.end(), test.end());
    filter_iterator<Positivity, std::set<int>::iterator> it = make_filter_iterator(Positivity(), test.begin(), test.end());
    std::vector<int> result;
    while (it != end) {
        result.push_back(*it);
        ++it;
    }
    std::vector<int> expection = { 1, 3, 5, 6, 7, 8, 10 };
    EXPECT_TRUE(result == expection);
}

TEST(FilterIteratorTest, EmptySet) {
    std::set<int> test;

    filter_iterator<Positivity, std::set<int>::iterator> end = make_filter_iterator(Positivity(), test.end(), test.end());
    filter_iterator<Positivity, std::set<int>::iterator> it = make_filter_iterator(Positivity(), test.begin(), test.end());
    std::vector<int> result;
    while (it != end) {
        result.push_back(*it);
        ++it;
    }
    std::vector<int> expection = {};
    EXPECT_TRUE(result == expection);
}

TEST(FilterIteratorTest, PositiveNumbersList) {
    std::list<int> test = { 1, -2, 3, -4, 5, 6, 7, 8, -9, 10 };

    filter_iterator<Positivity, std::list<int>::iterator> end = make_filter_iterator(Positivity(), test.end(), test.end());
    filter_iterator<Positivity, std::list<int>::iterator> it = make_filter_iterator(Positivity(), test.begin(), test.end());
    std::vector<int> result;
    while (it != end) {
        result.push_back(*it);
        ++it;
    }
    std::vector<int> expection = { 1, 3, 5, 6, 7, 8, 10 };
    EXPECT_TRUE(result == expection);
}

TEST(FilterIteratorTest, ParityNumbersList) {
    std::list<int> test = { 1, -2, 3, -4, 5, 6, 7, 8, -9, 10 };

    filter_iterator<Parity, std::list<int>::iterator> end = make_filter_iterator(Parity(), test.end(), test.end());
    filter_iterator<Parity, std::list<int>::iterator> it = make_filter_iterator(Parity(), test.begin(), test.end());
    std::vector<int> result;
    while (it != end) {
        result.push_back(*it);
        ++it;
    }
    std::vector<int> expection = { -2, -4, 6, 8, 10 };
    EXPECT_EQ(result, expection);
}

TEST(FilterIteratorTest, EmptyList) {
    std::list<int> test;

    filter_iterator<Positivity, std::list<int>::iterator> end = make_filter_iterator(Positivity(), test.end(), test.end());
    filter_iterator<Positivity, std::list<int>::iterator> it = make_filter_iterator(Positivity(), test.begin(), test.end());
    std::vector<int> result;
    while (it != end) {
        result.push_back(*it);
        ++it;
    }
    std::vector<int> expection = {};
    EXPECT_TRUE(result == expection);
}

TEST(FilterIteratorTest, PositiveNumbersForwardList) {
    std::forward_list<int> test = { 1, -2, 3, -4, 5, 6, 7, 8, -9, 10 };

    filter_iterator<Positivity, std::forward_list<int>::iterator> end = make_filter_iterator(Positivity(), test.end(), test.end());
    filter_iterator<Positivity, std::forward_list<int>::iterator> it = make_filter_iterator(Positivity(), test.begin(), test.end());
    std::vector<int> result;
    while (it != end) {
        result.push_back(*it);
        ++it;
    }
    std::vector<int> expection = { 1, 3, 5, 6, 7, 8, 10 };
    EXPECT_TRUE(result == expection);
}

TEST(FilterIteratorTest, ParityNumbersForwardList) {
    std::forward_list<int> test = { 1, -2, 3, -4, 5, 6, 7, 8, -9, 10 };

    filter_iterator<Parity, std::forward_list<int>::iterator> end = make_filter_iterator(Parity(), test.end(), test.end());
    filter_iterator<Parity, std::forward_list<int>::iterator> it = make_filter_iterator(Parity(), test.begin(), test.end());
    std::vector<int> result;
    while (it != end) {
        result.push_back(*it);
        ++it;
    }
    std::vector<int> expection = { -2, -4, 6, 8, 10 };
    EXPECT_EQ(result, expection);
}

TEST(FilterIteratorTest, EmptyForwardList) {
    std::forward_list<int> test;

    filter_iterator<Positivity, std::forward_list<int>::iterator> end = make_filter_iterator(Positivity(), test.end(), test.end());
    filter_iterator<Positivity, std::forward_list<int>::iterator> it = make_filter_iterator(Positivity(), test.begin(), test.end());
    std::vector<int> result;
    while (it != end) {
        result.push_back(*it);
        ++it;
    }
    std::vector<int> expection = {};
    EXPECT_TRUE(result == expection);
}