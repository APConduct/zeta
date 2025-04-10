//
// Created by Aidan Jost on 4/10/25.
//


#include <iostream>

import zeta.fixdec;

int main()
{
    auto a = zeta::fixed_decimal(5.75);
    auto b = zeta::fixed_decimal(2.5);

    auto c = a + b;
    // with explicit decimal conversion
    std::cout << "a + b = " << c.as_double() << std::endl;

    c = a - b;
    std::cout << "a - b = " << c.as_double() << std::endl;

    c = a * b;
    std::cout << "a * b = " << c.as_double() << std::endl;

    c = a / b;
    std::cout << "a / b = " << c.as_double() << std::endl;


    return 0;
}