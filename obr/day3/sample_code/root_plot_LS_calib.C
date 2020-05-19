int root_plot_LS_calib(){

  TGraphErrors* g1 = new TGraphErrors();
  int index = 0;
  
  char ReadFilename[256] = "./sample_data/data1.txt";
  ifstream fin(ReadFilename);
  if(!fin.good()){
    cerr << "# Error: failed to open file" << endl;
    return -1;
  }
  double energy, adc_mean, adc_error;
  while(fin >> energy >> adc_mean >> adc_error){
    g1->SetPoint(index, energy, adc_mean);
    g1->SetPointError(index, 0, adc_error);
    index++;
  }
  fin.close();

  g1->SetMarkerStyle(3);
  g1->SetMarkerColor(4);
  g1->SetTitle("LS Calib; energy (keV); ADC mean");
  g1->Draw("AP");

  //g1->Fit("pol1");
  g1->Fit("pol1", "", "", 300, 1200);  
  
  return 0;
}
