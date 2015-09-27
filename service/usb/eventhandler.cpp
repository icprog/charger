#include <QDebug>
#include <QtCore/QThread>

#include "libusb.h"
#include "eventhandler.h"

UseQtEventDriver::UseQtEventDriver(libusb_context *context, QObject *parent) :
    QObject(parent), context(context), timer(0)
{
    timer = new QTimer(this);
    timer->setInterval(1);
    
    connect(timer, SIGNAL(timeout()), this, SLOT(handle()));
    
    timer->start();
}

UseQtEventDriver::~UseQtEventDriver() {
    timer->stop();
}

void UseQtEventDriver::handle()
{
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 100000;
    libusb_handle_events_timeout(this->context, &tv);
    qDebug() << "event finished";
}



