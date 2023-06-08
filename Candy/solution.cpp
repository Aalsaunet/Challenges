#include <vector>

using namespace std;

class Solution {
public:

    int candy(std::vector<int>& ratings) {
        if (ratings.empty())
            return 0;

        int totalCandyRequired = 0; 
        std::vector<int> givenCandy(ratings.size(), 1);

        // Traverse from left to right
        for (int i = 1; i < ratings.size(); i++) {
            if (ratings[i] > ratings[i - 1])
                givenCandy[i] = givenCandy[i - 1] + 1;
        }

        // Traverse from right to left
        for (int i = ratings.size() - 2; i >= 0; i--) {
            if (ratings[i] > ratings[i + 1])
                givenCandy[i] = std::max(givenCandy[i], givenCandy[i + 1] + 1);
        }

        // Calculate the total candy required
        for (int i = 0; i < givenCandy.size(); i++)
            totalCandyRequired += givenCandy[i];

        return totalCandyRequired;
    }
};