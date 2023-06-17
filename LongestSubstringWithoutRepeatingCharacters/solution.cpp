#include <string>
#include <map>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        map<char, int> charToIdx;
        int longestStreak = 0;

        int i = 0;
        while (i < s.size()) {
            if (charToIdx.count(s[i]) == 0) {
                charToIdx[s[i]] = i;
                i++;
            } else {
                longestStreak = max(int(charToIdx.size()), longestStreak);
                i = charToIdx[s[i]] + 1;
                charToIdx.clear();
            }
        }
        return max(int(charToIdx.size()), longestStreak);
    }
};