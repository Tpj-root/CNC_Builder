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
ax.set_title("Harmonic Motion of 12 Stepper Motors")
ax.set_ylabel("Displacement")
ax.grid()

bars = ax.bar(np.arange(num_motors), np.zeros(num_motors), width=0.5, color='skyblue')

# Generator
def data_gen():
    t = 0
    while True:
        displacements = amp * np.sin(2 * np.pi * 0.5 * t + np.arange(num_motors) * phase_shift)
        t += step
        yield displacements

# Update function
def update(displacements):
    for bar, y in zip(bars, displacements):
        bar.set_height(y)
    return bars

ani = animation.FuncAnimation(fig, update, data_gen, blit=True, interval=50)
plt.show()
