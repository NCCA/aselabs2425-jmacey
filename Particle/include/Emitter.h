#ifndef EMITTER_H_
#define EMITTER_H_
#include <vector>
#include "Particle.h"
class Emitter
{
  public :
    Emitter(size_t _numParticles);
    size_t size() const ;
    void debug() const ;
  private :
    void resetParticle(Particle &io_p);
    std::vector<Particle> m_particles;
};

#endif
