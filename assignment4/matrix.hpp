#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>

class Matrix
{
    private:
        int rows;
        int cols;
        float *data;
        static char count;

    public:
        Matrix()
        {
            rows = 0;
            cols = 0;
            data = nullptr;
        }
        Matrix(int rows, int cols)
        {
            this->rows = rows;
            this->cols = cols;
            this->data = new float[rows * cols]{0};
            count++;
            std::cout << "Matrix " << count << " is created!" << std::endl;
        }
        ~Matrix()
        {
            std::cout << "Matrix " << count << " is deleted!" << std::endl;
            count--;
            delete[] data;
        }

        int getrows() const;
        int getcols() const;
        float * getdata() const;


        Matrix &operator=(const Matrix &mat);       
        friend std::ostream &operator<<(std::ostream &os, const Matrix &mat);
        friend std::istream &operator>>(std::istream &is, Matrix &mat);
        Matrix operator*(const Matrix &mat) const;
        friend Matrix operator*(const Matrix &mat, int x);
        friend Matrix operator*(int x, const Matrix &mat);
};

#endif