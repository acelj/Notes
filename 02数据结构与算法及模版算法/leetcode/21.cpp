class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        auto dummy = new ListNode(-1), tail = dummy;
        while(l1 && l2)
        {
            if(l1->val < l2->val)
            {
                dummy = dummy->next = l1;   // 需要加上中间的，申请空间
                l1 = l1->next;
            }
            else
            {
                dummy = dummy->next = l2;
                l2 = l2->next;
            }
        }
        if(l1) dummy->next = l1;
        if(l2) dummy->next = l2;
        return tail->next;
    }
};