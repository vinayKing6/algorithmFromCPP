#include <iostream>
#include <string>
#include <unordered_map>
#include "../../include/CStyle/Stack.h"
#include "../../include/CStyle/Util.h"
#include "../../include/CStyle/List.h"

using namespace Algorithm;
namespace Algorithm {
    namespace AS {

        /**
         *
         */
        bool InitArrayStack(ArrayStack &S, int InitSize, int t_size,void (* CopyFunc)(char *,char *,size_t) ,void (*init)(void *))
        {  
            S.length=0; // must done,可用于判断栈是否为空或是否为满
            S.MaxSize=InitSize; 
            S.t_size=t_size;
            if ((S.data=malloc(InitSize*S.t_size))==nullptr) {
                return false;
            }
            S.CopyFunc=CopyFunc;
            if (init!=0) {
                init(&S); // 自己写初始化列表的接口
            }
            return true;
        }

        int size(ArrayStack &S)
        {
            return S.length;
        }

        bool empty(ArrayStack &S)
        {
            return S.length==0;
        }

        bool full(ArrayStack &S)
        {
            return S.length==S.MaxSize;
        }

        char *top(ArrayStack &S,void *r){
            if (empty(S)) {
                return nullptr;
            } //判断stack是否为空
            //将栈顶元素存储在r中
            fill(getArrayElement(S.data, S.length-1, S.t_size),(char *)r,S.t_size,S.CopyFunc);
             
            return getArrayElement(S.data, S.length-1, S.t_size);
        }

        void push(ArrayStack &S, void *e)
        {
            if (full(S)) {
                return; //如果stack已满,则返回
            }
            //S.data[S.length]=e,S.length表示现有元素个数,也表示下一个元素数组下标,因为数组下标从0开始
            fill((char *)e,getArrayElement(S.data,S.length,S.t_size),S.t_size,S.CopyFunc);
            S.length++; //stack元素个数加1
        }

        void pop(ArrayStack &S,void *r)
        {
            if (empty(S)) {
                return; //如果为空则返回
            }
            //如果传入r,则将删除的元素返回到r
            if (r!=0) {
                fill(getArrayElement(S.data,S.length-1,S.t_size),(char *)r,S.t_size,S.CopyFunc);
            }
            S.length--; //只需将个数减1,表示删除栈顶元素
        }

        void clear(ArrayStack &S)
        {
            S.length=0;
        }

    }

    namespace LS {

        /**
         *
         */
        void InitLinkedStack(LinkedStack &S, int t_size,void (* CopyFunc)(char *,char *,size_t), void (*init)(void *))
        {  
            S.length=0; // must done,可用于判断栈是否为空或是否为满
            LL::InitLinkList(S.L,t_size); //初始化栈里的链表就行
            S.CopyFunc=CopyFunc;
            S.L->CopyFunc=S.CopyFunc; //先凑合着用吧
            if (init!=0) {
                init(&S); // 自己写初始化列表的接口
            }
        }

        int size(LinkedStack &S)
        {
            return S.length;
        }

        bool empty(LinkedStack &S)
        {
            return S.length==0;
        }

        char *top(LinkedStack &S,void *r){
            if (empty(S)) {
                return nullptr;
            } //判断stack是否为空
            //将栈顶元素存储在r中
            LL::LNode *p=LL::getElement(S.L,1); //找到链表的第一个元素，由于这里设定栈是头插，所以最后推入的元素在第一个
            fill((char *)p->type,(char *)r,S.L->t_size,S.CopyFunc); //将结果赋值到r
             
            return (char *)p->type;
        }

        void push(LinkedStack &S, void *e)
        {
            LL::Head_append(S.L,e);
            S.length++; //stack元素个数加1
        }

        void pop(LinkedStack &S,void *r)
        {
            if (empty(S)) {
                return; //如果为空则返回
            }
            //如果传入r,则将删除的元素返回到r
            LL::LinkListDelete(S.L,1,r); //后进先出，故删除第一个
            S.length--; //只需将个数减1,表示删除栈顶元素
        }

        void clear(LinkedStack &S)
        {
            LL::clear(S.L);
            S.length=0;
        }

    }

    namespace APP {
        char *genPostExpr(char formula[]){
            char c;
            int i=0;
            std::string expr="";

            while ((c=formula[i])!='\0') {
                if (c>='0'||c<='9') {
                }
            }
        }
    }
}
