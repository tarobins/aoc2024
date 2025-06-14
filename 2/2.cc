#include <iostream>

#include "flags/flags.h"
#include "table_read/table_read.h"

int process(Table table) {
    // Output the table contents
    for (const Row &row : table) {
        for (const int &cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}