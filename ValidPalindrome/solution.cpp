#include <string>

using namespace std;

class Solution {
public:
    bool isPalindrome(string s) {
        string normalizedStr;
    
        for (char c : s) {
            if (isalnum(c))
                normalizedStr += tolower(c);
        }
        
        int i = 0, j = normalizedStr.size() - 1;
        while (i < j) {
            if (normalizedStr[i++] != normalizedStr[j--])
                return false;
        }

        return true;
    }
};