void convert(const char* filename)
{
    const Double_t mup = 2.7928;  // magnetic momentum of proton 
    const Double_t alpha = 1/137.036;                                       
    const Double_t hbarc2 = 0.389e3; // (hbar*c)^2 in GeV^2*ub
    const Double_t mp = 0.938272;

    if (gSystem->AccessPathName(filename)) {
        cout << "The file " << filename << " does not exist!" << endl;
        return;
    }

    ifstream* infile = new ifstream;
    infile->open(filename);

    if (!infile->is_open()) {
        cout << "Can not open file " << filename << endl;
        delete infile;
        return;
    }

    TString outfilename = filename;
    UInt_t ind = outfilename.Last('.');
    TString suffix(outfilename(ind+1, outfilename.Length()-ind-1));
    outfilename.Remove(ind);
    outfilename += "_new.";
    outfilename += suffix;
    ofstream* outfile = new ofstream;

    outfile->open(outfilename);

    *outfile << scientific;

    Double_t QQ, E0, Ep, theta, eps, sig, stats, sys, norm, dsig; // stats is the absolute statistical uncertainty if dsig > 0
    // Otherwise it is relative statistical uncertainty


    while (*infile >> QQ >> E0 >> Ep >> theta >> eps >> sig >> dsig) {

      //  Double_t dsig = TMath::Sqrt(stats*stats + sys*sys);

        Double_t angle = theta*TMath::DegToRad();
        Double_t s2 = pow(sin(angle/2.),2);
        Double_t c2 = pow(cos(angle/2.),2);
        Double_t t2 = pow(tan(angle/2.),2);
        Double_t ef = E0/(1.+2*E0/mp*s2);
        Double_t Q2 = 2*E0*ef*(1-TMath::Cos(angle));
        Double_t tau = Q2/(4.*mp*mp);
        Double_t epsilon = 1./(1+2*(1+tau)*t2);
        Double_t mott = pow(alpha,2)/(4.*E0*E0)*c2/s2/s2*hbarc2;
        Double_t recoil = ef/E0;
        //mott *= recoil;
        Double_t GD = TMath::Power(1+Q2/0.71,-2);

        Double_t Ge_par = (1. -1.651*tau +1.287*pow(tau,2) -0.185*pow(tau,3))/(1. + 9.531*tau + 0.591*pow(tau,2)  + 4.994*pow(tau,5));
        Double_t Gm_par = mup*(1. -2.151*tau +4.261*pow(tau,2)+ 0.159*pow(tau,3))/(1. + 8.647*tau + 0.001*pow(tau,2)  + 5.245*pow(tau,3)  + 82.817*pow(tau,4) + 14.191*pow(tau,5));

        //Double_t Ge_par = (1. + 3.439*tau - 1.602*pow(tau,2)+ 0.068*pow(tau,3))/(1. + 15.055*tau + 48.061*pow(tau,2)  + 99.304*pow(tau,3) + 0.012*pow(tau,4) + 8.650*pow(tau,5));  //PT
        //Double_t Gm_par = mup*(1. - 1.465*tau +1.260*pow(tau,2)+ 0.262*pow(tau,3))/(1. + 9.627*tau + 11.179*pow(tau,4)  + 13.245*pow(tau,5));


        Double_t Ge_Gm = Ge_par/Gm_par;
        Double_t sigr = epsilon*(1. + 1./tau)*sig/mott/(ef/E0);
        Double_t Gm = sqrt(sigr/(1. + epsilon/tau*Ge_Gm*Ge_Gm));
        Double_t rf =  Gm/(mup*GD);
        Double_t d_rf = Gm*(dsig)/2./(mup*GD);

        *outfile << Q2 << "\t" << rf << "\t" << d_rf << "\t" << endl;

    }

    infile->close();
    delete infile;
    outfile->close();
    delete outfile;
}
