//#pragma once
//
//#include <QObject>
//#include <iostream>
//#include <qbasictimer.h>
//#include <qdatastream.h>
//#include <qiodevice.h>
//#include <qpixmap.h>
//#include <qtimer.h>
//#include <qbasictimer.h>
//#include <qevent.h>
//#include <QMutex>
//using namespace std;
//
//
//class Buffer : public QObject
//{
//	Q_OBJECT
//public: 	
//	std::list <QPixmap> frames_buff;
//	QMutex m;
//	//QBasicTimer m_timer;
//
//public:
//
//	explicit Buffer(QObject *parent=nullptr);
//	~Buffer();
//	//void timerEvent(QTimerEvent* ev);
//
//signals:
//	void PixmapisReaddy(QByteArray data);
//	void pixmapispush();
//	void pixmapispop(QPixmap _mpixmap);
//public slots:
//	void dataReceived(QByteArray data);
//	void pushPixmap(QByteArray data);
//	//void popPixmap(QPixmap _mpixmap);
//	//void timerStart();
//	void readytopop();
//private:
//	QByteArray imageData;
//	int imageSize=0;
//	int count = 0;
//	int buffer = 0;
//};
