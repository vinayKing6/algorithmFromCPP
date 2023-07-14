//
// Created by vinay on 23-7-14.
//
#include <iostream>
#include <algorithm>

namespace SOLUTION{
    class B1025{
        /**
         * PAT B1025 反转链表
         */
    public:
        const static int maxn=10010;

        struct Node{
            int address,data,next;
            int order;
        };
        Node node[maxn];

        static bool cmp(Node a, Node b){
            return a.order<b.order;
        }

        void solution(){
            for (int i = 0; i < maxn ; ++i) {
                node[i].order=maxn;
            }
            int begin, n, K, address;
            scanf("%d%d%d",&begin,&n,&K); //起始地址，结点个数，步长
            for (int j = 0; j < n ; ++j) {
                scanf("%d",&address);
                scanf("%d%d",&node[address].data,&node[address].next);
                node[address].address=address;
            }
            int p=begin,count=0;
            while (p!=-1){
                node[p].order=count++;
                p=node[p].next;
            }
            std::sort(node,node+maxn,cmp); //按照order排序
            n=count;
            //反转
            for (int i = 0; i < n/K ; ++i) {
                for (int j = (i+1)*K-1; j >i*K ; j--) {
                    printf("%05d %d %05d\n",node[j].address,node[j].data,node[j-1].address); //从每一块的最后一个元素开始输出
                }
                printf("%05d %d",node[i*K].address,node[i*K].data);
                if (i<n/K-1){
                    printf("%05d",node[(i+2)*K-1].address);
                } else{ //是最后一块
                    if (n%K==0){
                        printf("-1\n"); //恰好是最后一块
                    } else{
                        printf("%05d\n",node[(i+1)*K].address);
                        for (int j = n/K*K; j < n ; ++j) {
                            printf("%05d %d ",node[j].address,node[j].data);
                            if (i<n-1){
                                printf("%05d\n",node[j+1].address);
                            } else{
                                printf("-1\n");
                            }

                        }
                    }
                }

            }

        }

    };
}
