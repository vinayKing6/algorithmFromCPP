//
// Created by vinay on 23-7-24.
//

/**
 * 洛谷 入门题
 */
#include <string>
#include <iostream>

namespace SOLUTION{


    class P2084{
        /**
         * 题目描述
            今天小明学会了进制转换，比如（10101）2 ，那么它的十进制表示的式子就是 :

            1*2^4+0*2^3+1*2^2+0*2^1+1*2^0，

            那么请你编程实现，将一个M进制的数N转换成十进制表示的式子。

            注意：当系数为0时，该单项式要省略。

            输入格式
            两个数，M和N，中间用空格隔开。

            输出格式
            共一行，一个十进制表示的式子。

            输入输出样例
            输入 #1复制
            2 10101
            输出 #1复制
            1*2^4+1*2^2+1*2^0
            说明/提示
            对于100%的数据，1<M<10，N的位数不超过1000。
         */
    public:
        void Print(int base,std::string val,int length,int count){
            //递归的打印
            if (length==val.length()){
                return;
            }

            if (val[length]!='0'){
                if (count==0)
                    std::cout<<val[length]<<"*"<<base<<"^"<<val.length()-length-1;
                else
                    std::cout<<"+"<<val[length]<<"*"<<base<<"^"<<val.length()-length-1;
                count++;
            }
            Print(base,val,length+1,count);
        }

        void solution(){
            int base;
            std::string val;
            std::cin>>base>>val;
            Print(base,val,0,0);
        }
    };
}

