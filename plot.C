//C, C++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include <time.h>

template <class T>
void get_data_agilent(T *gr, TString name_dat_file);
Double_t temp(Double_t R2);

Int_t plot(){
  //
  TGraph *gr_26V = new TGraph();
  gr_26V->SetNameTitle("gr_26V","gr_26V");
  TGraph *gr_20V = new TGraph();
  gr_20V->SetNameTitle("gr_20V","gr_20V");
  TGraph *gr_15V = new TGraph();
  gr_15V->SetNameTitle("gr_15V","gr_15V");
  TGraph *gr_10V = new TGraph();
  gr_10V->SetNameTitle("gr_10V","gr_10V");
  TGraph *gr_5V = new TGraph();
  gr_5V->SetNameTitle("gr_5V","gr_5V");
  TGraph *gr = new TGraph();
  gr->SetNameTitle("gr","gr");
  //
  get_data_agilent<TGraph>( gr_26V, "data/agilent_34410A_meas_26V_f.csv");
  get_data_agilent<TGraph>( gr_20V, "data/agilent_34410A_meas_20V_f.csv");
  get_data_agilent<TGraph>( gr_15V, "data/agilent_34410A_meas_15V_f.csv");
  get_data_agilent<TGraph>( gr_10V, "data/agilent_34410A_meas_10V_f.csv");
  get_data_agilent<TGraph>( gr_5V, "data/agilent_34410A_meas_5V_f.csv");
  get_data_agilent<TGraph>( gr, "data/agilent_34410A_meas_f.csv");  
  //  
  TCanvas *c1 = new TCanvas("c1","c1",10,10,1200,600);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  gStyle->SetOptStat(kFALSE);
  //
  gPad->SetGridx();
  gPad->SetGridy();
  //gPad->SetLogx();
  //gPad->SetLogy();
  //
  TMultiGraph *mg = new TMultiGraph();
  gr_26V->SetMarkerStyle(20);
  gr_26V->SetMarkerColor(kBlack);
  gr_26V->SetLineWidth(2);
  gr_26V->SetLineColor(kBlack);
  //
  gr_20V->SetMarkerStyle(20);
  gr_20V->SetMarkerColor(kRed);
  gr_20V->SetLineWidth(2);
  gr_20V->SetLineColor(kRed);
  //
  gr_15V->SetMarkerStyle(20);
  gr_15V->SetMarkerColor(kBlue);
  gr_15V->SetLineWidth(2);
  gr_15V->SetLineColor(kBlue);
  //
  gr_10V->SetMarkerStyle(20);
  gr_10V->SetMarkerColor(kGreen);
  gr_10V->SetLineWidth(2);
  gr_10V->SetLineColor(kGreen);
  //
  gr_5V->SetMarkerStyle(20);
  gr_5V->SetMarkerColor(kMagenta);
  gr_5V->SetLineWidth(2);
  gr_5V->SetLineColor(kMagenta);
  //
  gr->SetMarkerStyle(20);
  gr->SetMarkerColor(kRed+2);
  gr->SetLineWidth(2);
  gr->SetLineColor(kRed+2);
  //
  mg->Add(gr_26V);
  mg->Add(gr_20V);
  mg->Add(gr_15V);
  mg->Add(gr_10V);
  mg->Add(gr_5V);
  mg->Add(gr);
  //
  mg->Draw("APL");
  //
  TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  leg->AddEntry(gr_26V, "26V", "apl");
  leg->AddEntry(gr_20V, "20V", "apl");
  leg->AddEntry(gr_15V, "15V", "apl");
  leg->AddEntry(gr_10V, "10V", "apl");
  leg->AddEntry(gr_5V, "5V", "apl");
  leg->Draw();  
  //
  mg->GetXaxis()->SetTitle("time, s");
  mg->GetYaxis()->SetTitle("T, ^{o}C");
  //
  return 0;
}

template <class T>
void get_data_agilent(T *gr, TString name_dat_file){
  //
  Double_t x,y;
  Double_t x0;
  //
  Int_t np = 0;
  //  
  ifstream indata;
  string mot;
  indata.open(name_dat_file.Data());
  assert(indata.is_open());  
  indata>>mot>>mot;
  while(indata>>x>>y){
    if(np == 0)
      x0 = x;
    gr->SetPoint(np,x-x0,temp(y));
    np++;
  }
  indata.close();
}

Double_t temp(Double_t R2){
  //
  //Double_t R2 = 2.11*1000.0;
  // 
  Double_t R1 = 10000.0;
  Double_t T1 = 25.0 + 273.15;
  Double_t B = 3425.0;
  Double_t T2 = B/(B/T1 - TMath::Log(R1/R2));
  //
  //
  //cout<<"T2          : "<<T2<<endl
  //     <<"T2 - 273.15 : "<<T2 - 273.15<<endl;
  //
  //
  return (T2 - 273.15);
}
