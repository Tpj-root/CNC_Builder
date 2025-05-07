import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import tkinter as tk

# Screen size for plot
root = tk.Tk()
screen_width = root.winfo_screenwidth()
screen_height = root.winfo_screenheight()
root.destroy()

fig_width = screen_width * 0.8 / plt.rcParams['figure.dpi']
fig_height = screen_height * 0.4 / plt.rcParams['figure.dpi']

# Parameters
num_motors = 12
amp = 1.0
step = 0.05
phase_shift = np.pi / 6  # 30° between each motor

# Setup
fig, ax = plt.subplots(figsize=(fig_width, fig_height))
ax.set_ylim(-1.5 * amp, 1.5 * amp)
ax.set_xlim(-1, num_motors)
ax.set_xticks(range(num_motors))
ax.set_yticks(np.linspace(-1.5, 1.5, 7))
ax.set_title("Stepper Motors Moving Up/Down")
ax.set_ylabel("Position")
ax.grid()

# All bars start at y=0, with fixed height
bar_height = 0.5
bars = ax.bar(np.arange(num_motors), [bar_height]*num_motors, bottom=np.zeros(num_motors), width=0.5, color='orange')

# Generator
def data_gen():
    t = 0
    while True:
        positions = amp * np.sin(2 * np.pi * 0.5 * t + np.arange(num_motors) * phase_shift)
        t += step
        yield positions

# Update function
def update(positions):
    for bar, y in zip(bars, positions):
        bar.set_y(y)  # move bar up/down without changing height
    return bars

ani = animation.FuncAnimation(fig, update, data_gen, blit=True, interval=50)
plt.show()
