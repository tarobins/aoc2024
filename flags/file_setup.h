#ifndef FLAGS_FILE_SETUP_H_
#define FLAGS_FILE_SETUP_H_

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"

#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

ABSL_DECLARE_FLAG(std::string, filename);

std::ifstream setup_and_open_file(int argc, char *argv[], const std::string& target_dir);

#endif  // FLAGS_FILE_SETUP_H_
