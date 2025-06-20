#include "flags/flags_string.h"
#include <iostream>
#include <regex>
#include <vector>

int process(const std::string& content) {
    // Vector to store pairs of numbers from mul() instances
    std::vector<std::pair<int, int>> mul_pairs;
    
    // Regex pattern to match mul(num1,num2) where num1 and num2 are 1-3 digit numbers
    std::regex mul_pattern(R"(mul\((\d{1,3}),(\d{1,3})\))");
    
    // Iterator for searching through the content
    std::sregex_iterator start(content.begin(), content.end(), mul_pattern);
    std::sregex_iterator end;
    
    // Extract all matches
    for (std::sregex_iterator i = start; i != end; ++i) {
        std::smatch match = *i;
        int num1 = std::stoi(match[1].str());  // First captured group
        int num2 = std::stoi(match[2].str());  // Second captured group
        mul_pairs.push_back({num1, num2});
    }
    
    int sum = 0;
    for (const auto& pair : mul_pairs) {
        sum += pair.first * pair.second;  // Calculate the sum of products
    }


    std::cout << "Sum of products: " << sum << std::endl;
    
    return 0;
}