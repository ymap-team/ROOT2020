#include <TH1D.h>
#include <TF1.h>
#include <TMath.h>
#include <fstream>
#include <iostream>
#include "my_style.hpp"
using namespace std;

void temperature_hist()
{
    SetMyStyle();
    double temp;
    int nbin = 10;
    double bin_min = 36.05;
    double bin_max = 38.05;
    double bin_width = (bin_max - bin_min) / nbin;
    TH1D *histgram = new TH1D("temp", "", nbin, bin_min, bin_max);
    ifstream ifs("temperature.txt");
    while (ifs >> temp)
    {
        histgram->Fill(temp);
    }
    histgram->SetTitle(";Body temperature [#circ C];Frequency");
    histgram->Draw();

    int N = histgram->GetEntries();
    double mean = histgram->GetMean();
    double stdev = histgram->GetStdDev();

    TF1 *pdf = new TF1("pdf", "ROOT::Math::gaussian_pdf(x,[0],[1])*[2]*[3]", bin_min, bin_max);
    pdf->SetParameter(0, stdev);
    pdf->SetParameter(1, mean);
    pdf->SetParameter(2, N);
    pdf->SetParameter(3, bin_width);
    pdf->SetLineColor(kRed);
    pdf->SetNpx(500);
    pdf->Draw("same");

    double chi2 = 0;
    for (int i = 1; i <= nbin; i++)
    {
        double observed = histgram->GetBinContent(i);
        if (observed == 0)
        {
            continue;
        }
        double expected = TMath::Gaus(histgram->GetBinCenter(i), mean, stdev, true) * (N * bin_width);
        cout << histgram->GetBinCenter(i) << " " << expected << " " << observed << endl;

        chi2 += (observed - expected) * (observed - expected) / expected;
    }
    cout << "N    :" << N << endl;
    cout << "mean :" << mean << endl;
    cout << "stdev:" << stdev << endl;
    cout << "chi2 :" << chi2 << endl;
}