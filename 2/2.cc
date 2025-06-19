#include <iostream>
#include <cstdlib>
#include <vector>

#include "flags/flags.h"
#include "table_read/table_read.h"

enum class Direction {
    UP,
    DOWN, 
    UNKNOWN
};

// Returns an iterator that skips the element at the given index
template<typename Iterator>
class SkipIterator {
private:
    Iterator current;
    Iterator end;
    size_t skipIndex;
    size_t currentIndex;

public:
    SkipIterator(Iterator begin, Iterator end, size_t skipIndex) 
        : current(begin), end(end), skipIndex(skipIndex), currentIndex(0) {
        // Advance to first non-skipped element
        if (currentIndex == skipIndex && current != end) {
            ++current;
            ++currentIndex;
        }
    }

    SkipIterator& operator++() {
        ++current;
        ++currentIndex;
        if (currentIndex == skipIndex && current != end) {
            ++current;
            ++currentIndex;
        }
        return *this;
    }

    SkipIterator operator++(int) {
        SkipIterator temp = *this;
        ++(*this);
        return temp;
    }

    auto operator*() const -> decltype(*current) {
        return *current;
    }

    bool operator!=(const SkipIterator& other) const {
        return current != other.current;
    }

    bool operator==(const SkipIterator& other) const {
        return current == other.current;
    }
};

// Helper function to create a skip iterator range
template<typename Iterator>
std::pair<SkipIterator<Iterator>, SkipIterator<Iterator>> 
makeSkipRange(Iterator begin, Iterator end, size_t skipIndex) {
    return {
        SkipIterator<Iterator>(begin, end, skipIndex),
        SkipIterator<Iterator>(end, end, skipIndex)
    };
}

template<typename Iterator>
bool checkRow(Iterator begin, Iterator end) {
    Direction direction = Direction::UNKNOWN;
    Iterator colItr = begin;
    int lastValue = *colItr;
    colItr++;
    while (true) {
        const int diff = *colItr - lastValue;
        if (direction == Direction::UNKNOWN) {
            if (diff == 1 || diff == 2 || diff == 3) {
                direction = Direction::UP; // Initial direction
            } else if (diff == -1 || diff == -2 || diff == -3) {
                direction = Direction::DOWN; // Initial direction
            } else {
                break; // Skip rows that are not safe
            }
        } else if (direction == Direction::UP) {
            if (diff <= 0 || diff > 3) {
                break; // Skip rows that are not safe
            }
        } else if (direction == Direction::DOWN) {
            if (diff >= 0 || diff < -3) {
                break; // Skip rows that are not safe
            }
        }
        lastValue = *colItr;
        if (++colItr == end) {
            // If we reach the end of the row, it is a safe row
            return true;
            break;
        }
    }
    return false; 
}

int process(Table table) {
    int numberOfSafeRows = 0;
    // Output the table contents
    for (const Row &row : table) {
        for (int i = 0; i < row.size(); i++) { 
            auto [begin, end] = makeSkipRange(row.begin(), row.end(), i);
            if (checkRow(begin, end)) {
                numberOfSafeRows++;
                break;  
            }
        }
    }

    std::cout << "Number of safe rows: " << numberOfSafeRows << std::endl;
    return 0;
}