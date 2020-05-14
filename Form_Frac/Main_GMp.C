//////////////////////////////////////////////////////////////////////
//
// plot_gmp.C
//   Bryan Moffit - May 2007
//
//  ROOT macro to plot the experimental GMP data
//

void Main_GMp() {
    //    gROOT->Macro("HallA_style.cxx");

    gStyle->SetPaintTextFormat("5.4g");
    gStyle->SetTitleFontSize(0.06);
    gStyle->SetTitleOffset(0.06);
    //gStyle->SetTitleFont(62);
    gStyle->SetNdivisions(510);
    gStyle->SetTitleYOffset(0.65);
//    gStyle->SetTitleXOffset(0.65);
    gStyle->SetTitleYSize(0.06);
    gStyle->SetTitleXSize(0.06);
    gStyle->SetLabelFont(62,"X");
    gStyle->SetLabelFont(62,"Y");
   // gStyle->SetTitleFont(62,"X");
    //gStyle->SetTitleFont(62,"Y");
    gStyle->SetLabelSize(0.033,"X");
    gStyle->SetLabelSize(0.033,"Y");
    gStyle->SetPaperSize(11,22);
    gStyle->SetTickLength(0.035,"Y");
        gStyle->SetLineWidth(1.5);
       gStyle->SetPadRightMargin(0.03);


        gStyle->SetPadLeftMargin(0.14);
        gStyle->SetPadBottomMargin(0.14);
        gStyle->SetPadTopMargin(0.1);
double lsz = 0.045;
double ax_ti = 0.06;
double ax_off = 0.96;
double ax_offx = 1.1;



    const UInt_t nexp = 3;
    TString expdata[nexp][2] =
    {
        "andivahis", "Andivahis",
        "sill", "Sill (3% norm. uncert. not shown)",
        "christy_qattan", "Christy"
    };
    TString datadir = "";

   TGraphErrors* g_band = new TGraphErrors("fitplot_Eric.dat", "%lg %lg %lg");
      g_band->SetFillColor(12);
      g_band->SetFillStyle(3001);


    TGraphErrors *expgraphs[nexp];
    TMultiGraph *mg = 
        new TMultiGraph("mg",
                ";,");
    mg->SetMinimum(0.65);
    mg->SetMaximum(1.1);
   
      mg->Add(g_band, "A3");


    for(UInt_t iexp=0; iexp<nexp; iexp++) {
        expgraphs[iexp] = 
            new TGraphErrors(datadir+expdata[iexp][0]+".dat",
                    "%lg %lg %lg");
  //      expgraphs[iexp]->SetMarkerStyle(24+iexp);
//        expgraphs[iexp]->SetMarkerSize(1);
    	expgraphs[iexp]->SetMarkerStyle(27);
            expgraphs[iexp]->SetMarkerSize(2.5);
            expgraphs[iexp]->SetMarkerColor(kBlack);
            expgraphs[iexp]->SetLineColor(kBlack);
        if (iexp==nexp-2) {
            expgraphs[iexp]->SetMarkerStyle(25);
            expgraphs[iexp]->SetMarkerSize(2);
            expgraphs[iexp]->SetMarkerColor(kBlue);
            expgraphs[iexp]->SetLineColor(kBlue);
        }


        if (iexp==nexp-3) {
            expgraphs[iexp]->SetMarkerStyle(20);
            expgraphs[iexp]->SetMarkerSize(2.5);
            expgraphs[iexp]->SetMarkerColor(kBlue);
            expgraphs[iexp]->SetLineColor(kBlue);
        }
        mg->Add(expgraphs[iexp],"pZ");
    }

    TGraphErrors* g_b = new TGraphErrors(datadir+"band.dat", "%lg %lg %lg");
    g_b->SetMarkerSize(1.1);
    g_b->SetMarkerColor(kRed);
    g_b->SetLineColor(kRed);
    g_b->SetLineWidth(2);

   TGraphErrors* g_mydata = new TGraphErrors(datadir+"gmp_thirMar19_new.dat", "%lg %lg %lg");
    g_mydata->SetMarkerStyle(20);
    g_mydata->SetMarkerSize(2);
    g_mydata->SetMarkerColor(kRed);
    g_mydata->SetLineColor(kRed);
    g_mydata->SetLineWidth(2);
    mg->Add(g_mydata, "p");

   TGraph* g_nband = new TGraph("fitplot_Eric.dat", " %lg %lg");
 g_nband->SetLineStyle(1);
 g_nband->SetLineWidth(2);
   mg->Add(g_nband); 

   
TCanvas *canv = new TCanvas("canv","canv",50,200,1200,1200);
 //TCanvas *canv  =  new TCanvas("c1","c1",40,200,1200,1200);
    mg->Draw("a");
    //g_b->Draw("sameP");
    mg->GetXaxis()->SetLabelFont(62);

    mg->GetXaxis()->SetTitleSize(ax_ti);
    mg->GetXaxis()->SetTitleOffset(ax_offx);
    mg->GetXaxis()->SetLabelSize(lsz);
    mg->GetXaxis()->CenterTitle();
    mg->GetYaxis()->SetTitleSize(ax_ti);
    mg->GetYaxis()->SetTitleOffset(ax_off);
    mg->GetYaxis()->SetLabelSize(lsz);
    mg->GetYaxis()->CenterTitle();
    mg->GetXaxis()->SetLimits(0,33);

   TH1F* h_k = (TH1F* )mg->Clone();
   
    mg->GetXaxis()->SetLimits(4,18);
    mg->GetYaxis()->SetRangeUser(0.7,1.15);
    mg->GetYaxis()->SetTitle("G_{M}/#mu_{p} G_{D}, OPE");
    mg->GetXaxis()->SetTitle("Q^{2}, (GeV/#it{c})^{2}");


    TLine *line = 
        new TLine(mg->GetXaxis()->GetXmin(),
                0.8,
                mg->GetXaxis()->GetXmax(),
                0.8);
    line->Draw("same");
    line->SetLineStyle(3);   
    TLine *line1 = 
        new TLine(mg->GetXaxis()->GetXmin(),
                1,
                mg->GetXaxis()->GetXmax(),
                1);
    line1->Draw("same");
    line1->SetLineStyle(3);   
    g_b->SetFillColor(4);
    g_b ->SetFillStyle(10);
  //TPad *pad = new TPad("", "",0.5208551,0.5115431,0.8952033,0.8967193);
  TPad *pad = new TPad("", "",0.46988551,0.49855431,0.9552033,0.898999999);
   pad->Draw();
   pad->cd();

   
   //pad->DrawFrame(0,0.7,33,1.15);  
   pad->DrawFrame(0,0.8,23,0.9);  
   h_k->Draw("SameP");
    canv->SaveAs("/home/thir/Desktop/GMP_/Ref_new/Plots/Fig2.png");
    canv->SaveAs("/home/thir/Desktop/GMP_/Ref_new/Plots/Fig2.pdf");
}
