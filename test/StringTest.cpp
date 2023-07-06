#include "../include/CStyle/String.h"
#include <iostream>
#include <ostream>
#include <string>

using namespace Algorithm;

namespace TEST {
    void TestKMP()
    {
        // std::cout<<SM::KMP("ababcabcacbab", "abcac")<<std::endl;
        // std::cout<<SM::KMP("ababcabcacbab", "aaaab")<<std::endl;
        // std::cout<<SM::KMP("ababcabcacbab", "ababaaababaa")<<std::endl;
        std::cout<<SM::KMP("abaabaabacacaabaabcc", "abaabc")<<std::endl;
    }
}

