#include <iostream>
#include "matrix.hpp"
#include <stdlib.h>

int main()
{
    int x;
    Matrix A(2, 3);
    std::cin >> A;
    std::cout << "Please enter a number:" << std::endl;
    std::cin >> x;
    A = A * x;
    Matrix B(3, 4);
    std::cin >> B;
    Matrix C = A * B;

    std::cout << "A = " << std::endl
              << A << std::endl;
    std::cout << "B = " << std::endl
              << B << std::endl;
    std::cout << "C = " << std::endl
              << C << std::endl;


    system("pause");
    return 0;
}
