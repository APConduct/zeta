//
// Created by Aidan Jost on 4/10/25.
//
import zeta;

// optional test

#include <iostream>
int main()
{

    zeta::optional<int> opt1;
    zeta::optional opt2(42);

    if (opt1.has_value())
    {
        std::cout << "opt1 has value: " << opt1.value() << std::endl;
    }
    else
    {
        std::cout << "opt1 has no value" << std::endl;
    }

    if (opt2.has_value())
    {
        std::cout << "opt2 has value: " << opt2.value() << std::endl;
    }

    auto opt3 = opt2.map([](int v) { return v * 2; });

    if (opt3.has_value())
    {
        std::cout << "opt3 has value: " << opt3.value() << std::endl;
    }

    int default_value = 100;
    std::cout << "opt1 value or default: " << opt1.value_or(default_value) << std::endl;

    return 0;

}