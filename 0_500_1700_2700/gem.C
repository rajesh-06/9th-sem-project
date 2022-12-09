//# include <execution>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include<algorithm>
#include <TApplication.h>
#include <TCanvas.h>
#include <TH1.h>
#include "Garfield/ComponentAnsys123.hh"
#include "Garfield/ViewField.hh"
#include "Garfield/ViewFEMesh.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/Sensor.hh"
#include "Garfield/AvalancheMicroscopic.hh"
#include "Garfield/AvalancheMC.hh"
#include "Garfield/Random.hh"

using namespace Garfield;

int main(int argc, char * argv[]) {

  TApplication app("app", &argc, argv);

  // Setup the gas.
  MediumMagboltz gas("ar", 70., "co2", 30.);
  gas.SetTemperature(293.15);//in K
  gas.SetPressure(760.);//in torr
  gas.Initialise(true);  
  // Set the Penning transfer efficiency.
  constexpr double rPenning = 0.51;
  constexpr double lambdaPenning = 0.;
  gas.EnablePenningTransfer(rPenning, lambdaPenning, "ar");
  // Load the ion mobilities.
  const std::string path = std::getenv("GARFIELD_INSTALL");
  gas.LoadIonMobility(path + "/share/Garfield/Data/IonMobility_Ar+_Ar.txt");

  // Load the field map.
  ComponentAnsys123 fm;
  fm.Initialise("ELIST.lis", "NLIST.lis", "MPLIST.lis", "PRNSOL.lis", "mm");
  fm.EnableMirrorPeriodicityX();
  fm.EnableMirrorPeriodicityY();
  fm.PrintRange();

  // Associate the gas with the corresponding field map material.
  fm.SetGas(&gas); 
  fm.PrintMaterials();
  // fm.Check();

  // Dimensions of the GEM [cm]
  constexpr double pitch = 0.045;

  ViewField fieldView;
  ViewFEMesh meshView;
  constexpr bool plotField = false;
  if (plotField) {
    fieldView.SetComponent(&fm);
    // Set the normal vector of the viewing plane (xz plane).
    fieldView.SetPlane(0, -1, 0, 0, 0, 0);
    // Set the plot limits in the current viewing plane.
    fieldView.SetArea(-0.5 * pitch, -0.25, 0.5 * pitch, 0.5);
    fieldView.SetVoltageRange(0., -2500.);
    TCanvas* cf = new TCanvas("cf", "", 600, 600);
    cf->SetLeftMargin(0.16);
    fieldView.SetCanvas(cf);
    fieldView.PlotContour();

    meshView.SetArea(-0.5 * pitch, -0.25, 0.5 * pitch, 0.5); 
    meshView.SetCanvas(cf);
    meshView.SetComponent(&fm);
    meshView.SetPlane(0, -1, 0, 0, 0, 0);
    meshView.SetFillMesh(true);
    meshView.SetColor(2, kGray);
    meshView.Plot(true);
  }

  // Create the sensor.
  Sensor sensor;
  sensor.AddComponent(&fm);
  sensor.SetArea(-5 * pitch, -5 * pitch, -0.25,
                  5 * pitch,  5 * pitch,  0.5);

  AvalancheMicroscopic aval;
  aval.SetSensor(&sensor);

  AvalancheMC drift;
  drift.SetSensor(&sensor);
  drift.SetDistanceSteps(2.e-4);

  ViewDrift driftView;
  constexpr bool plotDrift = false;//To plot the drift lines
  if (plotDrift) {
    aval.EnablePlotting(&driftView);
    drift.EnablePlotting(&driftView);
  }

  constexpr unsigned int nEvents = 1000;
  //std::vector<int> indexes
  std::vector<int> gain_vec;
  TCanvas C1;
  
  for (unsigned int i = 0; i < nEvents; ++i) { 
    std::cout << i+1 << "/" << nEvents << "\n";
    // Randomize the initial position. 
    const double x0 = -0.5 * pitch + RndmUniform() * pitch;
    const double y0 = -0.5 * pitch + RndmUniform() * pitch;
    const double z0 = 0.48; 
    const double t0 = 0.;
    const double e0 = 2;
    aval.AvalancheElectron(x0, y0, z0, t0, e0, 0., 0., 0.);
    int ne = 0, ni = 0;
    aval.GetAvalancheSize(ne, ni);

    const unsigned int gain = aval.GetNumberOfElectronEndpoints();
    if (gain > 1)    gain_vec.push_back(gain);//->Fill(gain);
    // std::cout<<"number of electron endpoints "<<gain<<std::endl;
    double xe1, ye1, ze1, te1, e1;
    double xe2, ye2, ze2, te2, e2;
    double xi1, yi1, zi1, ti1;
    double xi2, yi2, zi2, ti2;
    int status;
    for (unsigned int j = 0; j < gain; ++j) {
      aval.GetElectronEndpoint(j, xe1, ye1, ze1, te1, e1, 
                                  xe2, ye2, ze2, te2, e2, status);
      //drift.DriftIon(xe1, ye1, ze1, te1);
      //drift.GetIonEndpoint(0, xi1, yi1, zi1, ti1,xi2, yi2, zi2, ti2, status);
    }
  }
  int max_gain = *std::max_element(gain_vec.begin(), gain_vec.end());
  printf("maxgain=%d",max_gain);
  TH1I *hist = new TH1I("Gain","Gain",40,0,max_gain+1);
  for (int gn:gain_vec) hist->Fill(gn); 
  hist->Draw();
  if (plotDrift) {
    TCanvas* cd = new TCanvas();
    constexpr bool plotMesh = true;
    if (plotMesh) {
      meshView.SetCanvas(cd);
      meshView.SetComponent(&fm);
      constexpr bool twod = true;
      // x-z projection.
      meshView.SetPlane(0, -1, 0, 0, 0, 0);
      if (twod) {
        meshView.SetArea(-2 * pitch, -0.25, 2 * pitch, 0.5);
      } else {
        meshView.SetArea(-0.5 * pitch, -0.5 * pitch, -0.25, 0.5 * pitch, 0.5 * pitch, 0.5);
      }
      meshView.SetFillMesh(true);
      meshView.SetColor(0, kGray);
      // Set the color of the kapton.
      meshView.SetColor(2, kYellow + 3);
      meshView.EnableAxes();
      meshView.SetViewDrift(&driftView);
      meshView.Plot(twod);
    } else {
      driftView.SetPlane(0, -1, 0, 0, 0, 0);
      driftView.SetArea(-2 * pitch, -0.25, 2 * pitch, 0.5);
      driftView.SetCanvas(cd);
      constexpr bool twod = true;
      driftView.Plot(twod);
    }
  }

  app.Run();
}
