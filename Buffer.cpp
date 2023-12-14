//#include "Buffer.h"
//
//Buffer::Buffer(QObject *parent)
//	: QObject(parent)
//{
//    connect(this, &Buffer::PixmapisReaddy, this, &Buffer::pushPixmap);
//    connect(this, &Buffer::pixmapispush, this, &Buffer::readytopop);
//}
//
//Buffer::~Buffer()
//{
//    frames_buff.clear();
//    imageData.clear();
//
//}
//
//void Buffer::dataReceived(QByteArray data) {
//    QDataStream stream(&data, QIODevice::ReadOnly);
//    count = count + 1;
//    if (count == 1) {
//        stream >> imageSize;
//        QString pstring = QString::number(imageSize);
//        int remainingDataSize = data.size() - sizeof(int);
//
//        imageData = data.mid(sizeof(int), remainingDataSize);
//        buffer = imageData.size();
//        QString p1string = QString::number(buffer);
//    }
//    else {
//        buffer += data.size();
//        if (buffer >= imageSize) {
//            int previousdata = buffer - data.size();
//            int dataThatMustBeInclude = imageSize - previousdata;
//            QByteArray temp;
//            temp = data.mid(0, dataThatMustBeInclude);
//            imageData.append(temp);
//            emit PixmapisReaddy(imageData);
//            int dataReside = buffer - imageSize;
//            if (dataReside == 0) {
//                count = 0;
//                imageData.clear();
//                buffer = 0;
//            }
//            else {
//                imageData.clear();
//                QByteArray temp1 = data.mid(dataThatMustBeInclude, dataReside);
//                imageSize = 0;
//                QDataStream stream1(&temp1, QIODevice::ReadOnly);
//                stream1 >> imageSize;
//                int remainingDataSize = temp1.size() - sizeof(int);
//                imageData = data.mid(sizeof(int), remainingDataSize);
//                buffer = imageData.size();
//                count = 1;
//                temp1.clear();
//            }
//        }
//        else {
//            imageData.append(data);
//        }
//    }
//}
//
//void Buffer::pushPixmap(QByteArray data) {
//    QPixmap pixmap;
//    pixmap.loadFromData(data);
//    m.lock();
//    frames_buff.push_back(pixmap);
//    m.unlock();
//    emit pixmapispush();
//}
//
//void Buffer::readytopop() {
//    if (frames_buff.size() >= 1) {
//        m.lock();
//        QPixmap _pixmap = frames_buff.front();
//        frames_buff.pop_front();
//        m.unlock();
//        emit pixmapispop(_pixmap);
//    }
//}
//
////void Buffer::timerStart()
////{
////    if (!m_timer.isActive()) {
////        m_timer.start(100, this);
////    }
////}
////
////void Buffer::timerEvent(QTimerEvent* ev) {
////    if (ev->timerId() != m_timer.timerId()) return;
////    // in buffer is more frames at 1. If not, stop timer
////    if (frames_buff.size() >= 1) {
////        // read and pop frame in front 
////        m.lock();
////        QPixmap _pixmap = frames_buff.front();
////        // emit framePoped
////        emit pixmapispop(_pixmap);
////        frames_buff.pop_front();
////        m.unlock();
////        //cv::imshow("image", image);
////    }
////    else {
////        m_timer.stop();
////    }
////}