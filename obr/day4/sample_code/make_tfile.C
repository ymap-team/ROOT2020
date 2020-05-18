int make_tfile(){

  TTree* tree = new TTree("tree", "tree");
  double energy;
  double adc_mean, adc_error;
  tree->Branch("energy", &energy, "energy/D");
  tree->Branch("adc_mean", &adc_mean, "adc_mean/D");
  tree->Branch("adc_error", &adc_error, "adc_error/D");
  
  ifstream fin("./sample_data/data1.txt");
  while(fin >> energy >> adc_mean >> adc_error){
    tree->Fill();
  }
  fin.close();

  

  TFile* foutROOT = new TFile("./hoge.root", "RECREATE");
  tree->Write();
  foutROOT->Close();

  return 0;
}
