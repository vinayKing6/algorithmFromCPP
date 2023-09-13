#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <ostream>
#include <string>
#include "../../include/CStyle/Util.h"

using namespace Algorithm;
namespace SOLUTION {

    namespace WD {
        namespace ListPuzzles {
            void W2_2_3_10(void *array,int start,int end,int p,size_t t_size,void (*Copy)(char *, char *, size_t)){
                //王道数据结构2.2.3 408真题
                //整个数组向前循环移动p个位置
                //start and end is inclusive
                reverseArray(array,start,p-1,t_size,Copy);
                reverseArray(array,p,end,t_size,Copy);
                reverseArray(array,start,end,t_size,Copy);
            }

            void TestW2_2_3_10(){
                char str[]="abcdefgh";
                W2_2_3_10(str,0,7,6,sizeof(char),copy);
                std::cout<<str<<std::endl;
            }

            int W2_2_3_11(int a[],int b[],int n){
                //王道数据结构2.2.3 11 408真题
                //查找两个等长升序序列A和B的中位数
                int s1=0,d1=n-1,m1,s2=0,d2=n-1,m2; //分别表示A,B的首位数、末位数、中位数
                while (s1!=d1 || s2!=d2) {
                    m1=(s1+d1)/2;
                    m2=(s2+d2)/2;
                    if (a[m1]==b[m2]) {
                        return a[m1];
                    }
                    else if (a[m1]<b[m2]) {
                        if ((s1+d1)%2==0) {
                            s1=m1;
                            d2=m2;
                        }
                        else {
                            s1=m1+1;
                            d2=m2;
                        }
                    }
                    else {
                        if ((s2+d2)%2==0) {
                            d1=m1;
                            s2=m2;
                        }
                        else {
                            d1=m1;
                            s2=m2+1;
                        }
                    }
                }
                return a[s1]<b[s2]? a[s1]:b[s2];
            }

            void TestW2_2_3_11(){
                int a[]={11,13,15,17,19};
                int b[]={2,4,6,8,20};
                std::cout<<W2_2_3_11(a,b,5)<<std::endl;
            }

            int W2_2_3_12(int a[],int n){
                //王道数据结构2.2.3 12 408真题
                //寻找主元素，主元素是指出现个数大于n/2的元素
                //首先使用暴力解 时间复杂度O(n)，空间复杂度O(n)
                //-----------------------------
                // int max=a[0];//先找到最大值
                // for (int i=1;i<n;i++) {
                //     if (max<a[i]) {
                //         max=a[i];
                //     }
                // }
                // int count[max+1];
                // for (int i=0;i<max+1;i++) {
                //     count[i]=0; //初始化
                // }
                // for (int i=0;i<n;i++) {
                //     count[a[i]]++; //记录每个元素的个数
                // }
                // for (int i=0;i<max+1;i++) {
                //     if (count[i]>n/2) {
                //         return i;
                //     }
                // }
                // return -1;
                //-----------------------------
                //王道解法,时间复杂度O(n),空间复杂度O(1)
                int c,count; //c是候选主元素,count表示候选主元素是否可能存在
                c=a[0];
                count=0;
                for(int i=1;i<n;i++){
                    if (a[i]==c) {
                        count++;
                    }else if (count>0) {
                        count--;
                    }else {
                        c=a[i];
                        count=0;
                    }
                }
                if (count>0) {
                    for (int i=count=0;i<n;i++) {
                        if (a[i]==c) {
                            count++;
                        }
                    }
                }
                return count>n/2?c:-1;
            }

            void TestW2_2_3_12(){
                int array[8]={0,5,5,3,5,7,5,5};
                int array2[8]={0,5,5,5,5,1,3,7};
                std::cout<<W2_2_3_12(array,8)<<std::endl;
                std::cout<<W2_2_3_12(array2,8)<<std::endl;
            }

            /**
             *王道数据结构2.2.3 13 408真题
             */
            class W2_2_3_13{
                public:

                    /**
                     * 暴力解 时间复杂度O(n^2) 空间复杂度O(1)
                     */
                    static int BruteForce(int array[],int length){
                        int target=1;
                        for (int i=0;i<length;i++){
                            for(int j=0;j<length;j++)
                                if (array[j]==target) {
                                    target++;
                                }
                        }
                        return target;
                    }

                    /**
                     * 王道解法，时间复杂度O(n) 空间复杂度O(n)
                     */
                    static int Answer(int array[], int length){
                        int i,*B; //标记数组
                        B=(int *)malloc (sizeof (int)*length);//分配空间
                        for (int i=0;i<length;i++) {
                            B[i]=0;//初值0
                        }
                        for(i=0;i<length;i++) {
                            if (array[i]>0&&array[i]<=length) //若A[i]的值介于1-n，则标记数组B
                                B[array[i]-1]=1;
                        } 

                        for (int i=0;i<length;i++) {
                            if (B[i]==0) {
                                return B[i+1]; //扫描数组B，找到目标值
                            }
                        }
                        return length+1; //最小未出现正整数要么在1-n之间，要么是1+n
                    }

                    static void solution(){
                        int array[]={-5,3,2,3};
                        int array2[]={5,4,3,2,1};
                        std::cout<<BruteForce(array, 4)<<std::endl;
                        std::cout<<BruteForce(array2, 5)<<std::endl;
                        std::cout<<Answer(array2, 5)<<std::endl;
                    }
            };

            /**
             *王道数据结构2.2.3 13 408真题
             */
            class W2_2_3_14{
                public:
                    /**
                     * 暴力解 时间复杂度O(O^3) 空间复杂度O(1)
                     */
                    static int BruteForce(int a1[],int n1,int a2[],int n2,int a3[],int n3){
                        int distance=0;
                        for (int i=0;i<n1;i++) {
                            for (int j=0;j<n2;j++) {
                                for (int k=0;k<n3;k++) {
                                    int D=abs(a1[i]-a2[j])+abs(a2[j]-a3[k])+abs(a1[i]-a3[k]);
                                    if (i==0&&j==0&&k==0) {
                                        distance=D;
                                    }else {
                                        if(distance>D)
                                            distance=D;
                                    }
                                }
                            }
                        }
                        return distance;
                    }

                    /**
                     * 判断a是不是最小值
                     */
                    static bool if_min(int a,int b,int c){
                        if (a<=b&&a<=c) {
                            return true;
                        }else {
                            return false;
                        }
                    }

                    /**
                     * 王道解法 时间复杂度O(n) 空间复杂度O(1)
                     * 三个点只更新最小的点 l=2*l3 a-b-c a往右移
                     */
                    static int Answer(int a1[],int n1,int a2[],int n2,int a3[],int n3){
                        int distance=abs(a1[0]-a2[0])+abs(a2[0]-a3[0])+abs(a1[0]-a3[0]);
                        int i=0;
                        int j=0;
                        int k=0;
                        while (i<n1&&j<n2&&k<n3&&distance>0) {
                            int D=abs(a1[i]-a2[j])+abs(a2[j]-a3[k])+abs(a1[i]-a3[k]);
                            if (D<distance) {
                                distance=D;
                            }
                            if (if_min(a1[i],a2[j],a3[k])) {
                                i++;
                            }else if (if_min(a2[j],a1[i],a3[k])) {
                                j++;
                            }else {
                                k++;
                            }//找到最小的点并向右移
                        }
                        return distance;
                    }

                    static void solution(){
                        int a1[]={-1,0,9};
                        int a2[]={-25,-10,10,11};
                        int a3[]={2,9,17,30,41};
                        std::cout<<BruteForce(a1,3,a2,4,a3,5)<<std::endl;
                        std::cout<<Answer(a1,3,a2,4,a3,5)<<std::endl;
                    }
            };

            /**
             * 408真题 2009 查找链表倒数k个位置的值
             */
            class W2_2_3_7_22{

                public:
                    struct Node{
                        int data;
                        Node *next;
                    };

                    static Node *BruteForce(Node *L,int k){
                        int l=0;//算表长
                        Node *p=L;
                        while (p->next!=nullptr) {
                            l++;
                            p=p->next;
                        }//到表尾
                        if (k>l) {
                            return nullptr;
                        }
                        p=L;//到表头
                        for(int i=1;i<=l-k+1;i++){
                            p=p->next;
                        }
                        return p;
                    }

                    static Node *data(){
                        Node *L=(Node *)malloc(sizeof(Node));
                        L->data=-1;
                        L->next=nullptr;
                        for (int i=0;i<10;i++) {
                            Node *p=(Node *)malloc(sizeof(Node));
                            p->data=i;
                            p->next=L->next;
                            L->next=p;
                        }
                        return L;
                    }

                    /**
                     * 王道解法，时间复杂度O(n)
                     */
                    static Node *Answer(Node *L,int k){
                        //只扫描一遍
                        Node *fast=L->next;
                        Node *slow=L->next;
                        int count=0; //记录fast与slow之间的间隔
                        while (fast!=nullptr) {
                            if (count<k) {
                                count++;//使间隔增加到k
                            }else {
                                slow=slow->next;//间隔达到k与fast一同前进
                            }
                            fast=fast->next;//无论如何fast都前进遍历
                        }
                        return slow;
                    }

                    static void solution(){
                        std::cout<<BruteForce(data(), 5)->data<<std::endl;
                        std::cout<<Answer(data(), 5)->data<<std::endl;
                    }

            };

            /**
             * 408真题 2012真题，字符串共享后缀 
             */
            class W2_2_3_7_23{
                public:
                    struct Node{
                        char data;
                        Node *next;
                    };

                    /**
                     * 暴力解 时间复杂度O(n^2)
                     */
                    static Node *BruteForce(Node *str1,Node *str2){
                        int m=0;
                        int n=0;
                        Node *p=str1;
                        Node *q=str2;

                        //先算长度
                        while (p!=nullptr) {
                            m++;
                            p=p->next;
                        }
                        while (q!=nullptr) {
                            n++;
                            q=q->next;
                        }

                        p=str1;
                        q=str2;
                        //暴力解
                        while (p!=nullptr) {
                            q=str2;//从头来过
                            while (q!=nullptr) {
                                if (q==p) {
                                    return q;
                                }else {
                                    q=q->next;
                                }
                            }
                            p=p->next;
                        }
                        return p;
                    }

                    static void data(Node *&str1,Node *&str2){
                        //建立题目里面的共享单链表
                        char s1[]="gnidaol";
                        char s2[]="eb";

                        str1=(Node *)malloc(sizeof(Node));
                        str2=(Node *)malloc(sizeof(Node));
                        str1->next=nullptr;
                        str2->next=nullptr;
                        Node *tmp=nullptr;

                        for(int i=0;i<7;i++){
                            Node *p=(Node *)malloc(sizeof(Node));
                            if (s1[i]=='i') {
                                tmp=p;
                            }
                            p->data=s1[i];
                            p->next=str1->next;
                            str1->next=p;
                        }

                        for(int i=0;i<2;i++){
                            Node *q=(Node *)malloc(sizeof(Node));
                            q->data=s2[i];
                            q->next=str2->next;
                            str2->next=q;
                        }

                        str2->next->next->next=tmp;
                    }

                    static void solution(){
                        Node *str1,* str2;
                        data(str1 ,str2);
                        Node *r=BruteForce(str1,str2);
                    }

            };

            /**
             * 408真题 2015 去除绝对值相等的结点只保留第一次出先的结点
             */
            class W2_2_3_7_24{
                public:
                    struct Node{
                        int data;
                        Node *next;
                    };

                    static Node *data(){
                        //题目里面的数据
                        int array[]={15,-7,15,-15,21};
                        Node *L=(Node *)malloc(sizeof(Node));
                        L->next=nullptr;

                        for(int i=0;i<5;i++){
                            Node *p=(Node *)malloc(sizeof(Node));
                            p->data=array[i];
                            p->next=L->next;
                            L->next=p;
                        }

                        return L;
                    }

                    /**
                     * 暴力解 时间复杂度(O^2)
                     */
                    static Node *BruteForce(Node *L){
                        Node *p=L->next;
                        while (p!=nullptr) {
                            Node *q=p;//从p结点开始
                            while (q!=nullptr&&q->next!=nullptr) {
                                //判断绝对值是否相等
                                //因为不能改变链表的顺序,所以要记录前区
                                if (abs(q->next->data)==abs(p->data)) {
                                    //删除q.next结点
                                    Node *tmp=q->next;
                                    q->next=tmp->next;
                                    free(tmp);
                                }else {
                                    q=q->next;
                                }
                            }
                            p=p->next;
                        }
                        return L;
                    }

                    static void solution(){
                        Node *L=data();
                        BruteForce(L);
                    }
            };

            /**
             * 408真题 2019 重排单链表
             */
            class W2_2_3_7_25{
                public:
                    struct Node{
                        int data;
                        Node *next;
                    };

                    static Node *data(){
                        Node *L=(Node *)malloc(sizeof(Node));
                        L->next=nullptr;
                        for(int i=0;i<10;i++){
                            Node *p=(Node *)malloc(sizeof(Node));
                            p->data=i;
                            p->next=L->next;
                            L->next=p;
                        }
                        return L;
                    }

                    /**
                     * 暴力解
                     */

                    /**
                     * 寻找倒数第一个元素
                     */
                    static Node *find_tail(Node *L){
                        while (L->next!=nullptr) {
                            L=L->next;
                        }
                        return L;
                    }

                    /**
                     * 寻找倒数第二个元素
                     */
                    static Node *find_last_sec(Node *L){
                        while (L->next!=nullptr&&L->next->next!=nullptr) {
                            L=L->next;
                        }
                        return L;
                    }

                    /**
                     * 暴力解 时间复杂度O(n^2)
                     */
                    static Node *BruteForce(Node *L){
                        Node *head=L;
                        Node *tail=find_tail(L);
                        Node *last_sec=find_last_sec(L);

                        int i=0;
                        while (tail!=head) {
                            if (i%2==0) {
                                //i是偶数就不插入直接跳
                                i++;
                                head=head->next;
                            }else {
                                last_sec->next=tail->next;
                                tail->next=head->next;
                                head->next=tail; //如果i是奇数就把最后一个插入到head和head.next之间
                                head=tail;//让head跳到插入的那个位置
                                i++;
                                tail=find_tail(L);//更新最后的值
                                last_sec=find_last_sec(L);//更新倒数第二个值
                            }
                        }
                        return L;
                    }

                    static void solution(){
                        Node *L=data();
                        BruteForce(L);
                    }
            };

            void TestListQues(){
                // TestW2_2_3_10();
                // TestW2_2_3_11();
                // TestW2_2_3_12();
                // W2_2_3_13::solution();
                // W2_2_3_14::solution();
                // W2_2_3_7_22::solution();
                // W2_2_3_7_23::solution();
                // W2_2_3_7_24::solution();
                W2_2_3_7_25::solution();
            }
        }
    }




}
