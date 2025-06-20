#include "flags/file_setup.h"

#include <iostream>
#include <vector>
#include <numeric>
#include <string>
#include <sstream>

int process(const std::string& content);

int main(int argc, char *argv[])
{
    std::ifstream file_stream = setup_and_open_file(argc, argv, TARGET_DIR);
    
    // Read entire file content into a string
    std::stringstream buffer;
    buffer << file_stream.rdbuf();
    std::string content = buffer.str();

    std::cerr << "File content read successfully." << std::endl;

    return process(content);
}
