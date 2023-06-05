#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        sort(nums.begin(), nums.end());

        vector<int>::iterator startIt = find(nums.begin(), nums.end(), val);
        int k = nums.size();

        if (startIt != nums.end()) {
            vector<int>::iterator endIt = next(startIt);
            k--;
            while (endIt != nums.end() && *endIt == val) {
                k--;
                endIt = next(endIt);
            }
                
            nums.erase(startIt, endIt);
        }

        return k;
    }
};