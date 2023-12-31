#include <iostream>
#include <string>
#include <vector>

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
        /**
         * string spilt Algorithm
         */
        void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c);
    }
}
