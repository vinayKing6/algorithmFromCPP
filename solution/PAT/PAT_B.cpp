//
// Created by vinay on 23-7-6.
//
#include <iostream>

namespace SOLUTION{

    class B1001{
        /**
         * pat 基础题1001 害死人不偿命的3n+1猜想
         */
    public:
        static void solution(){
            int n,step=0; //n输入的数,step是n->1的步数
            std::cin>>n; //输入n
            while (n>1){
                if (n%2==0) //偶数情况
                    n=n/2;
                else
                    n=(3*n+1)/2; //n是奇数
                step++; //步数+1
            }
            std::cout<<step<<std::endl;
        }
    };

    class B1002{
        /**
         * pat 基础题1002
         * 读入一个正整数 n，计算其各位数字之和，用汉语拼音写出和的每一位数字。

        输入格式：
        每个测试输入包含 1 个测试用例，即给出自然数 n 的值。这里保证 n 小于 10
        100
         。

        输出格式：
        在一行内输出 n 的各位数字之和的每一位，拼音数字间有 1 空格，但一行中最后一个拼音数字后没有空格。

        输入样例：
        1234567890987654321123456789
        输出样例：
        yi san wu
        代码长度限制
        16 KB
        时间限制
        400 ms
        内存限制
        64 MB
         */
    public:
        static void solution(){
            long sum=0;
            std::string n;
            std::cin>>n;
            std::string s[10]={"ling","yi","er","san","si","wu","liu","qi","ba","jiu"};
            for (int i = 0; i < n.length(); ++i) {
                sum+=int(n[i])-48;
            }
            Print(sum,s);
        }

        static void Print(int sum,std::string s[]){
            if (sum<10){
                std::cout<<s[sum%10];
                return;
            }
            Print(sum/10,s);
            std::cout<<" "<<s[sum%10];
        }
    };

    class B1032{
        /**
         * PAT 基础题1032 挖掘机技术哪家强
         */
    public:
        static void solution(){
            int n,max=-1,max_num=-1,maxn=10000; //参赛人数,最高分数,最高分数的学校编码，学校编码最大值
            std::cin>>n; //输入参赛人数
            int scores[maxn]; //存储每个学校分数,这里有点浪费内存
            for (int j = 0; j < n; ++j) {
                scores[j]=0; //初始化
            }
            for (int i = 0; i < n; ++i) {
                int num,score;
                std::cin>>num>>score; //输入学校编码,分数
                scores[num]+=score;
                if (max<scores[num])
                {
                    max=scores[num];
                    max_num=num;
                }
            }
            std::cout<<max_num<<" "<<max<<std::endl;
        }
    };

}
