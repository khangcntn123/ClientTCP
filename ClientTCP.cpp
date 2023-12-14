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

    mouse.moveToThread(&EventThread);
    connect(&EventThread, &QThread::finished, &EventThread, &QThread::deleteLater);
    connect(&mouse, &Client::send_Event, &_controller, &DeviceController::sendEvents);
    EventThread.start();
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
    EventThread.quit();
    EventThread.wait();
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


void ClientTCP::device_dataReady(QByteArray data)
{   
    QDataStream stream(&data, QIODevice::ReadOnly);
    count = count + 1;
    if (count == 1) {
        stream >> imageSize;
        QString pstring = QString::number(imageSize);
        ui->lstConsole->addItem("Image Size is:" +pstring);
        int remainingDataSize = data.size() - sizeof(int);
        imageData = data.mid(sizeof(int), remainingDataSize);
        buffer = imageData.size();
        QString p1string = QString::number(buffer);
        ui->lstConsole->addItem("Image data now is: "+ p1string);
    }
    else {
        buffer += data.size();
        if (buffer >= imageSize) {
            int previousdata = buffer - data.size();
            int dataThatMustBeInclude = imageSize - previousdata;
            QByteArray temp;
            temp = data.mid(0, dataThatMustBeInclude);
            QString ps2 = QString::number(dataThatMustBeInclude);
            ui->lstConsole->addItem("Data that must be included: "+ps2);
            imageData.append(temp);
            QString ps11 = QString::number(imageData.size());
            ui->lstConsole->addItem("Data that after included: " + ps11);

            emit video_streaming(imageData);
            int dataReside = buffer - imageSize;
            if (dataReside == 0) {
                count = 0;
                imageData.clear();
                buffer = 0;
            }
            else {
                imageData.clear();
                QByteArray temp1 = data.mid(dataThatMustBeInclude, dataReside);
                imageSize = 0;
                QDataStream stream1(&temp1, QIODevice::ReadOnly);
                stream1 >> imageSize;
                QString pstring10 = QString::number(imageSize);
                ui->lstConsole->addItem("Image Size is:" + pstring10);
                int remainingDataSize = temp1.size() - sizeof(int);
                imageData = data.mid(sizeof(int), remainingDataSize);
                buffer = imageData.size();
                QString p1string = QString::number(buffer);
                ui->lstConsole->addItem("Image data now is: " + p1string);
                count = 1;
            }
        }
        else {
            imageData.append(data);
            QString p1string = QString::number(imageData.size());
            ui->lstConsole->addItem("Image data now is: " + p1string);
        }
    }
}







void ClientTCP::my_video_streaming(QByteArray data) {
    emit sendimage();
    QPixmap pixmap;
    pixmap.loadFromData(data);

    //currentPixmap = pixmap;
    imageLabel->setGeometry(this->rect());
    imageLabel->setPixmap(pixmap);
    imageLabel->setScaledContents(true);
    imageLabel->show();
    imageLabel->update();

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
    connect(&_controller, &DeviceController::dataReady, this, &ClientTCP::device_dataReady);
    connect(this, &ClientTCP::sendimage, &_controller, &DeviceController::sendimagesignal);
    //connect(&myBuffer, &Buffer::pixmapispop, this, &ClientTCP::updateImageLabel);
    connect(this, &ClientTCP::video_streaming, this, &ClientTCP::my_video_streaming);
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


