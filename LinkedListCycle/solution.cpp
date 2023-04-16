#include <unordered_set>

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
    ListNode *detectCycle(ListNode *head) {
        
        unordered_set<ListNode*> entries; 
        ListNode* currentNode = head;

        while (currentNode != nullptr) {
            
            if (entries.count(currentNode))
                return currentNode;
            
            entries.insert(currentNode);
            currentNode = currentNode->next;
        } 
        return nullptr;
    }
};