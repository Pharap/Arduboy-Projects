#include "Vector.h"
#include <math.h>

vec3::vec3(){
  x = 0;
  y = 0;
  z = 0;
}

vec3::vec3(float n) {
  x = n;
  y = n;
  z = n;
}

vec3::vec3(float ax, float ay, float az) {
  x = ax;
  y = ay;
  z = az;
}


float vec3::magnitude() {
  return sqrt(this->dot(*this));
}

vec3 vec3::normalize() {
  float m = 1 / this->magnitude();
  return *this * m;
}

float vec3::dot(vec3 v) {
  return this->x*v.x + this->y*v.y + this->z*v.z;
}


vec3 vec3::operator+(const vec3& v) {
  return vec3(this->x + v.x, this->y + v.y, this->z + v.z);
}

vec3 vec3::operator*(const vec3& v) {
  return vec3(this->x * v.x, this->y * v.y, this->z * v.z);
}

vec3 vec3::operator*(const float& f) {
  return vec3(this->x * f, this->y * f, this->z * f);
}

