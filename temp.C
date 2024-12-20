Int_t temp(){
  //
  Double_t R2 = 2.11*1000.0;
  // 
  Double_t R1 = 10000.0;
  Double_t T1 = 25.0 + 273.15;
  Double_t B = 3425.0;
  Double_t T2 = B/(B/T1 - TMath::Log(R1/R2));
  //
  //
  cout<<"T2          : "<<T2<<endl
      <<"T2 - 273.15 : "<<T2 - 273.15<<endl;
  //
  //
  return 0;
}
