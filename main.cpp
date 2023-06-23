#include <cstdio>
#include <iostream>
#include "./include/CStyle/Queue.h"
#include "./src/Sort.cpp"
#include <iterator>
#include <ostream>
#include <vector>
#include <cstdlib>
#include "./include/CStyle/Util.h"
#include <string>
#include "include/Divide_and_Conquer.h"
#include "./include/CStyle/List.h"
#include "./test/StackTest.cpp"
#include "./test/QueueTest.cpp"
#include "./solution/ListQues.cpp"
#include "./solution/STL/STLQues.cpp"

using namespace Algorithm;

class Node{
public:
    Node(){

    }

    Node(int value){
        this->value=value;
    }
    int value;

    bool operator<(const Node& node) const {
        return this->value<node.value;
    }

    bool operator==(const Node& node) const {
        return this->value==node.value;
    }

    bool operator>(const Node& node) const {
        return this->value>node.value;
    }

    std::string toString(){
        return "node: "+std::to_string(this->value);
    }
};

struct STU{
    int num;
};

void Test_Sort(){
    int size=100000;
    int start=0;
    int end=10;
    int *array;

    array=Algorithm::random_int_array(size,start,end);

//    for (int i = 0; i <size ; ++i) {
//        std::cout<<array[i]<<" ";
//    }
//
//    std::cout<<std::endl;

    // Node nodes[size];
    // for (int i = 0; i < size; ++i) {
    //     nodes[i].value=(rand()%(end-start)+start);
    // }
    //
    Algorithm::Insert_Sort(array,size);
//    Algorithm::Merge_Sort(array,size);

    bool result=Algorithm::is_sorted(array,size);
    if (!result)
        std::cout<<"sort failed !!!"<<std::endl;
    else
        std::cout<<"sort succeed !!!"<<std::endl;

    Algorithm::test();

}

void Test_Divde_and_Conquer(){
    int rows=16;
    int cols=16;
    auto a=Algorithm::Matrix2D<int>(rows,cols);
    auto b=Algorithm::Matrix2D<int>(rows,cols);
    auto c=Algorithm::Matrix2D<int>(rows,cols);

    int a_copy[][16]={
            {1,2,3,4,5,6,7,8,3,4,5,6,7,8,9,0},
            {4,5,6,7,8,9,0,1,5,6,7,8,9,0,1,2},
            {1,2,3,4,5,6,7,8,1,2,2,2,3,4,5,6},
            {1,2,2,2,2,4,4,5,0,9,7,0,3,4,5,6},
            {1,2,2,2,2,4,4,5,0,9,7,0,3,4,5,6},
            {1,2,2,2,2,4,4,5,0,9,7,0,3,4,5,6},
            {1,2,2,2,2,4,4,5,0,9,7,0,3,4,5,6},
            {1,2,2,2,2,4,4,5,0,9,7,0,3,4,5,6},
            {1,2,2,2,2,4,4,5,0,9,7,0,3,4,5,6},
            {1,2,2,2,2,4,4,5,0,9,7,0,3,4,5,6},
            {1,2,2,2,2,4,4,5,0,9,7,0,3,4,5,6},
            {1,2,2,2,2,4,4,5,0,9,7,0,3,4,5,6},
            {1,2,2,2,2,4,4,5,0,9,7,0,3,4,5,6},
            {1,2,2,2,2,4,4,5,0,9,7,0,3,4,5,6},
            {1,2,2,2,2,4,4,5,0,9,7,0,3,4,5,6},
            {1,2,2,2,2,4,4,5,0,9,7,0,3,4,5,6}};

    int c_copy[][16]={{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0}};
    a.fill(a_copy);
    b.fill(a_copy);
    c.fill(c_copy);
    c.show();
    std::cout<<std::endl;

    Algorithm::Square_Matrix_Multiply_Origin(a,b,c);
    c.show();
    std::cout<<std::endl;
    c.zeros();
    Algorithm::Square_Matrix_Multiply_Recurse_values_(a,b,c);
    c.show();
}

void test(){
    int c[2][3]={{1,2,3},{1,2,3}};
    int b[3][2]={{1,2},{1,2},{1,2}};
    auto c_m=Algorithm::Matrix2D<int>(2,3);
    c_m.zeros();

    auto m=Algorithm::Matrix2D<int>(2,5);
    m.fill(c);
    m.show();
    auto n=m.SubMatrix(0,2,1,6);
    n.show();

//    n.show();
//    int a[]={1,2,3,4,5,6,7};
//    int *b=a;
//    b+=3;
//    std::cout<<b[0];
}

int *testPointer(){
    static int i[]={1,2,3};
    return i;
}

void test_2(){
    int *i=testPointer();
    std::cout<<i[2]<<std::endl;
}

//----------testList--------

void init(void *SL){
    SL::SeqList *sl=(SL::SeqList *)SL;
    for (int i=0;i<sl->MaxSize;i++){
        *(int *)SL::getElement(*sl, i)=10;
    }
}

void testList(){
    SL::SeqList sl;
    int MaxSize=10000;
    int t_size=sizeof(int);
    SL::InitSeqList(sl,MaxSize ,t_size, copy,init);
    //insert 1 to location 1;
    int e=100;
    for (int i=0;i<sl.MaxSize;i++){
        e=rand()%1000;
        SL::SeqListInsert(sl, i+1, &e);
    }

    //print and see if this works
    for (int i=0;i<sl.MaxSize;i++){
        printf("%d ",*(int *)SL::getElement(sl, i));
    }
    printf("\n%d ",sl.length);
    SL::IncreaseSeqListSize(sl, MaxSize*2);
    SL::SeqListInsert(sl, MaxSize+1, &e);
    for (int i=0;i<sl.length;i++){
        printf("%d ",*(int *)SL::getElement(sl, i));
    }
    printf("\n%d %d \n",sl.length,sl.MaxSize);

    SL::SeqListDelete(sl, sl.length,&e);
    printf("\n%d %d \n",sl.length,sl.MaxSize);
    printf("the last element is %d\n",e);
    SL::clear(sl);
    SL::SeqListDelete(sl,1);
}

int STU_compar(const void *a,const void *b){
    return ((STU *)a)->num-((STU *)b)->num;
}

void testLinkList(){
    LL::LinkList ll;
    LL::InitLinkList(ll, sizeof(STU));
    STU s={1};
    STU s1={4};
    LL::LinkListInsert(ll, 1, &s);
    LL::LinkListInsert(ll, 1, &s1,0,LL::InsertPriorNode); //前置插入
    STU s3;
    s3.num=0;
    LL::LinkListDelete(ll, 2,&s3);
    LL::LNode *p=ll->next;
    auto ge=LL::LocateElement(ll, &s3, STU_compar);
    if (ge==nullptr) {
        printf("fuck nullptr\n");
    }else{
        printf("ge %d\n",((STU *)ge->type)->num);
    }
    printf("s3 %d\n",s3.num);
    while (p!=nullptr) {
        printf("s: %d\n",((STU *)p->type)->num);
        p=p->next;
    }

    //测试插入
    for(int i=0;i<100;i++){
        int n=rand()%1000;
        STU s{i};
        // LL::Head_append(ll, &s);
        LL::Tail_append(ll, &s);
    }
    p=ll->next;
    int n=0;
    while (p!=nullptr) {
        printf("s: %d\n",((STU *)p->type)->num);
        p=p->next;
        n++;
    }
    printf("head test-----%d %d\n",n,LL::length(ll));
    //测试随机删除
    int count=0;
    for(int i=0;i<100;i++){
        int n=rand()%100;
        if (n<=LL::length(ll)) {
            count++;
        }
        LL::LinkListDelete(ll, n);
    }
    n=0;
    p=ll->next;
    while (p!=nullptr) {
        printf("s: %d\n",((STU *)p->type)->num);
        p=p->next;
        n++;
    }
    printf("delete test-----%d %d\n",n,LL::length(ll));
    // LL::clear(ll);
    // printf("clear test-----%d\n",LL::length(ll));
    // p=ll->next;
    // STU *s2=(STU *)p->type;
    // s2->num=3;
    // printf("%d\n",s.num);
    //

    //测试双链表
    DLL::DLinkList dl;
    DLL::InitDLinkList(dl, sizeof(STU));
    //测试双链表插入
    p=ll->next;
    for(int i=1;i<=LL::length(ll);i++){
        LL::LNode *t=LL::getElement(ll, i);
        DLL::DLinkListInsert(dl, i, (STU *)(t->type));
    }
    DLL::DLNode *q=dl->next;
    while (q->next!=nullptr) {
        printf("s: %d\n",((STU *)q->type)->num);
        q=q->next;
        n++;
    }
    while (q->pre!=nullptr) {
        printf("s: %d\n",((STU *)q->type)->num);
        q=q->pre;
    }
    for(int i=1;i<32;i++){
        q=DLL::getElementByNext(dl, i);
        if (q!=nullptr) {
            printf("s: %d\n",((STU *)q->type)->num);
        }else{
            printf("fuck nullptr\n");
        }
    }
    for(int i=1;i<31;i++){
        DLL::DLNode *s=DLL::getElementByPre(q, i);
        if (s!=nullptr) {
            printf("s: %d\n",((STU *)s->type)->num);
        }else{
            printf("fuck nullptr\n");
        }
    }
}

int main() {
    // Test_Sort();
    // Test_Divde_and_Conquer();
    //    test();
    //    test_2();
    // std::cout<<"fuck"<<std::endl;
    // testList();
    // testLinkList();
    // TEST::TestArrayStack();
    // TEST::TestLinkedStack();
    // TEST::TestArrayQueue();
    // SOLUTION::TestListQues();
    SOLUTION::TestJB_5_1();
    return 0;
}
