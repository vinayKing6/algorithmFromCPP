#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>

namespace Algorithm
{

    namespace DP
    {

        class RodCutting
        {
        private:
            /* data */
            int n;       // size of input aka length of rod
            std::vector<int> prices; // prices of each length of rods
            int res;
        public:
            RodCutting(int n, std::vector<int> &prices)
            {
                this->n = n;
                this->prices = prices;
                res=BottomUp();
            }
            // ~RodCutting();

            // top down approach
            int TopDown()
            {
                std::vector<int> auxliar(n+1); // 辅助数组,0-n
                for (int i = 0; i < n + 1; i++)
                {
                    auxliar[i] = -1; // 初始化,price必须大于0
                }
                return TopDownAux(auxliar,prices,n);
            }

            int TopDownAux(std::vector<int> &auxliar, std::vector<int> &preices, int n)
            {
                // 辅助函数,递归实现rod cutting
                if (auxliar[n] >= 0)
                {
                    return auxliar[n]; // 如果对n的最优解以存储
                }
                // 否则计算对n的最优解
                int optimal = -1;
                if (n == 0)
                {
                    optimal = 0; // 长度为0,价格为0
                }
                for (int i = 1; i <= n; i++)
                {
                    optimal = std::max(optimal, prices[i-1] + TopDownAux(auxliar, prices, n - i));//第一段切i长度,prices从0开始代表切第一段
                }
                auxliar[n] = optimal;
                return optimal;
            }

            int BottomUp(){
                //不递归,具体请见CLRS
                std::vector<int> auxliar(n+1,-1);
                auxliar[0]=0;//长度为0肯定价格为0
                for(int i=1;i<=n;i++){
                    for(int j=1;j<=i;j++){
                        auxliar[i]=std::max(auxliar[i],prices[j-1]+auxliar[i-j]);//第一段j不分,第二段分
                    }
                }
                return auxliar[n];
            }

            static void test()
            {
                std::vector<int> prices = {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
                Algorithm::DP::RodCutting rc(4, prices);
            }
        };

        class MatrixChain {
            //动态规划 矩阵链乘法链
            //此算法只实现bottomUp方法,具体请参考算法导论
        private:
            /*data*/
            std::vector<int> p;//矩阵链的维度Ai的维度表示为p[i-1,i],其中i从1开始
            std::vector<std::vector<int>> memory;
            std::vector<std::vector<int>> split;

        public:
            MatrixChain(std::vector<int> &dimensions){
                p=dimensions;
            }

            void Order(){
                //方便起见,m,s均从1开始
                int n=p.size()-1;
                //初始值是最大值
                std::vector<std::vector<int>> m(n+1,std::vector<int>(n+1,std::numeric_limits<int>::max()));//m[i,j]表示Ai~Aj相乘所需最小的开销,请见算法导论
                std::vector<std::vector<int>> s(n+1,std::vector<int>(n+1,0));//s[i,j]表示Ai~Aj相乘所经中间的矩阵,请见算法导论
                //bottom up方法
                //m[i,i]必定是0,即对角线,单个矩阵不用相乘
                for(int i=1;i<=n;i++){
                    m[i][i]=0;
                    s[i][i]=i;
                }
                //从矩阵乘法链长度2开始.直到n
                for(int length=2;length<=n;length++){
                    //由于j-i+1=length,其中i从1开始,因为矩阵下标从1开始,显然这里是先确定矩阵链长度的
                    for(int i=1;i<=n-length+1;i++){//j<=n,所以i<=n-length+1
                        int j=length+i-1;//确定此时矩阵链下界Ai~Aj
                        for(int k=i;k<=j-1;k++){//从Ai~Aj中遍历找分界矩阵
                            int cost=m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];//Ai左维度*Ak右维度*Aj右维度
                            if(cost<m[i][j]){
                                m[i][j]=cost;//存储最优开销
                                s[i][j]=k;//存储最有解中间矩阵
                            }
                        }
                    }
                }
                this->memory=m;
                this->split=s;
            }

            void PrintOptimalParens(int i,int j){
                if(i==j){
                    std::cout<<"A"<<split[i][i];
                } else{
                    std::cout<<"(";
                    PrintOptimalParens(i,split[i][j]);//很明显这是递归树
                    PrintOptimalParens(split[i][j]+1,j);
                    std::cout<<")";
                }
            }

            static void test(){
                std::vector<int> dimensions={30,35,15,5,10,20,25};
                MatrixChain M(dimensions);
                M.Order();
                M.PrintOptimalParens(1,dimensions.size()-1);
            }
        };
        

    }
}
