#include <iostream>
#include "Matrix.h"
int main()
{
    Matrix<int> m ({ 
        {1,2,3},
        {1,2,3},
        {1,2,3}
        });
    Matrix<int> m1({
        {2,2,2},
        {3,3,3},
        {1,2,3}
        });
    int elem = m[0][0];
    std::cout << m.GetRows();
   /* std::cout << "Hello World!\n";*/
    std::cout << m;
    Matrix<int> m3(3, 4);
    std::cout <<m + m1;
    std::cout << m3;
    std::cout << m * m1;

    return 0;
}


