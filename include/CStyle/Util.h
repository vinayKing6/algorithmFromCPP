//
// Created by 17804 on 2022/10/18.
//

#ifndef ALGORITHM_UTIL_H
#define ALGORITHM_UTIL_H
#include <cstddef>
#include <vector>
#include <unordered_map>

namespace Algorithm{
    class data{
        public:
            static std::unordered_map<char, int> OP;

        data()
        {
            OP['-']=1;
            OP['+']=1;
            OP['*']=2;
            OP['/']=2;
        }

    };
   


    int *random_int_array(int size,int start,int end);

    void copy(char *from,char *to,size_t size);

    /**
     * 填充数据,可以看成to=from,但是对所有类型都适用,如有需要,可以自定义赋值函数Copy
     */
    void fill(char *from,char *to,size_t size,void (* Copy)(char *,char *,size_t));

    char *getArrayElement(void *array,int index,int size); //从数组中取下标为index的元素,需要传入数据类型的大小,相当于array[index],但是泛型

    void swap(void *q,void *p,size_t t_size,void (* Copy)(char *,char *,size_t));//交换q,p的值
    
    void reverseArray(void *array,int start,int end,size_t t_size,void (*Copy)(char *, char *, size_t)); //逆置一个数组例如[1,2,4]=>[4,2,1]

}


#endif //ALGORITHM_UTIL_H
