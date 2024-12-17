#include <QMouseEvent>
#include <QGuiApplication>

#include "NGLScene.h"
#include <ngl/NGLInit.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>
#include <ngl/Util.h>

#include <iostream>

NGLScene::NGLScene(QWidget *parent) :QOpenGLWidget(parent)
{
}


NGLScene::~NGLScene()
{
  std::cout<<"Shutting down NGL, removing VAO's and Shaders\n";
}

void NGLScene::spreadChanged(double _value)
{
    m_emitter->setSpread(_value);
}

void NGLScene::resizeGL(int _w , int _h)
{
  m_win.width  = static_cast<int>( _w * devicePixelRatio() );
  m_win.height = static_cast<int>( _h * devicePixelRatio() );
  m_project = ngl::perspective(45.0f,float(_w)/float(_h) , 0.01f,200.0f );
}


void NGLScene::initializeGL()
{
  // we must call that first before any other GL commands to load and link the
  // gl commands from the lib, if that is not done program will crash
  ngl::NGLInit::initialize();
  glClearColor(0.7f, 0.7f, 0.7f, 1.0f);			   // Grey Background
  // enable depth testing for drawing
  glEnable(GL_DEPTH_TEST);
  // enable multisampling for smoother drawing
  glEnable(GL_MULTISAMPLE);
  m_emitter = std::make_unique<Emitter>(100000,ngl::Vec3(),20000,500);
  m_view = ngl::lookAt({0,40.0f,40.f},{0,0,0},{0,1.0f,0});
  ngl::VAOPrimitives::createLineGrid("floor",40,40,40);
  ngl::ShaderLib::loadShader("ParticleShader","shaders/ParticleVertex.glsl","shaders/ParticleFragment.glsl");


  startTimer(10);
}

void NGLScene::timerEvent(QTimerEvent *)
{
  m_emitter->update();
  update();
}

void NGLScene::paintGL()
{
  // clear the screen and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0,0,m_win.width,m_win.height);

  auto rotX = ngl::Mat4::rotateX(m_win.spinXFace);
  auto rotY = ngl::Mat4::rotateY(m_win.spinYFace);
  auto mouseRotation = rotX * rotY;
  mouseRotation.m_m[3][0] = m_modelPos.m_x;
  mouseRotation.m_m[3][1] = m_modelPos.m_y;
  mouseRotation.m_m[3][2] = m_modelPos.m_z;


  ngl::ShaderLib::use(ngl::nglColourShader);
  ngl::ShaderLib::setUniform("MVP", m_project*m_view*mouseRotation);
  ngl::VAOPrimitives::draw("floor");


  ngl::ShaderLib::use("ParticleShader");
  ngl::ShaderLib::setUniform("MVP", m_project*m_view*mouseRotation);

  m_emitter->draw();
}

//----------------------------------------------------------------------------------------------------------------------

void NGLScene::keyPressEvent(QKeyEvent *_event)
{
  // this method is called every time the main window recives a key event.
  // we then switch on the key value and set the camera in the GLWindow
  const float inc=0.5f;

  switch (_event->key())
  {
  // escape key to quite
  case Qt::Key_Escape : QGuiApplication::exit(EXIT_SUCCESS); break;
  case Qt::Key_Space :
      m_win.spinXFace=0;
      m_modelPos.set(ngl::Vec3::zero());
  break;

    case Qt::Key_Left : m_emitter->move(-inc,0.0,0.0); break;
    case Qt::Key_Right : m_emitter->move(inc,0.0,0.0); break;
    case Qt::Key_Up : m_emitter->move(0.0,inc,0.0); break;
    case Qt::Key_Down : m_emitter->move(0.0,-inc,0.0); break;
    case Qt::Key_I : m_emitter->move(0.0,0.0,-inc); break;
    case Qt::Key_O : m_emitter->move(0.0,0.0,inc); break;


    default : break;
  }
  // finally update the GLWindow and re-draw

    update();
}
