#include <iostream>
#include "Matrix.h"
int main()
{
    Matrix<int> m ({ 
        {1,2,3},
        {1,2,3} 
        });
    
    std::cout << m.getNumOfRows();
    std::cout << m.getNumOfColumns();

    std::cout << "Hello World!\n";
}

