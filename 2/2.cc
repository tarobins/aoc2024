#include <iostream>
#include <cstdlib>
#include <vector>

#include "flags/flags.h"
#include "table_read/table_read.h"

enum class Direction {
    UP,
    DOWN, 
    UNKNOWN
};

bool checkRow(ConstColItr begin, ConstColItr end) {
    Direction direction = Direction::UNKNOWN;
        ConstColItr colItr = begin;
        int lastValue = *colItr;
        colItr++;
        while (true) {
            const int diff = *colItr - lastValue;
            if (direction == Direction::UNKNOWN) {
                if (diff == 1 || diff == 2 || diff == 3) {
                    direction = Direction::UP; // Initial direction
                } else if (diff == -1 || diff == -2 || diff == -3) {
                    direction = Direction::DOWN; // Initial direction
                } else {
                    break; // Skip rows that are not safe
                }
            } else if (direction == Direction::UP) {
                if (diff <= 0 || diff > 3) {
                    break; // Skip rows that are not safe
                }
            } else if (direction == Direction::DOWN) {
                if (diff >= 0 || diff < -3) {
                    break; // Skip rows that are not safe
                }
            }
            lastValue = *colItr;
            if (++colItr == end) {
                // If we reach the end of the row, it is a safe row
                return true;
                break;
            }
        }
        return false; 
}

int process(Table table) {
    int numberOfSafeRows = 0;
    // Output the table contents
    for (const Row &row : table) {
        if (checkRow(row.begin(), row.end())) {
            numberOfSafeRows++;
        }
    }

    std::cout << "Number of safe rows: " << numberOfSafeRows << std::endl;
    return 0;
}