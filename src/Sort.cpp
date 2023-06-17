//
// Created by vinay on 2022/10/8.
//
#include "../include/Sort.h"
#include <iostream>
using namespace std;

namespace Algorithm{
    void test(){
        cout<<"shit it"<<std::endl;
    }

    /**
         *
         * @tparam T
         * @param array
         * @param size
         */
        template <typename T>
        void Insert_Sort(T *array,int size){
            for (int i = 1; i < size; ++i) {
                T key=array[i];
                int j=i-1;
                while (j>=0&&array[j]>key){
                    array[j+1]=array[j];
                    j--; //you can not write inside [] like array[j--], i have no idea
                }
                array[j+1]=key;
            }
        }
}
