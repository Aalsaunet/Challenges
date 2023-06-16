#include <vector>

using namespace std;

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        
        int sum = 0; int minLength = INT_MAX;
        int i = 0; int j = 0;

        while (j < nums.size()) {
            sum += nums[j];

            if (sum < target) {
                j++;
            } else {
                while (sum >= target) {
                    minLength = min(minLength, (j - i) + 1);
                    sum -= nums[i];
                    i++;
                }
                j++;
            }
        }

        return (minLength == INT_MAX) ? 0 : minLength;
    }
};
