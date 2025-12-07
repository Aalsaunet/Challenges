#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

// Helper to check if a specific column is entirely spaces (separator)
bool isColumnEmpty(const std::vector<std::string>& grid, int colIndex) {
    for (const auto& row : grid) {
        if (colIndex < row.length() && row[colIndex] != ' ') {
            return false;
        }
    }
    return true;
}

// Function to process a specific block of columns (a single problem)
long long solveBlock(const std::vector<std::string>& grid, int startCol, int endCol) {
    std::vector<long long> numbers;
    char operation = '+'; // Default to addition if not found
    int rows = grid.size();

    // 1. Find the operator (It's in the last row)
    // We scan the bottom row within this block's column range
    for (int c = startCol; c <= endCol; c++) {
        if (grid.back().length() > c) {
            char ch = grid.back()[c];
            if (ch == '+' || ch == '*') {
                operation = ch;
                break;
            }
        }
    }

    // 2. Build Numbers Vertically
    // Iterate through each column in this block
    for (int c = startCol; c <= endCol; c++) {
        std::string numStr = "";
        
        // Scan from Top Row down to Second-to-Last Row (excluding operator row)
        for (int r = 0; r < rows - 1; r++) {
            if (c < grid[r].length() && std::isdigit(grid[r][c])) {
                numStr += grid[r][c];
            }
        }

        // If we found digits in this column, parse them
        if (!numStr.empty()) {
            numbers.push_back(std::stoll(numStr));
        }
    }

    // 3. Calculate Result
    if (numbers.empty()) return 0;

    long long result = (operation == '*') ? 1 : 0;
    
    if (operation == '+') {
        for (long long n : numbers) result += n;
    } else {
        for (long long n : numbers) result *= n;
    }

    return result;
}

int main() {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    std::vector<std::string> lines;
    std::string line;
    size_t maxWidth = 0;

    // 1. Read all lines
    while (std::getline(file, line)) {
        lines.push_back(line);
        if (line.length() > maxWidth) maxWidth = line.length();
    }

    // Edge case: empty file
    if (lines.empty()) {
        std::cout << 0 << std::endl;
        return 0;
    }

    // 2. Pad lines with spaces to ensure rectangular grid
    // This prevents out-of-bounds errors when accessing grid[r][c]
    for (auto& l : lines) {
        if (l.length() < maxWidth) {
            l.append(maxWidth - l.length(), ' ');
        }
    }

    long long grandTotal = 0;
    bool inBlock = false;
    int startCol = 0;

    // 3. Scan columns to identify blocks
    for (int c = 0; c < maxWidth; c++) {
        bool empty = isColumnEmpty(lines, c);

        if (!inBlock && !empty) {
            // Start of a new problem block
            inBlock = true;
            startCol = c;
        } 
        else if (inBlock && empty) {
            // End of the current problem block
            grandTotal += solveBlock(lines, startCol, c - 1);
            inBlock = false;
        }
    }

    // Handle the final block if the line doesn't end with spaces
    if (inBlock) {
        grandTotal += solveBlock(lines, startCol, maxWidth - 1);
    }

    std::cout << "Grand Total: " << grandTotal << std::endl;

    return 0;
}