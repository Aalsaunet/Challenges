#include <vector>

using namespace std;

class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
        int total = 0;
        vector<int> runningSum;
        for (auto num : nums) {
            runningSum.push_back(total += num);
        }
        return runningSum;
    }
};