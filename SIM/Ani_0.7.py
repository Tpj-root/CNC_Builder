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
scaling_factor = 4  # Scaling factor for stroke length

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
stroke_length_value = tk.IntVar(value=1)  # Stroke length variable

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

# Update function with stroke length controlling the oscillation distance
def update(positions):
    # Adjusting the stroke length as the oscillation range
    current_stroke_length = stroke_length_value.get()  # Stroke length controls the distance
    for bar, y in zip(bars, positions):
        bar.set_height(current_stroke_length)  # Bar height stays constant
        bar.set_y(y * current_stroke_length / amp)  # Apply stroke length to vertical movement
    return bars

# Matplotlib canvas
canvas = FigureCanvasTkAgg(fig, master=root)
canvas.get_tk_widget().pack()

# Entry + Button
frame = tk.Frame(root)
frame.pack(pady=10)

# Wave Factor Controls
tk.Label(frame, text="Wave Factor (0.0 to 1.0):").pack(side='left')
entry_wave = tk.Entry(frame, textvariable=wave_factor_value, width=5)
entry_wave.pack(side='left')

# Stroke Length Controls
tk.Label(frame, text="Stroke Length (100 to 1000):").pack(side='left')
entry_stroke = tk.Entry(frame, textvariable=stroke_length_value, width=5)
entry_stroke.pack(side='left')

# Apply Wave Value
def apply_wave_value():
    try:
        val = float(entry_wave.get())
        if 0.0 <= val <= 1.0:
            wave_factor_value.set(val)
        else:
            raise ValueError
    except ValueError:
        wave_factor_value.set(0.0)

# Apply Stroke Length
def apply_stroke_value():
    try:
        val = int(entry_stroke.get())
        if 1 <= val <= 10:
            stroke_length_value.set(val)
        else:
            raise ValueError
    except ValueError:
        stroke_length_value.set(10)

# Increment and Decrement Functions for Stroke Length
def increment_stroke_value():
    new_value = stroke_length_value.get() + 1
    if new_value <= 1:
        stroke_length_value.set(new_value)
    else:
        stroke_length_value.set(1)

def decrement_stroke_value():
    new_value = stroke_length_value.get() - 1
    if new_value >= 1:
        stroke_length_value.set(new_value)
    else:
        stroke_length_value.set(10)

# Increment and Decrement Functions for Wave Factor
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
increment_button_wave = tk.Button(frame, text="Increment Wave Factor", command=increment_wave_value)
increment_button_wave.pack(side='left', padx=5)

decrement_button_wave = tk.Button(frame, text="Decrement Wave Factor", command=decrement_wave_value)
decrement_button_wave.pack(side='left', padx=5)

increment_button_stroke = tk.Button(frame, text="Increment Stroke", command=increment_stroke_value)
increment_button_stroke.pack(side='left', padx=5)

decrement_button_stroke = tk.Button(frame, text="Decrement Stroke", command=decrement_stroke_value)
decrement_button_stroke.pack(side='left', padx=5)

# Apply Buttons
apply_button_wave = tk.Button(frame, text="Apply Wave Factor", command=apply_wave_value)
apply_button_wave.pack(side='left', padx=5)

apply_button_stroke = tk.Button(frame, text="Apply Stroke Length", command=apply_stroke_value)
apply_button_stroke.pack(side='left', padx=5)

# Start animation and GUI
ani = animation.FuncAnimation(fig, update, data_gen, blit=True, interval=50)
root.mainloop()
