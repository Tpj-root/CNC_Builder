#include "wavecontrolwindow.h"
#include <cmath>

WaveControlWindow::WaveControlWindow(QWidget *parent)
    : QMainWindow(parent),
      numMotors(12),
      amp(1.0),
      step(0.05),
      basePhaseShift(M_PI / 6),
      waveFactorValue(0.0),
      strokeLengthValue(1),
      t(0.0)
{
    mainWidget = new QWidget(this);
    mainLayout = new QVBoxLayout(mainWidget);

    // Control Sliders
    QHBoxLayout *controlLayout = new QHBoxLayout;

    QLabel *waveLabel = new QLabel("Wave Factor (0 - 10):");
    waveSlider = new QSlider(Qt::Horizontal);
    waveSlider->setRange(0, 10);  // represents 0.0 to 1.0
    waveSlider->setValue(0);
    connect(waveSlider, &QSlider::valueChanged, this, [=](int val) {
        waveFactorValue = val / 10.0;
    });

    QLabel *strokeLabel = new QLabel("Stroke Length (1 - 10):");
    strokeSlider = new QSlider(Qt::Horizontal);
    strokeSlider->setRange(1, 10);
    strokeSlider->setValue(1);
    connect(strokeSlider, &QSlider::valueChanged, this, [=](int val) {
        strokeLengthValue = val;
    });

    controlLayout->addWidget(waveLabel);
    controlLayout->addWidget(waveSlider);
    controlLayout->addSpacing(20);
    controlLayout->addWidget(strokeLabel);
    controlLayout->addWidget(strokeSlider);

    mainLayout->addLayout(controlLayout);

    // Chart
    setupChart();
    mainLayout->addWidget(chartView);

    // Timer for animation
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &WaveControlWindow::updateWave);
    timer->start(50);

    setCentralWidget(mainWidget);
    setWindowTitle("Wave Control Slider");
    resize(800, 400);
}

WaveControlWindow::~WaveControlWindow() {}

void WaveControlWindow::setupChart()
{
    barSet = new QBarSet("Motors");
    for (int i = 0; i < numMotors; ++i)
        *barSet << 0;

    series = new QBarSeries();
    series->append(barSet);

    chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Stepper Motors Moving Up/Down");

    axisY = new QValueAxis;
    axisY->setRange(-15, 15);
    chart->setAxisY(axisY, series);

    chart->legend()->hide();
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
}

QVector<double> WaveControlWindow::generateWavePositions()
{
    QVector<double> positions(numMotors);
    double currentPhaseShift = basePhaseShift * waveFactorValue;
    for (int i = 0; i < numMotors; ++i)
        positions[i] = amp * sin(2 * M_PI * 0.5 * t + i * currentPhaseShift);
    return positions;
}

void WaveControlWindow::updateWave()
{
    QVector<double> positions = generateWavePositions();
    for (int i = 0; i < numMotors; ++i)
        barSet->replace(i, positions[i] * strokeLengthValue);
    t += step;
}
