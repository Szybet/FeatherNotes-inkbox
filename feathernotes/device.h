#ifndef DEVICE_H
#define DEVICE_H

#include <QDialog>

namespace Ui {
class device;
}

class device : public QDialog
{
    Q_OBJECT

public:
    explicit device(QWidget *parent = nullptr);
    ~device();

private slots:
    void on_pushButton_clicked();

    void on_brightnessSlider_valueChanged(int value);

private:
    Ui::device *ui;
};

#endif // DEVICE_H
