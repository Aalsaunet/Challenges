struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        
        ListNode* previous = nullptr; 
        ListNode* currentNode = head;
        ListNode* nextUp = nullptr;
        
        while (currentNode != nullptr) {
    
            nextUp = currentNode->next;
            currentNode->next = previous;

            if (nextUp == nullptr)
                return currentNode;

            previous = currentNode;
            currentNode = nextUp;
        }

        return currentNode;
    }
};