#include "../include/CStyle/Queue.h"
#include <iostream>

namespace TEST {
    void TestArrayQueue(){
        //测试顺序栈

        //初始化栈


        //存储整型元素
        std::cout<<"测试整型---------\n";
        AQ::ArrayQueue q_int;
        int capacity=10;
        int t_size=sizeof(int);
        AQ::InitArrayQueue(q_int,capacity,t_size);
        int *array=random_int_array(capacity,1,10);
        //测试enqueue和dequeue,打印
        for (int i=0;i<capacity;i++) {
            AQ::enqueue(q_int,getArrayElement(array,i,t_size));
            std::cout<<array[i]<<" ";
        }
        int int_r;
        AQ::dequeue(q_int,&int_r);
        AQ::enqueue(q_int,array+2);
        std::cout<<std::endl<<int_r;

        //测试front and rear
        std::cout<<"\n---front and rear\n";
        int int_front,int_rear;
        AQ::front(q_int,&int_front);
        std::cout<<std::endl<<int_front;
        AQ::rear(q_int,&int_rear);
        std::cout<<std::endl<<int_rear;
        //
        // //存储字符串元素 ,修改&string时出错,故使用char *
        // AQ::ArrayQueue s_str;
        // t_size=sizeof(char *);
        // AQ::InitArrayQueue(s_str,capacity,t_size);
        // char s1[]="hello world";
        // char s2[]="fuck you";
        // char s3[]="damn";
        // char *str[]={s1,s2,s3};
        //
        // for(int i=0;i<3;i++){
        //     AQ::push(s_str, getArrayElement(str,i, t_size));
        // }
        //
        // const char *rs,*tops;
        // AQ::pop(s_str,&rs);
        // std::cout<<std::endl<<rs;
        // AQ::top(s_str,&tops);
        // std::cout<<std::endl<<tops;
        //
        // //存储double类型
        // AQ::ArrayQueue s_d;
        // t_size=sizeof(s_d);
        // AQ::InitArrayQueue(s_d,capacity,t_size);
        // double d[]={1.2,3.4,3.90};
        // for(int i=0;i<3;i++){
        //     AQ::push(s_d, d+i);
        // }
        //
        // double d1,d2;
        // AQ::pop(s_d,&d1);
        // std::cout<<"\n"<<d1;
    }
}
