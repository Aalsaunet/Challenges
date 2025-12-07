#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>

long summerize(const std::vector<int>& nums) {
    long sum = 0;
    for (int i = 0; i < nums.size(); i++)
        sum += nums[i];
    return sum;
}

long multiply(const std::vector<int>& nums) {
    long product = 1;
    for (int i = 0; i < nums.size(); i++)
        product *= nums[i];
    return product;
}

int main() {
    std::ifstream file("input.txt");
    std::string line;
    std::vector<std::vector<int>> nums; 
    int rowCount = 0;
    long sum = 0;
    
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string item;
        std::vector<int> parts;
        while (std::getline(ss, item, ' ')) {
            if (item == "")
                continue;
            else if (item == "+")
                parts.emplace_back(-1);
            else if (item == "*")
                parts.emplace_back(-2);
            else
                parts.emplace_back(std::stoi(item));
        }
        rowCount++;
        nums.emplace_back(parts);
    }
    
    for (int i = 0; i < nums[0].size(); i++) {
        auto operation = nums[rowCount - 1][i] == -1 ? summerize : multiply;
        std::vector<int> column;
        for (int j = 0; j < rowCount - 1; j++)
            column.emplace_back(nums[j][i]);
        sum += operation(column);
    }
    std::cout << sum << std::endl;
}