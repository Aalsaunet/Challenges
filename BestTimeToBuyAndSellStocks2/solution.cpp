#include <vector>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int totalProfit = 0;
        bool hasShares = false;
        bool isLastday = false;

        for (int i = 0; i < prices.size(); i++) {
            
            isLastday = (i == prices.size() - 1);

            if (hasShares) {
                // Sell if last day or value is higher today than tomorrow
                if (isLastday || prices[i] > prices[i + 1]) {      
                    totalProfit += prices[i];
                    hasShares = false;
                }
            } else {        
                // Buy if not last day and value is lower today than tomorrow
                if (!isLastday && prices[i] < prices[i + 1]) {                
                    totalProfit -= prices[i];
                    hasShares = true;
                }
            }
        }
        return totalProfit;
    }
};