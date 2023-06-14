#include <vector>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        
        //sort(numbers.start(), numbers.end());
        int i = 0, j = numbers.size() - 1;

        while (i < j) {
            int sum = numbers[i] + numbers[j];
            if (sum < target) i++;
            else if (sum > target) j--;
            else return vector<int> {i + 1, j + 1};
        }
        return vector<int>();
    }
};