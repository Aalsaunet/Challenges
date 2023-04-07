#include <set>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        
        unordered_map<char, char> mappings;
        set<char> spentChars;
        string result = "";
        
        for (int i = 0; i < s.size(); i++) {
            // if mapping x -> y doesn't exist, add it
            if (!mappings.count(s[i]) && !spentChars.count(t[i])) {
                mappings[s[i]] = t[i];
                spentChars.insert(t[i]);
            }
        }
                 
        for (int i = 0; i < s.size(); i++) {
            if (!spentChars.count(t[i]))
                return false; 
            result += mappings[s[i]];
        }       
 
        return t.compare(result) == 0;
    }
};