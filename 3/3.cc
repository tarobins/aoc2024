#include "flags/flags_string.h"
#include <iostream>
#include <regex>
#include <vector>

int process(const std::string& content) {

    // Vector to store pairs of numbers from mul() instances
    std::vector<std::pair<int, int>> mul_pairs;
    
    // Regex pattern to match mul(num1,num2), do(), or don't()
    std::regex pattern(R"(mul\((\d{1,3}),(\d{1,3})\)|do\(\)|don't\(\))");
    
    // Iterator for searching through the content
    std::sregex_iterator start(content.begin(), content.end(), pattern);
    std::sregex_iterator end;
    
    bool mul_enabled = true;  // Track if mul operations are enabled
    
    // Extract all matches
    for (std::sregex_iterator i = start; i != end; ++i) {
        std::smatch match = *i;
        std::string full_match = match[0].str();  // The entire matched text
        
        if (full_match == "do()") {
            mul_enabled = true;
        } else if (full_match == "don't()") {
            mul_enabled = false;
        } else if (full_match.substr(0, 3) == "mul" && mul_enabled) {
            // This is a mul() match and multiplication is enabled
            int num1 = std::stoi(match[1].str());  // First captured group
            int num2 = std::stoi(match[2].str());  // Second captured group
            mul_pairs.push_back({num1, num2});
        }
    }
    
    int sum = 0;
    for (const auto& pair : mul_pairs) {
        sum += pair.first * pair.second;  // Calculate the sum of products
    }


    std::cout << "Sum of products: " << sum << std::endl;
    
    return 0;
}