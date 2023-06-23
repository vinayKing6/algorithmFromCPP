#include <iostream>
#include <stdio.h>
#include <algorithm>

namespace SOLUTION {

    void JB_5_1(){
        /**
         * 算法经典入门 例题5-1 大理石在哪
         */
        const int maxn=1000;
        int n,q,x,a[maxn],kcase=0;
        while (scanf("%d%d",&n,&q)==2 && n) {
            //scanf==2表示正确输入2个变量,n保存数组长度,q表示问题数量
            printf("CASE# %d:\n",++kcase);
            for (int i=0;i<n;i++)
                scanf("%d",a+i);
            std::sort(a,a+n); //排序数组
            while (q--) {
                scanf("%d",&x);
                int p=std::lower_bound(a,a+n,x)-a; //寻找数组中x的下标,lower_bound返回地址
                if (a[p]==x) {
                    printf("%d found at %d\n",x,p+1);
                }else {
                    printf("%d not found\n",x);
                }
            }
        }
    }

    /**
     * 为每一个算法写一个测试用例
     * */

    void TestJB_5_1(){
        JB_5_1();
    }

}
