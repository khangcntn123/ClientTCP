#include "ClientTCP.h"


#include <QMetaEnum>


QThread EventThread;

ClientTCP::ClientTCP(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::ClientTCPClass)
{   

    ui->setupUi(this);
    imageLabel = new QLabel(this);

/*    myBuffer->moveToThread(&bufferThread);
    _controller->moveToThread(&deviceControllerThread)*/;

    //connect(&bufferThread, &QThread::finished,&bufferThread, &QThread::deleteLater);
    //connect(&deviceControllerThread, &QThread::finished,& deviceControllerThread, &QThread::deleteLater);
    //connect(_controller, &DeviceController::dataReady, myBuffer, &Buffer::dataReceived);
    //connect(myBuffer, &Buffer::pixmapispop, this, &ClientTCP::updateImageLabel, Qt::QueuedConnection);
    //bufferThread.start();
    //deviceControllerThread.start();

    //mouse.moveToThread(&EventThread);
    //connect(&EventThread, &QThread::finished, &mouse, &QObject::deleteLater);
    //connect(&mouse, &Client::send_Event, &_controller, &DeviceController::sendEvents);
    //EventThread.start();
    setDeviceController();

}

ClientTCP::~ClientTCP()
{
    //bufferThread.quit();
    //bufferThread.wait();
    //deviceControllerThread.quit();
    //deviceControllerThread.wait();
    //delete myBuffer;
    //delete _controller;
    //EventThread.quit();
    //EventThread.wait();
    delete imageLabel;
    delete ui;
}

void ClientTCP::on_lnIPAddress_textChanged(const QString& arg1)
{
    QString state = "0";
    if (arg1 == "...") {
        state = "";
    }
    else {
        QHostAddress address(arg1);
        if (QAbstractSocket::IPv4Protocol == address.protocol()) {
            state = "1";
        }
    }
    ui->lnIPAddress->setProperty("state", state);
    style()->polish(ui->lnIPAddress);
}


void ClientTCP::on_btnConnect_clicked()
{
    if (_controller.isConnected()) {
        _controller.disconnect();
    }
    else {
        auto ip = ui->lnIPAddress->text();
        auto port = ui->spnPort->value();
        _controller.connectToDevice(ip, port);
    }
}

void ClientTCP::device_connected()
{
    ui->lstConsole->addItem("Connected To Device");
    connect(&mouse, &Client::send_Event, &_controller, &DeviceController::sendEvents);
    ui->btnConnect->setText("Disconnect");
    ui->grpSendData->setEnabled(true);
}

void ClientTCP::device_disconnected()
{
    ui->lstConsole->addItem("Disconnected from Device");
    ui->btnConnect->setText("Connect");
    ui->grpSendData->setEnabled(false);

}

void ClientTCP::device_stateChanged(QAbstractSocket::SocketState state)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketState >();
    ui->lstConsole->addItem(metaEnum.valueToKey(state));
}

void ClientTCP::device_errorOccurred(QAbstractSocket::SocketError error)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketError >();
    ui->lstConsole->addItem(metaEnum.valueToKey(error));

}

void ClientTCP::device_dataReady(QByteArray data) {
   
    QDataStream stream(&data, QIODevice::ReadOnly);

    if (imageSize == 0) {
      
        timer.start();
        stream >> imageSize; 

        imageData.resize(imageSize);
        buffer = data.size() - sizeof(int);
        memcpy(imageData.data(), data.data() + sizeof(int), buffer); 
    }
    else {
        int currentSize = buffer;
        buffer += data.size();
        memcpy(imageData.data() + currentSize, data.data(), data.size()); 
    }

    if (buffer >= imageSize) {

        qint64 elapsed = timer.elapsed();
        QString kkk = QString::number(elapsed);
        ui->lstConsole->addItem("Thoi gian nhan du liue" + kkk + "ms");
        emit video_streaming(imageData);


        imageSize = 0;
        buffer = 0;
        imageData.clear();
    }
}

void ClientTCP::mousePressEvent(QMouseEvent* event) {
    //mouse.mousePressEvent(event);
    QString kaka = QString::number(mouse.countPress);
    ui->lstConsole->addItem("Press : " + kaka);

}
void ClientTCP::mouseReleaseEvent(QMouseEvent* event) {
    mouse.mouseReleaseEvent(event);
    QString kaka = QString::number(mouse.countRelease);
    ui->lstConsole->addItem("Release : " + kaka);
}
void ClientTCP::keyPressEvent(QKeyEvent* event) {
    mouse.keyPressEvent(event);

}


//void ClientTCP::device_dataReady(QByteArray data) {
//    QDataStream stream(&data, QIODevice::ReadOnly);
//
//    if (imageSize == 0) {
//        timer.start();
//        stream >> imageSize;
//        imageData.reserve(imageSize);
//        buffer = data.size() - sizeof(int);
//        imageData.append(data.mid(sizeof(int)));
//    }
//    else {
//        buffer += data.size();
//        imageData.append(data);
//    }
//
//    if (buffer >= imageSize) {
//        qint64 elapsed = timer.elapsed();
//        qDebug() << "Time needed to receive data:" << elapsed << "ms";
//        QString kkk = QString::number(elapsed);
//        ui->lstConsole->addItem("Thoi gian nhan du liue" + kkk + "ms");
//        emit video_streaming(imageData);
//
//        // Reset for next image
//        imageSize = 0;
//        buffer = 0;
//        imageData.clear();
//    }
//}

//void ClientTCP::device_dataReady(QByteArray data) {
//    //QDataStream stream(&data, QIODevice::ReadOnly);
//
//    //if (imageSize == 0) {
//    //    count++;
//    //    QString count1 = QString::number(count);
//    //    ui->lstConsole->addItem("Nhan duoc du lieu lan thu " + count1);
//    //    timer.start();
//    //    stream >> imageSize;
//    //    imageData = QByteArray(); 
//    //    imageData.resize(imageSize);
//    //    int datasize = imageData.size();
//    //    QString qs1 = QString::number(datasize);
//    //    ui->lstConsole->addItem("Kich thuoc anh la: " + qs1);
//    //    buffer = data.size() - sizeof(int);
//    //    //imageData = data.mid(sizeof(int), data.size() - sizeof(int));
//    //    memcpy(imageData.data(), data.data() + sizeof(int), buffer);
//    //}else{
//    //    int currentSize = buffer;
//    //    QString qs2 = QString::number(currentSize);
//    //    ui->lstConsole->addItem("buffer hien tai : " + qs2);
//
//    //    buffer += data.size();
//    //    QString qs3 = QString::number(buffer);
//    //    ui->lstConsole->addItem("buffer sau khi them du lieu: " + qs3);
//    //    QString qs4 = QString::number(imageData.size());
//    //    ui->lstConsole->addItem("Du lieu anh hien tai la: " + qs4);
//    //    if (buffer > imageData.size()) {
//    //        MessageBox(NULL, TEXT("Tran du lieu"), TEXT("Title of the Message Box"), MB_OK);
//    //    }
//    //    //imageData.append(data);
//    //    memcpy(imageData.data() + currentSize, data.data(), data.size());
//    //}
//    //if (buffer >= imageSize) {
//    //    qint64 elapsed = timer.elapsed();
//    //    QString mystring = QString::number(elapsed);
//    //    ui->lstConsole->addItem("Time need to receive data:  " + mystring + " ms");
//    //    //qDebug() << "Time needed to receive data:" << elapsed << "ms";
//    //    emit video_streaming(imageData);
//    //    imageSize = 0;
//    //    buffer = 0;
//    //    imageData.clear();
//    QDataStream stream(&data, QIODevice::ReadOnly);
//    //MessageBox(NULL, TEXT("Nhan duoc du lieu"), TEXT("Title of the Message Box"), MB_OK);
//
//    if (imageSize == 0) {
//        count++;
//        QString count1 = QString::number(count);
//        ui->lstConsole->addItem("Nhan duoc du lieu lan thu " + count1);
//        timer.start();
//        stream >> imageSize; 
//        imageData.resize(imageSize);
//        buffer = data.size() - sizeof(int);
//        memcpy(imageData.data(), data.data() + sizeof(int), buffer);
//    }
//    else {
//        int currentSize = buffer;
//        buffer += data.size();
//        if (buffer >= imageSize) {
//            int dataneed = imageSize - currentSize;
//            int datareside = buffer - imageSize;
//            qint64 elapsed = timer.elapsed();
//            QString mystring = QString::number(elapsed);
//            ui->lstConsole->addItem("Time need to receive data:  " + mystring +" ms");
//            memcpy(imageData.data() + currentSize, data.data(), dataneed);
//            //MessageBox(NULL, TEXT("Tha ra tin hieu de hien thi hinh anh"), TEXT("Title of the Message Box"), MB_OK);
//
//            emit video_streaming(imageData);
//               imageSize = 0;
//               buffer = 0;
//               imageData.clear();
//            if (datareside > 0) {
//                QByteArray temp;
//                memcpy(temp.data(), data.data() + dataneed, sizeof(int));
//                QDataStream tempstream(&temp, QIODevice::ReadOnly);
//                stream >> imageSize;
//                imageData.resize(imageSize);
//                memcpy(imageData.data(), data.data() + dataneed + sizeof(int), datareside);
//            }
//        }
//        else {
//            memcpy(imageData.data() + currentSize, data.data(), data.size());
//        }
//      
//    }
//
//    //if (buffer >= imageSize) {
//    //    int previousdata = buffer - data.size();
//    //    int dataThatMustBeInclude = imageSize - previousdata;
//    //    qint64 elapsed = timer.elapsed();
//    //    QString mystring = QString::number(elapsed);
//    //    ui->lstConsole->addItem("Time need to receive data:  " + mystring +" ms");
//    //    //qDebug() << "Time needed to receive data:" << elapsed << "ms";
//    //    emit video_streaming(imageData);
//    //    imageSize = 0;
//    //    buffer = 0;
//    //    imageData.clear();
//    //}
// 
//}
//

//void ClientTCP::device_dataReady(QByteArray data)
//{   
//    QDataStream stream(&data, QIODevice::ReadOnly);
//    if (imageSize == 0) {
//        timer.start();
//        stream >> imageSize;
//        QString pstring = QString::number(imageSize);
//        ui->lstConsole->addItem("Image Size is:" +pstring);
//        int remainingDataSize = data.size() - sizeof(int);
//        imageData = data.mid(sizeof(int), remainingDataSize);
//        buffer = imageData.size();
//        QString p1string = QString::number(buffer);
//        ui->lstConsole->addItem("Image data now is: "+ p1string);
//    }
//    else {
//        buffer += data.size();
//        if (buffer >= imageSize) {
//            int previousdata = buffer - data.size();
//            int dataThatMustBeInclude = imageSize - previousdata;
//            QByteArray temp;
//            temp = data.mid(0, dataThatMustBeInclude);
//            QString ps2 = QString::number(dataThatMustBeInclude);
//            ui->lstConsole->addItem("Data that must be included: "+ps2);
//            imageData.append(temp);
//            QString ps11 = QString::number(imageData.size());
//            ui->lstConsole->addItem("Data that after included: " + ps11);
//            qint64 elapsed = timer.elapsed();
//            QString elapsedStr = QString::number(elapsed);
//            ui->lstConsole->addItem("Time that need to receive data: " + elapsedStr + "ms");
//            emit video_streaming(imageData);
//            int dataReside = buffer - imageSize;
//            if (dataReside == 0) {
//                imageSize = 0;
//                imageData.clear();
//                buffer = 0;
//            }
//            else {
//                imageData.clear();
//                QByteArray temp1 = data.mid(dataThatMustBeInclude, dataReside);
//                imageSize = 0;
//                QDataStream stream1(&temp1, QIODevice::ReadOnly);
//                stream1 >> imageSize;
//                QString pstring10 = QString::number(imageSize);
//                ui->lstConsole->addItem("Image Size is:" + pstring10);
//                int remainingDataSize = temp1.size() - sizeof(int);
//                imageData = data.mid(sizeof(int), remainingDataSize);
//                buffer = imageData.size();
//                QString p1string = QString::number(buffer);
//                ui->lstConsole->addItem("Image data now is: " + p1string);
//            }
//        }
//        else {
//            imageData.append(data);
//            QString p1string = QString::number(imageData.size());
//            ui->lstConsole->addItem("Image data now is: " + p1string);
//        }
//    }
//}
//






void ClientTCP::my_video_streaming(QByteArray data) {
    //MessageBox(NULL, TEXT("Hien thi duoc anh"), TEXT("Title of the Message Box"), MB_OK);
    emit sendimage();

    timer.start();

    QPixmap pixmap;
    pixmap.loadFromData(data);

    //currentPixmap = pixmap;
    imageLabel->setGeometry(this->rect());
    imageLabel->setPixmap(pixmap);
    imageLabel->setScaledContents(true);
    imageLabel->show();
    imageLabel->update();
    qint64 kekeke= timer.elapsed();
    QString kkk = QString::number(kekeke);
    ui->lstConsole->addItem("Thoi gian hien anh len man hinh :" + kkk + "ms");
    QString count1 = QString::number(count);
    ui->lstConsole->addItem("yeu cau ben kia gui hinh anh lan : " + count1);
    ui->lstConsole->addItem("Da gui tin hieu keu gui hinh anh ");

}



//void ClientTCP::my_video_streaming(QByteArray data) {
//    QThread* thread = QThread::create([=]() {
//        QPixmap pixmap;
//        pixmap.loadFromData(data);
//    
//        QMetaObject::invokeMethod(this, [=]() {
//        updateImageLabel(pixmap);
//        });
//        QThread::currentThread()->quit();
//        });
//
//    thread->start();
//}

//void ClientTCP::updateImageLabel(QPixmap pixmap) {
//    imageLabel->setGeometry(this->rect());
//    imageLabel->setPixmap(pixmap);
//    imageLabel->setScaledContents(true);
//    imageLabel->show();
//    imageLabel->update();
//}

void ClientTCP::setDeviceController()
{   
    connect(&_controller, &DeviceController::connected, this, &ClientTCP::device_connected);
    connect(&_controller, &DeviceController::disconnected, this, &ClientTCP::device_disconnected);
    connect(&_controller, &DeviceController::stateChanged, this, &ClientTCP::device_stateChanged);
    connect(&_controller, &DeviceController::errorOccurred, this, &ClientTCP::device_errorOccurred);
    
    //connect(this, &ClientTCP::mousePressEvent, &mouse, &Client::mousePressEvent);
    //connect(&_controller, &DeviceController::dataReady, this, &ClientTCP::device_dataReady);
    //connect(this, &ClientTCP::sendimage, &_controller, &DeviceController::sendimagesignal);
    //connect(&myBuffer, &Buffer::pixmapispop, this, &ClientTCP::updateImageLabel);
    //connect(this, &ClientTCP::video_streaming, this, &ClientTCP::my_video_streaming);
}



//void ClientTCP::pixmapisready(QPixmap _mpixmap) {
//    updateImageLabel(_mpixmap);
//  
//}

void ClientTCP::on_btnSend_clicked()
{
    auto message = ui->lnMessage->text().trimmed();
    _controller.send(message);
}

void ClientTCP::on_btnClear_clicked() {
    ui->lstConsole->clear();

}


