#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int uniqueOrDoublesCount = 1;
        int lead = 1;
        int tail = 0;
        
        while (lead < nums.size() && tail < nums.size()) {
            if (nums[lead] != nums[tail]) {
                uniqueOrDoublesCount++;
                tail = lead;
                lead++;
            } else if (nums[lead] == nums[tail] && lead - tail >= 2) {
                // more than 2 entries of the same number
                auto it = nums.begin() + lead;
                nums.erase(it);
                cout << nums.size() << endl;          
            } else {
                lead++;
                uniqueOrDoublesCount++;
            }
        }
        return uniqueOrDoublesCount;
    }
};

int main() {
    vector<int> ints = {1, 1, 1, 2, 2, 3};
    Solution s;
    s.removeDuplicates(ints);
    for (auto const &i: ints) {
        std::cout << i << " ";
    }
    return 0;
}

// [1,1,1,2,2,3]