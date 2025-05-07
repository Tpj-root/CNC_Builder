import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import tkinter as tk

# Get screen width and height
root = tk.Tk()
screen_width = root.winfo_screenwidth()
screen_height = root.winfo_screenheight()
root.destroy()

# Set figure size (80% of screen)
fig_width = screen_width * 0.8 / plt.rcParams['figure.dpi']
fig_height = screen_height * 0.4 / plt.rcParams['figure.dpi']  # single plot, so shorter height

# Step in seconds
step = 0.1
#step = 0.01

amp = 1.0

# ECG waveform generator
def ecg_waveform(t):
    return np.piecewise(
        t % 1,
        [t % 1 < 0.1, (t % 1 >= 0.1) & (t % 1 < 0.2),
         (t % 1 >= 0.2) & (t % 1 < 0.25),
         (t % 1 >= 0.25) & (t % 1 < 0.3),
         t % 1 >= 0.3],
        [0.1, -0.5, 1.5, -0.75, 0]
    )

# Generator for animation
def data_gen():
    t = 0
    while True:
        y = ecg_waveform(t) * amp
        t += step
        yield t, y

# Plot setup
fig, ax = plt.subplots(figsize=(fig_width, fig_height))
ax.set_ylim(-2, 2)
ax.set_xlim(0, 10)
ax.grid()
ax.set_title('ECG Simulation')
ax.set_xlabel('Time (s)')

xdata, ydata = [], []
line, = ax.plot([], [], lw=2)

# Update function
def calculate(data):
    x, y = data
    xdata.append(x)
    ydata.append(y)

    # Scroll the plot
    if x > 10:
        ax.set_xlim(x - 10, x)

    line.set_data(xdata, ydata)
    return line,

# Run animation
ani = animation.FuncAnimation(fig, calculate, data_gen, blit=True, interval=50)
plt.show()
