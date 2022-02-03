#include "mathlib.hpp"
#include "stdio.h"



int main()
{
  //Vec3 test
    Vec3 test = {3.f, 2.f, 4.f};
    float result = test.GetMagnitude();
    printf("Vec3 Magnitude = %f\n", result);
    Vec3 test2 = test * 2;
    printf("Vec3 * opp = %f\n", test2.z);
    Vec3 test3 = test + test2;
    printf("Vec3 + opp = %f\n", test3.z);
    test3.Normalize();
      printf("Vec3 Normalise = %f\n", test3.z);

  //Vec4 test
    Vec4 test4 ={test,2};
    test4.Homogenize();
    printf("Vec4 Homogenise = %f\n", test4.z);
  //Mat4 test
  float array[16] = 
  {
  7,7,8,9,
  8,9,7,7,
  10,1,12,1,
  4,5,7,9
  };
  float array2[16] = 
  {
  4,5,4,1,
  4,5,14,4,
  5,47,7,45,
  41,16,6,3
  };
  
  Mat4 test5 =array;
  Mat4 test6 =array2;
  Mat4 test7 = test5*test6;
  test7.Print();


  Vec4 test8 = test5*test4;
  test4.Print();

  test8.Print();

    
    

  return 0;
}
