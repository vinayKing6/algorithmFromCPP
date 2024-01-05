#include<vector>

namespace SOLUTION{

    namespace LC{
        class _509
        //题解跟我的不太一样，但是我这个是按照CLRS动态规划那一章来的
        {
        public:
            int fib(int n)
            {
                std::vector<int> auxliar(n + 1, -1);
                fibAux(auxliar, n);
                return auxliar[n];
            }

            int fibAux(std::vector<int> &auxliar, int n)
            {
                if (auxliar[n] >= 0)
                {
                    return auxliar[n];
                }
                if (n == 0)
                {
                    auxliar[n] = 0;
                }
                else if (n == 1)
                {
                    auxliar[n] = 1;
                }
                else
                {
                    auxliar[n] = fibAux(auxliar, n - 1) + fibAux(auxliar, n - 2);
                }
                return auxliar[n];
            }

            static void test(){
                SOLUTION::LC::_509 Fib;
                int res=Fib.fib(20);
            }
        };
    }

}
