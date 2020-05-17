#include <TGraph.h>
#include <TLine.h>
#include <TLegend.h>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

void poly_fit_manual(bool fit=false)
{
    vector<double> vx, vy;

    ifstream ifs("temperature.txt");
    double temp;
    int i = 1;
    while (ifs >> temp)
    {
        vx.push_back(i++);
        vy.push_back(temp);
    }

    int N = vx.size();

    TGraph *graph = new TGraph(N, &(vx.at(0)), &(vy.at(0)));
    graph->SetTitle(";Time [day];Body temperature [#circ C]");
    graph->SetMinimum(36);
    graph->SetMaximum(38);
    graph->SetMarkerStyle(2);
    graph->Draw("AP");

    if(fit == false){
        TLegend *legend = new TLegend(0.15,0.80,0.3,0.85);
        legend->AddEntry(graph,"Data","p");
        legend->Draw();
        return;
    }

    // 頻出する総和を先に計算
    double Nxy = 0, Nx = 0, Ny = 0, Nx2 = 0;
    for (int i = 0; i < N; i++)
    {
        const double xi = vx[i];
        const double yi = vy[i];
        Nxy += xi * yi;
        Nx += xi;
        Ny += yi;
        Nx2 += xi * xi;
    }
    double delta = N * Nx2 - Nx * Nx;

    // 係数
    double b = (N  * Nxy - Nx * Ny ) / delta;
    double a = (Nx2 * Ny - Nx * Nxy) / delta;

    // Yの誤差
    double dy = 0;
    for (int i = 0; i < N; i++)
    {
        const double xi = vx[i];
        const double yi = vy[i];
        dy += (b * xi + a - yi) * (b * xi + a - yi);
    }
    double sigma_y = sqrt(1.0 / (N - 2) * dy);

    // 係数の誤差
    double sigma_a = sigma_y * sqrt(Nx2 / delta);
    double sigma_b = sigma_y * sqrt(N / delta);

    // パラメータの出力
    cout << "N      : " << N << endl;
    cout << "A      : " << a << "+/-" << sigma_a << endl;
    cout << "B      : " << b << "+/-" << sigma_b << endl;
    cout << "Sigma_y: " << sigma_y << endl;

    // グラフ生成
    TLine *line = new TLine(0, a + 0 * b, 70, a + 70 * b );
    line->SetLineColor(kRed);
    line->Draw();

    if(fit){
        TLegend *legend = new TLegend(0.15,0.75,0.3,0.85);
        legend->AddEntry(graph,"Data","p");
        legend->AddEntry(line,"Fitted line","l");
        legend->Draw();
    }
}