#include <string>
#include <fstream>
#include <vector>
#include <iostream>

int main() {
    std::ifstream file("input.txt");
    std::string line;
    int freshCount = 0;
    bool readingRanges = true;
    std::vector<std::pair<long,long>> ranges; 

    while (std::getline(file, line)) {
        if (line.size() == 0) {
            readingRanges = false;
        } else if (readingRanges) {
            size_t delimiter = line.find('-');
            long start = std::stol(line.substr(0, delimiter));
            long end = std::stol(line.substr(delimiter + 1));
            ranges.emplace_back(start, end);
        } else {
            long id = std::stol(line);
            for (auto range : ranges) {
                if (id >= range.first && id <= range.second) {
                    freshCount++;
                    break;
                }
            }
        }
    }

    std::cout << freshCount << std::endl;
}