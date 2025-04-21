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