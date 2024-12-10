#include "Emitter.h"
#include <iostream>
#include <fstream>
#include <ngl/Random.h>
#include <ngl/NGLStream.h>
#include <ngl/VAOFactory.h>
#include <algorithm>
Emitter::Emitter(size_t _numParticles, ngl::Vec3 _pos, size_t _maxAlive, size_t _numPerFrame)
{
  m_maxAlive=_maxAlive;
  m_numPerFrame=_numPerFrame;
  m_numParticles = _numParticles;
  m_pos=_pos;
  m_ppos.resize(m_numParticles);
  m_dir.resize(m_numParticles);
  m_colour.resize(m_numParticles);
  m_life.resize(m_numParticles);
  m_state.resize(m_numParticles);
  for(size_t i=0; i<m_numParticles; ++i)
  {
    resetParticle(i);
  }
  birthParticles();
  m_vao = ngl::vaoFactoryCast<ngl::MultiBufferVAO>( ngl::VAOFactory::createVAO(ngl::multiBufferVAO,GL_POINTS));
  m_vao->bind();
  m_vao->setData(ngl::MultiBufferVAO::VertexData(0,0)); // index 0 points
  m_vao->setData(ngl::MultiBufferVAO::VertexData(0,0)); // index 1 colours

  m_vao->unbind();
}

void Emitter::draw()
{
  m_vao->bind();
  m_vao->setData(0,ngl::MultiBufferVAO::VertexData(m_ppos.size()*sizeof(ngl::Vec4),m_ppos[0].m_x));
  m_vao->setVertexAttributePointer(0,4,GL_FLOAT,0,0);

  m_vao->setData(1,ngl::MultiBufferVAO::VertexData(m_colour.size()*sizeof(ngl::Vec3),m_colour[0].m_x));
  m_vao->setVertexAttributePointer(1,3,GL_FLOAT,0,0);


//  m_vao->setVertexAttributePointer(1,3,GL_FLOAT,sizeof(Particle),6);
  m_vao->setNumIndices(m_numParticles);
  glEnable(GL_PROGRAM_POINT_SIZE);
  m_vao->draw();
  glDisable(GL_PROGRAM_POINT_SIZE);
  m_vao->unbind();
}


void Emitter::resetParticle(size_t _i)
{
  ngl::Vec3 emitDir(0.0f,1.0f,0.0f);
  float spread = 5.5;
  m_ppos[_i]=m_pos;
  m_dir[_i] = emitDir * ngl::Random::randomPositiveNumber() +randomVectorOnSphere(1.0f) * spread;
  m_dir[_i].m_y = std::abs(m_dir[_i].m_y);
  m_ppos[_i].m_w = 0.1;
  m_life[_i] = 20 + static_cast<int>(ngl::Random::randomPositiveNumber(100));
  m_colour[_i] = ngl::Random::getRandomColour3();
  m_state[_i] = ParticleState::Dead;
}

void Emitter::move(float _dx, float _dy, float _dz)
{
  m_pos.m_x+=_dx;
  m_pos.m_y+=_dy;
  m_pos.m_z+=_dz;
}

void Emitter::birthParticles()
{
  auto births = 0 + static_cast<int>(ngl::Random::randomPositiveNumber(m_numPerFrame));
  for(size_t i=0; i<births; ++i)
  {
    for (size_t p = 0; p < m_numParticles; ++p)
    {
      if (m_state[p] == ParticleState::Dead)
      {
        resetParticle(p);
        m_state[p] = ParticleState::Active;
        break;
      }
    }
  }
}

size_t Emitter::size()const
{
  return m_numParticles;
}



void Emitter::update()
{
  const ngl::Vec3 gravity(0.0f,-9.81f,0.0f);
  const float dt=0.001f;

  auto numAlive = std::count_if(std::begin(m_state),std::end(m_state),
                                [](auto p){ return p == ParticleState::Active;});
  if(numAlive < m_maxAlive)
  {
    birthParticles();
  }

  for(size_t i=0; i<m_numParticles; ++i)
  {
    if(m_state[i] == ParticleState::Dead)
      continue;
    m_dir[i] += gravity * dt * 0.5f;
    m_ppos[i] += m_dir[i] * 0.5f;
    m_ppos[i].m_w +=0.1;
    m_ppos[i].m_w =std::clamp(m_ppos[i].m_w, 1.0f,10.0f);
    if(m_ppos[i].m_y <= 0.0f || --m_life[i] <=0)
    {
      resetParticle(i);
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







