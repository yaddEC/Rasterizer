#include "mathlib.hpp"
#include "stdio.h"

int main()
{
    Vec3 test = {3.f,2.f,4.f};
    float result = test.GetMagnitude();

    printf("%f\n",result);
    return 0;
}
