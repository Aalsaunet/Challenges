#include <vector>
#include <queue>
#include <map>
#include <set>
#include <iostream>

using namespace std;

class Solution
{
public:
    bool canJumpGraph(vector<int> &nums) {
        
        // Construct an adjecancy list (nodes and edges in a graph)
        map<int, vector<int>> nodes;
        for (int i = 0; i < nums.size(); i++) {
            vector<int> edges;
            for (int j = i + 1; j <= i + nums[i]; j++)
                edges.push_back(j);
            nodes[i] = edges;
        }

        // Do a BFS search for whether the last index can be reached
        int origin = 0;
        int destination = nums.size() - 1;

        queue<int> queue;
        queue.push(origin);
        set<int> visited;

        while (queue.size() > 0) {
            int current = queue.front();
            queue.pop();

            if (visited.count(current))
                continue;
            visited.insert(current);

            if (current == destination)
                return true;

            for (int i = 0; i < nodes[current].size(); i++) {
                queue.push(nodes[current][i]);
            }
        }

        return false;
    }

    // Alternative implementation (more efficient than the graph search)

    bool canJump(vector<int> &nums) {
        int maxReachable = 0;

        for (int i = 0; i < nums.size(); i++) {
            if (i > maxReachable) {
                // If the current index is not reachable from the previous indices,
                // it means we cannot reach the end.
                return false;
            }

            // Update the maximum reachable index
            maxReachable = std::max(maxReachable, i + nums[i]);

            if (maxReachable >= nums.size() - 1) {
                // If we can reach the end, no need to continue checking further.
                return true;
            }
        }

        return false;
    }
};

int main() {
    Solution st;
    vector<int> nums1 = {2, 3, 1, 1, 4};
    std::cout << st.canJump(nums1) << std::endl;
}