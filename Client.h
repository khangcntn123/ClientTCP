#pragma once

#include <QObject>
#include <QtWidgets/QMainWindow>
#include <QApplication>
#include <QWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <Windows.h>
#include <QTimer>


#define KEY_DOWN 7
#define KEY_UP 8
static int x = 1;

class Client  : public QObject
{
	Q_OBJECT

public:
	Client(QObject *parent=nullptr);
	~Client();
	void mousePressEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	void mouseDoubleClickEvent(QMouseEvent* event);
	void keyPressEvent(QKeyEvent* event);

signals:
	void send_Event(int a, int k,  int y);
private slots:
	void updateMousePosition();
private:
	QTimer* mouseUpdateTimer;
};

