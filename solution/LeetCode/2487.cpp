#include <map>

namespace SOLUTION
{
    namespace LC
    {
        using namespace std;

        class _2487
        {
        public:
            struct ListNode
            {
                int val;
                ListNode *next;
                ListNode() : val(0), next(nullptr) {}
                ListNode(int x) : val(x), next(nullptr) {}
                ListNode(int x, ListNode *next) : val(x), next(next) {}
            };

            ListNode *removeNodes(ListNode *head)
            {
                if (head == nullptr)
                {
                    return nullptr;
                }
                head->next = removeNodes(head->next);
                if (head->next != nullptr && head->val < head->next->val)
                {
                    return head->next;
                }
                else
                {
                    return head;
                }
            }

            ListNode* buildFromArray(int a[],int n,int index){
                if(index>=n){
                    return nullptr;
                }
                ListNode *p=(ListNode *)malloc(sizeof(ListNode));
                p->next=buildFromArray(a,n,index+1);
                p->val=a[index];
                return p;
            }

            void test(){
                int array[]={5,2,13,3,5,8};
                ListNode *head=buildFromArray(array,6,0);
                removeNodes(head);
            }
        };
    }
}