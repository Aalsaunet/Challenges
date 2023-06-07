#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    int fibDynamic(const int n, map<int, int64_t>* memo = new map<int, int64_t>()) {
        // This function using dynamic programming / memoization
        if (n <= 2) return 1;
        if (memo->count(n)) return (*memo)[n];
        (*memo)[n] = fibDynamic(n - 1, memo) + fibDynamic(n - 2, memo);
        return (*memo)[n];
    }

    int fibSimple(const long n) {
        if (n <= 2) return 1;
        return fibSimple(n - 1) + fibSimple(n - 2);
    }
};

int main() {
    // Find the nth Fibonacci number
    Solution s;
    cout << s.fibDynamic(5) << endl;
    cout << s.fibDynamic(6) << endl;
    cout << s.fibDynamic(7) << endl;
    cout << s.fibDynamic(8) << endl;
    cout << s.fibDynamic(20) << endl;
    cout << s.fibDynamic(40) << endl;
    return 0;
}