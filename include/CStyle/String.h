#include <iostream>
#include <string>

namespace Algorithm {

    namespace SM {
        //string matching Algorithm

        /**
         * KMP 算法的getNextVal
         *
         */
        void getNextVal(std::string P,int nextVal[]);

        /**
         * KMP string matching Algorithm
         */
        int KMP(std::string S, std::string P);
    }
}
