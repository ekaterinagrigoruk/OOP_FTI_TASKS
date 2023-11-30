#include "pch.h"
#include "../SharedPointer/SharedPointer.h"

struct Deleter {
    template <typename T>
    void operator()(T* ptr) const {
        delete ptr;
    }
};

TEST(SharedPTRTest, DefaultConstructor) {
    SharedPTR<int, Deleter> ptr;
    EXPECT_FALSE(ptr);
}

TEST(SharedPTRTest, CustomConstructor) {
    int* ptr = new int(1974);
    SharedPTR<int, Deleter> sp(ptr);
    EXPECT_TRUE(sp);
    EXPECT_EQ(*sp, 1974);
}

TEST(SharedPTRTest, MoveConstructor) {
    SharedPTR<int, Deleter> sp1(new int(1974));
    SharedPTR<int, Deleter> sp2(std::move(sp1));
    EXPECT_FALSE(sp1);
    EXPECT_TRUE(sp2);
    EXPECT_EQ(*sp2, 1974);
}

TEST(SharedPTRTest, CopyConstructor) {
    SharedPTR<int, Deleter> sp1(new int(1974));
    SharedPTR<int, Deleter> sp2(sp1);
    EXPECT_TRUE(sp1);
    EXPECT_TRUE(sp2);
    EXPECT_EQ(*sp1, 1974);
    EXPECT_EQ(*sp2, 1974);
}

TEST(SharedPTRTest, AssignmentOperatorMove) {
    SharedPTR<int, Deleter> sp1(new int(1974));
    SharedPTR<int, Deleter> sp2;
    sp2 = std::move(sp1);
    EXPECT_FALSE(sp1);
    EXPECT_TRUE(sp2);
    EXPECT_EQ(*sp2, 1974);
}

TEST(SharedPTRTest, AssignmentOperatorValue) {
    SharedPTR<int, Deleter> sp;
    sp = new int(1974);
    EXPECT_TRUE(sp);
    EXPECT_EQ(*sp, 1974);
}

TEST(SharedPTRTest, CopyAssignment) {
    SharedPTR<int, Deleter> sp1(new int(1974));
    SharedPTR<int, Deleter> sp2;
    sp2 = sp1;
    EXPECT_TRUE(sp1);
    EXPECT_TRUE(sp2);
    EXPECT_EQ(*sp1, 1974);
    EXPECT_EQ(*sp2, 1974);
}

TEST(SharedPTRTest, Get) {
    int* ptr = new int(1974);
    SharedPTR<int, Deleter> sp(ptr);
    EXPECT_EQ(sp.get(), ptr);
}

TEST(SharedPTRTest, GetDeleter) {
    SharedPTR<int, Deleter> sp(new int(1974));
    static_assert(std::is_same<decltype(sp.get_deleter()), Deleter&>::value);
}

TEST(SharedPTRTest, Bool) {
    SharedPTR<int, Deleter> sp;
    EXPECT_FALSE(sp);
    sp = new int(1974);
    EXPECT_TRUE(sp);
}

TEST(SharedPTRTest, Unique) {
    SharedPTR<int, Deleter> sp1(new int(1974));
    SharedPTR<int, Deleter> sp2(sp1);
    EXPECT_FALSE(sp1.unique());
    EXPECT_FALSE(sp2.unique());
}

TEST(SharedPTRTest, Release) {
    SharedPTR<int, Deleter> sp(new int(1974));
    sp.release();
    EXPECT_FALSE(sp);
}

TEST(SharedPTRTest, ResetMethod) {
    SharedPTR<int, Deleter> sp(new int(1974));
    int* newPtr = new int(2003);
    sp.reset(newPtr);
    EXPECT_TRUE(sp);
    EXPECT_EQ(*sp, 2003);
}

TEST(SharedPTRTest, Swap) {
    SharedPTR<int, Deleter> sp1(new int(1974));
    SharedPTR<int, Deleter> sp2(new int(2003));
    sp1.swap(sp2);
    EXPECT_EQ(*sp1, 2003);
    EXPECT_EQ(*sp2, 1974);
}

TEST(SharedPTRTest, MakeSharedPtr) {
    auto sp = make_shared_ptr<int> (1974);
    EXPECT_TRUE(sp);
    EXPECT_EQ(*sp, 1974);
}

TEST(SharedPTRTest, ArrayType) {
    int* ptr = new int[5]{ 1, 2, 3, 4, 5 };
    SharedPTR<int[], Deleter> sp(ptr);
    EXPECT_TRUE(sp);
    EXPECT_EQ(sp + 2, 3);
}

TEST(SharedPTRTest, ResetNullPtr) {
    int* ptr = new int(1974);
    SharedPTR<int, Deleter> sp(ptr);
    sp.reset();
    EXPECT_FALSE(sp);
}
