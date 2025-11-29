//----------------------------------------------------------------
// mucos.C
//
// This root macro can be used to read a root file generated
// by Geant4 program. Root files contain position and momentum
// data of a charged particle (p or pi) after passing
// through a copper block. Using these data, one can evaluate
// rms value of the Multiple Coulomb Scattering Angle and compare
// it with the theoretical expectation.
//
// By default we assume that
//  - charged particle name can be "proton" or "pion"
//  - initial particle momentum is p = 600 MeV
//  - thickness of copper block is t = 5 mm
//
// Feb 2025
//----------------------------------------------------------------
void mucos(){

   // reset root and do not print Info messages
   gROOT->Reset();
   gErrorIgnoreLevel = kWarning;

   // input values particel can be proton or pion.
   string particle = "pion";
   double mass[2] = {938.3, 139.6}; // MeV

   // Rest of the program is used to read root (data) files and
   // to evavulate outgoing angle of the particle from copper
   // due to Multiple Coulomb Scattering.
   int parId = 0;
   TFile *file;
   if(particle == "proton"){
	   file = new TFile("../build/output0.root");
	   parId  = 0;
   }
   else{
	   file = new TFile("../build/output1.root");
	   parId  = 1;
   }

   // get the tree name in the root file
   TTree *tree = (TTree*) file->Get("Hits");

   // number of data (lines) in the root file
   int nData = (int) tree->GetEntries();

   // set branches
   double px, py, pz, pmag, x, y, z;
   tree->SetBranchAddress("px",&px);
   tree->SetBranchAddress("py",&py);
   tree->SetBranchAddress("pz",&pz);
   tree->SetBranchAddress("pmag",&pmag);
   tree->SetBranchAddress("x",&x);
   tree->SetBranchAddress("y",&y);
   tree->SetBranchAddress("z",&z);

   // book histpgram(s)
   TH1F *mcsAngle = new TH1F ("mcsAngle",";Angle [deg];Entries",100, 0, 14);

   // fill and draw tge histogram
   const double deg = 180.0 / 3.1415926;
   for(int i=0; i<nData; i++)
   {
      tree->GetEntry(i);
      double theta = fabs(atan(py/pz))*deg; // plane angle
      mcsAngle->Fill(theta);
   }
   mcsAngle->Draw();

   // set particle data
   double p    = 600.0;         // momentum, MeV
   double m    = mass[parId];   // mass, MeV
   double E    = sqrt(p*p+m*m); // total energy, MeV
   double beta = p/E;           // speed/c
   double q    = 1.0;           // charge/e

   // set material data
   double t   = 0.5;   // copper thickness, cm
   double rho = 8.93;  // copper density, g/cm3
   double Z   = 29;    // copper Z
   double A   = 64;    // copper A
   double X0  = 716.4*A/(Z*(Z+1)*log(287.0/sqrt(Z))) / rho;

   // rms values of theoretical multiple scattering (plane) angle
   double theta_rms  = 13.6 * sqrt(t/X0) * q / (beta * p) * deg;
          theta_rms *= 1.0 + 0.038*log(t*q*q/X0/beta/beta);

   // evaluate multiple scattering (plane) angle
   double histo_rms = mcsAngle->GetRMS();

   // results to the user screen
   cout << fixed << setprecision(3);
   cout << "Multiple scattering angle for " << particle << endl;
   cout << "histo_rms = " << histo_rms << " deg" << endl;
   cout << "theta_rms = " << theta_rms << " deg" << endl;
   cout << "ratio     = " << histo_rms / theta_rms << " deg" << endl;
}
// EOF
