#include "flags/file_setup.h"
#include <unistd.h>  // for getcwd
#include <cstdlib>   // for exit

ABSL_FLAG(std::string, filename, "test_data.txt", "Filename to process");

std::ifstream setup_and_open_file(int argc, char *argv[], const std::string& target_dir)
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
        exit(1);
    }

    // Use the target directory parameter
    std::filesystem::path file_path = std::filesystem::current_path() / target_dir / filename;
    std::cout << "File path: " << file_path << std::endl;
    std::ifstream file_stream(file_path.string());

    if (!file_stream.is_open())
    {
        std::cerr << "Unable to open file: " << file_path << std::endl;
        exit(1);
    }

    std::cerr << "File opened successfully." << std::endl;
    return file_stream;
}
