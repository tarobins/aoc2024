#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <fstream>
#include <numeric>
// #include "../flags/flags.h"
#include "table_read.h"



// Test case for the process function
TEST(Test, Test1) {

    // // Create a mock input file
    std::istringstream mock_file("1 2\n3 4 5\n1");

    // // // Verify the result
    Table table(mock_file);

    EXPECT_EQ(table[0][0], 1);
    EXPECT_EQ(table[0][1], 2);
    EXPECT_EQ(table[1][0], 3);
    EXPECT_EQ(table[1][1], 4);
    EXPECT_EQ(table[1][2], 5);
}

TEST(Test, ExtraSpaces) {
    // Create a mock input file with extra spaces
    std::istringstream mock_file("1  2");

    // Verify the result
    Table table(mock_file);

    EXPECT_EQ(table[0][0], 1);
    EXPECT_EQ(table[0][1], 2);
}

TEST(Test, TestRowCount) {
    // Create a mock input file
    std::istringstream mock_file("1 2\n3 4 5\n1");

    // Verify the result
    Table table(mock_file);

    EXPECT_EQ(table.size(), 3);
}

TEST(Test, TestColumnCount) {
    // Create a mock input file
    std::istringstream mock_file("1 2\n3 4 5\n1");

    // Verify the result
    Table table(mock_file);

    EXPECT_EQ(table[0].size(), 2);
    EXPECT_EQ(table[1].size(), 3);
}

TEST(Test, TestRowIterator) {
    std::istringstream mock_file("1 2\n3 4 5\n1");

    Table table(mock_file);

    ConstRowItr it = table.begin();

    EXPECT_EQ((*it)[0], 1);
    EXPECT_EQ((*it)[1], 2);
    ++it;
    EXPECT_EQ((*it)[0], 3);
    EXPECT_EQ((*it)[1], 4);
    EXPECT_EQ((*it)[2], 5);
    ++it;
    EXPECT_EQ((*it)[0], 1);
    ++it;
    EXPECT_EQ(it, table.end());
}

TEST(Test, TestSingleRowIterator) {
    std::istringstream mock_file("1 2\n3 4 5\n1");

    Table table(mock_file);

    ConstColItr it = table[1].begin();
    EXPECT_EQ(*it, 3);
    ++it;
    EXPECT_EQ(*it, 4);
    ++it;
    EXPECT_EQ(*it, 5);
    ++it;
    EXPECT_EQ(it, table[1].end());
}


