#include <iostream>

#include "library.h"

int main(int argc, char* argv[])
{
    std::cout << "Basic demo\n";
    DemoClass *a = new DemoClass();
    a->foo();
    return 0;
}
