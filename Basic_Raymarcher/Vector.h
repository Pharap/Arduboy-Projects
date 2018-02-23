#ifndef VECTOR_H
#define VECTOR_H

class vec3 {
public:
  float x, y, z;
  
  vec3();
  vec3(float);
  vec3(float, float, float);

  float magnitude();
  vec3 normalize();
  float dot(vec3);

  vec3 operator+(const vec3&);
  vec3 operator*(const vec3&);
  vec3 operator*(const float&);
};

#endif
