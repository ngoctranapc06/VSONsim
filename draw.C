void draw(){
  ifstream data("data2.txt");
  TH1F *h = new TH1F("h","h",150,0,1500);
  double value;
  while(data>>value){
    if(value!=0)h->Fill(value);
  }
  h->SetFillColor(2);
  h->GetXaxis()->SetTitle("Energy (keV)");
  h->Draw();
}
