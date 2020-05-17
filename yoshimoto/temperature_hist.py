import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import norm
import my_style


def temperature_hist():
    nbin = 10
    bin_min = 36.05
    bin_max = 38.05
    bin_width = (bin_max - bin_min) / nbin
    vy = []
    with open("temperature.txt") as f:
        for line in f:
            vy.append(float(line.split()[0]))

    N = len(vy)
    mean = np.mean(vy)
    stdev = np.std(vy)

    label="Entries {0}\nMean {1:.2f}\nStd Dev {2:.4f}".format(N,mean,stdev)
    content = plt.hist(vy, bins=nbin, range=[
                       bin_min, bin_max], histtype="step", edgecolor='k',label=label)


    xx = np.linspace(bin_min, bin_max, 500)
    plt.plot(xx, norm.pdf(xx, mean, stdev)*N*bin_width, color="red")
    plt.xlim(bin_min, bin_max)
    plt.xlabel("Body temperature[$^\\circ$C]")
    plt.ylabel("Frequency")

    chi2 = 0
    for i in range(nbin):
        observed = content[0][i]
        center = (content[1][i]+content[1][i+1])*0.5
        if observed == 0:
            continue
        expected = norm.pdf(center, mean, stdev)*(N*bin_width)

        print("{:.2f} {:.4f} {:.0f}".format(center, expected, observed))
        chi2 += (observed - expected) * (observed - expected) / expected

    print("N    :{}".format(N))
    print("mean :{:.4f}".format(mean))
    print("stdev:{:.4f}".format(stdev))
    print("chi2 :{:.4f}".format(chi2))

    plt.legend()
    plt.show()


if __name__ == "__main__":
    temperature_hist()
