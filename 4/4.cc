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


    // Count the number of instances of XMAS, in any direction, in the table
    int xmas_count = 0;
    const std::string target = "XMAS";
    
    // Define all 8 directions: horizontal, vertical, and diagonal
    std::vector<std::pair<int, int>> directions = {
        {0, 1},   // right
        {0, -1},  // left
        {1, 0},   // down
        {-1, 0},  // up
        {1, 1},   // down-right diagonal
        {1, -1},  // down-left diagonal
        {-1, 1},  // up-right diagonal
        {-1, -1}  // up-left diagonal
    };
    
    // Check each position in the table as a potential starting point
    for (int row = 0; row < static_cast<int>(table.size()); ++row) {
        for (int col = 0; col < static_cast<int>(table[row].size()); ++col) {
            // Try each direction from this position
            for (const auto& dir : directions) {
                int dr = dir.first;
                int dc = dir.second;
                bool found = true;
                
                // Check if we can fit the entire word in this direction
                for (int i = 0; i < static_cast<int>(target.length()); ++i) {
                    int new_row = row + i * dr;
                    int new_col = col + i * dc;
                    
                    // Check bounds
                    if (new_row < 0 || new_row >= static_cast<int>(table.size()) ||
                        new_col < 0 || new_col >= static_cast<int>(table[new_row].size())) {
                        found = false;
                        break;
                    }
                    
                    // Check if character matches
                    if (table[new_row][new_col] != target[i]) {
                        found = false;
                        break;
                    }
                }
                
                if (found) {
                    xmas_count++;
                }
            }
        }
    }
    
    std::cout << "Number of XMAS instances found: " << xmas_count << std::endl;

    return 0;
}