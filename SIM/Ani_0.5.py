import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import tkinter as tk
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

# Parameters
num_motors = 12
amp = 1.0
step = 0.05
base_phase_shift = np.pi / 6

# Tkinter setup
root = tk.Tk()
root.title("Wave Control Input")

screen_width = root.winfo_screenwidth()
screen_height = root.winfo_screenheight()

fig_width = screen_width * 0.8 / plt.rcParams['figure.dpi']
fig_height = screen_height * 0.4 / plt.rcParams['figure.dpi']

# Wave factor variable
wave_factor_value = tk.DoubleVar(value=0.0)
increment_value = 0.1  # Define the increment/decrement value

# Setup plot
fig, ax = plt.subplots(figsize=(fig_width, fig_height))
ax.set_ylim(-1.5 * amp, 1.5 * amp)
ax.set_xlim(-1, num_motors)
ax.set_xticks(range(num_motors))
ax.set_yticks(np.linspace(-1.5, 1.5, 7))
ax.set_title("Stepper Motors Moving Up/Down")
ax.set_ylabel("Position")
ax.grid()

bar_height = 0.5
bars = ax.bar(np.arange(num_motors), [bar_height]*num_motors, bottom=np.zeros(num_motors), width=0.5, color='orange')

# Generator
def data_gen():
    t = 0
    while True:
        current_phase_shift = base_phase_shift * wave_factor_value.get()
        positions = amp * np.sin(2 * np.pi * 0.5 * t + np.arange(num_motors) * current_phase_shift)
        t += step
        yield positions

# Update
def update(positions):
    for bar, y in zip(bars, positions):
        bar.set_y(y)
    return bars

# Matplotlib canvas
canvas = FigureCanvasTkAgg(fig, master=root)
canvas.get_tk_widget().pack()

# Entry + Button
frame = tk.Frame(root)
frame.pack(pady=10)

tk.Label(frame, text="Wave Factor (0.0 to 1.0):").pack(side='left')
entry = tk.Entry(frame, textvariable=wave_factor_value, width=5)
entry.pack(side='left')

# Apply Wave Value
def apply_wave_value():
    try:
        val = float(entry.get())
        if 0.0 <= val <= 1.0:
            wave_factor_value.set(val)
        else:
            raise ValueError
    except ValueError:
        wave_factor_value.set(0.0)

# Increment and Decrement Functions
def increment_wave_value():
    new_value = wave_factor_value.get() + increment_value
    if new_value <= 1.0:
        wave_factor_value.set(new_value)
    else:
        wave_factor_value.set(1.0)

def decrement_wave_value():
    new_value = wave_factor_value.get() - increment_value
    if new_value >= 0.0:
        wave_factor_value.set(new_value)
    else:
        wave_factor_value.set(0.0)

# Buttons for Increment and Decrement
increment_button = tk.Button(frame, text="Increment", command=increment_wave_value)
increment_button.pack(side='left', padx=5)

decrement_button = tk.Button(frame, text="Decrement", command=decrement_wave_value)
decrement_button.pack(side='left', padx=5)

# Apply Button
apply_button = tk.Button(frame, text="Apply", command=apply_wave_value)
apply_button.pack(side='left', padx=5)

# Start animation and GUI
ani = animation.FuncAnimation(fig, update, data_gen, blit=True, interval=50)
root.mainloop()
