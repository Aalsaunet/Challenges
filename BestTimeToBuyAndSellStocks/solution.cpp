#include <vector>

using namespace std;

class Solution {
public:
    int maxProfitNested(vector<int>& prices) {
        
        int maxProfit = 0;
        for (int i = 0; i < prices.size() - 1; i++)
            for (int j = i + 1; j < prices.size(); j++)
                if (prices[j] - prices[i] > maxProfit)
                    maxProfit = prices[j] - prices[i];
        return maxProfit;
    }

    int maxProfitSingle(vector<int>& prices) {
        
        if (prices.size() < 2)
            return 0; // we need at least two entries to make a profit
        
        int start = prices[0], end = prices[1];
        int maxProfit = end - start;
        
        for (int i = 0; i < prices.size(); i++) {

            if (prices[i] < start)
                start = prices[i], end = prices[i];
            else if (prices[i] > end)
                end = prices[i];

            if (end - start > maxProfit)
                maxProfit = end - start;
        }

        return maxProfit;
    }
};
