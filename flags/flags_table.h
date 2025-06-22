#include "flags/file_setup.h"
#include "table/table.h"

#include <iostream>
#include <vector>
#include <numeric>

int process(Table<int> table);

int main(int argc, char *argv[])
{
    std::ifstream file_stream = setup_and_open_file(argc, argv, TARGET_DIR);
    auto parsed_data = parseTable<int>(file_stream);
    Table<int> table(parsed_data);

    std::cerr << "Table read successfully." << std::endl;

    return process(table);
}