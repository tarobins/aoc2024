#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <fstream>
#include <vector>
#include <numeric>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "flags/flags.h"

int process(std::ifstream& filestream)
{
    
    // Read the file into two vectors
    std::vector<int> column1;
    std::vector<int> column2;

    int val1, val2;
    while (filestream >> val1 >> val2)
    {
        column1.push_back(val1);
        column2.push_back(val2);
    }
    filestream.close();

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

