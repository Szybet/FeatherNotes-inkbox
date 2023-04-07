#include "sleepdialog.h"
#include "qdebug.h"
#include "ui_sleepdialog.h"
#include <QFile>

sleepDialog::sleepDialog(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::sleepDialog)
{
    ui->setupUi(this);

    // Stylesheet
    QFile stylesheetFile("/mnt/onboard/.adds/inkbox/eink.qss");
    stylesheetFile.open(QFile::ReadOnly);
    this->setStyleSheet(stylesheetFile.readAll());
    stylesheetFile.close();
}

sleepDialog::~sleepDialog()
{
    delete ui;
}

void sleepDialog::launchSleepDialog()
{
    qDebug() << "Launching sleep dialog";
    this->exec();
}

void sleepDialog::hideSleepDialog()
{
    qDebug() << "Hiding sleep dialog";
    this->hide();
}
