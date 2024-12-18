#ifndef EMITTER_H_
#define EMITTER_H_
#include <vector>
#include <ngl/MultiBufferVAO.h>
#include <ngl/Vec3.h>
#include <ngl/Vec4.h>
#include <memory>
#include <QObject>
#include <memory>
class Emitter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int m_maxLife READ maxLife WRITE setMaxLife NOTIFY maxLifeChanged)
    Q_PROPERTY(int m_velocity READ velocity WRITE setVelocity NOTIFY velocityChanged)

  public :
    Emitter(size_t _numParticles, ngl::Vec3 _pos,size_t _maxAlive, size_t _numPerFrame);
    size_t size() const ;
    //void debug() const ;
    void update();
    void draw() ;
    void move(float _dx, float _dy, float _dz);
    void setSpread(float _value);
    int maxLife() const;
    float velocity() const;
  public slots :
    void setNumPerFrame(int _value);
    void setMaxLife(int _value);
    void setVelocity(float _v);

  signals :
    void maxLifeChanged();
    void velocityChanged();




  private :
    void resetParticle(size_t _i);
    void birthParticles();
    std::unique_ptr<ngl::MultiBufferVAO> m_vao;
    [[nodiscard]] ngl::Vec3 randomVectorOnSphere(float _radius) const;
    ngl::Vec3 m_pos;
    // Particle structure of arrays
    // x,y,z size
    std::vector<ngl::Vec4> m_ppos;
    std::vector<ngl::Vec3> m_dir;
    std::vector<ngl::Vec3> m_colour;
    std::vector<int> m_life;
    enum class ParticleState : bool {Active,Dead};
    std::vector<ParticleState> m_state;
    size_t m_maxAlive = 1000;
    size_t m_numPerFrame = 120;
    size_t m_numParticles;
    float m_spread = 5.5;
    int m_maxLife=100;
    float m_velocity = 2.0f;


};

#endif
