//
// Created by vinay on 2023/5/9.
//

#ifndef ALGORITHM_STACK_H
#define ALGORITHM_STACK_H
#include "List.h"
#include "Util.h"
#include <cstddef>
#include <iostream>
#include <string>

using namespace Algorithm;
namespace Algorithm {
    namespace AS {
        /**
         *使用数组实现栈
         **/
        struct ArrayStack{
            void *data;//存储的数据数组
            int t_size;//存储的数据类型的大小
            int length;//已经存储的数据的个数
            int MaxSize;//可存储的数据的最大个数
            void (* CopyFunc)(char *,char *,size_t)=copy;//赋值函数,决定to=from的细致操作,默认是Util的copy
        };

        bool InitArrayStack(ArrayStack &S,int InitSize,int t_size,void (* CopyFunc)(char *,char *,size_t)=copy,void (* init)(void *)=0); //初始化栈,如有需要,可以传入自定义的初始函数init
        int size(ArrayStack &S); //栈的元素个数
        bool empty(ArrayStack &S); //栈是否为空
        bool full(ArrayStack &S); //栈是否已满
        char *top(ArrayStack &S,void *r); //返回栈顶元素到r
        void push(ArrayStack &S,void *e); //推入栈顶
        void pop(ArrayStack &S,void *r=0); //弹出栈顶元素,如有需要,存储在传入的r中
        void clear(ArrayStack &S); //清空栈
    }

    namespace LS {
        //use LinkedList to implement stack
        struct LinkedStack{
            LL::LinkList L;
            int length;
            void (* CopyFunc)(char *,char *,size_t)=copy;//赋值函数,决定to=from的细致操作,默认是Util的copy
        };

        void InitLinkedStack(LinkedStack &S,int t_size,void (* CopyFunc)(char *,char *,size_t)=copy,void (* init)(void *)=0); //初始化栈,如有需要,可以传入自定义的初始函数init和赋值函数CopyFunc
        int size(LinkedStack &S); //栈的元素个数
        bool empty(LinkedStack &S); //栈是否为空
        char *top(LinkedStack &S,void *r); //返回栈顶元素到r
        void push(LinkedStack &S,void *e); //推入栈顶
        void pop(LinkedStack &S,void *r=0); //弹出栈顶元素,如有需要,存储在传入的r中
        void clear(LinkedStack &S); //清空栈

    }

    namespace APP{

        char *genPostExpr(char formula[]); //生成后缀表达式
    }
}

#endif //ALGORITHM_STACK_H
