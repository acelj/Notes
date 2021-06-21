**
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
    struct Cmp{
        bool operator() (ListNode* a, ListNode* b)
        {
            return a->val > b->val;   // 默认的大根堆，
        }
    };

    ListNode* mergeKLists(vector<ListNode*>& lists) {

        // if(lists.empty()) return nullptr;
        // if(lists.size() == 1 && !lists[0]) return nullptr;
        // 将多个数组转化成两个两个，然后二路合并

        // 利用有限队列作为堆，将多个数据转化成两个两个

        priority_queue<ListNode*, vector<ListNode*>, Cmp> heap;

        auto dummy = new ListNode(-1), tail = dummy;
        for(auto l : lists) if (l)  heap.push(l);

        while(heap.size())
        {
            auto t = heap.top();
            heap.pop();

            tail = tail->next = t; 
            if(t->next) heap.push(t->next);
        }
        return dummy->next;
    }
};