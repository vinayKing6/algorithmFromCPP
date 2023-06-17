//
// Created by vinay on 2023/3/22.
//

#ifndef ALGORITHM_LIST_H
#define ALGORITHM_LIST_H
#include <iostream>
#include "Util.h"

using namespace Algorithm;
namespace Algorithm {
    namespace SL {
        //顺序表
        struct SeqList{
            void *data; //为了存储任何类型的数据
            int t_size;//存储的数据类型的大小
            int length;//已经存储的数据的个数
            int MaxSize;//可存储的数据的最大个数
            void (* CopyFunc)(char *,char *,size_t)=copy;//赋值函数,决定to=from的细致操作,默认是Util的copy
        };

        void InitSeqList(SeqList &L,int InitSize,int t_size,void (* CopyFunc)(char *,char *,size_t)=copy,void (* init)(void *)=0);

        void IncreaseSeqListSize(SeqList &L,int len);

        char *getElement(SeqList &L,int i);//获得第i个位置的数据，从0开始

        bool SeqListInsert(SeqList &L,int i, void *e);

        bool SeqListDelete(SeqList &L,int i, void *e=0);

        bool isEmpty(SeqList &L);

        bool clear(SeqList &L);

    }

    namespace LL {
        //LinkedList 单链表

        struct LNode{
            void *type;
            int t_size;
            LNode *next;
            void (* CopyFunc)(char *,char *,size_t)=copy;//赋值函数,决定to=from的细致操作,默认是Util的copy
        };

        using LinkList=LNode *;

        bool InitLinkList(LinkList &L,int t_size,void (* CopyFunc)(char *,char *,size_t)=copy);

        int length(LinkList &L);

        LNode *getElement(LinkList &L,int i);//获得第i个位置的数据，从0开始

        LNode *LocateElement(LinkList &L,void *e,int (* compar)(const void *,const void *)); //按值查找

        bool LinkListDelete(LinkList &L,int i, void *e=0);

        bool isEmpty(LinkList &L);

        bool clear(LinkList &L);

        bool InsertNextNode(void *p_,void *s_);

        bool InsertPriorNode(void *p_,void *s_);

        bool LinkListInsert(LinkList &L,int i, void *e,int head=1,bool (* insert)(void *,void *)=InsertNextNode,int t_size=0);

        bool Head_append(LinkList &L,void *e,int t_size=0);

        bool Tail_append(LinkList &L,void *e,int t_size=0);

    }

    namespace DLL {
        //Double linklist 双链表
        struct DLNode{
            void *type;
            int t_size;
            DLNode *pre,*next;//可以向前遍历也可以向后遍历
            void (* CopyFunc)(char *,char *,size_t)=copy;//赋值函数,决定to=from的细致操作,默认是Util的copy
        };

        using DLinkList=DLNode *;

        //只实现向后插入，删除节点，按序查找和按值查找（两个方向),时间有限
        bool InitDLinkList(DLinkList &L,int t_size);

        bool InsertNextNode(void *p_, void *s_);
        
        bool DLinkListInsert(DLinkList &L,int i,void *e,bool (* insert)(void *,void *)=InsertNextNode,int t_size=0);

        bool DLinkListDelete(DLinkList &L, int i,void *e=0);

        DLNode *getElementByNext(DLinkList &L,int i); //向后按序查找
        DLNode *getElementByPre(DLinkList &L,int i); //向前按序查找

        DLNode *LocateElementByNext(DLinkList &L, void *e, int (*compar)(const void *, const void *)); //向后按值查找
        DLNode *LocateElementByPre(DLinkList &L, void *e, int (*compar)(const void *, const void *)); //向前按值查找

    }

}


#endif //ALGORITHM_LIST_H
