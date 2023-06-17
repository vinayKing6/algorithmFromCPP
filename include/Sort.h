//
// Created by vinay on 2022/10/8.
//

#ifndef ALGORITHM_SORT_H
#define ALGORITHM_SORT_H
#include <iostream>
#include <vector>
namespace Algorithm{

    /**
     *
     * @tparam T
     * @param array
     * @param size
     */
    template <typename T>
    void Insert_Sort(T *array,int size);

    /**
     *
     * @tparam T
     * @param array :array to be merged
     * @param p :start of interval of array which can be indexed
     * @param q :midpoint between p and r
     * @param r :end of interval of array which can be indexed
     * the elements between p and q should be in order as well as q+1 and r
     */
    template <typename T>
    void Merge(T *array,const int p,const int q,int r){
        const int Nl=q-p+1; //length of array[p:q] note that both p,q is included in array
        const int Nr=r-q; //length of array[q+1:r]
        T L[Nl]; //create left array equal to array[p:q]
        T R[Nr]; //create right array equal to array[q+1,r]

        //copy array[p:q] into L[0:Nl-1]
        for (int i = 0; i < Nl; ++i) {
            L[i]=array[p+i];
        }
        //copy array[q+1:r] into R[0:Nr-1]
        for (int i = 0; i < Nr; ++i) {
            R[i]=array[q+1+i];
        }

        int i=0; // i indexes the smallest unmerged element of left
        int j=0; // j indexes the smallest unmerged element of right
        int k=p; // k indexes the current element of array being filled in
        /**
         * As long as either left or right has element unmerged,
         * copy the smallest element unmerged back into array
         */
        while (i<Nl && j<Nr){
            if (L[i]<R[j]){
                array[k++]=L[i++];
            } else{
                array[k++]=R[j++];
            }
        }
        //copy the remainder of left or right into array, noted that both only one of the have remainder
        while (i<Nl){
            array[k++]=L[i++];
        }
        while (j<Nr){
            array[k++]=R[j++];
        }
    }

    /**
     *
     * @tparam T
     * @param array
     * @param p
     * @param q
     * @param r
     */
    template <typename T>
    void Merge_Sort_Recurse(T *array,int p,int r){
        if(p>=r)
            return;
        int midPoint=p+(r-p)/2;
        Merge_Sort_Recurse(array,p,midPoint);
        Merge_Sort_Recurse(array,midPoint+1,r);
        Merge(array,p,midPoint,r);
    }

    /**
     *
     * @tparam T
     * @param array
     * @param size
     */
    template <typename T>
    void Merge_Sort(T *array,int size){
        Merge_Sort_Recurse(array,0,size-1);
    }

    template <typename T>
    bool is_sorted(T *array,int size){
        for (int i = 1; i <size ; ++i) {
            if (array[i]<array[i-1])
                return false;
        }
        return true;
    }

    inline void test();
}


#endif //ALGORITHM_SORT_H
