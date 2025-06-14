#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <fstream>
#include <vector>
#include <numeric>
#include <algorithm>

// #include "absl/flags/flag.h"
// #include "absl/flags/parse.h"
#include "flags/flags.h"
#include "table_read/table_read.h"

int process(Table table)
{
    // Read the table into two vectors
    std::vector<int> column1;
    std::vector<int> column2;

    for (Row row : table)
    {
        column1.push_back(row[0]);
        column2.push_back(row[1]);
    }

    // print the contents of the vectors
    std::cout << "Column 1: ";
    for (const auto &val : column1)
    {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    std::cout << "Column 2: ";
    for (const auto &val : column2)
    {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // print the contents of the vectors
    int sum = std::transform_reduce(
        column1.begin(), column1.end(), 0, std::plus<>(),
        [&column2](int val)
        {
            int count = std::count(column2.begin(), column2.end(), val);
            return val * count;
        });

    std::cout << "Sum of counts: " << sum << std::endl;

    return 0;
}

