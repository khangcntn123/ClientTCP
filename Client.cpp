#include "Client.h"

Client::Client(QWidget* parent)
    : QMainWindow(parent)
{


    //ui.setupUi(this);
   /* int x = sk.init_and_connect();*/
    //if (x == 1) ui.label_c1->setText("False");
    //if (x == 2) ui.label_c2->setText("False");
    //if (x == 3) ui.label_c3->setText("False");
    //mouseUpdateTimer = new QTimer(this);
    //connect(mouseUpdateTimer, &QTimer::timeout, this, &Client::updateMousePosition);
    //mouseUpdateTimer->start(10); 

}

Client::~Client()
{
    //sk.break_up();
}
void Client::keyPressEvent(QKeyEvent* event)
{
    //if (event->key() == Qt::Key_A) {
    //    INPUT keyInput;
    //    keyInput.type = INPUT_KEYBOARD;
    //    keyInput.ki.time = 0;
    //    keyInput.ki.dwExtraInfo = 0;
    //    keyInput.ki.wVk = 0x42;
    //    SendInput(0, &keyInput, sizeof(keyInput));
    //    keyInput.ki.dwFlags = KEYEVENTF_KEYUP;
    //    SendInput(0, &keyInput, sizeof(keyInput));
    //}
    //ui.key_press->setText(QChar(event->key()));
    int k = 0;
    if ((event->key() >= 0x30 && event->key() <= 0x39) || (event->key() >= 0x41 && event->key() <= 0x5A)) {
        k = event->key();
    }
    else {
        switch (event->key())
        {
        case Qt::Key_Tab:
            k = VK_TAB;
            break;
        case Qt::Key_Escape:
            k = VK_ESCAPE;
            break;
        case Qt::Key_Shift:
            k = VK_SHIFT;
            break;
        case Qt::Key_Space:
            k = VK_SPACE;
            break;
        case Qt::Key_Control:
            k = VK_CONTROL;
            break;
        case Qt::Key_CapsLock:
            k = VK_CAPITAL;
            break;
        case Qt::Key_Enter:
            k = VK_RETURN;
            break;
        case Qt::Key_Alt:
            k = VK_MENU;
            break;
        default:
            break;
        }
    }
        emit send_Event(KEY_DOWN, k, 0);

    //sk.send_Event(KEY_DOWN, k, 0);
}
//void CLIENT::keyReleaseEvent(QKeyEvent* event) {
//    int k = 0;
//    if ((event->key() >= 0x30 && event->key() <= 0x39) || (event->key() >= 0x41 && event->key() <= 0x5A)) {
//        k = event->key();
//    }
//    else {
//        switch (event->key())
//        {
//        case Qt::Key_Tab:
//            k = VK_TAB;
//            break;
//        case Qt::Key_Escape:
//            k = VK_ESCAPE;
//            break;
//        case Qt::Key_Shift:
//            k = VK_SHIFT;
//            break;
//        case Qt::Key_Space:
//            k = VK_SPACE;
//            break;
//        case Qt::Key_Control:
//            k = VK_CONTROL;
//            break;
//        case Qt::Key_CapsLock:
//            k = VK_CAPITAL;
//            break;
//        case Qt::Key_Enter:
//            k = VK_RETURN;
//            break;
//        case Qt::Key_Alt:
//            k = VK_MENU;
//            break;
//        default:
//            break;
//        }
//    }
//    sk.send_Event(KEY_UP, k, 0);
//}
void Client::updateMousePosition()
{

    QPoint pos = QCursor::pos();
    //ui.label_move->setText("Mouse Move Send: X: " + QString::number(sk.data[1]) + " Y: " + QString::number(sk.data[2]));
    //if (!sk.send_Event(0, pos.x(), pos.y()));
    //ui.label_double_click->setText("Mouse Move Client: X: " + QString::number(sk.data[1]) + " Y: " + QString::number(sk.data[2]));

        emit send_Event(0, pos.x(), pos.y());

}
//void ActiveClient::mouseMoveEvent(QMouseEvent* event) {
//    QPoint pos = QCursor::pos();
//    //sk.send_Event(0, pos.x(), pos.y());
//    ui.label_move->setText("Mouse Move: X: " + QString::number(pos.x()) + " Y: " + QString::number(pos.y()));
//}
void Client::mousePressEvent(QMouseEvent* event)
{
    //MessageBox(NULL, TEXT("Press left mouse"), TEXT("Title of the Message Box"), MB_OK);
    countPress++;

    QPoint pos = QCursor::pos();
    if (event->button() == Qt::LeftButton) {
       // MessageBox(NULL, TEXT("Press left mouse"), TEXT("Title of the Message Box"), MB_OK);

      /*  sk.send_Event(1, pos.x(), pos.y());
        ui.label_press->setText("Mouse Press L: X: " + QString::number(pos.x()) + " Y: " + QString::number(pos.y()));*/
          emit send_Event(3, pos.x(), pos.y());
          

    }
    if (event->button() == Qt::RightButton) {
     /*   sk.send_Event(2, pos.x(), pos.y());
        ui.label_press->setText("Mouse Press R: X: " + QString::number(pos.x()) + " Y: " + QString::number(pos.y()));*/
        emit send_Event(2, pos.x(), pos.y());
    }
 /*   count = 0;*/
}
void Client::mouseReleaseEvent(QMouseEvent* event) {
    //MessageBox(NULL, TEXT("Release left mouse"), TEXT("Title of the Message Box"), MB_OK);
    countRelease++;
    QPoint pos = QCursor::pos();
    if (event->button() == Qt::LeftButton) {
       /* sk.send_Event(3, pos.x(), pos.y());
        ui.label_release->setText("Mouse Release L: X: " + QString::number(pos.x()) + " Y: " + QString::number(pos.y()));*/
        emit send_Event(1, pos.x(), pos.y());
    }
    if (event->button() == Qt::RightButton) {
     /*   sk.send_Event(4, pos.x(), pos.y());
        ui.label_release->setText("Mouse Release R: X: " + QString::number(pos.x()) + " Y: " + QString::number(pos.y()));*/
        emit send_Event(4, pos.x(), pos.y());
    }
}
void Client::mouseDoubleClickEvent(QMouseEvent* event) {
    QPoint pos = QCursor::pos();
    if (event->button() == Qt::LeftButton) {
       /* ui.label_double_click->setText("Mouse Double Click L: X: " + QString::number(pos.x()) + " Y: " + QString::number(pos.y()));
        sk.send_Event(5, pos.x(), pos.y());*/
    }
    if (event->button() == Qt::RightButton) {
    /*    ui.label_double_click->setText("Mouse Double Click R: X: " + QString::number(pos.x()) + " Y: " + QString::number(pos.y()));
        sk.send_Event(6, pos.x(), pos.y());*/
    }
}



//#include "Client.h"
//
//Client::Client(QObject *parent)
//	: QObject(parent)
//{
//	//mouseUpdateTimer = new QTimer(this);
//	//connect(mouseUpdateTimer, &QTimer::timeout, this, &Client::updateMousePosition);
//	//mouseUpdateTimer->start(100);
//
//
//}
//
//Client::~Client()
//{
//    delete mouseUpdateTimer;
//}
//
//void Client::keyPressEvent(QKeyEvent* event)
//{
//    //if (event->key() == Qt::Key_A) {
//    //    INPUT keyInput;
//    //    keyInput.type = INPUT_KEYBOARD;
//    //    keyInput.ki.time = 0;
//    //    keyInput.ki.dwExtraInfo = 0;
//    //    keyInput.ki.wVk = 0x42;
//    //    SendInput(0, &keyInput, sizeof(keyInput));
//    //    keyInput.ki.dwFlags = KEYEVENTF_KEYUP;
//    //    SendInput(0, &keyInput, sizeof(keyInput));
//    //}
//    //ui.key_press->setText(QChar(event->key()));
//    int k = 0;
//    if ((event->key() >= 0x30 && event->key() <= 0x39) || (event->key() >= 0x41 && event->key() <= 0x5A)) {
//        k = event->key();
//    }
//    else {
//        switch (event->key())
//        {
//        case Qt::Key_Tab:
//            k = VK_TAB;
//            break;
//        case Qt::Key_Escape:
//            k = VK_ESCAPE;
//            break;
//        case Qt::Key_Shift:
//            k = VK_SHIFT;
//            break;
//        case Qt::Key_Space:
//            k = VK_SPACE;
//            break;
//        case Qt::Key_Control:
//            k = VK_CONTROL;
//            break;
//        case Qt::Key_CapsLock:
//            k = VK_CAPITAL;
//            break;
//        case Qt::Key_Enter:
//            k = VK_RETURN;
//            break;
//        case Qt::Key_Alt:
//            k = VK_MENU;
//            break;
//        default:
//            break;
//        }
//    }
//    MessageBox(NULL, TEXT("Da gui tin hieu ban phim di"), TEXT("Title of the Message Box"), MB_OK);
//
//    emit send_Event(KEY_DOWN, k, 0);
//}

//void Client::updateMousePosition()
//{
//
//    QPoint pos = QCursor::pos();
//   /* ui.label_move->setText("Mouse Move Send: X: " + QString::number(sk.data[1]) + " Y: " + QString::number(sk.data[2]));*/
//    emit send_Event(0, pos.x(), pos.y());
//   /* ui.label_double_click->setText("Mouse Move Client: X: " + QString::number(sk.data[1]) + " Y: " + QString::number(sk.data[2]));*/
//}
////void ActiveClient::mouseMoveEvent(QMouseEvent* event) {
////    QPoint pos = QCursor::pos();
////    //sk.send_Event(0, pos.x(), pos.y());
////    ui.label_move->setText("Mouse Move: X: " + QString::number(pos.x()) + " Y: " + QString::number(pos.y()));
////}
//void Client::mousePressEvent(QMouseEvent* event)
//{  
//    QPoint pos = QCursor::pos();
//    if (event->button() == Qt::LeftButton) {
//        MessageBox(NULL, TEXT("Da gui tin hieu nhan chuot trai di"), TEXT("Title of the Message Box"), MB_OK);
//        emit send_Event(1, pos.x(), pos.y());
//       /* ui.label_press->setText("Mouse Press L: X: " + QString::number(pos.x()) + " Y: " + QString::number(pos.y()));*/
//    }
//    if (event->button() == Qt::RightButton) {
//        emit send_Event(2, pos.x(), pos.y());
//        MessageBox(NULL, TEXT("Da gui tin hieu nhan chuot phai di"), TEXT("Title of the Message Box"), MB_OK);
//
//        //ui.label_press->setText("Mouse Press R: X: " + QString::number(pos.x()) + " Y: " + QString::number(pos.y()));
//    }
//}
//void Client::mouseReleaseEvent(QMouseEvent* event) {
//    QPoint pos = QCursor::pos();
//    if (event->button() == Qt::LeftButton) {
//        MessageBox(NULL, TEXT("Da gui tin hieu tha chuot trai di"), TEXT("Title of the Message Box"), MB_OK);
//
//        emit send_Event(3, pos.x(), pos.y());
//    /*    ui.label_release->setText("Mouse Release L: X: " + QString::number(pos.x()) + " Y: " + QString::number(pos.y()));*/
//    }
//    if (event->button() == Qt::RightButton) {
//        MessageBox(NULL, TEXT("Da gui tin hieu tha chuot phai di"), TEXT("Title of the Message Box"), MB_OK);
//
//        emit send_Event(4, pos.x(), pos.y());
//       /* ui.label_release->setText("Mouse Release R: X: " + QString::number(pos.x()) + " Y: " + QString::number(pos.y()));*/
//    }
//}
//void Client::mouseDoubleClickEvent(QMouseEvent* event) {
//    QPoint pos = QCursor::pos();
//    if (event->button() == Qt::LeftButton) {
//        //ui.label_double_click->setText("Mouse Double Click L: X: " + QString::number(pos.x()) + " Y: " + QString::number(pos.y()));
//        emit send_Event(5, pos.x(), pos.y());
//    }
//    if (event->button() == Qt::RightButton) {
//       /* ui.label_double_click->setText("Mouse Double Click R: X: " + QString::number(pos.x()) + " Y: " + QString::number(pos.y()));*/
//        emit send_Event(6, pos.x(), pos.y());
//    }
//}
