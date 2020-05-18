int root_draw_registered(){ // <-- 関数名はファイル名と一致させる
  
  //-----[ フォントの種類や大きさのセッティング]-----//
  const int font = 132;  //Helvetica
  gStyle->SetTextFont(132);
  gStyle->SetLabelFont(132, "xyz");
  gStyle->SetTitleFont(132, "xyz");
  gStyle->SetLegendFont(132);
  gStyle->SetStatFont(132);
  gStyle->SetLabelSize(0.05,"xyz");
  gStyle->SetTitleSize(0.05,"xyz");
  gStyle->SetOptStat(0); //グラフ描くだけなのに統計Boxは邪魔なので消す
  //
  // もちろんgROOT->SetStyle("ATLAS");としてみても良い
  // 自分の所属する実験グループのスタイルに合わせておくのが良い
  //
 

  //-----[ キャンバスの準備 ]-----//
  TCanvas* c1 = new TCanvas("c1", "title", 600, 400);
  //
  //  titleは何も書かずに""でも動く
  //  nameはちゃんと定義しないといけない
  //

  //--- 上下左右の余白を調整
  c1->SetTopMargin(0.07);
  c1->SetLeftMargin(0.12);
  c1->SetRightMargin(0.05);
  c1->SetBottomMargin(0.12);


  //-----[ 枠の準備 ]------//
  // 
  //  人によってはTGraphを描く時に
  //  g1->Draw("a");
  //  として軸も描く人もいるけど,
  //  後々綺麗な図を描きたい時に
  //  TH1Dで軸を定義しておいた方が楽
  //
  const Int_t Nbins = 2; //今回TH1Dで描くのは枠だけなのでビン数はどうでもいい
  const ULong64_t XMin = 1587014000; //横軸unixtimeの下限
  const ULong64_t XMax = 1587915638; //横軸unixtimeの上限
  TH1D* frame1 = new TH1D("frame1", "title", Nbins, XMin, XMax);
  const Double_t YMin = 0;
  const Double_t YMax = 350;
  //
  // Int_t, Double_tなどはROOTで定義されている変数の型
  // CやC++だと int, double に対応している
  // パソコンや環境が違っても適切に処理できるようにしている(が最近のマシンを使っている限りはあんまり気にしなくて良いと思う)
  // ex) ULong64_tは64ビットunsigned long long int
  //
  frame1->SetMinimum(YMin);
  frame1->SetMaximum(YMax);
  frame1->SetYTitle("Number of Registered");
  frame1->GetYaxis()->SetTitleOffset(0.9);
  frame1->SetXTitle("Date");
  frame1->GetXaxis()->SetTitleOffset(1.2);
  //--- x軸を数値(unixtime)じゃなくて日付(date)表記にする
  frame1->GetXaxis()->SetTimeDisplay(1);
  frame1->GetXaxis()->SetTimeFormat("%Y/%m/%d");
  //
  //  ROOTのオフセットはunixtimeとずれているので, 必ずSetTimeOffsetする
  //
  frame1->GetXaxis()->SetTimeOffset(32400, "gmt");  //今回は日本時間(JST = GMTに対して32400秒のずれ)で表記
  frame1->GetXaxis()->SetLabelOffset(0.02);
  frame1->Draw("");

  
  //-----[ ファイルから読み込む]-----//
  //--- ファイルを開く
  const string ReadFilename = "./SampleData.txt";
  ifstream fin(ReadFilename.c_str());
  if(!fin.good()){//--- 開けなかったらエラーを吐いて終了する
    cerr << "# Error: failed to open readfile" << endl;
    return -1;
  }
  //--- 配列の初期化
  const int NofARRAY = 163; //データの個数
  double x_val[NofARRAY], y_val[NofARRAY];
  for(int i=0; i<NofARRAY; i++){
    x_val[i] = 0;
    y_val[i] = 0;
  }
  int index = 0;
  //--- 1行ずつ読んでいく(ファイルの読み方はたくさん方法がある)
  //ここでは1行ずつbuffに詰めて, buffからx_valとy_valの配列にいれている
  string buff;
  double tmp_x, tmp_y;
  while(!fin.eof()){
    getline(fin, buff);
    istringstream iss(buff);
    if(iss >> tmp_x >> tmp_y){
      x_val[index] = tmp_x;
      y_val[index] = tmp_y;
      index++;
    }
  }
  fin.close();

  //-----[ TGraphに詰める ]-----//
  TGraph* g1 = new TGraph(index,  //点の数
                          x_val,  //xの値が詰まった配列
                          y_val); //yの値が詰まった配列
  g1->SetName("g1"); //TGraphは名前がコンストラクタの引数にない
  g1->SetMarkerStyle(7);
  g1->SetMarkerColor(1);
  g1->SetLineColor(1);  
  //
  // 実はifstreamでファイルを開いて配列に詰めなくても
  // TGraph* g1 = new TGraph("./SampleData.txt");
  // だけでいける
  // 勝手に一列目をx, 二列目をyとして突っ込んでくれる
  //
  g1->Draw("same, P");
  //
  // オプション"same"で前に描いたframe1に重ね描きする
  // オプション"P"で点を打つ
  // TH1Dで先に枠を描いてない場合にはオプション"A"でTGraphが勝手に軸を描く
  //

  /*
  //-----[ フィットしてみる ]-----//
  gStyle->SetOptFit(1111); //フィット結果表示Box
  g1->Fit("pol1", //関数形
          "",     //フィッティングオプション, "LL"でLogLikelihoodなど
          "",     //グラフオプション
          XMin,  //Fitting下限
          XMax); //Fitting上限
  //--- パラメータを取り出す
  const Double_t p0 = g1->GetFunction("pol1")->GetParameter(0);
  const Double_t p1 = g1->GetFunction("pol1")->GetParameter(1);
  cout << "### fit parameters " << endl
       << "  p0 = " << p0 << endl
       << "  p1 = " << p1 << endl
       << endl;      
  //
  // 関数形は下記のものなどがdefaultで用意されてる
  // "gaus", "landau", "expo", "pol1", etc...
  //
  //
  // エラーバーがないのでこのフィットに統計学的意味はない
  // 何かモデルがあって１次関数を選んでいるわけではないので, 数学的・物理学的にも意味がない
  // フィット結果も全く合っていないのでこのフィットには全く意味がない
  //
  */
  
  return 0;
}
