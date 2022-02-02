#include "mathlib.hpp"
#include "stdio.h"

int main()
{
    Vec3 test = {3.f, 2.f, 4.f};
    float result = test.GetMagnitude();
    printf("Vec3 Magnitude = %f\n", result);
    Vec3 test2 = test * 2;
    printf("Vec3 * opp = %f\n", test2.z);
    Vec3 test3 = test + test2;
    printf("Vec3 + opp = %f\n", test3.z);
    test3.Normalize();
      printf("Vec3 Normalise = %f\n", test3.z);


    
    

    return 0;
}
