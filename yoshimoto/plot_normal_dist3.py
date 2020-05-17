import sys
import numpy as np
from scipy.stats import norm
import matplotlib.pyplot as plt
from plot_normal_dist import normal_dist
import my_style


if __name__ == "__main__":
    vx, vy = normal_dist(1.0, 0.0)
    plt.plot(vx, vy)
    vx, vy = normal_dist(0.4, 1.5)
    plt.plot(vx, vy)
    vx, vy = normal_dist(2.0, -0.5)
    plt.plot(vx, vy)

    plt.xlim(-5, 5)
    plt.ylim(0, None)
    plt.xlabel("x")
    plt.ylabel("Probability density")
    plt.show()
