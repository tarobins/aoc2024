#include <iostream>
#include <cstdlib>

#include "flags/flags.h"
#include "table_read/table_read.h"

int process(Table table) {
    int numberOfSafeRows = 0;
    // Output the table contents
    for (const Row &row : table) {
        ConstColItr colItr = row.begin();
        const int lastValue = *colItr;
        colItr++;
        while (true) {
            const int diff = std::abs(lastValue - *colItr);
            if (!(diff == 1 || diff == 2)) {
                break; // Skip rows that are not safe
            } else {
                colItr++;
                if (colItr == row.end()) {
                    numberOfSafeRows++;
                    break; // Safe row found, exit the loop
                }
            }
        }
        
    }
    std::cout << "Number of safe rows: " << numberOfSafeRows << std::endl;
    return 0;
}