#include "Emitter.h"
#include <iostream>
#include "Random.h"
void Emitter::debug() const
{
  for (auto p: m_particles)
  {
    std::cout << p.pos.x<<' '<<p.pos.y<<' '<<p.pos.z;
    std::cout <<" Dir : "<<p.dir.x<<' '<<p.dir.y<<' '<<p.dir.z;
    std::cout <<" Life "<<p.life<< " Size "<<p.size<<'\n';
  }
}
Emitter::Emitter(size_t _numParticles)
{
  m_particles.resize(_numParticles);
  for(auto &p : m_particles)
  {
    resetParticle(p);
  }
}

void Emitter::resetParticle(Particle &io_p)
{
  Vec3 emitDir(0.0f,1.0f,0.0f);
  float spread = 5.5;
  io_p.dir = emitDir * Random::randomPositiveFloat() +
             Random::randomVectorOnSphere() * spread;
  io_p.dir.y = std::abs(io_p.dir.y);
  io_p.size = 0.01;
  io_p.life = 20 + static_cast<int>(Random::randomPositiveFloat(100));
  io_p.colour = Random::randomPositiveVec3();
}

size_t Emitter::size()const
{
  return m_particles.size();
}