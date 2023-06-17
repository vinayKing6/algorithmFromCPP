#include "../include/CStyle/Stack.h"
#include "../include/CStyle/Util.h"
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>

using namespace Algorithm;


namespace TEST {
    struct STU{
        public:
            int num;
            std::string name; //最好使用char *，否则会出现不知名问题，详情见TestLinkedStack
            // const char *name;
            STU(int num,const char *name){
                this->num=num;
                this->name=name;
            }

            STU(){
            }

            std::string getName(){
                return this->name;
            }
    };
    void copy_test(char *from,char *to,size_t size){
        std::cout<<"arraystack test copy\n";
        Algorithm::copy(from,to,size);
    }

    void copyForString(char *from,char *to,size_t size){
        std::string *s_from=(std::string *)from;
        std::string *s_to=(std::string *)to;
        *s_to=*s_from;
    }

    void copyForStu(char *from, char *to, size_t size){
        TEST::STU *s_from=(TEST::STU *)from;
        TEST::STU *s_to=(TEST::STU *)to;
        *s_to=*s_from;
    }

    void TestArrayStack(){
        //测试顺序栈

        //初始化栈
        AS::ArrayStack s;
        int capacity=10;
        int t_size=sizeof(int);
        AS::InitArrayStack(s,capacity,t_size);
        s.CopyFunc=copy_test;

        //存储整型元素
        int *array=random_int_array(capacity,1,10);
        //测试push和pop,打印
        for (int i=0;i<capacity;i++) {
            AS::push(s,getArrayElement(array,i,t_size));
            std::cout<<array[i]<<" ";
        }

        //测试top和pop
        int r,top;
        AS::pop(s,&r);
        std::cout<<std::endl<<r;
        AS::top(s,&top);
        std::cout<<std::endl<<top;

        //存储字符串元素 ,修改&string时出错,故使用char *
        AS::ArrayStack s_str;
        t_size=sizeof(char *);
        AS::InitArrayStack(s_str,capacity,t_size);
        char s1[]="hello world";
        char s2[]="fuck you";
        char s3[]="damn";
        char *str[]={s1,s2,s3};

        for(int i=0;i<3;i++){
            AS::push(s_str, getArrayElement(str,i, t_size));
        }

        const char *rs,*tops;
        AS::pop(s_str,&rs);
        std::cout<<std::endl<<rs;
        AS::top(s_str,&tops);
        std::cout<<std::endl<<tops;

        //存储double类型
        AS::ArrayStack s_d;
        t_size=sizeof(s_d);
        AS::InitArrayStack(s_d,capacity,t_size);
        double d[]={1.2,3.4,3.90};
        for(int i=0;i<3;i++){
            AS::push(s_d, d+i);
        }

        double d1,d2;
        AS::pop(s_d,&d1);
        std::cout<<"\n"<<d1;
    }

    void TestLinkedStack(){
        //测试顺序栈

        //初始化栈
        LS::LinkedStack s;
        int capacity=10;
        int t_size=sizeof(int);
        LS::InitLinkedStack(s,t_size);

        //存储整型元素
        std::cout<<"\n---------------int test";
        int *array=random_int_array(capacity,1,10);
        //测试push和pop,打印
        for (int i=0;i<capacity;i++) {
            LS::push(s,array+i);
            std::cout<<array[i]<<" ";
        }

        //测试top和pop
        int r,top;
        LS::pop(s,&r);
        std::cout<<std::endl<<r;
        LS::top(s,&top);
        std::cout<<std::endl<<top;

        //存储字符串元素 ,修改&string时出错,故使用char *
        std::cout<<"\n---------------char * test";
        LS::LinkedStack s_str;
        t_size=sizeof(char *);
        LS::InitLinkedStack(s_str,t_size);
        char s1[]="hello world";
        char s2[]="fuck you";
        char s3[]="damn";
        const char *str[]={s1,s2,s3};

        for(int i=0;i<3;i++){
            LS::push(s_str, str+i);
        }

        str[2]="shit";
        std::cout<<std::endl<<str[2];

        const char *rs,*tops;
        LS::pop(s_str,&rs);
        std::cout<<std::endl<<rs;
        LS::top(s_str,&tops);
        std::cout<<std::endl<<tops;
        std::cout<<std::endl<<s_str.length;

        //存储字符串元素 ,修改&string时出错,但我想到了一个方法,不能直接初始化string并传入string的地址修改string的数据，这样会产生错误
        std::cout<<"\n---------------string test";
        LS::LinkedStack s_string;
        t_size=sizeof(std::string);
        s_string.CopyFunc=copyForString;
        LS::InitLinkedStack(s_string,t_size,copyForString);
        std::string strings[]={"niko","vinay","maike","bingo ss"};

        for(int i=0;i<4;i++){
            LS::push(s_string, strings+i);
        }
        //
        std::string rstr,topstr;
        // rstr=(std::string *)malloc(t_size);
        // topstr=(std::string *)malloc(t_size);
        LS::pop(s_string,&rstr); //似乎是操作指针内存空间导致的 //已找到解决方法：需要把copy函数自定义，其中必须将原指针转换成string *,然后*to=*from,也就是说由编译器决定如何操作内存
        std::cout<<std::endl<<(rstr);
        LS::top(s_string,&topstr);
        std::cout<<std::endl<<(topstr);
        std::cout<<std::endl<<s_string.length;

        //存储double类型
        std::cout<<"\n--------------double test";
        LS::LinkedStack s_d;
        t_size=sizeof(s_d);
        LS::InitLinkedStack(s_d,t_size);
        double d[]={1.2,3.4,3.90};
        for(int i=0;i<3;i++){
            LS::push(s_d, d+i);
        }

        double d1,d2;
        LS::pop(s_d,&d1);
        std::cout<<"\n"<<d1;

        //测试类
        std::cout<<"\n--------------class test";
        STU stus[]={STU(1,"vinay"),STU(2,"king"),STU(3,"jack")};
        LS::LinkedStack s_stu;
        t_size=sizeof(STU);
        LS::InitLinkedStack(s_stu,t_size,copyForStu);
        for (int i=0;i<3;i++){
            LS::push(s_stu,stus+i);
        }
        stus[2].name="mmmmmmmmmmm"; //如果修改，会改变栈里存储的stu.name,我猜测可能是赋值内存空间时,string里面的char *只赋值了地址,然而栈里的string仍然保持长度不变,可能只改变了char *里的值 //已找到解决方法,就是传入copyForSTU
        stus[2].num=5;//不会改变栈里面的num，因为本身按照设定就是新开辟的内存存储原先的数据，但是string由于跟原始据存储的是相同的char *地址罢了，太奇妙了啦

        STU stu1,stu2;
        LS::pop(s_stu,&stu1);
        std::cout<<std::endl<<stu1.name;
        std::cout<<std::endl<<stu1.num;
        LS::top(s_stu, &stu2);
        std::cout<<std::endl<<stu2.name;
        std::cout<<std::endl<<s_stu.length;

        STU stu3=stu1;
        STU stu4=stu3;
        std::cout<<std::endl<<stu3.name;

        stu3.name="change 3"; //测试改变此时的name,事实证明stu3是独立的,也就是说string本身不会因为赋值操作而相互影响，但是内存赋值会影响 //已找到解决方法,就是传入copyForSTU
        std::cout<<std::endl<<stu3.name;
        std::cout<<std::endl<<stu1.name;
        std::cout<<std::endl<<stus[2].name;
        std::cout<<std::endl<<stu4.name;
        
        stu1.name="llllllll"; //只会影响原数据stus[2]
        std::cout<<std::endl<<stu3.getName();
        std::cout<<std::endl<<stu1.getName();
        std::cout<<std::endl<<stus[2].getName();
        std::cout<<std::endl<<stu4.getName();
    }
}

