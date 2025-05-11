#ifndef tableread_h
#define tableread_h

#include <istream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

class Row;

using ColItr = std::vector<int>::iterator;
using RowItr = std::vector<Row>::iterator;

class Row
{
public:
  Row(const std::string& rowData) {
    // Parse the Row data into integers
    std::stringstream ss(rowData);
    std::string token;
    while (std::getline(ss, token, ' '))
    {
      if (!token.empty()) {
        data.push_back(std::stoi(token));
      }
    }
  }

  const int operator[](int c) const
  {
    return data[c]; 
  }

  int size() const
  {
    return data.size();
  }

  const ColItr begin()
  {
    return data.begin();
  }

  const ColItr end()
  {
    return data.end();
  }

private:
  std::vector<int> data;
};

class Table
{
public:
  Table(std::istream& input)
  {
    // Read data from the input stream
    std::string line;
    while (std::getline(input, line))
    {
      data.emplace_back(std::move(line)); // Assuming each line represents a Row
    }
  }

  Row& operator[](int r) 
  {
    return data[r]; 
  }

  int size() const
  {
    return data.size();
  }

  const RowItr begin()
  {
    return data.begin();
  }

  const RowItr end() 
  {
    return data.end();
  }

private:
  std::vector<Row> data;
};


#endif