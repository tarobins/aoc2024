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


    // Count the number of X-shaped MAS patterns (two MAS sequences crossing at A)
    int xmas_count = 0;
    
    // Check each position as a potential center 'A' of an X-shaped MAS pattern
    // We need at least 1 cell margin on all sides for the full X pattern
    for (int row = 1; row < static_cast<int>(table.size()) - 1; ++row) {
        for (int col = 1; col < static_cast<int>(table[row].size()) - 1; ++col) {
            // The center must be 'A'
            if (table[row][col] != 'A') {
                continue;
            }
            
            // Check both diagonals for MAS or SAM patterns
            // Diagonal 1: top-left to bottom-right
            char tl = table[row - 1][col - 1];  // top-left
            char br = table[row + 1][col + 1];  // bottom-right
            
            // Diagonal 2: top-right to bottom-left  
            char tr = table[row - 1][col + 1];  // top-right
            char bl = table[row + 1][col - 1];  // bottom-left
            
            // Check if diagonal 1 forms MAS or SAM
            bool diag1_valid = (tl == 'M' && br == 'S') || (tl == 'S' && br == 'M');
            
            // Check if diagonal 2 forms MAS or SAM
            bool diag2_valid = (tr == 'M' && bl == 'S') || (tr == 'S' && bl == 'M');
            
            // If both diagonals form valid MAS/SAM patterns, we found an X-MAS
            if (diag1_valid && diag2_valid) {
                xmas_count++;
            }
        }
    }
    
    std::cout << "Number of X-shaped MAS patterns found: " << xmas_count << std::endl;

    return 0;
}