#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QTimer>
#include "gldisplaywidget.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    // static bool bForButtonMesh;
    // static bool bForButtonWireframe;
    inline static bool bForButtonMesh;
    inline static bool bForButtonWireframe;
    inline static bool bForButtonQueen;
    inline static bool bForButtonNormal;
    inline static bool bForButtonCurvature;
    inline static bool bForButtonTriangle;
    inline static bool bForButtonAddPoint;





private:
    Ui::MainWindow *ui;

    QPushButton*   m_button_mesh; 
    QPushButton*   m_button_wireframe; 

    QPushButton*   m_button_queen;
    QPushButton*   m_button_Normal;
    QPushButton*   m_button_Curvature;
    QPushButton*   m_button_triangle;
    QPushButton*   m_button_add_point;
    QPushButton*   m_button_5;
    QPushButton*   m_button_6;
    QPushButton*   m_button_7;
    QPushButton*   m_button_8;
    QPushButton*   m_button_9;


public slots:
    static void onClickedMesh();
    static void onClickedWireframe();

    static void onClickedQueen();
    static void onClickedNormal();
    static void onClickedCurvature();
    static void onClickedTriangle();
    static void onClickedAddPoint();
    static void onClicked5();
    static void onClicked6();
    static void onClicked7();
    static void onClicked8();
    static void onClicked9();

};

#endif // MAINWINDOW_H
