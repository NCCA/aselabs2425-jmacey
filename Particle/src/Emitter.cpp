#include "Emitter.h"
#include <iostream>
#include <fstream>
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


void Emitter::writeGeo(std::string_view fname) const
{
  auto file=std::ofstream(fname.data());
  file <<"PGEOMETRY V5 \n";
  file <<"NPoints "<<m_particles.size()<<" NPrims 1 \n";
  file <<"NPointGroups 0 NPrimGroups 0 \n";
  file <<"NPointAttrib 2 NVertexAttrib 0 NPrimAttrib 1 NAttrib 0 \n";
  file <<"PointAttrib \n";
  file <<"Cd 3 float 1 1 1 \n";
  file <<"pscale 1 float 0.5 \n";
  size_t numParts=0;
  for(auto p : m_particles)
  {
    file << p.pos.x <<' '<<p.pos.y<<' '<<p.pos.z<< " 1 (";
    file << p.colour.x<< ' ' << p.colour.y<<' '<<p.colour.z << ' ';
    file << p.size <<" )\n";
    ++numParts;
  }
  file<<"PrimitiveAttrib\n";
  file<<"generator 1 index 1 papi \n";
  file<<"Part "<<numParts<<' ';
  for(size_t i=0; i<numParts; ++i)
  {
    file<<i<<' ';
  }
  file<<"[0] \n";
  file<<"beginExtra\nendExtra\n";
  file.close();
}


void Emitter::update()
{
  for(auto &p : m_particles)
  {
    p.size +=0.1;
  }
}




















