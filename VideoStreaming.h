//#pragma once
//
//#include <QObject>
//#include <QtWidgets/QMainWindow>
//#include <qstyle.h>
//#include <QtNetwork/qhostaddress.h>
//#include <QtNetwork/qabstractsocket.h>
//#include "ui_ClientTCP.h"
//#include "DeviceController.h"
//#include <QGuiApplication>
//#include <QScreen>
//#include <qevent.h>
//#include <QThread>
//#include <qmetaobject.h>
//#include "Buffer.h"
//#include "Client.h"
//#include <qelapsedtimer.h>
//#include <Windows.h>
//
//
//class VideoStreaming  : public QObject
//{
//	Q_OBJECT
//
//public:
//    QByteArray imageData;
//    int count = 0;
//    QLabel* imageLabel;
//    QVBoxLayout* layout;
//
//    QElapsedTimer timer;
//    int imageSize = 0;
//    int buffer = 0;
//    void setDeviceController();
//    //void mouseDoubleClickEvent(QMouseEvent* event);
//	VideoStreaming(QObject *parent);
//	~VideoStreaming();
//
//public slots:
//    void my_video_streaming(QByteArray data);
//	void device_dataReady(QByteArray data);
//
//signals:
//	void video_streaming(QByteArray data);
//    void sendimage();
//
//};
