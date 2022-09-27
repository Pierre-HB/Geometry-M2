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
    MainWindow::bForButtonMesh = false;
    MainWindow::bForButtonWireframe = true;
    MainWindow::bForButtonQueen = false;
    MainWindow::bForButtonNormal = false;
    MainWindow::bForButtonCurvature = false;
    MainWindow::bForButtonTriangle = false;
    MainWindow::bForButtonAddPoint = false;


    m_button_mesh = new QPushButton("Mesh", this);
    m_button_mesh->setGeometry(QRect(QPoint(10, 30), QSize(100, 25)));

    m_button_wireframe = new QPushButton("Wireframe", this);
    m_button_wireframe->setGeometry(QRect(QPoint(10, 60), QSize(100, 25)));

    m_button_queen = new QPushButton("Load Queen", this);
    m_button_queen->setGeometry(QRect(QPoint(10, 90), QSize(100, 25)));
    m_button_Normal = new QPushButton("normals", this);
    m_button_Normal->setGeometry(QRect(QPoint(10, 120), QSize(100, 25)));
    m_button_Curvature = new QPushButton("curvatures", this);
    m_button_Curvature->setGeometry(QRect(QPoint(10, 150), QSize(100, 25)));
    m_button_triangle = new QPushButton("load triangle", this);
    m_button_triangle->setGeometry(QRect(QPoint(10, 180), QSize(100, 25)));
    m_button_add_point = new QPushButton("add point", this);
    m_button_add_point->setGeometry(QRect(QPoint(10, 210), QSize(100, 25)));
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

    connect(m_button_queen , SIGNAL(clicked()), this, SLOT(onClickedQueen()));
    connect(m_button_Normal , SIGNAL(clicked()), this, SLOT(onClickedNormal()));
    connect(m_button_Curvature , SIGNAL(clicked()), this, SLOT(onClickedCurvature()));
    connect(m_button_triangle , SIGNAL(clicked()), this, SLOT(onClickedTriangle()));
    connect(m_button_add_point , SIGNAL(clicked()), this, SLOT(onClickedAddPoint()));
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

void MainWindow::onClickedQueen(){
    MainWindow::bForButtonQueen = !MainWindow::bForButtonQueen;
    std::cout << "press button 0" << std::endl;
}
void MainWindow::onClickedNormal(){
    MainWindow::bForButtonNormal = !MainWindow::bForButtonNormal;
    std::cout << "press button normal" << std::endl;
}
void MainWindow::onClickedCurvature(){
    MainWindow::bForButtonCurvature = !MainWindow::bForButtonCurvature;
    std::cout << "press button curvature" << std::endl;
}
void MainWindow::onClickedTriangle(){
    MainWindow::bForButtonTriangle = ! MainWindow::bForButtonTriangle;
    std::cout << "press button Triangle" << std::endl;
}
void MainWindow::onClickedAddPoint(){
    MainWindow::bForButtonAddPoint = !MainWindow::bForButtonAddPoint;
    std::cout << "press button add point" << std::endl;
}
void MainWindow::onClicked5(){std::cout << "press button 5" << std::endl;}
void MainWindow::onClicked6(){std::cout << "press button 6" << std::endl;}
void MainWindow::onClicked7(){std::cout << "press button 7" << std::endl;}
void MainWindow::onClicked8(){std::cout << "press button 8" << std::endl;}
void MainWindow::onClicked9(){std::cout << "press button 9" << std::endl;}