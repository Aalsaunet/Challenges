#include <vector>

using namespace std;

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int majorityThreshold = nums.size() / 2 + 1;
        int currentStreak = 1;

        sort(nums.begin(), nums.end());

        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == nums[i - 1]) {
                currentStreak++;
                if (currentStreak >= majorityThreshold)
                    return nums[i];
            } else {
                currentStreak = 1;
            }
        }
        return currentStreak;
    }
};