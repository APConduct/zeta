//
// Created by Aidan Jost on 4/10/25.
//

#include <iostream>
import zeta.integer;



int main()
{
    const zeta::integer a = 5;
    const zeta::integer b = 3;
    zeta::integer c = a + b;
    std::cout << "a + b = " << c << std::endl;
    c = a - b;
    std::cout << "a - b = " << c << std::endl;
}
