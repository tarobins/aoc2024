#include <iostream>
#include <sstream>
#include "table.h"

int main() {
    // Example 1: Using the refactored Table and Row classes as before
    std::cout << "=== Example 1: Using Table and Row classes ===" << std::endl;
    std::istringstream input("10 20 30\n40 50\n60 70 80 90");
    Table<int> table(input);
    
    for (size_t i = 0; i < table.size(); ++i) {
        std::cout << "Row " << i << ": ";
        for (size_t j = 0; j < table[i].size(); ++j) {
            std::cout << table[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
    // Example 2: Using the standalone parsing functions
    std::cout << "\n=== Example 2: Using standalone parsing functions ===" << std::endl;
    
    // Parse a single row
    std::string rowStr = "100 200 300";
    auto rowData = parseRow<int>(rowStr);
    std::cout << "Parsed row: ";
    for (const auto& val : rowData) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    // Parse with different delimiter
    std::string csvRow = "1.5,2.7,3.9";
    auto csvData = parseRow<double>(csvRow, ',');
    std::cout << "Parsed CSV row: ";
    for (const auto& val : csvData) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    // Parse string data
    std::string stringRow = "hello world test";
    auto stringData = parseRow<std::string>(stringRow);
    std::cout << "Parsed string row: ";
    for (const auto& val : stringData) {
        std::cout << "'" << val << "' ";
    }
    std::cout << std::endl;
    
    // Example 3: Parse entire table using standalone function
    std::cout << "\n=== Example 3: Using parseTable function ===" << std::endl;
    std::istringstream tableInput("1 2 3\n4 5 6\n7 8 9");
    auto tableData = parseTable<int>(tableInput);
    
    std::cout << "Parsed table data:" << std::endl;
    for (size_t i = 0; i < tableData.size(); ++i) {
        std::cout << "Row " << i << ": ";
        for (const auto& val : tableData[i]) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    
    // Example 4: Create Table from pre-parsed data
    std::cout << "\n=== Example 4: Creating Table from pre-parsed data ===" << std::endl;
    Table<int> prebuiltTable(tableData);
    std::cout << "Table created from parsed data has " << prebuiltTable.size() << " rows" << std::endl;
    std::cout << "First row: ";
    for (size_t j = 0; j < prebuiltTable[0].size(); ++j) {
        std::cout << prebuiltTable[0][j] << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
