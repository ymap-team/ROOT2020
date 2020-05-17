#include <Math/PdfFuncMathCore.h>
#include <TGraph.h>
#include <TAxis.h>
#include "my_style.hpp"

void plot_normal_dist3()
{
    SetMyStyle();
    Double_t x[1000], y1[1000], y2[1000], y3[1000];
    for (int i = 0; i < 1000; i++)
    {
        double d = (i - 500) * 0.01;
        x[i] = d;
        y1[i] = ROOT::Math::normal_pdf(d, 1.0, 0.0);
        y2[i] = ROOT::Math::normal_pdf(d, 0.4, 1.5);
        y3[i] = ROOT::Math::normal_pdf(d, 2.0, -0.5);
    }
    TGraph *graph1 = new TGraph(1000, x, y1);
    TGraph *graph2 = new TGraph(1000, x, y2);
    TGraph *graph3 = new TGraph(1000, x, y3);
    graph2->SetMinimum(0.0);
    graph2->GetXaxis()->SetLimits(-5.0, 5.0);
    graph2->SetTitle(";x;Probability density");
    graph2->SetLineColor(2);
    graph2->Draw("AL");
    graph1->Draw("L");
    graph3->SetLineColor(4);
    graph3->Draw("L");
}