#include "flags/flags_string.h"
#include <iostream>

int process(const std::string& content) {
    std::cout << "File content:" << std::endl;
    std::cout << content << std::endl;
    return 0;
}