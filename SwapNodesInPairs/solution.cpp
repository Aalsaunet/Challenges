struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (head == nullptr) 
            return nullptr;

        ListNode dummy = ListNode(0, head);
        ListNode* prev = &dummy;
        ListNode* node1 = head;
        ListNode* node2 = head->next;
        
        while (node1 != nullptr) {
            // Return if there's no pair to swap
            if (node2 == nullptr) return dummy.next;

            // Swap from prev->n1->n2 to prev->n2->n1
            prev->next = node2;
            node1->next = node2->next;
            node2->next = node1;

            // Return if we're at the end of the list
            if (node1->next == nullptr) return dummy.next;
            
            // Update pointers prev = n1, n1 = n3 and n2 = n4
            prev = node1;
            node1 = node1->next;
            node2 = node1->next;
        }
        
        return dummy.next;
    }
};