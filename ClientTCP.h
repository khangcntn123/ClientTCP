#pragma once

#include <QtWidgets/QMainWindow>
#include <qstyle.h>
#include <QtNetwork/qhostaddress.h>
#include <QtNetwork/qabstractsocket.h>
#include "ui_ClientTCP.h"
#include "DeviceController.h"
#include <QGuiApplication>
#include <QScreen>
#include <qevent.h>
#include <QThread>
#include <qmetaobject.h>
#include "Buffer.h"
#include "Mouse_Keyboard.h"
#include <qelapsedtimer.h>
#include <Windows.h>

QT_BEGIN_NAMESPACE
namespace Ui { class ClientTCP; }
QT_END_NAMESPACE

class ClientTCP : public QMainWindow
{
    Q_OBJECT

public:
    ClientTCP(QWidget* parent = nullptr);
    ~ClientTCP();
    //Buffer myBuffer;
    //DeviceController _controller;
    //QThread bufferThread;
    //QThread deviceControllerThread;
    //Buffer* myBuffer = new Buffer;
    //DeviceController* _controller = new DeviceController;
    Mouse_Keyboard mouse;
    DeviceController _controller;
    QByteArray imageData;
signals:
    void video_streaming(QByteArray data);
    void sendimage();

public slots:
    void kk(int a,int x,int y);
    void receivesignal(int x, int y, int z);
    void on_btnClear_clicked();
    void on_lnIPAddress_textChanged(const QString& arg1);

    //void updateImageLabel(QPixmap pixmap);
    void on_btnConnect_clicked();

    void device_connected();
    void device_disconnected();
    void device_stateChanged(QAbstractSocket::SocketState);
    void device_errorOccurred(QAbstractSocket::SocketError);
    void device_dataReady(QByteArray data);
    //void dataisready(QByteArray data);

    void on_btnSend_clicked();
    void my_video_streaming(QByteArray data);
    //void pixmapisready(QPixmap _mpixmap);
//protected:
//    void resizeEvent(QResizeEvent* event) override;
public:
    int count = 0;
    //QPixmap currentPixmap;
    QLabel* imageLabel;
    QVBoxLayout* layout;
    Ui::ClientTCPClass* ui;
    QElapsedTimer timer;
    int imageSize = 0;
    int buffer = 0;
    void mousePressEvent(QMouseEvent* event);
    void setDeviceController();
    void mouseReleaseEvent(QMouseEvent* event);
    //void mouseDoubleClickEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
};
