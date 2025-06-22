#ifndef table_h
#define table_h

#include <istream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

template <typename T>
class Row;

template <typename T>
using ConstColItr = typename std::vector<T>::const_iterator;

template <typename T>
using ConstRowItr = typename std::vector<Row<T>>::const_iterator;

template <typename T>
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

  const T operator[](int c) const
  {
    return data[c]; 
  }

  int size() const
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
  Table(std::istream& input)
  {
    // Read data from the input stream
    std::string line;
    while (std::getline(input, line))
    {
      data.emplace_back(std::move(line)); // Assuming each line represents a Row
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
