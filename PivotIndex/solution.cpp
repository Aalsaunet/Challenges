#include <vector>
#include <numeric>
#include <iostream>
 
using namespace std;

class Solution {
// Explanation 
// Example: [1,7,3,6,5,6]
// Step 0: leftSum = 0, rightSum = 28
// Step 1: leftSum = 0, rightSum = 27, i = 0
// IF
// Step 2: leftSum = 1, rightSum = 27, i = 0
// Step 3: leftSum = 1, rightSum = 20, i = 1
// IF
// Step 4: leftSum = 8, rightSum = 20, i = 1
// Step 5: leftSum = 8, rightSum = 17, i = 2
// IF
// Step 6: leftSum = 11, rightSum = 17, i = 2
// Step 7: leftSum = 11, rightSum = 11, i = 3
// IF --> Success!

public:
    int pivotIndex(vector<int>& nums) {
        
        int leftSum = 0; // sum left of index 0
        int rightSum = accumulate(nums.begin(), nums.end(), 0); // sum right of index 0

        for (int i = 0; i < nums.size(); i++) {
            rightSum -= nums[i]; // exclude index->value from right side
            if (leftSum == rightSum) { //compare
                cout << leftSum << " vs " << rightSum << endl;
                return i;
            }
                
            leftSum += nums[i]; // include index->value to left side
        }
        return -1;
    }
};