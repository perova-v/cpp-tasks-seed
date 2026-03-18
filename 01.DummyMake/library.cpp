#include "library.h"

int DemoClass::foo()
{
    return 5;
}

bool DemoClass::bar(int x)
{
    return x==this->foo();
}

void DemoClass::biz(double a)
{
    foo();
    bar(1);
    bar(5);
}
