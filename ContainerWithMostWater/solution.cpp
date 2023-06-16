#include <vector>

using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int lpos = 0, rpos = height.size() - 1;
        int lmax = 0, rmax = 0;
        int maxWater = 0;

        while (lpos < rpos) {
            lmax = max(lmax, height[lpos]);
            rmax = max(rmax, height[rpos]);

            if ((rpos - lpos) * min(lmax, rmax) > maxWater)
                maxWater = (rpos - lpos) * min(lmax, rmax);

            if (lmax < rmax)
                lpos++;
            else
                rpos--;
        }
        return maxWater;
    }
};
