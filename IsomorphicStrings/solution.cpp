#include <set>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        
        unordered_map<char, char> mappings;
        set<char> 
        string result = "";
        
        for (int i = 0; i < s.size(); i++)
            // if mapping x -> y doesn't exist, add it
            if (!mappings.count(s[i])) 
                mappings[s[i]] = t[i]; 

        for (int i = 0; i < s.size(); i++) 
            result += mappings[s[i]];
 
        return t.compare(result) == 0;
    }
};