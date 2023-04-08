//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
// Solution using lambdas
class Solution {
public:
    void compareAndUpdateNodes(ListNode** list1, ListNode** list2, ListNode** prev, 
        void (*assignFunc)(ListNode**, ListNode**)) {
        
        if (*list1 == nullptr && *list2 == nullptr) {
            return;
        } else if (*list1 == nullptr) {
            assignFunc(prev, list2);
            *list2 = (*list2)->next;
        } else if (*list2 == nullptr) {
            assignFunc(prev, list1);
            *list1 = (*list1)->next; 
        } else if ((*list1)->val <= (*list2)->val) {
            assignFunc(prev, list1);
            *list1 = (*list1)->next;
        } else {
            assignFunc(prev, list2);
            *list2 = (*list2)->next;
        }
    }

    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* start = nullptr;
        compareAndUpdateNodes(&list1, &list2, &start, 
            [](ListNode** d, ListNode** s){*d = *s;});
        if (start == nullptr)
            return start;
        ListNode* previous = start;

        while (list1 != nullptr || list2 != nullptr) {
            compareAndUpdateNodes(&list1, &list2, &previous, 
                [](ListNode** d, ListNode** s){(*d)->next = *s;});
            previous = previous->next;
        }
        return start;
    }
};


// Verbose solution
// class Solution {
// public:
//     ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        
//         ListNode* start = nullptr;
//         if (list1 == nullptr && list2 == nullptr) {
//             return nullptr;
//         } else if (list1 == nullptr) {
//             start = list2;
//             list2 = list2->next;
//         } else if (list2 == nullptr) {
//             start = list1;
//             list1 = list1->next; 
//         } else if (list1->val <= list2->val) {
//             start = list1;
//             list1 = list1->next;
//         } else {
//             start = list2;
//             list2 = list2->next;
//         }
        
//         ListNode* previous = start;

//         while (list1 != nullptr || list2 != nullptr) {

//             if (list1 == nullptr) {
//                 previous->next = list2;
//                 list2 = list2->next;
//             } else if (list2 == nullptr) {
//                 previous->next = list1;
//                 list1 = list1->next; 
//             } else if (list1->val <= list2->val) {
//                 previous->next = list1;
//                 list1 = list1->next;
//             } else {
//                 previous->next = list2;
//                 list2 = list2->next;
//             }

//             previous = previous->next;
//         }
//         return start;
//     }
// };