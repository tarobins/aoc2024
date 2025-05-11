#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "table_read/table_read.h"

#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>
#include <numeric>

ABSL_FLAG(std::string, filename, "test_data.txt", "Filename to process");

int process(Table table);

int main(int argc, char *argv[])
{
    absl::ParseCommandLine(argc, argv); // Initialize Abseil Flags

    std::string filename = absl::GetFlag(FLAGS_filename);
    if (!filename.empty())
    {
        std::cout << "Processing file: " << filename << std::endl;
    }
    else
    {
        std::cout << "No filename provided." << std::endl;
        exit(1);
    }

    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != nullptr)
    {
        std::cout << "Current working directory: " << cwd << std::endl;
    }
    else
    {
        std::cerr << "getcwd() error" << std::endl;
        return 1; // Indicate an error
    }

    // Use the macro to determine the directory
    std::filesystem::path file_path = std::filesystem::current_path() / TARGET_DIR / filename;
    std::cout << "File path: " << file_path << std::endl;
    std::ifstream file_stream(file_path.string());

    if (!file_stream.is_open())
    {
        std::cerr << "Unable to open file: " << file_path << std::endl;
        return 1;
    }

    std::cerr << "File opened successfully." << std::endl;
    Table table(file_stream);

    std::cerr << "Table read successfully." << std::endl;

    return process(table);
}