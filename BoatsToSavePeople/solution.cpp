#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        // Assumption: people[i] always <= limit
        
        // 1. sort people into buckets by their weight
        // Use dictionary with K = weight, V = count
        unordered_map<int, int> peopleByWeight;
        int remainingPeople = people.size();
        int requiredBoats = 0;

        for (auto p : people) {
            if (peopleByWeight.count(p)) {
                // Key exists 
                peopleByWeight[p]++;
            } else {
                peopleByWeight[p] = 1; // alternatively peopleByWeight.insert(std::make_pair(p, 1));
            }
        }

        // 2. Find combinations X == limit, then X == (limit - 1) etc
        while (remainingPeople > 0) { 
            int boatWeight = 0;
            int peopleInBoat = 0;
            requiredBoats++;
            for (int i = limit; i > 0; i--) {
                if (peopleByWeight.count(i) && peopleByWeight[i] > 0) {
                    // Key exists 
                    if (boatWeight + i <= limit) {
                        boatWeight += i;
                        peopleInBoat++;
                        peopleByWeight[i++]--;
                        remainingPeople--;             
                    }
                 
                    if (boatWeight == limit || peopleInBoat == 2) {
                       break; 
                    }
                } 
            }
        }

        return requiredBoats;
    }

    int numRescueBoatsOptimized(vector<int>& people, int limit) {
       
        sort(people.begin(), people.end());

        int i = 0, j = people.size() - 1, boatsRequired = 0;        
        while (i <= j) {   
            if (people[i] + people[j] <= limit) {
                i++;
                j--;
            }
            else
                j--;        
            boatsRequired++; 
        }
        return boatsRequired;  
    }
};

int main() {
    Solution solution;
    std::vector<int> people;
    people.push_back(3);
    people.push_back(2);
    people.push_back(2);
    people.push_back(1);
    int limit = 3;
    
    int result = solution.numRescueBoatsOptimized(people, limit);
    std::cout << "Number of required boats: " << result << endl;

    return 0;
}