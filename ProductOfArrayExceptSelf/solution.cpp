#include <vector>

using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int totalProduct = 1;
        int zeroCount = 0;

        vector<int> answer(nums.size());
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == 0) {
                zeroCount++;
            } else {
                totalProduct *= nums[i];
            }    
        }

        if (zeroCount >= 2) 
            return answer;
            
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == 0) {
                answer[i] = totalProduct;
            } else {
                answer[i] = zeroCount == 0 ? totalProduct/nums[i] : 0;
            }       
        }
            
        return answer;
    }
};
