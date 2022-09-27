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

private:
    Ui::MainWindow *ui;

    QPushButton*   m_button_mesh; 
    QPushButton*   m_button_wireframe; 

    QPushButton*   m_button_0;
    QPushButton*   m_button_1;
    QPushButton*   m_button_2;
    QPushButton*   m_button_3;
    QPushButton*   m_button_4;
    QPushButton*   m_button_5;
    QPushButton*   m_button_6;
    QPushButton*   m_button_7;
    QPushButton*   m_button_8;
    QPushButton*   m_button_9;


public slots:
    static void onClickedMesh();
    static void onClickedWireframe();

    static void onClicked0();
    static void onClicked1();
    static void onClicked2();
    static void onClicked3();
    static void onClicked4();
    static void onClicked5();
    static void onClicked6();
    static void onClicked7();
    static void onClicked8();
    static void onClicked9();

};

#endif // MAINWINDOW_H
