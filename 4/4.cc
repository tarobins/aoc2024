#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>

#include "flags/flags_table_char.h"
#include "table/table.h"

int process(Table<char> table)
{
    std::cout << "Table contents:" << std::endl;
    std::cout << "===============" << std::endl;
    
    // Print the table dimensions
    std::cout << "Table size: " << table.size() << " rows" << std::endl;
    if (table.size() > 0) {
        std::cout << "Row size: " << table[0].size() << " columns" << std::endl;
    }
    std::cout << std::endl;
    
    // Print each row of the table
    for (size_t i = 0; i < table.size(); ++i) {
        const Row<char>& row = table[i];
        std::cout << "Row " << i << ": ";
        for (const char& c : row) {
            std::cout << c;
        }
        std::cout << std::endl;
    }
    
    std::cout << "===============" << std::endl;
    std::cout << "Table printing complete." << std::endl;

    // print item 2,2 from the table
    if (table.size() > 2 && table[2].size() > 2) {
        std::cout << "Item at (2, 2): " << table[2][2] << std::endl;
    } else {
        std::cout << "Item at (2, 2) does not exist." << std::endl;
    }
    
    return 0;
}