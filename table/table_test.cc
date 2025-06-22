#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <fstream>
#include <numeric>
// #include "../flags/flags.h"
#include "table.h"



// Test case for the process function
TEST(Test, Test1) {

    // // Create a mock input file
    std::istringstream mock_file("1 2\n3 4 5\n1");

    // // // Verify the result
    Table<int> table(mock_file);

    EXPECT_EQ(table[0][0], 1);
    EXPECT_EQ(table[0][1], 2);
    EXPECT_EQ(table[1][0], 3);
    EXPECT_EQ(table[1][1], 4);
    EXPECT_EQ(table[1][2], 5);
}

// TEST(Test, Characters) {

//     // // Create a mock input file
//     std::istringstream mock_file("AB\nCD\n1");

//     // // // Verify the result
//     Table table(mock_file);

//     EXPECT_EQ(table[0][0], 'A');
//     EXPECT_EQ(table[0][1], 'B');
//     EXPECT_EQ(table[1][0], 'C');
//     EXPECT_EQ(table[1][1], 'D');
// }

TEST(Test, ExtraSpaces) {
    // Create a mock input file with extra spaces
    std::istringstream mock_file("1  2");

    // Verify the result
    Table<int> table(mock_file);

    EXPECT_EQ(table[0][0], 1);
    EXPECT_EQ(table[0][1], 2);
}

TEST(Test, TestRowCount) {
    // Create a mock input file
    std::istringstream mock_file("1 2\n3 4 5\n1");

    // Verify the result
    Table<int> table(mock_file);

    EXPECT_EQ(table.size(), 3);
}

TEST(Test, TestColumnCount) {
    // Create a mock input file
    std::istringstream mock_file("1 2\n3 4 5\n1");

    // Verify the result
    Table<int> table(mock_file);

    EXPECT_EQ(table[0].size(), 2);
    EXPECT_EQ(table[1].size(), 3);
}

TEST(Test, TestRowIterator) {
    std::istringstream mock_file("1 2\n3 4 5\n1");

    Table<int> table(mock_file);

    ConstRowItr<int> it = table.begin();

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

    Table<int> table(mock_file);

    ConstColItr<int> it = table[1].begin();
    EXPECT_EQ(*it, 3);
    ++it;
    EXPECT_EQ(*it, 4);
    ++it;
    EXPECT_EQ(*it, 5);
    ++it;
    EXPECT_EQ(it, table[1].end());
}

// Tests for the new parsing functions
TEST(Test, ParseRowFunction) {
    // Test parseRow with integers
    std::string rowData = "10 20 30";
    auto result = parseRow<int>(rowData);
    
    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 10);
    EXPECT_EQ(result[1], 20);
    EXPECT_EQ(result[2], 30);
}

TEST(Test, ParseRowWithDelimiter) {
    // Test parseRow with comma delimiter
    std::string csvData = "1.5,2.7,3.9";
    auto result = parseRow<double>(csvData, ',');
    
    EXPECT_EQ(result.size(), 3);
    EXPECT_DOUBLE_EQ(result[0], 1.5);
    EXPECT_DOUBLE_EQ(result[1], 2.7);
    EXPECT_DOUBLE_EQ(result[2], 3.9);
}

TEST(Test, ParseRowStringData) {
    // Test parseRow with strings
    std::string stringData = "hello world test";
    auto result = parseRow<std::string>(stringData);
    
    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], "hello");
    EXPECT_EQ(result[1], "world");
    EXPECT_EQ(result[2], "test");
}

TEST(Test, ParseTableFunction) {
    // Test parseTable function
    std::istringstream input("1 2 3\n4 5 6\n7 8 9");
    auto result = parseTable<int>(input);
    
    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0].size(), 3);
    EXPECT_EQ(result[1].size(), 3);
    EXPECT_EQ(result[2].size(), 3);
    
    EXPECT_EQ(result[0][0], 1);
    EXPECT_EQ(result[0][1], 2);
    EXPECT_EQ(result[0][2], 3);
    EXPECT_EQ(result[1][0], 4);
    EXPECT_EQ(result[1][1], 5);
    EXPECT_EQ(result[1][2], 6);
    EXPECT_EQ(result[2][0], 7);
    EXPECT_EQ(result[2][1], 8);
    EXPECT_EQ(result[2][2], 9);
}

TEST(Test, ParseTableWithEmptyLines) {
    // Test parseTable ignores empty lines
    std::istringstream input("1 2\n\n3 4\n\n5 6");
    auto result = parseTable<int>(input);
    
    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0][0], 1);
    EXPECT_EQ(result[0][1], 2);
    EXPECT_EQ(result[1][0], 3);
    EXPECT_EQ(result[1][1], 4);
    EXPECT_EQ(result[2][0], 5);
    EXPECT_EQ(result[2][1], 6);
}

TEST(Test, RowConstructorFromVector) {
    // Test Row constructor from pre-parsed vector
    std::vector<int> data = {100, 200, 300};
    Row<int> row(data);
    
    EXPECT_EQ(row.size(), 3);
    EXPECT_EQ(row[0], 100);
    EXPECT_EQ(row[1], 200);
    EXPECT_EQ(row[2], 300);
}

TEST(Test, TableConstructorFromParsedData) {
    // Test Table constructor from pre-parsed 2D vector
    std::vector<std::vector<int>> tableData = {
        {1, 2, 3},
        {4, 5},
        {6, 7, 8, 9}
    };
    
    Table<int> table(tableData);
    
    EXPECT_EQ(table.size(), 3);
    EXPECT_EQ(table[0].size(), 3);
    EXPECT_EQ(table[1].size(), 2);
    EXPECT_EQ(table[2].size(), 4);
    
    EXPECT_EQ(table[0][0], 1);
    EXPECT_EQ(table[0][1], 2);
    EXPECT_EQ(table[0][2], 3);
    EXPECT_EQ(table[1][0], 4);
    EXPECT_EQ(table[1][1], 5);
    EXPECT_EQ(table[2][0], 6);
    EXPECT_EQ(table[2][1], 7);
    EXPECT_EQ(table[2][2], 8);
    EXPECT_EQ(table[2][3], 9);
}

TEST(Test, ParseValueSpecializations) {
    // Test parseValue template specializations
    EXPECT_EQ(parseValue<int>("42"), 42);
    EXPECT_EQ(parseValue<int>("-123"), -123);
    
    EXPECT_DOUBLE_EQ(parseValue<double>("3.14"), 3.14);
    EXPECT_DOUBLE_EQ(parseValue<double>("-2.5"), -2.5);
    
    EXPECT_EQ(parseValue<std::string>("hello"), "hello");
    EXPECT_EQ(parseValue<std::string>(""), "");
}

TEST(Test, IntegrationParseAndConstruct) {
    // Test integration: parse data then construct objects
    std::istringstream input("10 20\n30 40 50");
    auto parsedData = parseTable<int>(input);
    
    // Create table from parsed data
    Table<int> table(parsedData);
    
    EXPECT_EQ(table.size(), 2);
    EXPECT_EQ(table[0][0], 10);
    EXPECT_EQ(table[0][1], 20);
    EXPECT_EQ(table[1][0], 30);
    EXPECT_EQ(table[1][1], 40);
    EXPECT_EQ(table[1][2], 50);
}

TEST(Test, ParseRowEdgeCases) {
    // Test empty string
    auto empty = parseRow<int>("");
    EXPECT_EQ(empty.size(), 0);
    
    // Test single value
    auto single = parseRow<int>("42");
    EXPECT_EQ(single.size(), 1);
    EXPECT_EQ(single[0], 42);
    
    // Test multiple spaces
    auto multiSpace = parseRow<int>("1    2     3");
    EXPECT_EQ(multiSpace.size(), 3);
    EXPECT_EQ(multiSpace[0], 1);
    EXPECT_EQ(multiSpace[1], 2);
    EXPECT_EQ(multiSpace[2], 3);
}


