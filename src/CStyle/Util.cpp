//
// Created by 17804 on 2022/10/18.
//
#include "../../include/CStyle/Util.h"
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

namespace Algorithm {

    void copy(char *from,char *to,size_t size){
        for (size_t i=0;i<size;i++){
            *to=*from;
            from++;
            to++;
        }
    }

    //填充数据，将一个类型指针的数据填充到另一个类型指针
    void fill(char *from,char *to,size_t size,void (* Copy)(char *,char *,size_t)){
        Copy(from,to,size);
    }

    int * random_int_array(int size, int start, int end) {
        auto *array=new int[size];
        for (int i = 0; i <size ; ++i) {
            array[i]=(rand()%(end-start)+start);
        }
        return array;
    }

    char *getArrayElement(void *array, int index, int size)
    {
        return (char *)array+index*size;
    }

    void swap(void *q, void *p, size_t t_size, void (*Copy)(char *, char *, size_t)){
        void *tmp=malloc(t_size);
        fill((char *)q,(char *)tmp,t_size,Copy); //*tmp=*q
        fill((char *)p,(char *)q,t_size,Copy); //*q=*p
        fill((char *)tmp,(char *)p,t_size,Copy); //*p=*tmp
    }

    void reverseArray(void *array, int start, int end, size_t t_size,void (*Copy)(char *, char *, size_t)){
        for (int i=0; i<(end-start+1)/2; i++) {
            //i=[0,mid-1], should be inclusive, for instance: an array with indexes range [0,4],so you need to swap (0,4),(1,3), (4-0+1)/2=2, 2 is middle one which is not reachable by i
            //in this way, array like [1,4,5,6] would be reversed in this sequence:---->
            //[6,4,5,1]=>[6,5,4,1]
            swap(getArrayElement(array,start+i,t_size),getArrayElement(array,end-i,t_size),t_size,Copy); //swap array[start+i] and array[end-i]
        }
    }
    
}

