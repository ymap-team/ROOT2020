int back_scatter(){ // <-- 関数名はファイル名と一致させる
  
  //-----[ フォントの種類や大きさのセッティング]-----//
  const int font = 132;  //Helvetica
  gStyle->SetTextFont(132);
  gStyle->SetLabelFont(132, "xyz");
  gStyle->SetTitleFont(132, "xyz");
  gStyle->SetLegendFont(132);
  gStyle->SetStatFont(132);
  gStyle->SetLabelSize(0.05,"xyz");
  gStyle->SetTitleSize(0.05,"xyz");
  gStyle->SetOptFit(1111);
  //
  // もちろんgROOT->SetStyle("ATLAS");としてみても良い
  // 自分の所属する実験グループのスタイルに合わせておくのが良い
  //

  //-----[ファイル読み込み]-----//
  const string ReadFilename = "./sample_data/data3.root";
  TFile* finROOT = new TFile(ReadFilename.c_str(), "read");  
  if(!finROOT->IsOpen()){
    cerr << "# Error: failed to open rootfile" << endl;
    return -1;
  }
  //
  // string型のReadFilenameをchar型にして引数に指定
  // read only modeで開く (間違って上書きしないようにする)
  //
  TTree* tree = (TTree*)finROOT->Get("tree");
  //
  // "finROOT"で開いたファイルから"tree"という名前のオブジェクトをGetする
  //
  Float_t adc_LS, adc_NaI;
  tree->SetBranchAddress("adc_LS", &adc_LS);
  tree->SetBranchAddress("adc_NaI", &adc_NaI);
  //
  // 読み込んだtreeの変数のアドレスを指定
  //


  
  //-----[ キャンバスの準備 ]-----//
  TCanvas* c1 = new TCanvas("c1", "title", 900, 600);
  //
  //  titleは何も書かずに""でも動く
  //  nameはちゃんと定義しないといけない
  //
  //--- 上下左右の余白を調整
  c1->SetTopMargin(0.07);
  c1->SetLeftMargin(0.12);
  c1->SetRightMargin(0.05);
  c1->SetBottomMargin(0.12);

  c1->Divide(2,2);  //--- canvasを2×2に分割


  //-----[ 選択条件 ]-----//
  TCut selection = "adc_NaI>1250 && adc_NaI<1300";
  
  
  //-----[ LSのヒストグラム ]-----//
  c1->cd(1);  //---- canvasの左上に移動  
  const Double_t MinLS = 0;
  const Double_t MaxLS = 500;
  const Double_t BinWidthLS = 2;
  const Int_t NofBinsLS = (Int_t)((MaxLS-MinLS)/BinWidthLS);
  TH1D* hLS = new TH1D("hLS", "LS", NofBinsLS, MinLS, MaxLS);  
  TH1D* hLScut = new TH1D("hLScut", "LS", NofBinsLS, MinLS, MaxLS);
  hLS->SetLineColor(1);
  hLS->SetXTitle("ADC [ch]");
  hLS->SetYTitle("counts/2ch");  
  hLScut->SetLineColor(4);
  tree->Draw("adc_LS >> hLS", "", "");
  tree->Draw("adc_LS >> hLScut", selection , "same");
  //-- fitting
  const double FitRangeMin = 260;
  const double FitRangeMax = 350;
  hLScut->Fit("gaus", "", "", FitRangeMin, FitRangeMax);
  const double mean = hLScut->GetFunction("gaus")->GetParameter(1);
  const double mean_error  = hLScut->GetFunction("gaus")->GetParError(1);
  cout << mean << " +- " << mean_error << endl;
    

  //-----[ NaIのヒストグラム ]-----//
  c1->cd(2);  //---- canvasの右上に移動  
  const Double_t MinNaI = 0;
  const Double_t MaxNaI = 1500;
  const Double_t BinWidthNaI = 2;
  const Int_t NofBinsNaI = (Int_t)((MaxNaI-MinNaI)/BinWidthNaI);
  TH1D* hNaI = new TH1D("hNaI", "NaI", NofBinsNaI, MinNaI, MaxNaI);  
  TH1D* hNaIcut = new TH1D("hNaIcut", "NaI",NofBinsNaI, MinNaI, MaxNaI);
  hNaI->SetLineColor(1);
  hNaI->SetXTitle("ADC [ch]");
  hNaI->SetYTitle("counts/2ch");  
  hNaIcut->SetLineColor(4);
  tree->Draw("adc_NaI >> hNaI", "", "");
  tree->Draw("adc_NaI >> hNaIcut", selection , "same");

  //-----[ 2次元 ]-----//
  c1->cd(3); //左下
  TH2D* scat = new TH2D("scat", "NaI vs LS", NofBinsLS, MinLS, MaxLS, NofBinsNaI, MinNaI, MaxNaI);
  scat->SetXTitle("LS");
  scat->SetYTitle("NaI");
  scat->GetYaxis()->SetTitleOffset(0.8);
  tree->Draw("adc_NaI:adc_LS >> scat", "", "colz");
  

  return 0;
}
