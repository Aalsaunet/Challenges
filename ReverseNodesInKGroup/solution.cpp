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
    ListNode* reverseKGroup(ListNode* head, int k) {

        ListNode dummy = ListNode(0, head);
        ListNode* currentNode = head;
        ListNode* prevGroupTail = &dummy;    
        vector<ListNode*> currentGroup(k);

        while (currentNode != nullptr) {
            
            for (int i = 0; i < k; i++) {
                if (currentNode == nullptr) 
                    return dummy.next; //incomplete group
                currentGroup[i] = currentNode;
                currentNode = currentNode->next;
            }

            // [1,2,3] => 3->2->1
            for (int i = k-1; i > 0; i--) {
                currentGroup[i]->next = currentGroup[i-1];
            }

            prevGroupTail->next = currentGroup[k-1];
            prevGroupTail = currentGroup[0];
            currentGroup[0]->next = currentNode;
        }  
        
        return dummy.next;
    }
};