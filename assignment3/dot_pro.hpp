#pragma once
#include <immintrin.h>
#include <iostream>
#include <chrono>
#include <omp.h>
#include <ctime>
using namespace std;

void vector_omp(float *, float *, size_t );
void input_vector(float *, float *, size_t);
void input_v1(float *, size_t);
void input_v2(float *, size_t);
void random_numbers(float *, size_t);
bool isNumber(string &);














// float dot_omp_simd(float *, float *, size_t n);
//float dot_simd(float *, float *, size_t n);
//float dot(float *, float *, size_t n);