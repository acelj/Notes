/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        auto cur = new ListNode(-1);
        auto ret = cur;

        int sum = 0;
        for(;;)
        {
            if(l1)
            {
                sum += l1->val;
                l1 = l1->next;
            }
            if(l2)
            {
                sum += l2->val;
                l2 = l2->next;
            }
            cur->val = sum % 10;
            sum /= 10;

            if(l1 || l2 || sum)
            {
                cur->next = new ListNode(-1);
                cur = cur->next;
            }
            else break;
        }
        return ret;
    }
};