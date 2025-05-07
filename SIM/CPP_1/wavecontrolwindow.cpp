#include "wavecontrolwindow.h"
#include <cmath>       // for sin()
#include <QSlider>
#include <QLabel>

// Constructor: Sets up the GUI, sliders, chart, and animation timer
WaveControlWindow::WaveControlWindow(QWidget *parent)
    : QMainWindow(parent),
      numMotors(12),             // Number of motors/bars
      amp(1.0),                  // Amplitude base value (not used directly)
      step(0.05),                // Time step increment per timer tick
      basePhaseShift(M_PI / 6), // Phase shift between each motor/bar
      waveFactorValue(1.0),     // 1.0 = full sine wave
      strokeLengthValue(5),     // Amplitude multiplier
      t(0.0)                     // Initial time
{
    mainWidget = new QWidget(this);
    mainLayout = new QVBoxLayout(mainWidget);

    // === SLIDER SECTION ===

    QVBoxLayout *controlLayout = new QVBoxLayout;

    // Wave Factor Slider: Adjusts the smoothness or wavelength of the sine wave
    waveFactorSlider = new QSlider(Qt::Horizontal);
    waveFactorSlider->setRange(0, 100);         // Value from 0 to 100
    waveFactorSlider->setValue(100);            // Default = 100% wave
    connect(waveFactorSlider, &QSlider::valueChanged, this, &WaveControlWindow::updateWaveFactor);
    controlLayout->addWidget(new QLabel("Wave Factor"));
    controlLayout->addWidget(waveFactorSlider);

    // Stroke Length Slider: Controls amplitude of the sine wave
    strokeLengthSlider = new QSlider(Qt::Horizontal);
    strokeLengthSlider->setRange(1, 10);        // Value from 1 to 10
    strokeLengthSlider->setValue(5);            // Default = 5
    connect(strokeLengthSlider, &QSlider::valueChanged, this, &WaveControlWindow::updateStrokeLength);
    controlLayout->addWidget(new QLabel("Stroke Length"));
    controlLayout->addWidget(strokeLengthSlider);

    mainLayout->addLayout(controlLayout);

    // === CHART SECTION ===
    setupChart();                      // Initializes the chart and bars
    mainLayout->addWidget(chartView);  // Add chart to main layout

    // === TIMER SECTION ===
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &WaveControlWindow::updateWave);
    timer->start(50);  // Updates every 50 ms

    // Final setup
    setCentralWidget(mainWidget);
    setWindowTitle("Wave Control with Sliders");
    resize(800, 400);
}

// Destructor: Nothing special here
WaveControlWindow::~WaveControlWindow() {}


// Setup chart elements: bars, axes, and rendering options
void WaveControlWindow::setupChart()
{
    barSet = new QBarSet("Motors");
    for (int i = 0; i < numMotors; ++i)
        *barSet << 0;  // Initialize all motor values to 0

    series = new QBarSeries();
    series->append(barSet);

    chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Stepper Motors Moving Up/Down");

    // X-Axis: shows each motor index
    axisX = new QBarCategoryAxis();
    QStringList categories;
    for (int i = 0; i < numMotors; ++i)
        categories << QString::number(i);
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Y-Axis: wave amplitude (vertical movement)
    axisY = new QValueAxis;
    axisY->setRange(-10, 10);  // Range for full wave swing
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->hide();  // Hide legend
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);  // Smoother rendering
}

// Update wave factor from slider (0.0 to 1.0)
void WaveControlWindow::updateWaveFactor(int value)
{
    waveFactorValue = value / 100.0;
}

// Update stroke length (amplitude) from slider
void WaveControlWindow::updateStrokeLength(int value)
{
    strokeLengthValue = value;
}

// Called by timer to animate the wave
void WaveControlWindow::updateWave()
{
    double currentPhaseShift = basePhaseShift * waveFactorValue;  // Phase shift scaled by wave factor

    // Update each bar's height using sine wave
    for (int i = 0; i < numMotors; ++i) {
        double pos = strokeLengthValue * sin(2 * M_PI * 0.5 * t + i * currentPhaseShift);  // Sine wave formula
        barSet->replace(i, pos);  // Set bar height
    }

    t += step;  // Advance time for next wave update
}
