#ifndef EMITTER_H_
#define EMITTER_H_
#include <vector>
#include <string_view>
#include "Particle.h"
#include <ngl/AbstractVAO.h>
#include <memory>
class Emitter
{
  public :
    Emitter(size_t _numParticles);
    size_t size() const ;
    void debug() const ;
    void writeGeo(std::string_view fname) const ;
    void update();
    void draw() ;
  private :
    void resetParticle(Particle &io_p);
    std::vector<Particle> m_particles;
    std::unique_ptr<ngl::AbstractVAO> m_vao;
};

#endif
