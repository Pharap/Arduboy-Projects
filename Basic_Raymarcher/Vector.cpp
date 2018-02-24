#include "Vector.h"
#include <math.h>

vec3::vec3(){
  x = 0;
  y = 0;
  z = 0;
}

vec3::vec3(SQ15x16 n) {
  x = n;
  y = n;
  z = n;
}

vec3::vec3(SQ15x16 ax, SQ15x16 ay, SQ15x16 az) {
  x = ax;
  y = ay;
  z = az;
}


SQ15x16 vec3::magnitude() {
  return sqrt((double)this->dot(*this));
}

vec3 vec3::normalize() {
  SQ15x16 m = 1 / this->magnitude();
  return *this * m;
}

SQ15x16 vec3::dot(vec3 v) {
  return this->x*v.x + this->y*v.y + this->z*v.z;
}


vec3 vec3::operator+(const vec3& v) {
  return vec3(this->x + v.x, this->y + v.y, this->z + v.z);
}

vec3 vec3::operator*(const vec3& v) {
  return vec3(this->x * v.x, this->y * v.y, this->z * v.z);
}

vec3 vec3::operator*(const SQ15x16& f) {
  return vec3(this->x * f, this->y * f, this->z * f);
}

