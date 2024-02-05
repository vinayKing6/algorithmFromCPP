#include <iostream>
#include <algorithm>

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

        

    }
}