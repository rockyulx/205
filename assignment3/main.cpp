#include "dot_pro.hpp"

// void set_vector(float *, float *, size_t);

float *v1 = nullptr;
float *v2 = nullptr;
size_t vsize;
int main()
{
    while (true)
    {
        string s, c;
        cout << "please set the size of dot:" << endl;
        while (true)
        {
            cin >> s;
            if (isNumber(s))
            {
                vsize = stof(s);
                if (vsize > 200000001)
                {
                    cout << "the size is too big!"
                         << "please set again:" << endl;
                    continue;
                }
                else
                {
                    v1 = new float[vsize];
                    v2 = new float[vsize];
                    input_vector(v1, v2, vsize);
                    break;
                }
            }
            cout << "the input is not a number, please input again:" << endl;
        }
        vector_omp(v1, v2, vsize);
        cout << "do you want to do it again?[Y]:" << endl;
        cin >> c;
        if (c == "Y")
        {
            continue;
        }
        break;
    }

    delete[] v1;
    delete[] v2;
    return 0;
}

/* void set_vector(float *v1, float *v2, size_t size)
{
    string s;
    cout << "please set the size of dot:" << endl;
    while (true)
    {
        cin >> s;
        if (isNumber(s))
        {
            size = stof(s);
            if (size > 262144)
            {
                cout << "the size is too big!"
                     << "please set again:" << endl;
                continue;
            }
            else
            {
                v1 = new float[size];
                v2 = new float[size];
                input_vector(v1, v2, size);
                break;
            }
        }
        cout << "the input is not a number, please input again:" << endl;
    }
} */