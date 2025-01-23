#include "arduino.h"

#include <QDateTime>
#include <QSerialPortInfo>
#include <qdebug.h>

Arduino::Arduino()
{
    QList<QSerialPortInfo> ports= QSerialPortInfo::availablePorts();
    if(ports.size()>0)
    { for (int i= 0; i < ports.size(); i++)
            portList<<ports[i].portName()+" / "+ports[i].description();
    }
    connect(this,SIGNAL(readyRead()),SLOT(OnReadyRead()));
}

bool Arduino::open(int idxPort, int BaudRate)
{
    if(isOpen())
        close();
    QString port = portList[idxPort].left(portList[idxPort].indexOf("/"));
    setPortName(port);
    if(!QSerialPort::open(QIODevice::ReadWrite))
        return false;
    setBaudRate(BaudRate);
    setDataBits(QSerialPort::Data8);
    setFlowControl(QSerialPort::UnknownFlowControl );
    setParity(QSerialPort::NoParity);
    setStopBits(QSerialPort::OneStop);
    return true;
}

bool Arduino::echo()
{
    if(!isOpen())
        return false;
    trame.cmd = ECHO;
    trame.fin = FIN_TRAME;
    if(write(trame.data,sizeof(trame)) == sizeof (trame))
        return true;
    return false;
}

bool Arduino::setTime()
{
    QDateTime dateTime = QDateTime::currentDateTime();
    int jSem = dateTime.date().dayOfWeek();

    trame.cmd= SET_TIME; // Met à l'heure
    trame.heure= static_cast<unsigned char>(dateTime.time().hour());
    trame.minute= static_cast<unsigned char>(dateTime.time().minute());
    trame.seconde= static_cast<unsigned char>(dateTime.time().second());
    if(jSem>=7) jSem=0;
    trame.jourSem= static_cast<unsigned char>(jSem);
    trame.jour= static_cast<unsigned char>(dateTime.date().day());
    trame.mois= static_cast<unsigned char>(dateTime.date().month());
    trame.annee= static_cast<unsigned char>(dateTime.date().year() - 2000);

    trame.fin = FIN_TRAME;

    if(write(trame.data, sizeof(trame)) == sizeof(trame))
        return true;
    return false;
}

bool Arduino::getTime()
{
    if(!isOpen())
        return false;
    trame.cmd = GET_TIME;
    trame.fin = FIN_TRAME;
    if(write(trame.data,sizeof(trame)) == sizeof (trame))
        return true;
    return false;
}

void Arduino::OnReadyRead()
{
    if(bytesAvailable())
    { data+= readAll();
        if(data.contains("\n"))
        { emit envoi(QString::fromLatin1(data));
            qDebug() << data;
            data.clear();
        }
    }
}
