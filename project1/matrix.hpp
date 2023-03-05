#pragma once

#include <iostream>

class Matrix
{
private:
    int rows;
    int cols;
    float *data;

public:
    Matrix();
    Matrix(int rows, int cols);
    ~Matrix();

    float *getdata();
    int getrows();
    int getcols();

    Matrix &operator=(const Matrix &mat);
    friend std::ostream &operator<<(std::ostream &os, const Matrix &mat);
};
