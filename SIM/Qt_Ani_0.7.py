import sys
import numpy as np
from PyQt5.QtWidgets import QApplication, QMainWindow, QVBoxLayout, QWidget, QSlider, QLabel, QHBoxLayout, QLineEdit, QPushButton
from PyQt5.QtCore import Qt, QTimer
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from PyQt5.QtGui import QDoubleValidator, QIntValidator  # Added import

class WaveControlWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Wave Control Input")

        # Parameters
        self.num_motors = 12
        self.amp = 1.0
        self.step = 0.05
        self.base_phase_shift = np.pi / 6
        self.scaling_factor = 4  # Scaling factor for stroke length

        # Variables
        self.wave_factor_value = 0.0
        self.stroke_length_value = 1

        # Set up the main layout
        self.main_widget = QWidget(self)
        self.layout = QVBoxLayout(self.main_widget)

        # Set up plot
        self.fig, self.ax = plt.subplots(figsize=(8, 4))
        self.x = np.arange(self.num_motors)
        self.ax.set_ylim(-1.5 * self.amp, 1.5 * self.amp)
        self.ax.set_xlim(-1, self.num_motors)
        self.ax.set_xticks(self.x)
        self.ax.set_yticks(np.linspace(-1.5, 1.5, 7))
        self.ax.set_title("Stepper Motors Moving Up/Down")
        self.ax.set_ylabel("Position")
        self.ax.grid()

        self.bar_height = 0.5
        self.bars = self.ax.bar(self.x, [self.bar_height] * self.num_motors, bottom=np.zeros(self.num_motors), width=0.5, color='orange')

        # Canvas setup
        self.canvas = FigureCanvas(self.fig)
        self.layout.addWidget(self.canvas)

        # Control Panel Layout
        control_layout = QHBoxLayout()

        # Wave Factor Control
        self.wave_factor_input = QLineEdit(self)
        self.wave_factor_input.setText(str(self.wave_factor_value))
        self.wave_factor_input.setFixedWidth(50)
        self.wave_factor_input.setValidator(QDoubleValidator(0.0, 1.0, 1))  # Fixed validator
        control_layout.addWidget(QLabel("Wave Factor (0.0 to 1.0):"))
        control_layout.addWidget(self.wave_factor_input)

        # Stroke Length Control
        self.stroke_length_input = QLineEdit(self)
        self.stroke_length_input.setText(str(self.stroke_length_value))
        self.stroke_length_input.setFixedWidth(50)
        self.stroke_length_input.setValidator(QIntValidator(1, 10))  # Stroke length validator
        control_layout.addWidget(QLabel("Stroke Length (1 to 10):"))
        control_layout.addWidget(self.stroke_length_input)

        # Apply Buttons
        self.apply_button_wave = QPushButton("Apply Wave Factor", self)
        self.apply_button_wave.clicked.connect(self.apply_wave_value)
        control_layout.addWidget(self.apply_button_wave)

        self.apply_button_stroke = QPushButton("Apply Stroke Length", self)
        self.apply_button_stroke.clicked.connect(self.apply_stroke_value)
        control_layout.addWidget(self.apply_button_stroke)

        self.layout.addLayout(control_layout)

        # Start the animation
        self.anim = animation.FuncAnimation(self.fig, self.update_wave, self.data_gen(), blit=True, interval=50)

        # Timer for updating values from the input fields
        self.timer = QTimer(self)
        self.timer.timeout.connect(self.update_input_fields)
        self.timer.start(100)

        self.setCentralWidget(self.main_widget)

    def data_gen(self):
        """ Generate data for wave animation """
        t = 0
        while True:
            current_phase_shift = self.base_phase_shift * self.wave_factor_value
            positions = self.amp * np.sin(2 * np.pi * 0.5 * t + self.x * current_phase_shift)
            t += self.step
            yield positions

    def update_wave(self, positions):
        """ Update wave bars """
        current_stroke_length = self.stroke_length_value  # Stroke length controls the distance
        for bar, y in zip(self.bars, positions):
            bar.set_height(current_stroke_length)  # Bar height stays constant
            bar.set_y(y * current_stroke_length / self.amp)  # Apply stroke length to vertical movement
        return self.bars

    def apply_wave_value(self):
        """ Update the wave factor """
        try:
            val = float(self.wave_factor_input.text())
            if 0.0 <= val <= 1.0:
                self.wave_factor_value = val
            else:
                raise ValueError
        except ValueError:
            self.wave_factor_value = 0.0

    def apply_stroke_value(self):
        """ Update the stroke length """
        try:
            val = int(self.stroke_length_input.text())
            if 1 <= val <= 10:
                self.stroke_length_value = val
            else:
                raise ValueError
        except ValueError:
            self.stroke_length_value = 1

    def update_input_fields(self):
        """ Update the input fields from the current values """
        self.wave_factor_input.setText(str(self.wave_factor_value))
        self.stroke_length_input.setText(str(self.stroke_length_value))


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = WaveControlWindow()
    window.show()
    sys.exit(app.exec_())
