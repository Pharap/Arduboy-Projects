#ifndef VECTOR_H
#define VECTOR_H

#include <FixedPoints.h>
#include <FixedPointsCommon.h>

class vec3 {
public:
  SQ15x16 x, y, z;
  
  vec3();
  vec3(SQ15x16);
  vec3(SQ15x16, SQ15x16, SQ15x16);

  SQ15x16 magnitude();
  vec3 normalize();
  SQ15x16 dot(vec3);

  vec3 operator+(const vec3&);
  vec3 operator*(const vec3&);
  vec3 operator*(const SQ15x16&);
};

#endif
