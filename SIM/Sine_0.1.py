import sys
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from PyQt5.QtWidgets import QApplication, QMainWindow, QVBoxLayout, QWidget, QSlider, QLabel
from PyQt5.QtCore import Qt
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas

class SineWaveWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Sine Wave Animation")

        # Set up the main layout
        self.main_widget = QWidget(self)
        self.layout = QVBoxLayout(self.main_widget)

        # Set up the plot
        self.fig, self.ax = plt.subplots(figsize=(6, 4))
        self.x = np.linspace(0, 2 * np.pi, 100)
        self.line, = self.ax.plot(self.x, np.sin(self.x), lw=2)
        self.ax.set_ylim(-10, 10)
        self.ax.set_xlim(0, 2 * np.pi)
        self.ax.set_title("Sine Wave")
        self.ax.set_xlabel("Time")
        self.ax.set_ylabel("Amplitude")
        self.ax.grid()

        # Set up the canvas
        self.canvas = FigureCanvas(self.fig)
        self.layout.addWidget(self.canvas)

        # Set up the amplitude slider
        self.amplitude_slider = QSlider(Qt.Horizontal)
        self.amplitude_slider.setRange(1, 100)
        self.amplitude_slider.setValue(10)
        self.amplitude_slider.setTickInterval(1)
        self.amplitude_slider.setTickPosition(QSlider.TicksBelow)
        self.layout.addWidget(self.amplitude_slider)

        # Label for amplitude
        self.amplitude_label = QLabel("Amplitude: 1.0")
        self.layout.addWidget(self.amplitude_label)

        # Connect the slider to update amplitude
        self.amplitude_slider.valueChanged.connect(self.update_amplitude)

        # Set up animation
        self.anim = animation.FuncAnimation(self.fig, self.update_wave, np.arange(0, 2 * np.pi, 0.05),
                                           blit=True, interval=50)

        # Set the main widget
        self.setCentralWidget(self.main_widget)

    def update_wave(self, t):
        """ Update the sine wave for animation """
        amplitude = self.amplitude_slider.value() / 10  # Adjust the amplitude scale
        y = amplitude * np.sin(self.x + t)
        self.line.set_ydata(y)
        return self.line,

    def update_amplitude(self):
        """ Update the amplitude based on the slider value """
        amplitude = self.amplitude_slider.value() / 10
        self.amplitude_label.setText(f"Amplitude: {amplitude:.1f}")

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = SineWaveWindow()
    window.show()
    sys.exit(app.exec_())
