#ifndef PARTICLE_H_
#define PARTICLE_H_
#include <ngl/Vec3.h>
struct Particle
{
  int life=100;
  float size=0.5f;
  ngl::Vec3 pos;
  ngl::Vec3 dir;
  ngl::Vec3 colour={1.0f,1.0f,1.0f};

};

#endif