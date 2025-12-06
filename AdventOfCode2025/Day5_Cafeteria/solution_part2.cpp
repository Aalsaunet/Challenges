#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

struct Interval {
    long long start;
    long long end;
};

bool compareIntervals(const Interval& a, const Interval& b) {
    return a.start < b.start;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    std::string line;
    std::vector<Interval> intervals;

    while (std::getline(file, line)) {
        if (line.empty()) 
            break;
        size_t delimiter = line.find('-');
        long long start = std::stoll(line.substr(0, delimiter));
        long long end = std::stoll(line.substr(delimiter + 1));
        intervals.push_back({start, end});
    }

    std::sort(intervals.begin(), intervals.end(), compareIntervals);

    long long totalUniqueIDs = 0;
    long long currentStart = intervals[0].start;
    long long currentEnd = intervals[0].end;

    for (size_t i = 1; i < intervals.size(); ++i) {
        if (intervals[i].start <= currentEnd + 1) {
            currentEnd = std::max(currentEnd, intervals[i].end);
        } else {
            totalUniqueIDs += (currentEnd - currentStart + 1);            
            currentStart = intervals[i].start;
            currentEnd = intervals[i].end;
        }
    }

    totalUniqueIDs += (currentEnd - currentStart + 1);
    std::cout << totalUniqueIDs << std::endl;
    return 0;
}