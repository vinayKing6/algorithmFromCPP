#include <iostream>
#include "../../include/CStyle/Queue.h"
#include "../../include/CStyle/Stack.h"

using namespace Algorithm;
namespace Algorithm {
    namespace AQ {

        bool InitArrayQueue(ArrayQueue &Q,int InitSize,int t_size,void (* CopyFunc)(char *,char *,size_t),void (* init)(void *)){
            Q.f=Q.r=0; //f,r初始化为0
            return AS::InitArrayStack(Q,InitSize,t_size,CopyFunc,init);
        }

        int size(ArrayQueue &Q){
            //return number of stored elements
            return Q.length;
        } 

        bool empty(ArrayQueue &Q){
            //if Queue is empty then return true
            return AS::empty(Q);
        }

        bool full(ArrayQueue &Q){
            //if Queue is full then return true
            return AS::full(Q);
        }

        bool front(ArrayQueue &Q,void *r){
            // return the first element of stored data, stored to r
            if (empty(Q)) {
                return false; //判断队列是否为空
            }
            if (r!=0) {
                //*r=Q.data[f]
                fill(getArrayElement(Q.data,Q.f,Q.t_size),(char *)r,Q.t_size,Q.CopyFunc);
            }
            return true;
        }

        bool rear(ArrayQueue &Q,void *r){
            // return the last element of stored data, stored to r
            if (empty(Q)) {
                return false;
            }

            if (r!=0) {
                //*r=Q.data[r-1] r-1=(r-1+Q.MaxSize)%Q.MaxSize
                fill(getArrayElement(Q.data,(Q.r-1+Q.MaxSize)%Q.MaxSize,Q.t_size),(char *)r,Q.t_size,Q.CopyFunc);
            }
            return true;
        }

        bool dequeue(ArrayQueue &Q,void *r){
            //pop out the first element,(first in first out),stored the result into r
            if (empty(Q)) {
                return false;
            }

            if (r!=0) {
                //*r=Q.data[f]
                fill(getArrayElement(Q.data,Q.f,Q.t_size),(char *)r,Q.t_size,Q.CopyFunc);
            }
            Q.f=(Q.f+1)%Q.MaxSize; //循环列表,比如f刚好是Q.length-1,那么弹出一个元素后,f是Q.length%Q.length=0
            Q.length--;
            return true;
        }

        bool enqueue(ArrayQueue &Q,void *e){
            //push new element into queue
            if (full(Q)) {
                return false;
            }

            //Q.data[r]=*e, r is always the next element would be stored in array
            fill((char *)e,getArrayElement(Q.data,Q.r,Q.t_size),Q.t_size,Q.CopyFunc);
            Q.r=(Q.r+1)%Q.MaxSize;//循环数组
            Q.length++;
            return true;
        }
    }
}



