#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QSlider>

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void updateLabel(int value);

private:
    QPushButton *button;
    QLabel *label;
    QSlider *slider;
    QSlider *slider2;
};

#endif // MAINWINDOW_H
