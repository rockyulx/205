#include "matrix.hpp"

float *Matrix::getdata()
{
    return this->data;
}

int Matrix::getcols()
{
    return this->cols;
}
int Matrix::getrows()
{
    return this->rows;
}

Matrix::Matrix() : rows(0), cols(0), data(nullptr)
{
    ;
}

Matrix::Matrix(int rows, int cols)
{
    this->rows = rows;
    this->cols = cols;
    this->data = new float[rows * cols]{0};
}

Matrix::~Matrix()
{
    delete[] data;
}

std::ostream &operator<<(std::ostream &os, const Matrix &mat)
{
    for (int i = 0; i < mat.rows; i++)
    {
        for (int j = 0; j < mat.cols; j++)
        {
            os << mat.data[i * mat.cols + j] << " ";
        }
        os << std::endl;
    }
    return os;
}

Matrix &Matrix::operator=(const Matrix &mat)
{
    if (this == (&mat))
    {
        return *this;
    }

    this->rows = mat.rows;
    this->cols = mat.cols;
    this->data = mat.data;
    return *this;
}
