#ifndef tableread_h
#define tableread_h

#include <istream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

class Row;

using ConstColItr = std::vector<int>::const_iterator;

using ConstRowItr = std::vector<Row>::const_iterator;

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

  ConstColItr begin() const { return data.begin(); }
  ConstColItr end() const { return data.end(); }


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

  const Row& operator[](int r) const
  {
    return data[r]; 
  }

  int size() const
  {
    return data.size();
  }

  ConstRowItr begin() const
  {
    return data.begin();
  }

  ConstRowItr end() const
  {
    return data.end();
  }

private:
  std::vector<Row> data;
};


#endif