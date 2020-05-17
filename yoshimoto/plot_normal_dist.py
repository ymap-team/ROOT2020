import sys
import numpy as np
from scipy.stats import norm
import matplotlib.pyplot as plt
import my_style


def normal_dist(sigma=1, mean=0):
    vx = np.linspace(-5, 5, 1000)
    return vx, norm.pdf(vx, mean, sigma)


if __name__ == "__main__":
    if len(sys.argv) == 1:
        vx, vy = normal_dist()
        plt.plot(vx, vy)
    elif len(sys.argv) == 2:
        vx, vy = normal_dist(float(sys.argv[1]))
        plt.plot(vx, vy)
    elif len(sys.argv) == 3:
        vx, vy = normal_dist(float(sys.argv[1]), float(sys.argv[2]))
        plt.plot(vx, vy)

    plt.xlim(-5, 5)
    plt.ylim(0, None)
    plt.xlabel("x")
    plt.ylabel("Probability density")
    plt.show()
