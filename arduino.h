#ifndef ARDUINO_H
#define ARDUINO_H

#include <QSerialPort>



class Arduino : public QSerialPort
{
    Q_OBJECT
    union uTrame
    { struct
        { unsigned char cmd;
            unsigned char heure;
            unsigned char minute;
            unsigned char seconde;
            unsigned char jourSem;
            unsigned char jour;
            unsigned char mois;
            unsigned char annee;
            unsigned char fin;
        };
        char data[9];
    } trame;
    QByteArray data;
    enum ARDUINO {ECHO=252,GET_TIME=253,SET_TIME=254,FIN_TRAME=255};

public:
    Arduino();
    QStringList portList;
    bool open(int idxPort, int BaudRate);
    bool echo();
    bool setTime();
    bool getTime();

private slots :
    void OnReadyRead();

signals :
    void envoi(QString);
};

#endif // ARDUINO_H
