#include "flags/file_setup.h"
#include "table/table.h"

#include <iostream>
#include <vector>
#include <numeric>

int process(Table<char> table);

int main(int argc, char *argv[])
{
    std::ifstream file_stream = setup_and_open_file(argc, argv, TARGET_DIR);
    auto parsed_data = parseTable<char>(file_stream);
    Table<char> table(parsed_data);

    std::cerr << "Table read successfully." << std::endl;

    return process(table);
}
