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
            this->values=new T[row*column];
            this->shape[0]=row;
            this->shape[1]=column;
            this->size=row*column;
            this->offset=offset;
        }

        Matrix2D(int row,int column,int offset,int *values){
            this->values=values;
            this->shape[0]=row;
            this->shape[1]=column;
            this->size=row*column;
            this->offset=offset;
        }

        void fill(std::vector<std::vector<T>> &from){
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

        /**
   *
   * @tparam T
   * @param A
   * @param B
   * @param C
   * @param n
   */
        static void Matrix_Multiply_Origin(Matrix2D<T> &A,Matrix2D<T> &B,Matrix2D<T> &C){
            int p=A.shape[0];
            int q=A.shape[1];
            int r=B.shape[1];//A_pxq B_qxr C_pxr
            for(int i=0;i<p;i++) // 从A的行开始乘
                for(int j=0;j<r;j++) // B的列
                    for (int k = 0; k < q; k++) {
                        // 矩阵相乘 存在C里
                        C.at(i,j)=C.at(i,j)+A.at(i,k)*B.at(k,j); // store results into C matrix , element-wise
                    }
        }

        static void Square_Matrix_Multiply_Recurse_values_(Matrix2D<T> &A,Matrix2D<T> &B,Matrix2D<T> &C){
            //只有偶数行，为什么？？？
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
         * @param A
         * @param B
         * @param C
         */
        static void Multiply(Matrix2D<T> &A,Matrix2D<T> &B,Matrix2D<T> &C){
            if(A.shape[1]!=B.shape[0]) {
                std::cout << "the shape of two matrix are not able to multiply";
                return;
            }
            Matrix_Multiply_Origin(A,B,C);
        }

        static void test(){
            Matrix2D<int> A(3,3);
            std::vector<std::vector<int>> A_values={{1,2,3},{1,2,3},{1,2,3},{1,2,3}};
            A.fill(A_values);
            Matrix2D<int> B(3,3);
            std::vector<std::vector<int>> B_values={{1,2,3},{1,2,3},{1,2,3},{1,2,3}};
            B.fill(B_values);
            Matrix2D<int> C(A.shape[0],B.shape[1]);
            C.zeros();
            Algorithm::Matrix2D<int>::Multiply(A,B,C);
            C.show();
        }

        int offset;
        int size;
        int shape[2];
        T *values;
    };



}


#endif //ALGORITHM_DIVIDE_AND_CONQUER_H

