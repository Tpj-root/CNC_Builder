#ifndef WAVECONTROLWINDOW_H
#define WAVECONTROLWINDOW_H

#include <QtCharts>
#include <QMainWindow>
#include <QTimer>
#include <QVBoxLayout>
#include <QSlider>

QT_CHARTS_USE_NAMESPACE

class WaveControlWindow : public QMainWindow
{
    Q_OBJECT

public:
    WaveControlWindow(QWidget *parent = nullptr);
    ~WaveControlWindow();

private slots:
    void updateWave();
    void updateWaveFactor(int value);
    void updateStrokeLength(int value);

private:
    void setupChart();

    QWidget *mainWidget;
    QVBoxLayout *mainLayout;

    QChart *chart;
    QChartView *chartView;
    QBarSeries *series;
    QBarSet *barSet;
    QBarCategoryAxis *axisX;
    QValueAxis *axisY;

    int numMotors;
    double amp, step, basePhaseShift, waveFactorValue, strokeLengthValue, t;

    QTimer *timer;
    QSlider *waveFactorSlider;
    QSlider *strokeLengthSlider;
};

#endif // WAVECONTROLWINDOW_H
