import ROOT
import os, sys
import ctypes

path = os.getenv('GARFIELD_INSTALL')
if sys.platform == 'darwin':
  ROOT.gSystem.Load(path + '/lib/libmagboltz.dylib')
  ROOT.gSystem.Load(path + '/lib/libGarfield.dylib')
else:
  ROOT.gSystem.Load(path + '/lib/libmagboltz.so')
  ROOT.gSystem.Load(path + '/lib/libGarfield.so')

# Load the field map.
fm = ROOT.Garfield.ComponentAnsys123()
fm.Initialise("ELIST.lis", "NLIST.lis", "MPLIST.lis", "PRNSOL.lis", "mm")
fm.EnableMirrorPeriodicityX()
fm.EnableMirrorPeriodicityY()
fm.PrintRange()

# Dimensions of the GEM [cm]
pitch = 0.014

fieldView = ROOT.Garfield.ViewField()
cF = ROOT.TCanvas('cF', '', 600, 600)
fieldView.SetCanvas(cF)
fieldView.SetComponent(fm)
# Set the normal vector of the viewing plane (xz plane).
fieldView.SetPlaneXZ()
# Set the plot limits in the current viewing plane.
fieldView.SetArea(-0.5 * pitch, -0.02, 0.5 * pitch, 0.02)
fieldView.SetVoltageRange(-160., 160.)
fieldView.GetCanvas().SetLeftMargin(0.16)
fieldView.PlotContour();

# Setup the gas.
gas = ROOT.Garfield.MediumMagboltz("ar", 80., "co2", 20.)
gas.SetTemperature(293.15)
gas.SetPressure(760.)
gas.Initialise(True)

# Set the Penning transfer efficiency.
rPenning = 0.51
gas.EnablePenningTransfer(rPenning, 0., "ar")
# Load the ion mobilities.
gas.LoadIonMobility(path + '/share/Garfield/Data/IonMobility_Ar+_Ar.txt')
 
fm.SetGas(gas)
fm.PrintMaterials()

# Assemble the sensor.
sensor = ROOT.Garfield.Sensor()
sensor.AddComponent(fm)
sensor.SetArea(-5 * pitch, -5 * pitch, -0.01, 5 * pitch,  5 * pitch, 0.025)

aval = ROOT.Garfield.AvalancheMicroscopic()
aval.SetSensor(sensor)

drift = ROOT.Garfield.AvalancheMC()
drift.SetSensor(sensor)
drift.SetDistanceSteps(2.e-4)

driftView = ROOT.Garfield.ViewDrift()
plotDrift = True
if plotDrift:
  aval.EnablePlotting(driftView)
  drift.EnablePlotting(driftView)

nEvents = 10
for i in range(nEvents):
  # print i, '/', nEvents
  # Randomize the initial position. 
  x0 = -0.5 * pitch + ROOT.Garfield.RndmUniform() * pitch
  y0 = -0.5 * pitch + ROOT.Garfield.RndmUniform() * pitch
  z0 = 0.02
  t0 = 0.
  e0 = 0.1
  aval.AvalancheElectron(x0, y0, z0, t0, e0, 0., 0., 0.)
  np = aval.GetNumberOfElectronEndpoints()
  xe1 = ctypes.c_double(0.)
  ye1 = ctypes.c_double(0.)
  ze1 = ctypes.c_double(0.)
  te1 = ctypes.c_double(0.)
  e1 = ctypes.c_double(0.)
  xe2 = ctypes.c_double(0.)
  ye2 = ctypes.c_double(0.)
  ze2 = ctypes.c_double(0.)
  te2 = ctypes.c_double(0.)
  e2 = ctypes.c_double(0.)
  status = ctypes.c_int(0)
  for j in range(np):
    aval.GetElectronEndpoint(j, xe1, ye1, ze1, te1, e1, xe2, ye2, ze2, te2, e2, status)
    drift.DriftIon(xe1.value, ye1.value, ze1.value, te1.value)

cD = ROOT.TCanvas('cD', '', 600, 600)
meshView = ROOT.Garfield.ViewFEMesh()
plotMesh = True 
if plotDrift:
  if plotMesh:
    meshView.SetArea(-2 * pitch, -0.02, 2 * pitch, 0.02)
    meshView.SetCanvas(cD)
    meshView.SetComponent(fm)
    # x-z projection.
    meshView.SetPlane(0, -1, 0, 0, 0, 0)
    meshView.SetFillMesh(True)
    #  Set the color of the kapton.
    meshView.SetColor(2, ROOT.kYellow + 3)
    meshView.EnableAxes()
    meshView.SetViewDrift(driftView)
    meshView.Plot()
  else:
    driftView.SetCanvas(cD)
    driftView.SetPlane(0, -1, 0, 0, 0, 0)
    driftView.SetArea(-2 * pitch, -0.02, 2 * pitch, 0.02)
    driftView.Plot(True)
