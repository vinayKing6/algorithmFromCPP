#include "../include/CStyle/String.h"
#include <iostream>
#include <ostream>
#include <string>

using namespace Algorithm;

namespace TEST {
    void TestKMP()
    {
        // std::cout<<STR::KMP("ababcabcacbab", "abcac")<<std::endl;
        // std::cout<<STR::KMP("ababcabcacbab", "aaaab")<<std::endl;
        // std::cout<<STR::KMP("ababcabcacbab", "ababaaababaa")<<std::endl;
        std::cout<<STR::KMP("abaabaabacacaabaabcc", "abaabc")<<std::endl;
    }
}

