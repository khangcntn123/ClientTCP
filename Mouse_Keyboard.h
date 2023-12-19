#pragma once

#include <QtWidgets/QMainWindow>
//#include "ui_CLIENT.h"
#include <QApplication>
#include <QWidget>
#include <QMouseEvent>
//#include "socket.h"
#include <QKeyEvent>
#include <Windows.h>
#include <QTimer>

#define KEY_DOWN 7
#define KEY_UP 8
static int x = 1;

class Mouse_Keyboard : public QMainWindow
{
    Q_OBJECT

public:
    int countPress = 0;
    int countRelease = 0;
    Mouse_Keyboard(QWidget* parent = nullptr);
    // void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    //Socket sk;
    ~Mouse_Keyboard();
public slots:
    void updateMousePosition();

signals:
    void send_Event(int a, int k, int y);
private:
    //Ui::Mouse_KeyboardClass ui;
    QTimer* mouseUpdateTimer;
};


//#pragma once
//
//#include <QObject>
//#include <QtWidgets/QMainWindow>
//#include <QApplication>
//#include <QWidget>
//#include <QMouseEvent>
//#include <QKeyEvent>
//#include <Windows.h>
//#include <QTimer>
//
//
//#define KEY_DOWN 7
//#define KEY_UP 8
//static int x = 1;
//
//class Client  : public QObject
//{
//	Q_OBJECT
//
//public:
//	int a = 99;
//	int b = 99 ;
//	int c = 99;
//	Client(QObject *parent=nullptr);
//	~Client();
//	void mousePressEvent(QMouseEvent* event);
//	void mouseReleaseEvent(QMouseEvent* event);
//	void mouseDoubleClickEvent(QMouseEvent* event);
//	void keyPressEvent(QKeyEvent* event);
//
//signals:
//	void send_Event(int a, int k,  int y);
//private slots:
//	void updateMousePosition();
//private:
//	QTimer* mouseUpdateTimer;
//};
