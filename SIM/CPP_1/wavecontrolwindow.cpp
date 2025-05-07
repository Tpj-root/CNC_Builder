#include "wavecontrolwindow.h"
#include <cmath>
#include <QSlider>
#include <QLabel>

WaveControlWindow::WaveControlWindow(QWidget *parent)
    : QMainWindow(parent),
      numMotors(12),
      amp(1.0),  // Initial amplitude
      step(0.05),
      basePhaseShift(M_PI / 6),
      waveFactorValue(1.0),  // Full wave initially
      strokeLengthValue(5),  // Default stroke length
      t(0.0)
{
    mainWidget = new QWidget(this);
    mainLayout = new QVBoxLayout(mainWidget);

    // Control Section with Sliders
    QVBoxLayout *controlLayout = new QVBoxLayout;

    // Wave Factor Slider
    waveFactorSlider = new QSlider(Qt::Horizontal);
    waveFactorSlider->setRange(0, 100);  // range from 0 to 100 (0.0 to 1.0)
    waveFactorSlider->setValue(100);  // Default value (full wave)
    connect(waveFactorSlider, &QSlider::valueChanged, this, &WaveControlWindow::updateWaveFactor);
    controlLayout->addWidget(new QLabel("Wave Factor"));
    controlLayout->addWidget(waveFactorSlider);

    // Stroke Length Slider
    strokeLengthSlider = new QSlider(Qt::Horizontal);
    strokeLengthSlider->setRange(1, 10);  // range from 1 to 10 (for amplitude control)
    strokeLengthSlider->setValue(5);  // Default value
    connect(strokeLengthSlider, &QSlider::valueChanged, this, &WaveControlWindow::updateStrokeLength);
    controlLayout->addWidget(new QLabel("Stroke Length"));
    controlLayout->addWidget(strokeLengthSlider);

    mainLayout->addLayout(controlLayout);

    // Chart Setup
    setupChart();
    mainLayout->addWidget(chartView);

    // Timer for animation
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &WaveControlWindow::updateWave);
    timer->start(50);

    setCentralWidget(mainWidget);
    setWindowTitle("Wave Control with Sliders");
    resize(800, 400);
}

WaveControlWindow::~WaveControlWindow() {}

void WaveControlWindow::setupChart()
{
    barSet = new QBarSet("Motors");
    for (int i = 0; i < numMotors; ++i)
        *barSet << 0;  // Initialize bars with 0 height

    series = new QBarSeries();
    series->append(barSet);

    chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Stepper Motors Moving Up/Down");

    axisX = new QBarCategoryAxis();
    QStringList categories;
    for (int i = 0; i < numMotors; ++i)
        categories << QString::number(i);
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    axisY = new QValueAxis;
    axisY->setRange(-10, 10);  // Amplitude range for wave
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->hide();
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
}

void WaveControlWindow::updateWaveFactor(int value)
{
    waveFactorValue = value / 100.0;  // Convert slider value to a float (0.0 - 1.0)
}

void WaveControlWindow::updateStrokeLength(int value)
{
    strokeLengthValue = value;  // Stroke length controls the amplitude (height of wave)
}

void WaveControlWindow::updateWave()
{
    double currentPhaseShift = basePhaseShift * waveFactorValue;  // Adjust phase shift based on wave factor
    for (int i = 0; i < numMotors; ++i) {
        // Apply wave function to each motor (position the bar based on sin function)
        double pos = strokeLengthValue * sin(2 * M_PI * 0.5 * t + i * currentPhaseShift);  // Use strokeLengthValue as the amplitude
        barSet->replace(i, pos);  // Update bar height based on the wave
    }

    // Animate vertical movement of the bars (scroll the chart)
    //chart->scroll(0, strokeLengthValue * sin(2 * M_PI * 0.5 * t));  // Scroll by the current wave value
    t += step;
}


