#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        
        ListNode dummy = ListNode(INT_MIN, nullptr);
        ListNode* prev = &dummy;
        ListNode* start = prev;

        while (lists.size() > 0) {
            // Find next node to go into the merged list
            int minValue = INT_MAX, minIdx = -1;
            for (int i = 0; i < lists.size(); i++) {
                // Check all source lists for lower val or nullptr
                if (lists[i] == nullptr) {
                    // Remove source list when it's empty.
                    lists.erase(lists.begin() + i--);
                    if (lists.size() == 0)
                        //All source lists empty. Merge complete.
                        return start->next;           
                } else if (lists[i]->val < minValue) {
                    minValue = lists[i]->val;
                    minIdx = i;
                    if (minValue == prev->val)
                        // skip remaining lists as we cant do lower than ==
                        break; 
                } 
            }
            // Add identified node to the merge list and update prev
            prev->next = lists[minIdx];
            lists[minIdx] = lists[minIdx]->next;
            prev = prev->next;
        }
        return start->next;
    }
};