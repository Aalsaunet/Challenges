#include <vector>

using namespace std;

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        k = k % nums.size();
        vector<int> rotated = vector<int>(nums.end() - k, nums.end());
        rotated.insert(rotated.end(), nums.begin(), nums.end() - k);
        nums = rotated;
    }
};