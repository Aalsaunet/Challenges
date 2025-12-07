#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

bool isColumnEmpty(const std::vector<std::string>& grid, int colIndex) {
    for (const auto& row : grid) {
        if (colIndex < row.length() && row[colIndex] != ' ') {
            return false;
        }
    }
    return true;
}

long long solveBlock(const std::vector<std::string>& grid, int startCol, int endCol) {
    std::vector<long long> numbers;
    char operation = '+';
    int rows = grid.size();
    for (int c = startCol; c <= endCol; c++) {
        if (grid.back().length() > c) {
            char ch = grid.back()[c];
            if (ch == '+' || ch == '*') {
                operation = ch;
                break;
            }
        }
    }

    for (int c = startCol; c <= endCol; c++) {
        std::string numStr = "";
        
        for (int r = 0; r < rows - 1; r++) {
            if (c < grid[r].length() && std::isdigit(grid[r][c])) {
                numStr += grid[r][c];
            }
        }

        if (!numStr.empty()) {
            numbers.push_back(std::stoll(numStr));
        }
    }

    if (numbers.empty()) 
        return 0;

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

    while (std::getline(file, line)) {
        lines.push_back(line);
        if (line.length() > maxWidth) maxWidth = line.length();
    }

    if (lines.empty()) {
        std::cout << 0 << std::endl;
        return 0;
    }

    for (auto& l : lines) {
        if (l.length() < maxWidth) {
            l.append(maxWidth - l.length(), ' ');
        }
    }

    long long grandTotal = 0;
    bool inBlock = false;
    int startCol = 0;

    for (int c = 0; c < maxWidth; c++) {
        bool empty = isColumnEmpty(lines, c);

        if (!inBlock && !empty) {
            inBlock = true;
            startCol = c;
        } 
        else if (inBlock && empty) {
            grandTotal += solveBlock(lines, startCol, c - 1);
            inBlock = false;
        }
    }

    if (inBlock) {
        grandTotal += solveBlock(lines, startCol, maxWidth - 1);
    }

    std::cout << grandTotal << std::endl;

    return 0;
}