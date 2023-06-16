#include <vector>
#include <set>

using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        set<vector<int>> resultSet;
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int i = 0, j = 1, k = n - 1;

        while (i < j && j < k) {
            int sum = nums[i] + nums[j] + nums[k];
            if (sum == 0) {
                vector<int> vc = {nums[i], nums[j], nums[k]};
                resultSet.insert(vc);
            }

            if (sum <= 0 && j < k - 1) {
                j++;
            } else if (sum <= 0) {
                i++;
                j = i + 1;
                k = n - 1;
            } else {
                k--;
                j = (j == k) ? i + 1 : j;
            }
        }

        vector<vector<int>> results(resultSet.size());
        copy(resultSet.begin(), resultSet.end(), results.begin());
        return results;
    }
};