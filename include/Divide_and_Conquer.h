//
// Created by vinay on 22-10-29.
//
#include <iostream>

#ifndef ALGORITHM_DIVIDE_AND_CONQUER_H
#define ALGORITHM_DIVIDE_AND_CONQUER_H

namespace Algorithm{

    template <class T>
    class Matrix2D{
    public:
        Matrix2D(int row,int column,int offset=0){
            this->values=(T *)malloc(sizeof(T)*(row*column));
            this->shape=(int *)malloc(sizeof(int)*2);
            this->shape[0]=row;
            this->shape[1]=column;
            this->size=row*column;
            this->offset=offset;
        }

        Matrix2D(int row,int column,int offset,int *values){
            this->values=values;
            this->shape=(int *)malloc(sizeof(int)*2);
            this->shape[0]=row;
            this->shape[1]=column;
            this->size=row*column;
            this->offset=offset;
        }

        template <int N>
        void fill(T from[][N]){
            for (int i = 0; i < shape[0]; ++i) {
                for (int j = 0; j < shape[1]; ++j) {
                    values[i*shape[1]+j]=from[i][j];
                }
            }
        }

        /**
         *
         * @param startRow
         * @param endRow
         * @param startCol
         * @param endCol
         * @return
         * endRow and endCol are not included
         */
        Matrix2D<T> SubMatrix(int startRow,int endRow,int startCol,int endCol){
            if(endCol>shape[1]||endRow>shape[0]||startRow>endRow||startCol>endCol){
                std::cout<<"the shape input does not match correctly!!!"<<std::endl;
                return *this;
            }
            int current=index(startRow,startCol);
            int *start=this->values+current;
            int rows=endRow-startRow;
            int cols=endCol-startCol;
            int offset_tmp=(this->shape[1]-cols)+offset;
            return Matrix2D<T>(rows,cols,offset_tmp,start);
        }

        T &at(int i,int j){
            return values[i*(shape[1]+offset)+j];
        }

        int index(int i,int j){
            return i*(shape[1]+offset)+j;
        }

        void show(){
            for (int i = 0; i < shape[0]; ++i) {
                std::cout<<"[ ";
                for (int j = 0; j < shape[1]; ++j) {
                    std::cout<<at(i,j)<<" ";
                }
                std::cout<<"]"<<std::endl;
            }
        }

        void zeros(){
            for (int i = 0; i < size; ++i) {
                values[i]=0;
            }
        }

        int offset;
        int size;
        int *shape;
        T *values;
    };

    /**
    *
    * @tparam T
    * @param A
    * @param B
    * @param C
    * @param n
    */
    template <typename T>
    void Square_Matrix_Multiply_Origin(Matrix2D<T> &A,Matrix2D<T> &B,Matrix2D<T> &C){
        int n=A.shape[0];
        for(int i=0;i<n;i++) // row iteration
            for(int j=0;j<n;j++) // column iteration
                for (int k = 0; k < n; k++) {
                    // specify A row and iter its columns while specifying B column and iter its rows
                    C.at(i,j)=C.at(i,j)+A.at(i,k)*B.at(k,j); // store results into C matrix , element-wise
                }
    }

    /**
     *
     * @tparam T
     * @param A
     * @param B
     * @param C
     * @param n
     */
    template <typename T>
    void Square_Matrix_Multiply_Recurse_values(T *A,T *B,T *C,int n,int last_n){
        if(n==1){
            C[0]=C[0]+A[0]*B[0];
            return;
        }

        //divide
        int size=n/2;
        T *A_11=A; // A[1][1]
        T *A_12=A_11+size; // A[1][2]
        T *A_21=A+size*size*2+size*last_n; // A[2][1]
        T *A_22=A_21+size; /// A[2][2]

        T *B_11=B; // B[1][1]
        T *B_12=B_11+size; // B[1][2]
        T *B_21=B+size*size*2+size*last_n; // B[2][1]
        T *B_22=B_21+size; /// B[2][2]

        T *C_11=C; // C[1][1]
        T *C_12=C_11+size; // C[1][2]
        T *C_21=C+size*size*2+size*last_n; // C[2][1]
        T *C_22=C_21+size; /// C[2][2]

        Square_Matrix_Multiply_Recurse_values(A_11,B_11,C_11,size,size+last_n);
        Square_Matrix_Multiply_Recurse_values(A_11,B_12,C_12,size,size+last_n);
        Square_Matrix_Multiply_Recurse_values(A_21,B_11,C_21,size,size+last_n);
        Square_Matrix_Multiply_Recurse_values(A_21,B_12,C_22,size,size+last_n);
        Square_Matrix_Multiply_Recurse_values(A_12,B_21,C_11,size,size+last_n);
        Square_Matrix_Multiply_Recurse_values(A_12,B_22,C_12,size,size+last_n);
        Square_Matrix_Multiply_Recurse_values(A_22,B_21,C_21,size,size+last_n);
        Square_Matrix_Multiply_Recurse_values(A_22,B_22,C_22,size,size+last_n);
    }

    template <typename T>
    void Square_Matrix_Multiply_Recurse_values_(Matrix2D<T> &A,Matrix2D<T> &B,Matrix2D<T> &C){
        int n=A.shape[0];

        if(n==1){
            C.at(0,0)=C.at(0,0)+A.at(0,0)*B.at(0,0);
            return;
        } else if (n<=0){
            return;
        }

        //divide
        int size=n/2;
        Matrix2D<T> A_11=A.SubMatrix(0,size,0,size); // A[1][1]
        Matrix2D<T> A_12=A.SubMatrix(0,size,size,A.shape[1]); // A[1][2]
        Matrix2D<T> A_21=A.SubMatrix(size,A.shape[0],0,size); // A[2][1]
        Matrix2D<T> A_22=A.SubMatrix(size,A.shape[0],size,A.shape[1]); /// A[2][2]

        Matrix2D<T> B_11=B.SubMatrix(0,size,0,size); // B[1][1]
        Matrix2D<T> B_12=B.SubMatrix(0,size,size,B.shape[1]); // B[1][2]
        Matrix2D<T> B_21=B.SubMatrix(size,B.shape[0],0,size); // B[2][1]
        Matrix2D<T> B_22=B.SubMatrix(size,B.shape[0],size,B.shape[1]); /// B[2][2]

        Matrix2D<T> C_11=C.SubMatrix(0,size,0,size); // C[1][1]
        Matrix2D<T> C_12=C.SubMatrix(0,size,size,C.shape[1]); // C[1][2]
        Matrix2D<T> C_21=C.SubMatrix(size,C.shape[0],0,size); // C[2][1]
        Matrix2D<T> C_22=C.SubMatrix(size,C.shape[0],size,C.shape[1]); /// C[2][2]

        Square_Matrix_Multiply_Recurse_values_(A_11,B_11,C_11);
        Square_Matrix_Multiply_Recurse_values_(A_11,B_12,C_12);
        Square_Matrix_Multiply_Recurse_values_(A_21,B_11,C_21);
        Square_Matrix_Multiply_Recurse_values_(A_21,B_12,C_22);
        Square_Matrix_Multiply_Recurse_values_(A_12,B_21,C_11);
        Square_Matrix_Multiply_Recurse_values_(A_12,B_22,C_12);
        Square_Matrix_Multiply_Recurse_values_(A_22,B_21,C_21);
        Square_Matrix_Multiply_Recurse_values_(A_22,B_22,C_22);


    }

    /**
     *
     * @tparam T
     * @param A
     * @param B
     * @param C
     */
    template <typename T>
    void Square_Matrix_Multiply_Recurse(Matrix2D<T> &A,Matrix2D<T> &B,Matrix2D<T> &C){
        int n=A.shape[0];
        Square_Matrix_Multiply_Recurse_values(A.values,B.values,C.values,n,0);
    }

}


#endif //ALGORITHM_DIVIDE_AND_CONQUER_H

