#include <vector>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <iostream>

using namespace std;

class Solution
{
public:
    map<int, vector<int>> makeAdjecencyMap(vector<int> &nums) {   
        map<int, vector<int>> nodes;
        for (int i = 0; i < nums.size(); i++) {
            vector<int> edges;
            for (int j = i + 1; j <= i + nums[i]; j++)
                edges.push_back(j);
            nodes[i] = edges;
        }
        return nodes;
    }

    int findShortestPath(vector<int> &nums) {     
        // Construct an adjecency map of nodes and edges
        map<int, vector<int>> nodes = makeAdjecencyMap(nums);
        stack<tuple<int, int>> stack;
        
        // Do a DFS (depth first search) to find the shortest path from origin to destination
        int origin = 0; // first index of nums
        int destination = nums.size() - 1; // last index of nums
        int minRequiredSteps = nums.size() - 1; // keeps track of the current shortest path found
        stack.push(make_tuple(origin, 0)); 

        while (stack.size() > 0) {
            auto [current, steps] = stack.top();
            stack.pop();
            if (steps >= minRequiredSteps) continue;
            if (current == destination) minRequiredSteps = steps;

            for (int i = 0; i < nodes[current].size(); i++) {
                stack.push(make_tuple(nodes[current][i], steps + 1));
            }
        }

        return minRequiredSteps;
    }

    int findShortestPath2(const std::vector<int>& nums) {
        int origin = 0; // First index of nums
        int destination = nums.size() - 1; // Last index of nums
        int minRequiredSteps = nums.size() - 1; // Keeps track of the current shortest path found

        std::stack<std::pair<int, int>> stack;
        stack.push({ origin, 0 });

        while (!stack.empty()) {
            auto [current, steps] = stack.top();
            stack.pop();

            if (steps >= minRequiredSteps)
                continue;

            if (current == destination)
                minRequiredSteps = steps;

            for (int i = 1; i <= nums[current]; i++) {
                int nextIndex = current + i;
                if (nextIndex >= nums.size())
                    break;
                stack.push({ nextIndex, steps + 1 });
            }
        }

        return minRequiredSteps;
    }
};

int main() {
    Solution st;
    vector<int> nums1 = {2,9,6,5,7,0,7,2,7,9,3,2,2,5,7,8,1,6,6,6,3,5,2,2,6,3};
    vector<int> nums2 = {8,2,4,4,4,9,5,2,5,8,8,0,8,6,9,1,1,6,3,5,1,2,6,6,0,4,8,6,0,3,2,8,7,6,5,1,7,0,3,4,8,3,5,9,0,4,0,1,0,5,9,2,0,7,0,2,1,0,8,2,5,1,2,3,9,7,4,7,0,0,1,8,5,6,7,5,1,9,9,3,5,0,7,5};
    std::cout << "Minimum number of steps required is " << st.findShortestPath2(nums2) << std::endl;
}

 // Alternative implementation that's more efficient than the graph search but error prone.
    // int jump(vector<int> &nums) {
    //     int maxReachable = 0;
    //     int stepCount = 0;

    //     for (int i = 0; i < nums.size() && maxReachable < nums.size() - 1; i++) {
    //         if ((i + nums[i]) > maxReachable) {
    //             maxReachable = (i + nums[i]);
    //             i = maxReachable - 1;
    //             stepCount++;
    //         }
    //     }
    //     return stepCount;
    // }