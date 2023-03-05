#include <iostream>
#include <chrono>
#include <immintrin.h>
#include <omp.h>
#include "matrix.hpp"

#define TIME_START start = std::chrono::steady_clock::now();
#define TIME_END(NAME)                                                                     \
    end = std::chrono::steady_clock::now();                                                \
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); \
    std::cout << (NAME) << "=" << duration << "ms" << std::endl;

Matrix SIMD(Matrix mat1, Matrix mat2);

int main()
{
    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    auto duration = 0L;

    int A_rows, A_cols, B_rows, B_cols;

    std::cout << "setting A_rows:";
    std::cin >> A_rows;
    std::cout << "setting A_cols:";
    std::cin >> A_cols;

    Matrix A(A_rows, A_cols);

    std::cout << "setting B_rows:";
    std::cin >> B_rows;
    std::cout << "setting B_cols:";
    std::cin >> B_cols;

    Matrix B(B_rows, B_cols);

    TIME_START
    Matrix C = SIMD(A, B);
    TIME_END("Time of use:")

    std::cout<<C;
    return 0;
}

// 普通SIMD
/* Matrix SIMD(Matrix mat1, Matrix mat2)
{
    if (mat1.getcols() != mat2.getrows())
    {
        std::cerr << "Error: Cannot multiply matrices with dimensions "
                  << mat1.getrows() << "x" << mat1.getcols() << " and "
                  << mat2.getrows() << "x" << mat2.getcols() << std::endl;
        return Matrix();
    }

    float *mat1_data = mat1.getdata();
    float *mat2_data = mat2.getdata();
    __m256 mat1_num, mat2_num, temp;
    __m256 sum = _mm256_setzero_ps();

    Matrix output(mat1.getrows(), mat2.getcols());

    for (size_t i = 0; i < mat1.getrows(); i++)
    {
        for (size_t j = 0; j < mat2.getcols(); j += 8)
        {
            sum = _mm256_setzero_ps();
            for (size_t k = 0; k < mat1.getcols(); k += 8)
            {
                mat1_num = _mm256_load_ps(&mat1_data[i * mat1.getcols() + k]);
                mat2_num = _mm256_load_ps(&mat2_data[k * mat2.getcols() + j]);
                temp = _mm256_mul_ps(mat1_num, mat2_num);
                sum = _mm256_add_ps(sum, temp);
            }
            _mm256_store_ps(&output.getdata()[i * output.getcols() + j], sum);
        }
    }
    return output;
}  */

// SIMD细节优化
/* Matrix SIMD(Matrix mat1, Matrix mat2)
{
    if (mat1.getcols() != mat2.getrows())
    {
        std::cerr << "Error: Cannot multiply matrices with dimensions "
                  << mat1.getrows() << "x" << mat1.getcols() << " and "
                  << mat2.getrows() << "x" << mat2.getcols() << std::endl;
        return Matrix();
    }

    float *mat1_data = mat1.getdata();
    float *mat2_data = mat2.getdata();
    __m256 mat1_num, mat2_num, temp;
    __m256 sum = _mm256_setzero_ps();

    Matrix output(mat1.getrows(), mat2.getcols());

    for (size_t i = 0; i < mat1.getrows(); i++)
    {
        for (size_t j = 0; j < mat2.getcols(); j += 16)
        {
            sum = _mm256_setzero_ps();
            for (size_t k = 0; k < mat1.getcols(); k += 16)
            {
                for (size_t l = 0; l < 16; l += 8)
                {
                    mat1_num = _mm256_load_ps(&mat1_data[i * mat1.getcols() + k + l]);
                    for (size_t m = 0; m < 16; m += 8)
                    {
                        mat2_num = _mm256_load_ps(&mat2_data[(k + l) * mat2.getcols() + j + m]);
                        temp = _mm256_mul_ps(mat1_num, mat2_num);
                        sum = _mm256_add_ps(sum, temp);
                    }
                }
            }
            _mm256_store_ps(&output.getdata()[i * output.getcols() + j], sum);
        }
    }
    return output;
} */

// SIMD+OpenMP
Matrix SIMD(Matrix mat1, Matrix mat2)
{
    if (mat1.getcols() != mat2.getrows())
    {
        std::cerr << "Error: Cannot multiply matrices with dimensions "
                  << mat1.getrows() << "x" << mat1.getcols() << " and "
                  << mat2.getrows() << "x" << mat2.getcols() << std::endl;
        return Matrix();
    }

    float *mat1_data = mat1.getdata();
    float *mat2_data = mat2.getdata();
    __m256 mat1_num, mat2_num, temp;
    __m256 sum = _mm256_setzero_ps();

    Matrix output(mat1.getrows(), mat2.getcols());

#pragma omp parallel for schedule(auto) private(mat1_num, mat2_num, temp, sum)

    for (size_t i = 0; i < mat1.getrows(); i++)
    {
        for (size_t j = 0; j < mat2.getcols(); j += 16)
        {
            sum = _mm256_setzero_ps();
            for (size_t k = 0; k < mat1.getcols(); k += 16)
            {
                for (size_t l = 0; l < 16; l += 8)
                {
                    mat1_num = _mm256_load_ps(&mat1_data[i * mat1.getcols() + k + l]);
                    for (size_t m = 0; m < 16; m += 8)
                    {
                        mat2_num = _mm256_load_ps(&mat2_data[(k + l) * mat2.getcols() + j + m]);
                        temp = _mm256_mul_ps(mat1_num, mat2_num);
                        sum = _mm256_add_ps(sum, temp);
                    }
                }
            }
            _mm256_store_ps(&output.getdata()[i * output.getcols() + j], sum);
        }
    }
    return output;
}
