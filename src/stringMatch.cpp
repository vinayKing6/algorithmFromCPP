#include <string>
#include <iostream>

int bruteForce(std::string T, std::string P){
    for (int i=0; i<=T.length()-P.length();i++)
    {
        int j=0;
        for (; j<P.length();j++)
        {
            if (P[j]!=T[i+j]) {
                break;
            }
        }
        if (j==P.length()) {
            return i;
        }
    }
    return -1;
}

// int main(){
//     std::string s1="fuck you";
//     std::string s2="fuck";
//     std::string s3="fuckit";
//     std::string s4="you";
//     std::string s5="ck";
//     std::string s6="ou";
//     std::cout<<bruteForce(s1, s2);
//     std::cout<<bruteForce(s1, s3);
//     std::cout<<bruteForce(s1, s4);
//     std::cout<<bruteForce(s1, s5);
//     std::cout<<bruteForce(s1, s6);
// }
