#include <gtest/gtest.h>

#include "Vector.hpp"

//  PushBack
TEST(VectorTest, PushBack) {
    Vector vec;
    vec.PushBack(1);
    vec.PushBack(2);
    vec.PushBack(3);

    EXPECT_EQ(vec.Size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
}

//  Insert
TEST(VectorTest, Insert) {
    Vector vec = {1, 2, 3};
    const size_t pos{5};
    vec.Insert(1, pos);

    EXPECT_EQ(vec.Size(), 4);
    EXPECT_EQ(vec[1], pos);
}

//  DeleteElement
TEST(VectorTest, DeleteElement) {
    Vector vec = {1, 2, 3, 4};
    vec.DeleteElement(2);

    EXPECT_EQ(vec.Size(), 3);
    EXPECT_EQ(vec[2], 4);
}

//  FindLeft
TEST(VectorTest, FindLeft) {
    Vector vec = {1, 2, 3, 4, 3};
    size_t index = vec.FindLeft(3);

    EXPECT_EQ(index, 2);
}

//  FindRight
TEST(VectorTest, FindRight) {
    Vector vec = {1, 2, 3, 4, 3};
    size_t index = vec.FindRight(3);

    EXPECT_EQ(index, 4);
}

//  DeleteAll
TEST(VectorTest, DeleteAll) {
    Vector vec = {1, 2, 3, 2, 4};
    vec.DeleteAll(2, 0, vec.Size() - 1);

    EXPECT_EQ(vec.Size(), 2);
    EXPECT_NE(vec[1], 2);
}

//  Sort
TEST(VectorTest, Sort) {
    Vector vec = {3, 1, 4, 2};
    vec.Sort(0, vec.Size() - 1);

    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
    EXPECT_EQ(vec[3], 4);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
