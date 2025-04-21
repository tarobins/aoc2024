#include <istream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

class Column
{
public:
  Column(std::string columnData) : columnData(std::move(columnData)) {}
  int operator[](int c) const
  {
    std::vector<std::string> result;
    std::stringstream ss(columnData);
    std::string token;

    while (std::getline(ss, token, ' '))
    {
      result.push_back(token);
    }

    return std::stoi(result[c]);
  }

private:
  std::string columnData;
};

class Table
{
public:
  // Table() = default;
  Table(std::istream &input)
  {
    // Read data from the input stream
    std::string line;
    while (std::getline(input, line))
    {
      std::cout << "Read line: " << line << std::endl;
      data.push_back(line);
    }
  }

  Column operator[](int r) const
  {
    return Column(data[r]); // Dummy implementation for the sake of example
  }

private:
  std::vector<std::string> data;
};
