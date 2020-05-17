import sys
import numpy as np
from scipy.stats import chi2
import matplotlib.pyplot as plt
import my_style

def plot_chi2(ndf=4):

    x_max = 1
    while(True):
        if chi2.sf(x_max, ndf) < 0.00001:
            break
        x_max += 1
    x_max = (x_max // 10) * 10

    x = np.linspace(0, x_max, 500)
    plt.plot(x, chi2.pdf(x, ndf), 'k-')
    plt.title('$\\chi^2$ distribusion ndf = {0}'.format(ndf))
    plt.xlabel("$\\chi^2$")
    plt.ylabel("Probability")
    plt.xlim(0, x_max)
    plt.ylim(0, None)
    plt.show()


if __name__ == "__main__":
    if len(sys.argv) == 1:
        plot_chi2()
    if len(sys.argv) == 2:
        plot_chi2(float(sys.argv[1]))
