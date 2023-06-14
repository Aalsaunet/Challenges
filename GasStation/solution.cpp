#include <vector>

using namespace std;

class Solution {
public:

    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int totalGas = 0, totalCost = 0;
        int currentGas = 0, startIndex = 0;
        
        for(int i = 0; i < gas.size(); i++) {
            totalGas += gas[i];
            totalCost += cost[i];
            currentGas += gas[i] - cost[i];
            
            if(currentGas < 0) {
                startIndex = i + 1; //Out of gas, we'll try a later start point
                currentGas = 0; //Reset our fuel
            }
        }

        return totalGas < totalCost ? -1 : startIndex;
    }
};