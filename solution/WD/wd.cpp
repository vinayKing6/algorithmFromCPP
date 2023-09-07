#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <ostream>
#include "../../include/CStyle/Util.h"

using namespace Algorithm;
namespace SOLUTION {

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

        void TestListQues(){
            // TestW2_2_3_10();
            // TestW2_2_3_11();
            // TestW2_2_3_12();
            // W2_2_3_13::solution();
            W2_2_3_14::solution();
        }
    }


}
