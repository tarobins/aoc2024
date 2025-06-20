#include "flags/file_setup.h"
#include "table_read/table_read.h"

#include <iostream>
#include <vector>
#include <numeric>

int process(Table table);

int main(int argc, char *argv[])
{
    std::ifstream file_stream = setup_and_open_file(argc, argv, TARGET_DIR);
    Table table(file_stream);

    std::cerr << "Table read successfully." << std::endl;

    return process(table);
}