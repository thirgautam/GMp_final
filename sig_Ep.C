

void sig_Ep(){
	gStyle->SetOptFit(1);
	gStyle->SetOptStat(1);
	gStyle->SetPaintTextFormat("5.4g");
	gStyle->SetTitleFontSize(0.06);
	gStyle->SetTitleOffset(0.06);
	gStyle->SetTitleFont(42);
	//gStyle->SetNdivisions(510);
	gStyle->SetNdivisions(510);
	gStyle->SetTitleYOffset(0.6);
	gStyle->SetTitleXOffset(0.65);
	gStyle->SetTitleYSize(0.06);
	gStyle->SetTitleXSize(0.06);
	gStyle->SetLabelFont(42,"X");
	gStyle->SetLabelFont(42,"Y");
	gStyle->SetTitleFont(42,"X");
	gStyle->SetTitleFont(42,"Y");
	gStyle->SetLabelSize(0.033,"X");
	gStyle->SetLabelSize(0.033,"Y");
	gStyle->SetPaperSize(11,22);
	gStyle->SetLineWidth(1);
	gStyle->SetPadRightMargin(0.015);
	gStyle->SetPadLeftMargin(0.12);
	gStyle->SetPadBottomMargin(0.22);
	gStyle->SetPadTopMargin(0.4);
double x_d = 0;
double x_u = 18.;

	TCanvas *c1  =  new TCanvas("c1","c1",40,200,1200,1200);
        c1->Divide(1,2,0.01,0.001);
	c1->cd(1);
	gPad->SetBottomMargin(0.0);
	gPad->SetTopMargin(0.23);
       
//       	gStyle->SetTickLength(0.0,"X");
	//gPad->SetPad(0.0,0.4,1.0,1.0);
  ifstream infile("datafiles/for_table.dat");
  string line;
  int lines;
  const int count=-1;
  double Eps, Qsq, Qcsq, ExpNo, cs, ecs;
  vector<double> vaEps, vaQsq, vaQcsq, vaExpNo;
  ofstream* outfile = new ofstream;
  outfile->open("exp.txt");
  ofstream* outfile1 = new ofstream;
  outfile1->open("Q2c.txt");
  while(!infile.eof()){
    infile>>Qsq>>Qcsq>>Eps>>cs>>ecs>>ExpNo;
    count++;
    vaEps.push_back(Eps);
    vaQsq.push_back(Qsq);
    vaQcsq.push_back(Qcsq);
    vaExpNo.push_back(ExpNo);
    *outfile<<ExpNo<<"\t"<<endl;
    *outfile1<<Qcsq<<"\t"<<endl;

  }
  double aEps[count], aQsq[count], aQcsq[count], aExpNo[count];
  for(int i = 0; i < count; ++i){
    aEps[i] = vaEps[i];
    aQsq[i] = vaQsq[i];
    aQcsq[i] = vaQcsq[i];
    aExpNo[i] = vaExpNo[i];
  }

  //cout<<"couont::::::: "<<count<<endl;
  int a=system("rm exp_new.txt; sort exp.txt | uniq >exp_new.txt");
  int a=system("rm exp.txt ");
  int a=system("rm Q2c_new.txt; sort Q2c.txt | uniq >Q2c_new.txt");
  int a=system("rm Q2c.txt ");
  ifstream infile_exp("exp_new.txt");
  ifstream infile_exp1("exp_new.txt");
  ifstream infile_q2("Q2c_new.txt");
  ifstream infile_q21("Q2c_new.txt");
  string line_e, line_q2;
  int lines_e, lines_q2;
  int counts_e=-1,counts_q2=-1;

  while(!infile_exp1.eof()) {
    getline(infile_exp1, line_e);
    counts_e ++;
  }
  while(!infile_q21.eof()) {
    getline(infile_q21, line_q2);
    counts_q2 ++;
  }
  const int count_e = counts_e;
  const int count_q2 = counts_q2;
  Double_t q2c_n,q2c_nn[count_q2];	
  for(int j =0; j<count_q2;j++)
    {
      infile_q2>>q2c_n;
      q2c_nn[j] = q2c_n;


    }
double lsz = 0.07;
double ax_ti = 0.1;
double ax_off = 0.5;
double ax_offx = 1.0;
//TCanvas *c1 = new TCanvas("c1","c1",50,200,2000,2000);


  //TCanvas *c1  =  new TCanvas("c1","c1",2000,1300); 
//c1->Divide(1,2,0,0.01);
//c1->cd(1);
  TGraph* Graph = new TGraph(count,aQsq,aEps);
  Graph->Draw("AP");
	
  Graph->SetTitle("; Q^{2}, (GeV/c)^{2};#varepsilon");
  gStyle->SetTitleSize(0.04,"t");
 // gStyle->SetTitleFont(62,"t");
  Graph->GetYaxis()->SetTitleSize(ax_ti);
  Graph->GetYaxis()->SetTitleOffset(ax_off);
  Graph->GetYaxis()->SetLabelFont(62);
  Graph->GetXaxis()->SetTitleSize(ax_ti);
  Graph->GetXaxis()->SetTitleOffset(ax_offx);
  Graph->GetXaxis()->SetLabelFont(62);
  Graph->GetXaxis()->SetLabelSize(lsz);
  Graph->GetYaxis()->SetLabelSize(lsz);
  Graph->GetYaxis()->CenterTitle();
  Graph->GetXaxis()->CenterTitle();
  Graph->GetXaxis()->SetLimits(x_d,x_u);
  Graph->GetYaxis()->SetRangeUser(0.01,1);
  Graph->SetMarkerColor(kWhite);
  Graph->GetXaxis()->SetTickLength(0.0);
  Graph->GetYaxis()->SetNdivisions(505);
  int Exp_N, Exp_NN[count_e];



  Double_t* nx = Graph->GetX();
  Double_t* ny = Graph->GetY();

  double mn[count_q2];// = {aQsq[0]};
  double mx[count_q2];// = {aQsq[0]};
  TBox* b[count_q2];
  for(int j =0; j<count_e;j++)
    {

      infile_exp>>Exp_N;
      Exp_NN[j] = Exp_N;
      //cout<<Exp_NN[j]<<endl;

      for(int i=0;i<count;i++){
	TMarker* m=new TMarker(nx[i],ny[i],22);
	//if(Exp_NN[j]==aExpNo[i])
	m->SetMarkerSize(2.5);

	if(aExpNo[i]==1){
	  m->SetMarkerStyle(20); //And
	  m->SetMarkerColor(kBlue); //And
	}
	else  if(aExpNo[i]==2){
	  m->SetMarkerColor(kBlue); //And
	  m->SetMarkerStyle(20); //And
	}
	else if(aExpNo[i]==5)
	  m->SetMarkerStyle(21);//Bartel
	else if(aExpNo[i]==6)
	  m->SetMarkerStyle(29);//Albrechti
	else if(aExpNo[i]==8)
	  m->SetMarkerStyle(26); //Goiten
	else if(aExpNo[i]==9)
	  m->SetMarkerStyle(23);//Berger
	else if(aExpNo[i]==10)
	  m->SetMarkerStyle(22); //Price
	else if(aExpNo[i]==11)
	  m->SetMarkerStyle(33);//Bartel
	else if(aExpNo[i]==12)
	  m->SetMarkerStyle(33);//Bartel
	else if(aExpNo[i]==13)
	  m->SetMarkerStyle(33);//Bartel
	else if(aExpNo[i]==14)
	  m->SetMarkerStyle(32); //Krik
	else if(aExpNo[i]==15){
	  m->SetMarkerStyle(25); //Sill
	  m->SetMarkerColor(kBlue); //Sill
	}
	else if(aExpNo[i]==17)
	  m->SetMarkerStyle(26); //Goiten
	else if(aExpNo[i]==18)
	  m->SetMarkerStyle(29);// Albrecht
	else if(aExpNo[i]==20){
	  m->SetMarkerStyle(32); //Rock
	  m->SetMarkerColor(kRed); //Rock
	}

	else if(aExpNo[i]==25)
	  m->SetMarkerStyle(5); //Niculescu
	else if(aExpNo[i]==27)
	  m->SetMarkerStyle(27); //christy
	else if(aExpNo[i]==28){
	  m->SetMarkerStyle(20); //GMp
	  m->SetMarkerColor(kRed); //GMP
	}
	else if(aExpNo[i]==29){
	  m->SetMarkerStyle(20); //GMP
	  m->SetMarkerColor(kRed); //GMP
	}
	else continue;
	m->Draw();

      }
    }
  
  
  
  for(int k=0;k<count_q2;k++){
    mn[k] = 100;
    mx[k] = 0;

    for(int i=0;i<=count;i++){

      if(aQcsq[i]==q2c_nn[k]){
	if(mn[k]>aQsq[i])
	  mn[k]=aQsq[i];
	else if(mx[k]<aQsq[i])
	  mx[k]=aQsq[i];
      }		
    }
 //   if(/*k!=2 &&k!=4 &&k!=3*/){

     // b[k] = new TBox(mn[k]-0.16,0.08,mx[k]+0.16,0.99);
      b[k] = new TBox(mn[k]-0.22,0.015,mx[k]+0.22,0.99);
    // b[k] = new TBox(mn[k]-0.1,0.015,mx[k]+0.1,0.99);
      b[k]->SetFillColor(3);
      b[k]->SetLineColor(0+1);
      b[k]->SetFillStyle(0);
      b[k]->Draw();
		  

      //cout<<mn[k]<<"\t"<<q2c_nn[k]<<"\t"<<mx[k]<<endl;
   // }

    tex = new TLatex(5.826406,1.035,"1");
    tex->SetTextColor(2);
    tex->SetLineWidth(2);
    tex->Draw();
    tex = new TLatex(6.923652,1.035,"2");
    tex->SetTextColor(2);
    tex->SetLineWidth(2);
    tex->Draw();

    tex = new TLatex(7.825832,1.035,"3");
    tex->SetTextColor(2);
    tex->SetLineWidth(2);
    tex->Draw();
    tex = new TLatex(9.11162,1.035,"4");
    tex->SetTextColor(2);
    tex->SetLineWidth(2);
    tex->Draw();
    tex = new TLatex(12.199937,1.035,"5");
    tex->SetTextColor(2);
    tex->SetLineWidth(2);
    tex->Draw();
    tex = new TLatex(15.6797,1.035,"6");
    tex->SetTextColor(2);
    tex->SetLineWidth(2);
    tex->Draw();

 /*   TPaveText *t11 = new TPaveText(0.15,0.08,0.2,0.76,"NDC");
    t11->AddText(" ");
    t11->SetShadowColor(0);
    t11->SetFillColor(0);
    t11->SetTextSize(0.04);
    t11->SetBorderSize(0);
    t11->Draw("same");
*/
  }

	const  Int_t mk = 331;

	double a_1[mk],a_2[mk],a_3[mk],exl[mk],exh[mk];
	ifstream inputfile50;
	inputfile50.open("datafiles/fitplot_Eric.dat"); 
	double a2_max[mk],a2_min[mk];
	for(int i=0;i<mk;i++){
		inputfile50>>fixed>>a_1[i]>>a_2[i]>>a_3[i];
		a2_max[i] = a_3[i];
//		a2_min[i] = a_2[i] - a_3[i];
		exl[i] =0; exh[i]=0;
		cout<<a_1[i]<< "  "<<a_2[i]<<endl;
	}
	inputfile50.close();

	const Double_t mup = 2.792782;  // magnetic momentum of proton
	const Double_t mp = 0.938272;


	ifstream inputfile1,inputfile2,inputfile3,inputfile4,inputfile5,inputfile51, inputfile6, inputfile7;

	inputfile1.open("datafiles/hallc_gegm.dat");
	inputfile2.open("datafiles/walker_gegm.dat");
	inputfile3.open("datafiles/ne11_gegm.dat");
	inputfile4.open("datafiles/halla_gegm.dat");
	inputfile5.open("datafiles/Ge_Gm.dat");
	inputfile7.open("datafiles/quttan_data.dat");

	const  Int_t m1 = 7;
	const  Int_t m2 = 12;
	const  Int_t m3 = 8;
	const  Int_t m4 = 7;
	const  Int_t m5 = 6;
	const  Int_t m7 = 3;

	double Q21[m1],ge_gm1[m1], ege_gm1[m1], a1_max[m1]=0.,a1_min[m1]=0.;
	double Q22[m2],ge_gm2[m2], ege_gm2[m2], a2_max[m2]=0.,a2_min[m2]=0.;
	double Q23[m3],ge_gm3[m3], un31[m3], un32[m3],ege_gm3[m3], a3_max[m3]=0.,a3_min[m3] =0.;
	double Q24[m4],ge_gm4[m4], un41[m4], un42[m4],ege_gm4[m4], a4_max[m4]=0.,a4_min[m4] =0.;
	double ge_gm5[m5], ege_gm5[m5], a5_max[m5]=0.,a5_min[m5]=0.,Q25[m5] ;
	double eQ21[m1],eQ22[m2],eQ23[m3],eQ24[m4],eQ25[m5];
	double a7_max[m7]=0.,a7_min[m7]=0.;
	double Q27[m7],ge_gm7[m7], ege_gm7[m7],eQ27[m7];
	//double eQ251[m5] = {0.5,0.6,2.7e-3,0.5,0.2,0.16,0.45,0.14,0.22,0.4};
	double dy_y[m5];
	for(int j = 0;j<m1;j++)
	{
		inputfile1>>fixed>>Q21[j]>>ge_gm1[j]>>ege_gm1[j];

		eQ21[j] =0.;
		a1_max[j] = ege_gm1[j];
		a1_min[j] = ege_gm1[j];
		//cout<<"   Q2:   "<<Q21[j]<<"  R:  "<<ge_gm1[j]<<"  e_R:   "<<ege_gm1[j]<<"  max_E:  "<< a1_max[j]<<"  min_E:  "<<a1_min[j]<<endl;
		ge_gm1[j] = ge_gm1[j];

	}

	for(int j = 0;j<m2;j++)

	{
		inputfile2>>fixed>>Q22[j]>>ge_gm2[j]>>ege_gm2[j];
		a2_max[j] = ege_gm2[j];
		a2_min[j] = ege_gm2[j];
		ge_gm2[j] = ge_gm2[j];


		eQ22[j] =0.;
	}

	for(int j = 0;j<m3;j++)

	{
		inputfile3>>fixed>>Q23[j]>>ge_gm3[j]>>un31[j]>>un32[j];

		ege_gm3[j] = 0.5*(un31[j] + un32[j]);
		eQ23[j] =0.;
		a3_min[j] = ege_gm3[j];
		ge_gm3[j] = ge_gm3[j];

	}

	for(int j = 0;j<m4;j++)

	{
		inputfile4>>fixed>>Q24[j]>>ge_gm4[j]>>ege_gm4[j];

		//     cout<<Q24[j]<<"   "<<ge_gm4[j]<<"   "<<ege_gm4[j]<<endl;
		a4_min[j] = ege_gm4[j];
		ge_gm4[j] = ge_gm4[j];
		eQ24[j] =0.;
	}

	for(int j = 0;j<m5;j++)

	{
		inputfile5>>fixed>>Q25[j]>>ge_gm5[j]>>ege_gm5[j];
		a5_min[j] = ege_gm5[j];
		//		cout<<" Q2:  "<<Q25[j]<<"  ge_gm:  "<<ge_gm5[j]<< "  ege_gm:  "<<ege_gm5[j]<<"  a5_max:  "<<a5_max[j]<<"  a5_min:  "<<a5_min[j]<<endl;


		//		eQ25[j] =0.;
	}



	for(int j = 0;j<m7;j++)

	{
		inputfile7>>fixed>>Q27[j]>>ge_gm7[j]>>ege_gm7[j];
		a7_min[j] = ege_gm7[j];
		ge_gm7[j] = ge_gm7[j];


		eQ27[j] =0.;
	}
	inputfile1.close();
	inputfile2.close();
	inputfile3.close();
	inputfile4.close();
	inputfile5.close();
	inputfile7.close();

	TGraphErrors *t1 = new TGraphErrors(m1,Q21,ge_gm1,eQ21,a1_min);
	TGraphErrors *t2 = new TGraphErrors(m2,Q22,ge_gm2,eQ22,a2_min);
	TGraphErrors *t3 = new TGraphErrors(m3,Q23,ge_gm3,eQ23,a3_min);
	TGraphErrors *t4 = new TGraphErrors(m4,Q24,ge_gm4,eQ24,a4_min);
	TGraphErrors *t5 = new TGraphErrors(m5,Q25,ge_gm5,eQ25,a5_min);
	TGraphErrors *t7 = new TGraphErrors(m7,Q27,ge_gm7,eQ27,a7_min);
//gStyle->SetEndErrorSize(20);
	t1->SetLineColor(kBlack);
	t2->SetLineColor(kBlack);
	t3->SetLineColor(kBlue);
	t5->SetLineColor(kRed);
	t4->SetLineColor(kGreen+3);
	t1->SetMarkerColor(kBlack);
	t2->SetMarkerColor(kBlack);
	t3->SetMarkerColor(kBlue);
	t4->SetMarkerColor(kGreen+3);
	t5->SetMarkerColor(kRed);
	t7->SetMarkerColor(kMagenta);

	t1->SetMarkerSize(3);
	t2->SetMarkerSize(2);
	t3->SetMarkerSize(2);
	t4->SetMarkerSize(3);
	t5->SetMarkerSize(2);
	t7->SetMarkerSize(3);

//graph->SetLineWidth(2);
	t1->SetMarkerStyle(27);
	t2->SetMarkerStyle(21);
	t3->SetMarkerStyle(20);
	t4->SetMarkerStyle(33);
	t5->SetMarkerStyle(20);
	t7->SetMarkerStyle(29);
	
	t1->SetLineWidth(2);
	t2->SetLineWidth(2);
	t3->SetLineWidth(2);
	t4->SetLineWidth(2);
	t5->SetLineWidth(2);
	t7->SetLineWidth(2);


	c1->cd(2);
	//gPad->SetiBottomMargin(0.,0.0,1.0,0.6);
	gPad->SetTopMargin(0.);
        //gPad->SetFillColor(0);
	TMultiGraph* mg = new TMultiGraph();
	//mg->SetTitle(";Q^{2} [(GeV/c^{2})];#frac{#tau}{#sigma_{R}} #frac{d#sigma_{R}}{d#Omega};");
	mg->SetTitle(";Q^{2}, (GeV/c)^{2};#mu_{p} #sqrt{#tau #sigma_{L}/#sigma_{T}}");
	//mg->SetTitle(";Q^{2} [(GeV/c^{2})];#tau #mu^{2}_{p}#tau slope_{#sigma_{R}}/intercept_{#sigma_{R}}");


	// auto g_band = new TGraphErrors(mk,a_1,a_2,exl,a_3);
	//
	//
	TGraphErrors* g_band = new TGraphErrors("datafiles/fitplot_Eric.dat", "%lg %lg %lg");
g_band->SetFillColor(12);
	g_band->SetFillStyle(3001);
	mg->Add(g_band,"A3");


	TGraph* g_nband = new TGraph(mk,a_1,a_2);
	g_nband->SetLineStyle(1);
	g_nband->SetLineColor(1);
        g_nband->SetLineWidth(2);
        //g_nband->Draw("");
         
	mg->Add(g_nband,"L");
      
        mg->Add(t1);
	mg->Add(t2);
	mg->Add(t3);
	mg->Add(t4);
	mg->Add(t5);
	mg->Add(t7);



	mg->Draw("APP");
	mg->GetHistogram()->SetMaximum(3.9);
	mg->GetHistogram()->SetMinimum(-1.3);
	mg->GetXaxis()->SetLimits(x_d,x_u);
	mg->GetXaxis()->CenterTitle();
	mg->GetYaxis()->CenterTitle();
        mg->GetYaxis()->SetTitleSize(ax_ti);
        mg->GetYaxis()->SetTitleOffset(ax_off);
        mg->GetYaxis()->SetLabelFont(62);
        mg->GetXaxis()->SetTitleSize(ax_ti);
        mg->GetXaxis()->SetTitleOffset(ax_offx);
        mg->GetXaxis()->SetLabelFont(62);
        mg->GetYaxis()->CenterTitle();
        mg->GetXaxis()->CenterTitle();
        mg->GetXaxis()->SetLabelSize(lsz);
        mg->GetYaxis()->SetLabelSize(lsz);
  mg->GetXaxis()->SetTickLength(0.06);





	TLine * linek = new TLine (x_d,0,x_u,0);
	linek->SetLineStyle(2);
	linek->Draw();
	TLine * line2 = new TLine (x_d,1,x_u,1);
	line2->SetLineStyle(2);
	line2->Draw();
	TLegend *leg = new TLegend(0.15,0.74,0.4,0.95);
	leg->AddEntry(t5,"Table 1","p");
	leg->AddEntry(t1,"Ref. [26]","p");//Christy
	leg->AddEntry(t7,"Ref. [27]","p"); //Qattan

	leg->SetTextSize(0.04);
	leg->SetBorderSize(0);
	leg->Draw();

	TLegend *leg2 = new TLegend(0.3,0.74,0.45,0.95);

	leg2->AddEntry(t2,"Ref. [9]","p"); //Walker
	leg2->AddEntry(t3,"Ref. [24]","p");//NE11
	leg2->AddEntry(t4,"Ref. [17]","p"); //Puckett
	leg2->SetTextSize(0.04);
	leg2->SetBorderSize(0);
	leg2->Draw();

//TPaveText *t11 = new TPaveText(0.15,0.7,0.2,0.83,"NDC");
/*TPaveText *t11 = new TPaveText(0.15,0.7,0.2,0.83,"NDC");
     t11->AddText("b)");
     t11->SetShadowColor(0);
     t11->SetTextSize(0.07);
     t11->SetTextFont(42);
     t11->SetFillColor(0);
     t11->SetLineColor(0);
     t11->Draw();

*/



c1->Update();
gPad->Modified();
	
	c1->SaveAs("paperGMp12/Plots/Fig1.pdf");
	c1->SaveAs("paperGMp12/Plots/Fig1.png");
	c1->SaveAs("plots/Fig1.png");
	c1->SaveAs("plots/Fig1.pdf");
}








