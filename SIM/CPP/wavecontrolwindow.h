#ifndef WAVECONTROLWINDOW_H
#define WAVECONTROLWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSlider>
#include <QLabel>
#include <QTimer>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>
#include <QValueAxis>

QT_CHARTS_USE_NAMESPACE

class WaveControlWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit WaveControlWindow(QWidget *parent = nullptr);
    ~WaveControlWindow();

private:
    void setupChart();
    QVector<double> generateWavePositions();
    void updateWave();

    QWidget *mainWidget;
    QVBoxLayout *mainLayout;

    QSlider *waveSlider;
    QSlider *strokeSlider;

    QChart *chart;
    QChartView *chartView;
    QBarSet *barSet;
    QBarSeries *series;
    QValueAxis *axisY;
    QTimer *timer;

    int numMotors;
    double amp;
    double step;
    double basePhaseShift;
    double waveFactorValue;
    int strokeLengthValue;
    double t;
};

#endif // WAVECONTROLWINDOW_H
