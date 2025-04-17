//
// Created by Aidan Jost on 4/10/25.
//

#include <iostream>
import zeta;



int main()
{
    constexpr zeta::integer a = 5;
    constexpr zeta::integer b = 3;
    zeta::integer c = a + b;
    std::cout << "a + b = " << c << std::endl;
    c = a - b;
    std::cout << "a - b = " << c << std::endl;

    auto bar = sizeof(std::vector<zeta::i32>);
    std::cout << "Size of vector<i32>: " << bar << std::endl;
    bar = sizeof(zeta::i32);
    std::cout << "Size of i32: " << bar << std::endl;
}
