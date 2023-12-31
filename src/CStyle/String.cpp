#include "../../include/CStyle/String.h"
#include <iostream>
#include <ostream>

using namespace Algorithm;

namespace Algorithm {

    namespace SM {

        void getNextVal(std::string P, int *nextVal)
        {
            int k=-1;
            int j=0;
            nextVal[0]=-1;
            while (j<P.length())
            {
                if (k==-1 || P[j]==P[k]) {
                    ++k;
                    ++j;
                    if (P[j]==P[k]) {
                        nextVal[j]=nextVal[k];
                    }
                    else {
                        nextVal[j]=k;
                    }
                }
                else {
                    k=nextVal[k];
                }
            }
        }

        int KMP(std::string S, std::string P)
        {
            int i=0,j=0;
            int nextVal[P.length()];
            getNextVal(P, nextVal);
            //注意负数与无符号数的比较
            while (i<S.length() && j<int (P.length()))
            {
                if (j==-1 || S[i]==P[j]) {
                    ++i;
                    ++j;
                }
                else {
                    j=nextVal[j];
                }
            }

            std::cout<<j<<std::endl;
            if (j>=int (P.length())) {
                return i-P.length();
            }
            return -1;

        }

        void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c)
        {
            std::string::size_type pos1, pos2;
            pos2 = s.find(c);
            pos1 = 0;
            while(std::string::npos != pos2)
            {
                v.push_back(s.substr(pos1, pos2-pos1));

                pos1 = pos2 + c.size();
                pos2 = s.find(c, pos1);
            }
            if(pos1 != s.length())
                v.push_back(s.substr(pos1));
        }
    }
}
