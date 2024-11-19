#ifndef PARTICLE_H_
#define PARTICLE_H_
#include "Vec3.h"
struct Particle
{
  int life=100;
  float size=0.5f;
  Vec3 pos;
  Vec3 dir;
  Vec3 colour={1.0f,1.0f,1.0f};

};

#endif