#include "device.h"
#include "ui_device.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>

device::device(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::device)
{
    ui->setupUi(this);



    // No support for other devices.
    QFile file("/sys/bus/platform/devices/ricoh619-battery/power_supply/mc13892_bat/capacity");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString contents = QString(file.readAll()).replace("\n", "");
        ui->BatteryLabel->setText("Battery level: " + contents + "%");
    }
    file.close();

    QFile file2("/sys/class/backlight/mxc_msp430.0/brightness");
    if (file2.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString contents = QString(file2.readAll());
        int value = contents.toInt();
        qDebug() << "Initial brightness" << value;
        ui->brightnessSlider->setSliderPosition(value);
    }
    file2.close();
}

device::~device()
{
    delete ui;
}

void device::on_pushButton_clicked()
{
    this->deleteLater();
    this->close();
}


void device::on_brightnessSlider_valueChanged(int value)
{
    QString path = "/sys/class/backlight/mxc_msp430.0/brightness";
    QFile file(path);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << value;
        file.close();
    }
}

