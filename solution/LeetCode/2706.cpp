#include <cstdint>
#include <ostream>
#include <string>
#include <iostream>
#include <vector>

namespace SOLUTION {

    namespace LC {

        class _2706{
            public:
                int buyChoco(std::vector<int>& prices, int money) {
                    int fi = INT32_MAX, se =INT32_MAX;
                    for (auto p : prices) {
                        if (p < fi) {
                            //这是官方解答，当时这里不太懂，然后调试了一下发现这段已经默认first<second了，所以递推法得到first<scond一定成立
                            se = fi;
                            fi = p;
                        } else if (p < se) {
                            se = p;
                        }
                    }
                    return money < fi + se ? money : money - fi - se;
                }

                void test(){
                    std::vector<int> example={98,54,15,34,33,63,52,39};
                    std::cout<<buyChoco(example, 62)<<std::endl;
                }
        };

    }
}
