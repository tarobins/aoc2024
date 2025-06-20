#include <iostream>
#include <cstdlib>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>
#include <future>

#include "flags/flags_table.h"
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

// Function to check if a single row is safe (with skip logic)
bool isRowSafe(const Row& row) {
    for (int i = 0; i < row.size(); i++) { 
        auto [begin, end] = makeSkipRange(row.begin(), row.end(), i);
        if (checkRow(begin, end)) {
            return true;
        }
    }
    return false;
}

// Function to process a chunk of rows
int processRowChunk(const Table rows, size_t start, size_t end) {
    int safeCount = 0;
    for (size_t i = start; i < end && i < rows.size(); ++i) {
        if (isRowSafe(rows[i])) {
            safeCount++;
        }
    }
    return safeCount;
}

int process(Table table) {
    const unsigned int numThreads = std::thread::hardware_concurrency();
    const size_t numRows = table.size();
    
    // If we have fewer rows than threads, just use single thread
    if (numRows < numThreads || numThreads == 0) {
        int numberOfSafeRows = 0;
        for (const Row &row : table) {
            if (isRowSafe(row)) {
                numberOfSafeRows++;
            }
        }
        std::cout << "Number of safe rows: " << numberOfSafeRows << std::endl;
        return 0;
    }
    
    // Calculate chunk size for each thread
    const size_t chunkSize = numRows / numThreads;
    const size_t remainder = numRows % numThreads;
    
    // Create futures to store results from each thread
    std::vector<std::future<int>> futures;
    futures.reserve(numThreads);
    
    // Launch threads
    size_t currentStart = 0;
    for (unsigned int i = 0; i < numThreads; ++i) {
        size_t currentChunkSize = chunkSize + (i < remainder ? 1 : 0);
        size_t currentEnd = currentStart + currentChunkSize;
        
        // Launch async task
        futures.push_back(std::async(std::launch::async, processRowChunk, 
                                   table, currentStart, currentEnd));
        
        currentStart = currentEnd;
    }
    
    // Collect results from all threads
    int totalSafeRows = 0;
    for (auto& future : futures) {
        totalSafeRows += future.get();
    }

    std::cout << "Number of safe rows: " << totalSafeRows << std::endl;
    std::cout << "Processed using " << numThreads << " threads" << std::endl;
    return 0;
}