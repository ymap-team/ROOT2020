#include "my_style.hpp"
#include <TF1.h>
#include <TMath.h>
#include <sstream>
using namespace std;

void plot_chi2(int ndf = 4)
{
    SetMyStyle();

    int x_max = 1;
    while (true)
    {
        cout << TMath::Prob(x_max, ndf) << endl;
        if (TMath::Prob(x_max, ndf) < 0.00001)
        {
            break;
        }
        x_max++;
    }
    x_max = (x_max / 10) * 10;

    TF1 *pdf = new TF1("pdf", "ROOT::Math::chisquared_pdf(x,[0],0)", 0, x_max);
    pdf->SetParameter(0, ndf);
    pdf->SetNpx(500);
    pdf->SetTitle(Form("#chi^{2} distribusion ndf = %d;#chi^{2};Probability", ndf));
    pdf->Draw();
}