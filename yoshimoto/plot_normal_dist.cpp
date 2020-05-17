#include <Math/PdfFuncMathCore.h>
#include <TGraph.h>
#include <TAxis.h>
#include "my_style.hpp"

void plot_normal_dist(double sigma = 1.0, double mean = 0.0)
{
    SetMyStyle();
    Double_t x[1000], y[1000];
    for (int i = 0; i < 1000; i++)
    {
        double d = (i - 500) * 0.01;
        x[i] = d;
        y[i] = ROOT::Math::normal_pdf(d, sigma, mean);
    }
    TGraph *graph = new TGraph(1000, x, y);
    graph->SetMinimum(0.0);
    graph->SetTitle(";x;Probability density");
    graph->GetXaxis()->SetLimits(-5.0, 5.0);
    graph->Draw("AL");
}