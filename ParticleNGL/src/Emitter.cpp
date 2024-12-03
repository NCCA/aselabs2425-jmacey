#include "Emitter.h"
#include <iostream>
#include <fstream>
#include <ngl/Random.h>
#include <ngl/NGLStream.h>
#include <ngl/VAOFactory.h>
#include <algorithm>
void Emitter::debug() const
{
  for (auto p: m_particles)
  {
    std::cout << p.pos <<' ';
    std::cout <<" Dir : "<<p.dir<<' ';
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
  m_vao = ngl::VAOFactory::createVAO(ngl::simpleVAO,GL_POINTS);
}

void Emitter::draw()
{
//  glPointSize(4);
  m_vao->bind();
  m_vao->setData(ngl::AbstractVAO::VertexData(m_particles.size()*sizeof(Particle),m_particles[0].pos.m_x));
  m_vao->setVertexAttributePointer(0,3,GL_FLOAT,sizeof(Particle),0);
  m_vao->setVertexAttributePointer(1,3,GL_FLOAT,sizeof(Particle),6);
  m_vao->setNumIndices(m_particles.size());
  m_vao->draw();
  m_vao->unbind();
}


void Emitter::resetParticle(Particle &io_p)
{
  ngl::Vec3 emitDir(0.0f,1.0f,0.0f);
  float spread = 5.5;
  io_p.pos.set(0.0f,0.0f,0.0f);
  io_p.dir = emitDir * ngl::Random::randomPositiveNumber() +randomVectorOnSphere(1.0f) * spread;
  io_p.dir.m_y = std::abs(io_p.dir.m_y);
  io_p.size = 0.01;
  io_p.life = 20 + static_cast<int>(ngl::Random::randomPositiveNumber(100));
  io_p.colour = ngl::Random::getRandomColour3();
}

size_t Emitter::size()const
{
  return m_particles.size();
}


void Emitter::writeGeo(std::string_view fname) const
{
/*  auto file=std::ofstream(fname.data());
  file <<"PGEOMETRY V5 \n";
  file <<"NPoints "<<m_particles.size()<<" NPrims 1 \n";
  file <<"NPointGroups 0 NPrimGroups 0 \n";
  file <<"NPointAttrib 2 NVertexAttrib 0 NPrimAttrib 0 NAttrib 0 \n";
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
  file<<"Part "<<numParts<<' ';
  for(size_t i=0; i<numParts; ++i)
  {
    file<<i<<' ';
  }
  file<<"[0] \n";
  file<<"beginExtra\nendExtra\n";
  file.close();
*/
 }


void Emitter::update()
{
  const ngl::Vec3 gravity(0.0f,-9.81f,0.0f);
  const float dt=0.001f;

  for(auto &p : m_particles)
  {
    p.dir += gravity * dt * 0.5f;
    p.pos += p.dir * 0.5f;
    p.size +=0.01;
    p.size =std::clamp(p.size, 0.0f,2.0f);
    if(p.pos.m_y <= 0.0f || --p.life <=0)
    {
      resetParticle(p);
    }
  }
}



ngl::Vec3 Emitter::randomVectorOnSphere(float _radius) const
{
  auto phi = ngl::Random::randomPositiveNumber(M_PI * 2.0f);
  auto costheta = ngl::Random::randomNumber();
  auto u = ngl::Random::randomNumber();
  auto theta = acosf(costheta);
  auto r = _radius * std::cbrtf(u);
  return ngl::Vec3(r*sin(theta) * cos(phi),
                   r*sin(theta) * sin(phi),
                   r*cos(theta));
}







