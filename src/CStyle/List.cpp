#include "../../include/CStyle/Util.h"
#include "../../include/CStyle/List.h"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <iostream>

namespace Algorithm {

    namespace SL {
        void InitSeqList(SeqList &L,int InitSize,int t_size,void (* CopyFunc)(char *,char *,size_t),void (*init)(void *)){
            L.length=0; // must done
            L.MaxSize=InitSize; 
            L.t_size=t_size;
            L.data=malloc(InitSize*L.t_size);
            L.CopyFunc=CopyFunc;
            if (init!=0) {
                init(&L); // 自己写初始化列表的接口
            }
        }

        char *getElement(SeqList &L, int i){
            return (char *)L.data+i*L.t_size;
        }



        void IncreaseSeqListSize(SeqList &L, int len){
            void *p=L.data; // 先获得原始数据
            L.data=malloc((L.MaxSize+len)*L.t_size); //重新分配数组长度
            for (int i=0;i<L.length;i++){
                Algorithm::fill((char *)p+i*L.t_size, getElement(L, i), L.t_size,L.CopyFunc);
            }
            L.MaxSize=L.MaxSize+len;
            free(p);
        }

        bool SeqListInsert(SeqList &L, int i, void *e){
            if (i<1 || i>L.length+1) {
                printf("请输入正确的位序\n");
                return false;
            }
            if (L.length>=L.MaxSize) {
                printf("列表空间已满!\n");
                return false;
            }

            for (int j=L.length;j>=i;j--){
            Algorithm::fill(getElement(L,j-1),getElement(L, j),L.t_size,L.CopyFunc);
            }
            Algorithm::fill((char *)e, getElement(L, i-1), L.t_size,L.CopyFunc);
            L.length++;
            return true;
        }

        bool SeqListDelete(SeqList &L, int i,void *e){
            if (i<1 || i>L.length+1) {
                printf("请输入正确的位序\n");
                return false;
            }
            if (isEmpty(L)) {
                printf("列表空间已空!\n");
                return false;
            }
            if (e!=0) {
                Algorithm::fill(getElement(L, i-1), (char *)e, L.t_size,L.CopyFunc);
            }
            for (int j=i-1;j<L.length-1;j++){
                Algorithm::fill(getElement(L, j+1), getElement(L, j), L.t_size,L.CopyFunc);
            }
            L.length--;

            return true;
        }

        bool isEmpty(SeqList &L){
            return L.length==0;
        }

        bool clear(SeqList &L){
            if (isEmpty(L)) {
                printf("列表空间已空\n");
                return false;
            }
            L.length=0;
            return true;
        }

    }

    namespace LL {
        int length(LinkList &L){
            //求出链表的长度
            int l=0;
            LNode *p=L->next;
            while (p!=nullptr) {
                l++;
                p=p->next;
            }
            return l;
        }

        //判断是否为空
        bool isEmpty(LinkList &L){
            if (L==nullptr) {
                return false;
            }

            return L->next==nullptr;
        }

        //清空链表
        bool clear(LinkList &L){
            if (L==nullptr || isEmpty(L)) {
                return false;
            }
            
            LNode *q,*p=L->next;
            L->next=nullptr;//清空
            while (p!=nullptr) {
                q=p;
                p=p->next;
                free(q);
            }//释放内存
            return true;
        }

        LNode *getElement(LinkList &L,int i){
            //i是位序，第一个就是头结点的下一个节点
            if (i<0) {
                return nullptr;
            }//若i=0则返回头结点

            LNode *p=L;
            while (p!=nullptr && i>0) {
                i--;
                p=p->next;
            }//i>0,即可以循环i次，代表位序，例如i=2,则返回L->next->next，返回第二个，若没有，即p先到了nullptr,则返回空指针

            return p;
        }

        LNode *LocateElement(LinkList &L, void *e, int (*compar)(const void *, const void *)){
            if (L==nullptr) {
                return nullptr;
            }

            LNode *p=L->next;
            while (p!=nullptr && compar(e,p->type)!=0) {
                p=p->next;
            }//如果p不是空指针并且p的值不等于要寻找的值则继续寻找，若p先到了nullptr则返回空指针

            return p;
        }

        bool InitLinkList(LinkList &L, int t_size,void (* CopyFunc)(char *,char *,size_t)){
            L=(LNode *)malloc(sizeof(LNode));
            if (L==nullptr) {
                return false;
            }
            L->next=nullptr;//这里初始化空指针
            // L->next=L; //循环单链表
            L->t_size=t_size;
            L->CopyFunc=CopyFunc; //初始化赋值函数
            //头链表不用初始化type,因为不存储数据
            return true;
        }

        bool InsertNextNode(void *p_, void *s_){
            //后序插入，即若要插入到第i个节点则要找到第i-1个节点
            LNode *p=(LNode *)p_;
            LNode *s=(LNode *)s_;
            if (p==nullptr) {
                return false;
            }

            //将s插入到p的后面
            s->next=p->next;
            p->next=s;
            return true;
        }

        bool InsertPriorNode(void *p_, void *s_){
            //前置插入，应该要找到第i个节点然后在'前面插入'
            LNode *p=(LNode *)p_;
            LNode *s=(LNode *)s_;

            if (p==nullptr) {
                return false;
            }
            //将s插入在p后面，然后交换p和s的data，就相当于s插在p的前面。哈哈哈哈哈哈
            s->next=p->next;
            p->next=s;
            void *tmp=s->type;
            int tmp_s=s->t_size;
            s->type=p->type;
            s->t_size=p->t_size;
            p->type=tmp;
            p->t_size=tmp_s;
            return true;
        }

        bool LinkListInsert(LinkList &L, int i, void *e, int head, bool (* insert)(void *,void *),int t_size){
            //在第i个位置插入，则需要找到第i-1个指针然后在后面插入，i是位序，头结点是0
            LNode *p=L;
            // while (p!=nullptr && i>head) {
            //     p=p->next;
            //     i--;//i减i-1次就是第i-1个指针,例如i=1,则此时p就是L，若i=5,则i减到1(i=1时退出循环),则p===L->1->2->3->4
            // }
            //
            p=getElement(L, i-head); //默认head=1，即后序插入，找到第i-1个节点，若head=0则后置插入即找到第i个节点,这条代码即是上面那段代码

            if (p==nullptr) {
                return false;
            }

            //为了实现泛型，每个节点可以存储不同类型的数据
            int size=p->t_size;
            if (t_size!=0) {
                size=t_size;
            }

            //初始化新节点，分配空间，并且存储数据
            LNode *s=(LNode *)malloc(sizeof(LNode));
            if (s==nullptr) {
                return false;
            }
            s->next=nullptr;
            s->t_size=size;
            // s->type=e; //你可以这么写，但是一旦修改链表的数据，会改变main函数的数据，最好别这样
            s->type=malloc(t_size);
            s->CopyFunc=L->CopyFunc;//默认赋值函数一致
            Algorithm::fill((char *)e,  (char *)(s->type),size,s->CopyFunc);//也可以直接赋值，但是记住初始化s->type

            return insert(p,s);
        }

        bool LinkListDelete(LinkList &L, int i,void *e){
            //删除指定位序的节点，位序从1开始
            if (i<1) {
                return false;
            }

            LNode *p=L;
            p=getElement(L, i-1);//获得前驱节点，即第i-1个节点

            if (p==nullptr || p->next==nullptr) {
                return false;
            } //找不到所要删除的位置，1.i>p;2.i==p,但是p已经是最后一个节点

            LNode *q=p->next;//要删除的节点,因为找到的是前驱节点

            //如果传入e，则将删除的值填充到e,e默认为0，即空指针
            if (e!=0) {
                Algorithm::fill((char *)(q->type), (char *)e, q->t_size,q->CopyFunc);
            }

            p->next=q->next;//将后面的节点往前移动
            free(q);//释放要删除的节点的空间
            return true;
        }

        bool Head_append(LinkList &L, void *e,int t_size){
            //从表头插入
            // LinkListInsert(L, 1, e,1,InsertNextNode,t_size); //相当于这条代码
            LNode *s=(LNode *)malloc(sizeof(LNode));
            if (s==nullptr) {
                return false;
            }
            if (t_size==0) {
                s->t_size=L->t_size;
            }else {
                s->t_size=t_size;
            }
            //分配s的值空间
            s->type=malloc(s->t_size);
            s->CopyFunc=L->CopyFunc;
            Algorithm::fill((char *)e, (char *)(s->type), s->t_size,s->CopyFunc);
            //插入
            s->next=L->next;
            L->next=s;
            return true;
        }

        bool Tail_append(LinkList &L, void *e,int t_size){
            //在表尾插入
            return LinkListInsert(L, length(L), e,1,InsertNextNode,t_size);
        }

    }

    namespace DLL {
        bool InitDLinkList(DLinkList &L, int t_size){
            //初始化双链表
            L=(DLinkList)malloc(sizeof(DLNode));
            if (L==nullptr) {
                return false;
            }
            L->next=nullptr;
            L->pre=nullptr;
            //如果是循环双链表
            //L->next=L;
            //L->pre=L;
            L->t_size=t_size;
            L->CopyFunc=copy;
            return true;
        }

        DLNode *getElementByNext(DLinkList &L, int i){
            //i是位序，第一个就是头结点的下一个节点
            if (i<0) {
                return nullptr;
            }//若i=0则返回头结点

            DLNode *p=L;
            while (p!=nullptr && i>0) {
                i--;
                p=p->next;
            }//i>0,即可以循环i次，代表位序，例如i=2,则返回L->next->next，返回第二个，若没有，即p先到了nullptr,则返回空指针

            return p;
        }

        DLNode *getElementByPre(DLinkList &L, int i){
            //向前按序查找
            //i是位序，第一个就是头结点的下一个节点
            if (i<0) {
                return nullptr;
            }//若i=0则返回头结点

            DLNode *p=L;
            while (p!=nullptr && i>0) {
                i--;
                p=p->pre; //向前遍历即可
            }//L可以是表头但必须是循环双链表，否则应当传入任意一个节点，i>0,即可以循环i次，代表位序，例如i=2,则返回pre<-pre<-L，返回导数第二个，若没有，即p先到了nullptr,则返回空指针

            return p;
        }

        DLNode *LocateElementByNext(DLinkList &L, void *e, int (*compar)(const void *, const void *)){
            // 按值查找
            if (L==nullptr) {
                return nullptr;
            }

            DLNode *p=L->next;
            while (p!=nullptr && compar(e,p->type)!=0) {
                p=p->next;//向后遍历
            }//如果p不是空指针并且p的值不等于要寻找的值则继续寻找，若p先到了nullptr则返回空指针

            return p;
        }

        DLNode *LocateElementByPre(DLinkList &L, void *e, int (*compar)(const void *, const void *)){
            if (L==nullptr) {
                return nullptr;
            }

            DLNode *p=L->next;
            while (p!=nullptr && compar(e,p->type)!=0) {
                p=p->pre;//向前遍历
            }//如果p不是空指针并且p的值不等于要寻找的值则继续寻找，若p先到了nullptr则返回空指针

            return p;
        }

        bool InsertNextNode(void *p_, void *s_){
            //后序插入，即若要插入到第i个节点则要找到第i-1个节点
            DLNode *p=(DLNode *)p_;
            DLNode *s=(DLNode *)s_;
            if (p==nullptr) {
                return false;
            }

            //若p->next不是nullptr则将p->next往前链接到s,并将s插入到p的后面
            s->next=p->next;
            if (p->next!=nullptr) {
                p->next->pre=s;
            }
            s->pre=p;//往前链接p
            p->next=s;
            return true;
        }

        bool DLinkListDelete(DLinkList &L, int i,void *e){
            //删除指定位序的节点，位序从1开始
            if (i<1) {
                return false;
            }

            DLNode *p=L;
            p=getElementByNext(L, i-1);//获得前驱节点，即第i-1个节点

            if (p==nullptr || p->next==nullptr) {
                return false;
            } //找不到所要删除的位置，1.i>p;2.i==p,但是p已经是最后一个节点

            DLNode *q=p->next;//要删除的节点,因为找到的是前驱节点

            //如果传入e，则将删除的值填充到e,e默认为0，即空指针
            if (e!=0) {
                Algorithm::fill((char *)(q->type), (char *)e, q->t_size,q->CopyFunc);
            }

            p->next=q->next;//将后面的节点往前移动
            if (q->next!=nullptr) {
                q->next->pre=p;
            }
            free(q);//释放要删除的节点的空间
            return true;
        }

        bool DLinkListInsert(DLinkList &L, int i, void *e,bool (* insert)(void *,void *),int t_size){
            //在第i个位置插入，则需要找到第i-1个指针然后在后面插入，i是位序，头结点是0
            DLNode *p=L;
            // while (p!=nullptr && i>head) {
            //     p=p->next;
            //     i--;//i减i-1次就是第i-1个指针,例如i=1,则此时p就是L，若i=5,则i减到1(i=1时退出循环),则p===L->1->2->3->4
            // }
            //
            p=getElementByNext(L, i-1); //默认后序插入，找到第i-1个节点，这条代码即是上面那段代码

            if (p==nullptr) {
                return false;
            }

            //为了实现泛型，每个节点可以存储不同类型的数据
            int size=p->t_size;
            if (t_size!=0) {
                size=t_size;
            }

            //初始化新节点，分配空间，并且存储数据
            DLNode *s=(DLNode *)malloc(sizeof(DLNode));
            if (s==nullptr) {
                return false;
            }
            s->next=nullptr;
            s->pre=nullptr;
            s->t_size=size;
            // s->type=e; //你可以这么写，但是一旦修改链表的数据，会改变main函数的数据，最好别这样
            s->type=malloc(t_size);
            s->CopyFunc=L->CopyFunc;
            Algorithm::fill((char *)e,  (char *)(s->type),size,s->CopyFunc);//也可以直接赋值，但是记住初始化s->type

            return insert(p,s);
        }
    }

}
