void fill_from_file(){
    
    int total_bin = 10;
    int min_bin = 0;
    int max_bin = 10;
    TH1D* hist = new TH1D("hist", "Title", total_bin, min_bin-0.5, max_bin-0.5);

    ifstream ifs("../data/data1.txt");
    int n_escaped_turn;
    while(ifs >> n_escaped_turn){
        hist->Fill(n_escaped_turn);
    }

    hist->SetTitle(";n turn which the enemy escaped;Counts/turn");
    hist->Draw();


}
