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
            while (i<S.length() && j<P.length())
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
    }
}
