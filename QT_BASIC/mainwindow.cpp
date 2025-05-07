#include "mainwindow.h"
#include <QVBoxLayout>
#include <QString>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    resize(300, 200);  // Set window size

    button = new QPushButton("Click Me", this);
    button->setGeometry(20, 20, 100, 30); // x, y, width, height

    label = new QLabel("0", this);
    label->setGeometry(20, 60, 100, 30);

    slider = new QSlider(Qt::Horizontal, this);

    slider->setGeometry(20, 100, 200, 30);
    slider->setRange(0, 100);


    slider2 = new QSlider(Qt::Vertical, this);
	slider2->setGeometry(250, 20, 30, 150);
    slider2->setRange(0, 100);


    connect(slider, &QSlider::valueChanged, this, &MainWindow::updateLabel);
}


void MainWindow::updateLabel(int value) {
    label->setText(QString::number(value));
}
