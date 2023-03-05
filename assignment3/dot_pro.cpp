#include "dot_pro.hpp"

#define TIME_START start = chrono::steady_clock::now();
#define TIME_END(NAME)                                                                \
    auto end = chrono::steady_clock::now();                                           \
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count(); \
    cout << (NAME) << "=" << duration << "ms" << endl;

auto start = chrono::steady_clock::now();
auto end = chrono::steady_clock::now();
auto duration = 0L;

void vector_omp(float *v1, float *v2, size_t size)
{
    float sum = 0.0f;
    TIME_START
#pragma omp parallel for reduction(+ \
                                   : sum)
    for (size_t i = 0; i < size; i++)
    {
        sum += v1[i] * v2[i];
    }
    TIME_END("dot_product_time:")
    cout << "result:" << sum << endl;
}

void input_vector(float *v1, float *v2, size_t size)
{
    char choose;
    cout << "do you want to have a random dot?if so, input[Y]:" << endl;
    cin >> choose;
    if (choose == 'Y')
    {
        TIME_START
        random_numbers(v1, size);
        random_numbers(v2, size);
        TIME_END("random_time:")
    }
    else
    {
        input_v1(v1, size);
        input_v2(v2, size);
    }
}

bool isNumber(string &str)
{
    for (char c : str)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }
    return true;
}

void input_v1(float *v1, size_t size)
{
    string s;
    for (int i = 0; i < size; i++)
    {
        cout << "please input vector1[" << i << "]:" << endl;
        while (true)
        {
            cin >> s;
            if (isNumber(s))
            {
                v1[i] = stof(s);
                break;
            }
            cout << "the input is not a number, please input again:" << endl;
        }
    }
}

void input_v2(float *v2, size_t size)
{
    string s;
    for (int i = 0; i < size; i++)
    {
        cout << "please input vector2[" << i << "]:" << endl;
        while (true)
        {
            cin >> s;
            if (isNumber(s))
            {
                v2[i] = stof(s);
                break;
            }/*  */
            cout << "the input not a number, please input again:";
        }
    }
}

void random_numbers(float *v, size_t size)
{
    srand(time(NULL));
#pragma omp parallel for
    for (int i = 0; i < size; i++)
    {
        v[i] = rand() % 100 + 1;
    }
}

/* float dot_omp_simd(float * v1, float *v2, size_t n)
{
    float sum[8] = {0};
    __m256 v1_num, v2_num;
    __m256 temp = _mm256_setzero_ps();

#pragma omp parallel for reduction(+: sum)
    for (size_t i = 0; i < n; i+= 8)
    {
        v1_num = _mm256_load_ps(v1 + i);
        v2_num = _mm256_load_ps(v2 + i);
        temp = _mm256_add_ps(temp, _mm256_mul_ps(v1_num, v2_num));
    }
    _mm256_store_ps(sum, temp);

    return (sum[0] +sum[1] +sum[2] +sum[3] +sum[4] +sum[5] +sum[6] +sum[7]);
}

float dot_simd(float *v1, float *v2, size_t n)
{
    float sum[8] = {0};
    __m256 v1_num, v2_num;
    __m256 temp = _mm256_setzero_ps();

    for (size_t i = 0; i < n; i+= 8)
    {
        v1_num = _mm256_load_ps(v1 + i);
        v2_num = _mm256_load_ps(v2 + i);
        temp = _mm256_add_ps(temp, _mm256_mul_ps(v1_num, v2_num));
    }
    _mm256_store_ps(sum, temp);

    return (sum[0] +sum[1] +sum[2] +sum[3] +sum[4] +sum[5] +sum[6] +sum[7]);
}

float dot(float *v1, float *v2, size_t n)
{
    float sum = 0.0f;

    for (size_t i = 0; i < n; i++)
    {
        sum += v1[i] * v2[i];
    }

    return sum;
}
 */
