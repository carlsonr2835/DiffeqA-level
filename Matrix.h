#include "Matrix.h"
#ifndef MATRIX_H
#define MATRIX_H

template <typename T>
class Matrix {
    public:
        Matrix();
        //Matrix(const Matrix<T>& OTHER);
        //Matrix& operator=(const Matrix<T>& OTHER);
        //~Matrix();
        T getx1();
        T getx2();
        T gety1();
        T gety2();
        void setValues(T X1, T X2, T Y1, T Y2);
        

    private:
        T x1;
        T x2;
        T y1;
        T y2;
}




#endif