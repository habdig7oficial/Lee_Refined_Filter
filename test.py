import math
import matplotlib.pyplot as plt
import numpy as np


def plot_bresenham_thick_line_angle(N, angle_deg, w):
    """Plots the set S1 inside an N x N window using a direct angle theta.

    S1 = { (x,y) in Z^2 | |x*sin(theta) - y*cos(theta)| <= w / 2 }
    """
    # Convert angle to radians
    theta = math.radians(angle_deg)

    # Calculate direction vector components
    sin_t = math.sin(theta)
    cos_t = math.cos(theta)

    # Scaled integer conversion for direction vector (preserves precision)
    SCALE = 1000
    dx = int(round(cos_t * SCALE))
    dy = int(round(sin_t * SCALE))

    # Calculate threshold (w * L) / 2
    L = math.hypot(dx, dy)
    threshold = (w * L) / 2.0

    # Grid bounds centered at (0,0)
    half_win = N // 2
    x_range = range(-half_win, half_win + 1)
    y_range = range(-half_win, half_win + 1)

    two_dx = 2 * dx
    active_pixels = []

    # Rasterization loop
    for x in x_range:
        # Base value for y = y_range[0]
        F = 2 * (x * dy - y_range[0] * dx)

        for y in y_range:
            # Check condition |F(x,y)| <= 2 * threshold
            if abs(F) <= 2 * threshold:
                active_pixels.append((x, y))

            # Incremental update step for y -> y + 1
            F -= two_dx

    # Plotting
    fig, ax = plt.subplots(figsize=(7, 7))

    if active_pixels:
        px, py = zip(*active_pixels)
        ax.scatter(px, py, color="red", s=30, label="$S_1$ pixels")

    # Center reference line
    line_len = half_win
    ax.plot(
        [-line_len * cos_t, line_len * cos_t],
        [-line_len * sin_t, line_len * sin_t],
        color="blue",
        linestyle="--",
        linewidth=1.5,
        label=f"Center Line ({angle_deg}°)",
    )

    # Grid setup
    ax.set_xticks(np.arange(-half_win - 0.5, half_win + 1.5, 1))
    ax.set_yticks(np.arange(-half_win - 0.5, half_win + 1.5, 1))
    ax.grid(True, which="both", color="gray", linestyle=":", linewidth=0.5)

    ax.set_xlim(-half_win - 1, half_win + 1)
    ax.set_ylim(-half_win - 1, half_win + 1)
    ax.set_aspect("equal")
    ax.set_title(f"Set $S_1$ Rasterization ($\\theta={angle_deg}^\\circ, w={w}$)")
    ax.legend(loc="upper left")

    plt.show()


# Example Usage:
# Window size N = 41 (from -20 to 20)
# Pass angle theta in degrees directly (e.g., 30 degrees)
# Line width w = 6
plot_bresenham_thick_line_angle(N=41, angle_deg=30, w=6)