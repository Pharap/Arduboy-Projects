#include <Arduboy.h>
#include "Vector.h"

Arduboy a;

int16_t x, y;
vec3 pos, dir;
vec3 lightDir;

void setup() {
  a.begin();
  a.clear();
  Serial.begin(9600);
  
  x = 0;
  y = 0;
  lightDir = vec3(1, -1, -1).normalize();
}

bool shadow(vec3 pos, vec3 dir) {
  for(int i = 0; i < 16; i++) {
    float dist = pos.magnitude() - 1.;
    if(dist < 0.01) return true;
    pos = pos + (dir * dist);
  }
  return false;
}

void loop() {
  if(y > 63) {
    Serial.write(a.getBuffer(), 128 * 64 / 8);
    return;
  }
  
  pos = vec3(0, 0, -2);
  dir = vec3(x / 128., y / 64., 1.);
  dir = dir * 2.0 + vec3(-1);
  dir.x *= 2.;
  dir = dir.normalize();

  a.drawPixel(x, y, 0);
  for(int i = 0; i < 16; i++) {
    float dist_sphere = pos.magnitude() - 1.;
    float dist_plane  = -pos.y + 1.;

    bool isFloor = dist_plane < dist_sphere;
    float dist = isFloor ? dist_plane : dist_sphere;
    
    pos = pos + (dir * dist);
    if(dist < 0.01) {
      if(isFloor) {
        if(((int) (pos.x * 3.0 + 10.0) % 2) ^ ((int) (pos.z * 3.0 + 10.0) % 2)) {
          if(shadow(pos, vec3(1.0, -1.0, 0.0).normalize())) {
            if((x % 2) ^ (y % 2))
              a.drawPixel(x, y, 1);
          } else
            a.drawPixel(x, y, 1);
        }
      } else {
        float diffuse = pos.dot(lightDir);
        if(diffuse > 0.5 || (diffuse > 0.0 && ((x % 2) ^ (y % 2))))
          a.drawPixel(x, y, 1);
      }
      break;
    }
  }
  
  x++;
  if(x > 127) { x = 0; y++; }
  a.drawPixel(x, y, 1);
  a.display();
}

