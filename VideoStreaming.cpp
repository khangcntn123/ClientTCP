//#include "VideoStreaming.h"
//
//VideoStreaming::VideoStreaming(QObject *parent)
//	: QObject(parent)
//{}
//
//VideoStreaming::~VideoStreaming()
//{}
//
//void VideoStreaming::device_dataReady(QByteArray data) {
//
//    QDataStream stream(&data, QIODevice::ReadOnly);
//
//    if (imageSize == 0) {
//
//        timer.start();
//        stream >> imageSize;
//
//        imageData.resize(imageSize);
//        buffer = data.size() - sizeof(int);
//        memcpy(imageData.data(), data.data() + sizeof(int), buffer);
//    }
//    else {
//        int currentSize = buffer;
//        buffer += data.size();
//        memcpy(imageData.data() + currentSize, data.data(), data.size());
//    }
//
//    if (buffer >= imageSize) {
//
//        qint64 elapsed = timer.elapsed();
//        QString kkk = QString::number(elapsed);
//        emit video_streaming(imageData);
//        imageSize = 0;
//        buffer = 0;
//        imageData.clear();
//    }
//}
//
//void VideoStreaming::my_video_streaming(QByteArray data) {
//    //MessageBox(NULL, TEXT("Hien thi duoc anh"), TEXT("Title of the Message Box"), MB_OK);
//    emit sendimage();
//
//    timer.start();
//
//    QPixmap pixmap;
//    pixmap.loadFromData(data);
//
//    //currentPixmap = pixmap;
//    imageLabel->setGeometry(this->rect());
//    imageLabel->setPixmap(pixmap);
//    imageLabel->setScaledContents(true);
//    imageLabel->show();
//    imageLabel->update();
//    qint64 kekeke = timer.elapsed();
//    QString kkk = QString::number(kekeke);
//    ui->lstConsole->addItem("Thoi gian hien anh len man hinh :" + kkk + "ms");
//    QString count1 = QString::number(count);
//    ui->lstConsole->addItem("yeu cau ben kia gui hinh anh lan : " + count1);
//    ui->lstConsole->addItem("Da gui tin hieu keu gui hinh anh ");
//
//}