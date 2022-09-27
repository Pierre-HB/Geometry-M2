#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gldisplaywidget.h"

#ifdef __APPLE__
    #include <glu.h>
#else
    #include <GL/glu.h>
#endif

#include "QDebug"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    bForButtonMesh = true;
    bForButtonWireframe = true;
    // pushButton_2 = new QPushButton("pushButton_2", this);

    m_button_mesh = new QPushButton("Mesh", this);
    m_button_mesh->setGeometry(QRect(QPoint(10, 30), QSize(100, 25)));

    m_button_wireframe = new QPushButton("Wireframe", this);
    m_button_wireframe->setGeometry(QRect(QPoint(10, 60), QSize(100, 25)));

    m_button_0 = new QPushButton("Button 0", this);
    m_button_0->setGeometry(QRect(QPoint(10, 90), QSize(100, 25)));
    m_button_1 = new QPushButton("Button 1", this);
    m_button_1->setGeometry(QRect(QPoint(10, 120), QSize(100, 25)));
    m_button_2 = new QPushButton("Button 2", this);
    m_button_2->setGeometry(QRect(QPoint(10, 150), QSize(100, 25)));
    m_button_3 = new QPushButton("Button 3", this);
    m_button_3->setGeometry(QRect(QPoint(10, 180), QSize(100, 25)));
    m_button_4 = new QPushButton("Button 4", this);
    m_button_4->setGeometry(QRect(QPoint(10, 210), QSize(100, 25)));
    m_button_5 = new QPushButton("Button 5", this);
    m_button_5->setGeometry(QRect(QPoint(10, 240), QSize(100, 25)));
    m_button_6 = new QPushButton("Button 6", this);
    m_button_6->setGeometry(QRect(QPoint(10, 270), QSize(100, 25)));
    m_button_7 = new QPushButton("Button 7", this);
    m_button_7->setGeometry(QRect(QPoint(10, 300), QSize(100, 25)));
    m_button_8 = new QPushButton("Button 8", this);
    m_button_8->setGeometry(QRect(QPoint(10, 330), QSize(100, 25)));
    m_button_9 = new QPushButton("Button 9", this);
    m_button_9->setGeometry(QRect(QPoint(10, 360), QSize(100, 25)));

    // connect(pushButton_2 , SIGNAL(clicked()), this, SLOT(onClicked()));
    connect(m_button_wireframe , SIGNAL(clicked()), this, SLOT(onClickedWireframe()));
    connect(m_button_mesh , SIGNAL(clicked()), this, SLOT(onClickedMesh()));

    connect(m_button_0 , SIGNAL(clicked()), this, SLOT(onClicked0()));
    connect(m_button_1 , SIGNAL(clicked()), this, SLOT(onClicked1()));
    connect(m_button_2 , SIGNAL(clicked()), this, SLOT(onClicked2()));
    connect(m_button_3 , SIGNAL(clicked()), this, SLOT(onClicked3()));
    connect(m_button_4 , SIGNAL(clicked()), this, SLOT(onClicked4()));
    connect(m_button_5 , SIGNAL(clicked()), this, SLOT(onClicked5()));
    connect(m_button_6 , SIGNAL(clicked()), this, SLOT(onClicked6()));
    connect(m_button_7 , SIGNAL(clicked()), this, SLOT(onClicked7()));
    connect(m_button_8 , SIGNAL(clicked()), this, SLOT(onClicked8()));
    connect(m_button_9 , SIGNAL(clicked()), this, SLOT(onClicked9()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onClickedMesh()
{
     MainWindow::bForButtonMesh = !MainWindow::bForButtonMesh;
     std::cout << "toggle mesh" << std::endl;
}
void MainWindow::onClickedWireframe()
{
     MainWindow::bForButtonWireframe = !MainWindow::bForButtonWireframe;
     std::cout << "toggle wireframe" << std::endl;
}

void MainWindow::onClicked0(){std::cout << "press button 0" << std::endl;}
void MainWindow::onClicked1(){std::cout << "press button 1" << std::endl;}
void MainWindow::onClicked2(){std::cout << "press button 2" << std::endl;}
void MainWindow::onClicked3(){std::cout << "press button 3" << std::endl;}
void MainWindow::onClicked4(){std::cout << "press button 4" << std::endl;}
void MainWindow::onClicked5(){std::cout << "press button 5" << std::endl;}
void MainWindow::onClicked6(){std::cout << "press button 6" << std::endl;}
void MainWindow::onClicked7(){std::cout << "press button 7" << std::endl;}
void MainWindow::onClicked8(){std::cout << "press button 8" << std::endl;}
void MainWindow::onClicked9(){std::cout << "press button 9" << std::endl;}