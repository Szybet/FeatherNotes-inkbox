#include "sleepthread.h"
#include "qdebug.h"
#include "qdir.h"
#include "qthread.h"

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

sleepThread::sleepThread() {}

void sleepThread::start()
{
    qDebug() << "Sleep pipe thread active";
    QDir pipeDirPath = QDir("/dev/ipd");
    QFile pipePath = QFile("/dev/ipd/fifo");
    while(true) {
        QThread::sleep(1);
        if(pipePath.exists() == true and pipeDirPath.exists() == true) {
            qDebug() << "Looking for messages in pipe";
            char * pipe = "/dev/ipd/fifo";
            int fd = ::open(pipe, O_RDONLY);
            char * readchar[5];
            ::read(fd, readchar, 5);

            QString result = QString::fromUtf8((const char *)readchar, 5);

            qDebug() << "Received from pipe: ";

            ::close(fd);

            if(result == "start") {
                qDebug() << "Emiting signal to show sleepDialog";
                emit startDialog();
            }
            else if (result == "stop0") {
                qDebug() << "Emiting signal to hide sleepDialog";

                emit stopDialog();
            }
            else {
                qDebug() << "Something went wrong";
            }
        }
    }
}
