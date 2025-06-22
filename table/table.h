#ifndef table_h
#define table_h

#include <istream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

// Forward declarations
template <typename T>
class Row;

// Parsing utilities
template <typename T>
T parseValue(const std::string& str);

// Specialization for int
template <>
inline int parseValue<int>(const std::string& str) {
    return std::stoi(str);
}

// Specialization for double
template <>
inline double parseValue<double>(const std::string& str) {
    return std::stod(str);
}

// Specialization for string
template <>
inline std::string parseValue<std::string>(const std::string& str) {
    return str;
}

// Specialization for char
template <>
inline char parseValue<char>(const std::string& str) {
    return str.empty() ? '\0' : str[0];
}

template <typename T>
std::vector<T> parseRow(const std::string& rowData, char delimiter = ' ') {
    std::vector<T> result;
    std::stringstream ss(rowData);
    std::string token;
    
    while (std::getline(ss, token, delimiter)) {
        if (!token.empty()) {
            result.push_back(parseValue<T>(token));
        }
    }
    
    return result;
}

// Specialization for char to parse each character individually (no delimiter)
template <>
inline std::vector<char> parseRow<char>(const std::string& rowData, char delimiter) {
    std::vector<char> result;
    for (char c : rowData) {
        if (c != '\r' && c != '\n') {  // Skip line ending characters
            result.push_back(c);
        }
    }
    return result;
}

template <typename T>
std::vector<std::vector<T>> parseTable(std::istream& input, char delimiter = ' ') {
    std::vector<std::vector<T>> result;
    std::string line;
    
    while (std::getline(input, line)) {
        if (!line.empty()) {
            result.push_back(parseRow<T>(line, delimiter));
        }
    }
    
    return result;
}

// Type aliases
template <typename T>
using ConstColItr = typename std::vector<T>::const_iterator;

template <typename T>
using ConstRowItr = typename std::vector<Row<T>>::const_iterator;

template <typename T>
class Row
{
public:
  // Refactored constructor using the parsing utility
  Row(const std::string& rowData) : data(parseRow<T>(rowData)) {}
  
  // Alternative constructor from parsed data
  Row(const std::vector<T>& rowData) : data(rowData) {}

  const T operator[](int c) const
  {
    return data[c]; 
  }

  size_t size() const
  {
    return data.size();
  }

  ConstColItr<T> begin() const { return data.begin(); }
  ConstColItr<T> end() const { return data.end(); }

private:
  std::vector<T> data;
};

template <typename T>
class Table
{
public:
  // Refactored constructor using the parsing utility
  Table(std::istream& input) {
    std::string line;
    while (std::getline(input, line)) {
      if (!line.empty()) {
        data.emplace_back(line);
      }
    }
  }
  
  // Alternative constructor from parsed data
  Table(const std::vector<std::vector<T>>& tableData) {
    for (const auto& rowData : tableData) {
      data.emplace_back(rowData);
    }
  }

  const Row<T>& operator[](int r) const
  {
    return data[r]; 
  }

  size_t size() const
  {
    return data.size();
  }

  ConstRowItr<T> begin() const
  {
    return data.begin();
  }

  ConstRowItr<T> end() const
  {
    return data.end();
  }

private:
  std::vector<Row<T>> data;
};

#endif
