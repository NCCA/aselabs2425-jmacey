#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent), m_ui(new Ui::MainWindow)
{
  m_ui->setupUi(this);
  m_gl=new  NGLScene(this);
  m_ui->s_mainWindowGridLayout->addWidget(m_gl,0,0,2,1);

    // connect signals and slots
  connect(m_ui->spread,SIGNAL(valueChanged(double)),m_gl,SLOT(spreadChanged(double)) );
  // as we can't set these values until we have a valid object
  // we wait until m_gl signals it is ready then we can grab the
  // emitter which is created once we have a gl context.
  connect(m_gl,&NGLScene::glInitialized,  [=]{
      auto emitter=m_gl->getEmitter();
      connect(m_ui->numAlive,SIGNAL(valueChanged(int)),emitter,SLOT(setNumPerFrame(int)));
      connect(m_ui->maxLife,SIGNAL(valueChanged(int)),emitter,SLOT(setMaxLife(int)));
      connect(m_ui->velocity,SIGNAL(valueChanged(double)),emitter,SLOT(setVelocity(double)));

  });
    // reset the ui values to default
  connect(m_ui->reset,&QPushButton::clicked,[=]{
    m_ui->spread->setValue(5.5);
    m_ui->maxLife->setValue(100);
    m_ui->numAlive->setValue(120);
    m_ui->velocity->setValue(2.0);
  });


}

MainWindow::~MainWindow()
{
    delete m_ui;
}
