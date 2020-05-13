// ---------------------------- //
// fit_hagure.C
//      root macro
// Author: Keita Mizukoshi
// Date  : May 13 2020
// Usate : in macro directory,
// > root -l fit_hagure.C
// ---------------------------- //

int fit_hagure(){

    gROOT->SetStyle("ATLAS");

    TH1D* hist = new TH1D("hist", "hist", 25+1, 0-0.5, 25+0.5);
    ifstream ifs("./haguremetal_escape.txt");
    int n_escaped_turn;
    while(ifs >> n_escaped_turn){
        hist->Fill(n_escaped_turn);
    }
    hist->Draw("E");
    hist->SetTitle(";n turn which the enemy escaped;Counts/turn");
    // hist->Rebin(2);

    TF1* model_func = new TF1("model_func", 
        "[0]/([1]-1)*TMath::Log([1])*(TMath::Power([1],x)-TMath::Power([1],x+1))",
        -1,20);
    model_func->SetParName(0, "n_trials");
    model_func->SetParName(1, "Prob_remain");
    model_func->SetParameter(0, 37);
    model_func->SetParameter(1, 0.7);

    model_func->SetLineStyle(2);
    model_func->SetLineColor(kRed+3);

    hist->Fit("model_func","L","",-1,25);

    return 0;
}
