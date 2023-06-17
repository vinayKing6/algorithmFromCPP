#include <cstddef>
#include <iostream>
#include <iterator>
#include <ostream>
#include "../include/CStyle/Util.h"

using namespace Algorithm;
namespace SOLUTION {

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

    void TestListQues(){
        // TestW2_2_3_10();
        // TestW2_2_3_11();
        TestW2_2_3_12();
    }
}
