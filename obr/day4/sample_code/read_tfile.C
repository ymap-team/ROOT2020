int read_tfile(){

  TFile* finROOT = new TFile("./hoge.root", "read");  
  TTree* tree = (TTree*)finROOT->Get("tree");
  double energy;
  double adc_mean, adc_error;
  tree->SetBranchAddress("energy", &energy);
  tree->SetBranchAddress("adc_mean", &adc_mean);
  tree->SetBranchAddress("adc_error", &adc_error);

  tree->Draw("energy:adc_mean", "", "goff");
  TGraph* g1 = new TGraph(tree->GetSelectedRows(), tree->GetV2(), tree->GetV1());
  g1->GetXaxis()->SetTitle("ADC");
  g1->GetYaxis()->SetTitle("Energy");
  g1->SetMarkerStyle(3);
  g1->SetMarkerColor(4);
  g1->Draw("AP");
  

  return 0;
}
