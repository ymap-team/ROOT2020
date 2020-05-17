import numpy as np
import matplotlib.pyplot as plt
import sys
import my_style

def poly_fit_manual(fit=False):
    vx=[]
    vy=[]
    i=1
    with open("temperature.txt") as f:
        for line in f:
            vx.append(i)
            vy.append(float(line.split()[0]))
            i+=1

    # グラフ生成
    plt.plot(vx,vy,'k+',label='Data')
    plt.xlabel("Time [day]")
    plt.ylabel("Body temperature [$^\\circ$C]")
    plt.ylim(36,38)
    
    if fit==False:
        plt.legend()
        plt.show()
        return


    # 頻出する総和を先に計算
    N   = len(vy)
    Nxy = np.sum([xi*yi for xi,yi in zip(vx,vy)])
    Nx  = np.sum([xi    for xi,yi in zip(vx,vy)])
    Ny  = np.sum([yi    for xi,yi in zip(vx,vy)])
    Nx2 = np.sum([xi*xi for xi,yi in zip(vx,vy)])
    delta=N * Nx2 - Nx**2

    # 係数
    a = (Nx2 * Ny  - Nx * Nxy)/delta
    b = (N   * Nxy - Nx * Ny )/delta

    # Yの誤差
    sigma_y = np.sqrt(1/(N-2) * np.sum([(a+b*xi-yi)**2 for xi,yi in zip(vx,vy)]))

    # 係数の誤差
    sigma_a = sigma_y * np.sqrt(Nx2 / delta)
    sigma_b = sigma_y * np.sqrt(N   / delta)

    # パラメータの出力
    print(f"N      : {N}")
    print(f"A      : {a:7f} ± {sigma_a:7f}")
    print(f"B      : {b:7f} ± {sigma_b:7f}")
    print(f"Sigma_y: {sigma_y:7f}")

    # グラフ生成
    xx=np.linspace(0,70,100)
    plt.plot(xx,b*xx+a,label="Fitted line",color="red")

    plt.legend()
    plt.show()

if __name__ == "__main__":
    if len(sys.argv) == 1:
        poly_fit_manual()
    if len(sys.argv) == 2:
        poly_fit_manual(bool(sys.argv[1]))
