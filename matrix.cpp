#include "matrix.hpp"

char Matrix::count = 'A' - 1;

int Matrix::getrows() const
{
    return this->rows;
}
int Matrix::getcols() const
{
    return this->cols;
}
float *Matrix::getdata() const
{
    return this->data;
}

Matrix &Matrix::operator=(const Matrix &mat)
{
    if (this == (&mat))
    {
        return *this;
    }

    this->rows = mat.rows;
    cols = mat.cols;
    data = mat.data;
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Matrix &mat)
{
    for (int i = 0; i < mat.getrows(); i++)
    {
        for (int j = 0; j < mat.getcols(); j++)
        {
            os << mat.getdata()[i * mat.getcols() + j] << " ";
        }
        os << std::endl;
    }
    return os;
}

Matrix Matrix::operator*(const Matrix &mat) const
{
    if (cols != mat.rows)
    {
        std::cerr << "Error: Cannot multiply matrices with dimensions "
                  << rows << "x" << cols << " and "
                  << mat.rows << "x" << mat.cols << std::endl;
        return Matrix();
    }

    Matrix result(rows, mat.cols);

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < mat.cols; ++j)
        {
            float sum = 0.0;
            for (int k = 0; k < cols; ++k)
            {
                sum += data[i * cols + k] * mat.data[k * mat.cols + j];
            }
            result.data[i * mat.cols + j] = sum;
        }
    }
    return result;
}

std::istream &operator>>(std::istream &is, Matrix &mat)
{
    for (int i = 0; i < mat.rows; i++)
    {
        for (int j = 0; j < mat.cols; j++)
        {
            is >> mat.data[i * mat.cols + j];
        }
    }
    return is;
}

Matrix operator*(const Matrix &mat, int x)
{
    Matrix result(mat.rows, mat.cols); 
    for (int i = 0; i < mat.rows; i++)
    {
        for (int j = 0; j < mat.cols; j++)
        {
            result.data[i * mat.cols + j] = mat.data[i * mat.cols + j] * x; 
        }
    }
    return result; 
}

Matrix operator*(int x, const Matrix &mat)
{
    Matrix result(mat.rows, mat.cols); 
    for (int i = 0; i < mat.rows; i++)
    {
        for (int j = 0; j < mat.cols; j++)
        {
            result.data[i * mat.cols + j] = mat.data[i * mat.cols + j] * x; 
        }
    }
    return result; 
}

