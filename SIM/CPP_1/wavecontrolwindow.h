#ifndef WAVECONTROLWINDOW_H
#define WAVECONTROLWINDOW_H

// Include Qt Charts and basic Qt widgets
#include <QtCharts>
#include <QMainWindow>
#include <QTimer>
#include <QVBoxLayout>
#include <QSlider>

// Enable the Qt Charts namespace to avoid prefixing
QT_CHARTS_USE_NAMESPACE

// Define a custom window class for wave control
class WaveControlWindow : public QMainWindow
{
    Q_OBJECT  // Qt macro enabling signals and slots mechanism

public:
    // Constructor and destructor
    WaveControlWindow(QWidget *parent = nullptr);
    ~WaveControlWindow();

private slots:
    // Called periodically by timer to update the wave animation
    void updateWave();

    // Called when wave factor slider changes
    void updateWaveFactor(int value);

    // Called when stroke length slider changes
    void updateStrokeLength(int value);

private:
    // Setup chart components and UI layout
    void setupChart();

    // Main widget and layout for the window
    QWidget *mainWidget;
    QVBoxLayout *mainLayout;

    // Chart components
    QChart *chart;                  // Main chart object
    QChartView *chartView;         // Widget to display the chart
    QBarSeries *series;            // Series of bars to represent motor positions
    QBarSet *barSet;               // Actual bar set with data values
    QBarCategoryAxis *axisX;       // X-axis showing categories (motors)
    QValueAxis *axisY;             // Y-axis showing wave amplitude
    QLabel *waveFactorLabel;  // Declare the label here
    QLabel *strokeLengthLabel;

    // Wave control variables
    int numMotors;                 // Number of bars/motors
    double amp;                    // Amplitude of the wave
    double step;                   // Step size for time progression
    double basePhaseShift;         // Phase shift between motors
    double waveFactorValue;        // Multiplier to adjust wave shape
    double strokeLengthValue;      // Multiplier for bar height
    double t;                      // Time variable for wave animation

    // Timer and sliders for interactivity
    QTimer *timer;                 // Timer to drive animation updates
    QSlider *waveFactorSlider;     // Slider to adjust wave factor
    QSlider *strokeLengthSlider;   // Slider to adjust stroke length
};

#endif // WAVECONTROLWINDOW_H
