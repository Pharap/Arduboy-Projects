#include <Arduboy.h>
#include "Vector.h"

Arduboy a;

int16_t x, y; // Where we are currently rendering
vec3 pos, dir; // Current ray position and direction
vec3 lightDir, shadowDir; // Direction to the light & direction to the shadow source (This is just a cheat to make the render look better)

void setup() {
  a.begin();
  a.clear();
  Serial.begin(9600);
  
  x = 0; // Start at the top left
  y = 0;
  lightDir = vec3(1, -1, -1).normalize(); // equally up, to the right, and towards us
  shadowDir = vec3(1, -1, 0).normalize(); // up & to the right
}

bool shadow(vec3 pos, vec3 dir) {
  for(int i = 0; i < 16; i++) { // Limit our steps to 16 (Probably could go with 8)
    SQ15x16 dist = pos.magnitude() - 1.; // Find distance to sphere. It's at the origin, so we can just get the length of the position vector and subtract the sphere radius
    if(dist < 0.01) return true; // If we have hit the sphere, then we should have a shadow
    pos = pos + (dir * dist); // Move the ray
  }
  return false; // We didn't hit the sphere
}

void loop() {
  if(y > 63) { // If we are done rendering
    Serial.write(a.getBuffer(), 128 * 64 / 8); // Output the screen to serial
    return; // No need to continue rendering
  }

  // Note: We are not clearing the screen
  
  pos = vec3(0, 0, -2); // Camera is 2 units back from the origin
  dir = vec3(x / 128., y / 64., 1.); // Convert x,y to 0.0 - 1.0
  dir = dir * 2.0 + vec3(-1); // Convert x,y to -1.0 - 1.0
  dir.x *= 2.; // Apply screen aspect ration
  dir = dir.normalize(); // Normalize the direction, otherwise you will get warping

  a.drawPixel(x, y, 0); // Clear the current pixel
  for(int i = 0; i < 16; i++) { // Limit our steps to 16
    SQ15x16 dist_sphere = pos.magnitude() - 1.; // Find distance to sphere. It's at the origin, so we can just get the length of the position vector and subtract the sphere radius
    SQ15x16 dist_plane  = -pos.y + 1.; // Find the distance to the ground. Negative y is up

    // Finds the object that is closest and sets the bool and SQ15x16 accordingly
    bool isFloor = dist_plane < dist_sphere;
    SQ15x16 dist = isFloor ? dist_plane : dist_sphere;
    
    pos = pos + (dir * dist); // Move the ray
    if(dist < 0.01) { // If the ray hit something
      if(isFloor) {
        // Floor
        if(((int) (pos.x * 3.0 + 10.0) % 2) ^ ((int) (pos.z * 3.0 + 10.0) % 2)) { // This creates the checkboard pattern based on the ray's x & z coordinates
          if(shadow(pos, shadowDir)) { // If the white tile is in shadow
            if((x % 2) ^ (y % 2)) // Draw a checkerboard pattern
              a.drawPixel(x, y, 1);
          } else
            a.drawPixel(x, y, 1); // Not in shadow, so just always draw white
        }
      } else {
        // Sphere
        SQ15x16 diffuse = pos.dot(lightDir); // Since the sphere is radius 1, we can use the position as the sphere's normal. Diffuse will have a value of -1 (facing oposite the light) to 1 (facing the light)
        if(diffuse > 0.5 || (diffuse > 0.0 && ((x % 2) ^ (y % 2)))) // 0.5 - 1.0 we shade solid white, 0.0 - 0.5 we shade in a checkerboard pattern
          a.drawPixel(x, y, 1);
      }
      break; // We hit something, so we can stop raymarching for this pixel
    }
  }

  // Find the next pixel to render
  x++;
  if(x > 127) { x = 0; y++; }

  // Draw the cursor
  a.drawPixel(x, y, 1);
  a.display();
}

