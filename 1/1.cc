#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <fstream>
#include <vector>
#include <numeric>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"

ABSL_FLAG(std::string, filename, "test_data.txt", "Filename to process");

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

    // Add your file processing logic here

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

    // print the contents of the file at filename in the current working directory
    std::filesystem::path file_path = std::filesystem::current_path() / "1" / filename;

    // Read the file into two vectors
    std::vector<int> column1;
    std::vector<int> column2;
    std::ifstream file_stream(file_path.string());

    if (file_stream.is_open())
    {
        int val1, val2;
        while (file_stream >> val1 >> val2)
        {
            column1.push_back(val1);
            column2.push_back(val2);
        }
        file_stream.close();
    }
    else
    {
        std::cerr << "Unable to open file: " << file_path << std::endl;
        return 1;
    }

    // print the contents of the vectors
    int sum = std::transform_reduce(
        column1.begin(), column1.end(), 0, std::plus<>(),
        [&column2](int val) {
            int count = std::count(column2.begin(), column2.end(), val);
            return val * count;
        });

    std::cout << "Sum of counts: " << sum << std::endl;

    return 0;
}