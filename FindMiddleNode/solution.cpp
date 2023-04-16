struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        
        ListNode* middleNode = head;
        ListNode* currentNode = head;

        int stepCount = 0;
        while (currentNode != nullptr) {
            currentNode = currentNode->next; stepCount++;
            if (stepCount % 2 == 0)
                middleNode = middleNode->next;
        } 
        return middleNode;
    }
};