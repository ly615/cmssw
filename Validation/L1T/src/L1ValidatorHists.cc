#include "Validation/L1T/interface/L1ValidatorHists.h"

//#include <DataFormats/HepMCCandidate/interface/GenParticle.h>

#include "DataFormats/Math/interface/deltaR.h"

/*#define BOOKHISTS(TYPE) \
TYPE ## _N_Pt = new TH2F(#TYPE "_N_Pt", #TYPE " Number", 20, 0, 200); \
TYPE ## _N_Eta = new TH2F(#TYPE "_N_Eta", #TYPE " Number", 20, -4, 4); \
TYPE ## _Eff_Pt = new TH2F(#TYPE "_Eff_Pt", #TYPE " Number", 20, 0, 200); \
TYPE ## _Eff_Eta = new TH2F(#TYPE "_Eff_Eta", #TYPE " Number", 20, -4, 4); \
TYPE ## _dR = new TH2F(#TYPE "_dR", #TYPE " Number", 20, 0, 1); \
TYPE ## _dPt = new TH2F(#TYPE "_dPt", #TYPE " Number", 20, -1, 1);
*/
L1ValidatorHists::L1ValidatorHists(){
//  Name[0]="IsoEG";
//  Name[1]="NonIsoEG";
//  Name[2]="CenJet";
//  Name[3]="ForJet";
//  Name[4]="TauJet";
//  Name[5]="Muon";
  Name[0]="Egamma";
  Name[1]="Jet";
  Name[2]="Tau";
  Name[3]="Muon";

}
L1ValidatorHists::~L1ValidatorHists(){}

void L1ValidatorHists::Book(DQMStore::IBooker &iBooker){
  NEvents=0;

  for(int i=0; i<Type::Number; i++){
    N[i] = iBooker.book1D( (Name[i]+"_N").c_str(), (Name[i]+" Number").c_str(), 5, -0.5, 4.5);

    Eff_Pt[i] = iBooker.book1D( (Name[i]+"_Eff_Pt").c_str(), (Name[i]+" Efficiency vs Pt").c_str(), 30, 0, 150);
    Eff_Pt_Denom[i] = iBooker.book1D( (Name[i]+"_Eff_Pt_Denom").c_str(), (Name[i]+" Efficiency vs Pt Denom").c_str(), 30, 0, 150);
    Eff_Pt_Nomin[i] = iBooker.book1D( (Name[i]+"_Eff_Pt_Nomin").c_str(), (Name[i]+" Efficiency vs Pt Nomin").c_str(), 30, 0, 150);
    Eff_Eta[i] = iBooker.book1D( (Name[i]+"_Eff_Eta").c_str(), (Name[i]+" Efficiency vs Eta").c_str(), 20, -4, 4);
    Eff_Eta_Denom[i] = iBooker.book1D( (Name[i]+"_Eff_Eta_Denom").c_str(), (Name[i]+" Efficiency vs Eta Denom").c_str(), 20, -4, 4);
    Eff_Eta_Nomin[i] = iBooker.book1D( (Name[i]+"_Eff_Eta_Nomin").c_str(), (Name[i]+" Efficiency vs Eta Nomin").c_str(), 20, -4, 4);
    TurnOn_15[i] = iBooker.book1D( (Name[i]+"_TurnOn_15").c_str(), (Name[i]+" Turn On (15 GeV)").c_str(), 30, 0, 150);
    TurnOn_15_Denom[i] = iBooker.book1D( (Name[i]+"_TurnOn_15_Denom").c_str(), (Name[i]+" Turn On (15 GeV) Denom").c_str(), 30, 0, 150);
    TurnOn_15_Nomin[i] = iBooker.book1D( (Name[i]+"_TurnOn_15_Nomin").c_str(), (Name[i]+" Turn On (15 GeV) Nomin").c_str(), 30, 0, 150);
    TurnOn_30[i] = iBooker.book1D( (Name[i]+"_TurnOn_30").c_str(), (Name[i]+" Turn On (30 GeV)").c_str(), 30, 0, 150);
    TurnOn_30_Denom[i] = iBooker.book1D( (Name[i]+"_TurnOn_30_Denom").c_str(), (Name[i]+" Turn On (30 GeV) Denom").c_str(), 30, 0, 150);
    TurnOn_30_Nomin[i] = iBooker.book1D( (Name[i]+"_TurnOn_30_Nomin").c_str(), (Name[i]+" Turn On (30 GeV) Nomin").c_str(), 30, 0, 150);
    dR[i] = iBooker.book1D( (Name[i]+"_dR").c_str(), (Name[i]+" dR").c_str(), 20, 0, 1);
    dPt[i] = iBooker.book1D( (Name[i]+"_dPt").c_str(), (Name[i]+" dPt").c_str(), 20, -1, 1);
  }

}

void L1ValidatorHists::Fill(int i, const reco::LeafCandidate *GenPart, const reco::LeafCandidate *RecoPart){
  if(RecoPart==NULL) {
     Eff_Pt_Denom[i]->Fill(GenPart->pt());
     if(GenPart->pt()>10)Eff_Eta_Denom[i]->Fill(GenPart->eta());
     TurnOn_15_Denom[i]->Fill(GenPart->pt());
     TurnOn_30_Denom[i]->Fill(GenPart->pt());
  } else {

     Eff_Pt_Denom[i]->Fill(GenPart->pt());
     if(GenPart->pt()>10)Eff_Eta_Denom[i]->Fill(GenPart->eta());
     if(RecoPart->pt() > GenPart->pt())Eff_Pt_Nomin[i]->Fill(GenPart->pt());
     if(RecoPart->pt() > GenPart->pt() && GenPart->pt()>10)Eff_Eta_Nomin[i]->Fill(GenPart->eta());
     if(RecoPart->pt() > GenPart->pt())Eff_Pt[i]->Fill(GenPart->pt());
     TurnOn_15_Denom[i]->Fill(GenPart->pt());
     TurnOn_30_Denom[i]->Fill(GenPart->pt());
     if(RecoPart->pt()>15 && RecoPart->pt() > GenPart->pt()) TurnOn_15_Nomin[i]->Fill(GenPart->pt());
     if(RecoPart->pt()>30 && RecoPart->pt() > GenPart->pt()) TurnOn_30_Nomin[i]->Fill(GenPart->pt());
     if(RecoPart->pt()>15 && RecoPart->pt() > GenPart->pt()) TurnOn_15[i]->Fill(GenPart->pt());
     if(RecoPart->pt()>30 && RecoPart->pt() > GenPart->pt()) TurnOn_30[i]->Fill(GenPart->pt());
     if(RecoPart->pt() > GenPart->pt() && GenPart->pt()>10)Eff_Eta[i]->Fill(GenPart->eta());
     dR[i]->Fill(reco::deltaR(GenPart->eta(), GenPart->phi(), RecoPart->eta(), RecoPart->phi()));
     dPt[i]->Fill( (RecoPart->pt()-GenPart->pt()) / GenPart->pt() );
  }
}

void L1ValidatorHists::FillNumber(int i, int Number){
  N[i]->Fill(Number);
}

void L1ValidatorHists::Write(){
  for(int i=0; i<Type::Number; i++){
    N[i]->getTH1()->Write();
    Eff_Pt[i]->getTH1()->Write();
    Eff_Pt_Denom[i]->getTH1()->Write();
    Eff_Pt_Nomin[i]->getTH1()->Write();
    Eff_Eta[i]->getTH1()->Write();
    Eff_Eta_Denom[i]->getTH1()->Write();
    Eff_Eta_Nomin[i]->getTH1()->Write();
    TurnOn_15[i]->getTH1()->Write();
    TurnOn_15_Denom[i]->getTH1()->Write();
    TurnOn_15_Nomin[i]->getTH1()->Write();
    TurnOn_30[i]->getTH1()->Write();
    TurnOn_30_Denom[i]->getTH1()->Write();
    TurnOn_30_Nomin[i]->getTH1()->Write();
    dR[i]->getTH1()->Write();
    dPt[i]->getTH1()->Write();
  }
}

/*void L1ValidatorHists::NormalizeSlices(TH2F *Hist){
  int NBinsX = Hist->GetNbinsX();
  int NBinsY = Hist->GetNbinsY();
  for(int i=0; i<NBinsX+2; i++){
    float Total = Hist->Integral(i, i, 0, -1);
    if(Total == 0) continue;
    for(int j=0; j<NBinsY+2; j++){
      Hist->SetBinContent(i,j, Hist->GetBinContent(i,j)/Total);
    }
  }
}
*/
