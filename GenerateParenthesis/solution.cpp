#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    void recursive(vector<string>* results, int left, int right, string s, int n) {
        if (s.size() == n * 2) {
            results->push_back(s);
            return;
        }

        if (left < n)
            recursive(results, left + 1, right, s + "(", n);
        if (right < left)
            recursive(results, left, right + 1, s + ")", n);
    }

    vector<string> generateParenthesis(int n) {
        vector<string> results;
        recursive(&results, 0, 0, "", n);
        return results;
    }
};