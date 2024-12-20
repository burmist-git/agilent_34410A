//C, C++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include <time.h>

void get_data_IRCAM(TH2D *h2, TString name_dat_file);

Double_t temp(Double_t R2);

Int_t plot_IR(){
  //
  TH2D *h2_top = new TH2D();
  TH2D *h2_bot = new TH2D();
  h2_top->SetNameTitle("h2_top","h2_top");
  h2_bot->SetNameTitle("h2_bot","h2_bot");
  //
  get_data_IRCAM(h2_bot, "./data/hottilebot.csv");
  get_data_IRCAM(h2_top, "./data/hottiletop.csv");
  //  
  TCanvas *c1 = new TCanvas("c1","c1",10,10,640,480);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  gStyle->SetOptStat(kFALSE);
  //
  //
  h2_top->SetMinimum(50.0);
  h2_top->SetMaximum(55.0);
  h2_top->Draw("ZCOLOR");
  //
  h2_top->GetXaxis()->SetTitle("pixel x");
  h2_top->GetYaxis()->SetTitle("pixel y");
  //
  TCanvas *c2 = new TCanvas("c2","c2",10,10,640,480);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  gStyle->SetOptStat(kFALSE);
  //
  //
  h2_bot->SetMinimum(50.0);
  h2_bot->SetMaximum(55.0);
  h2_bot->Draw("ZCOLOR");
  //
  h2_bot->GetXaxis()->SetTitle("pixel x");
  h2_bot->GetYaxis()->SetTitle("pixel y");
  return 0;
}

void get_data_IRCAM(TH2D *h2, TString name_dat_file){
  //
  Int_t nx = 640;
  Int_t ny = 480;
  h2->SetBins(nx, 0, nx, ny, 0, ny);
  //
  Double_t t;
  //
  Int_t np = 0;
  Int_t iy=0;
  Int_t ix=0;
  //  
  ifstream indata;
  string mot;
  indata.open(name_dat_file.Data());
  assert(indata.is_open());  
  for(iy=0; iy<ny; iy++){
    for(ix=0; ix<nx; ix++){
      indata>>t;
      //cout<<t<<endl;
      h2->SetBinContent(ix+1,iy+1,t);
    }
  }
  indata.close();
}
