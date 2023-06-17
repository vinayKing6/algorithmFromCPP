//
// Created by vinay on 2023/5/5.
//

#ifndef ALGORITHM_QUEUE_H
#define ALGORITHM_QUEUE_H
#include <iostream>
#include "Stack.h"
#include "Util.h"

using namespace Algorithm;
namespace Algorithm {
    namespace AQ {
        //array-based queue


        /**
         *使用数组实现队列。
         */
        struct ArrayQueue : AS::ArrayStack{
            //基础数据类型跟stack一模一样,故使用stack作为父类
            int f,r; //由于是循环数组,所以f表示队列第一个元素,r表示队尾下一个元素
        };


        bool InitArrayQueue(ArrayQueue &Q,int InitSize,int t_size,void (* CopyFunc)(char *,char *,size_t)=copy,void (* init)(void *)=0); //初始化队列,如有需要,可以传入自定义的初始函数init和赋值函数
        int size(ArrayQueue &Q); //return number of stored elements
        bool empty(ArrayQueue &Q);//if Queue is empty then return true
        bool full(ArrayQueue &Q);//if Queue is full then return true
        bool front(ArrayQueue &Q,void *r=0);// return the first element of stored data, stored to r
        bool rear(ArrayQueue &Q,void *r=0);// return the last element of stored data, stored to r
        bool dequeue(ArrayQueue &Q,void *r=0);//pop out the first element,(first in first out),stored the result into r
        bool enqueue(ArrayQueue &Q,void *e);//push new element into queue
    }

}

#endif //ALGORITHM_QUEUE_H
