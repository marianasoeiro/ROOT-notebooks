#Import the ROOT libraries
import ROOT

#Import Data of DataSet_lowstat.root
fInput = ROOT.TFile("DataSet_lowstat.root")
dataset = fInput.Get("data")

#--------------------------------------------------------------------------------------
#-------------------------------------Signal-------------------------------------------
#--------------------------------------------------------------------------------------
#JPsi
massJpsi = ROOT.RooRealVar("mass","Jpsi Invariant Mass",2.,6.,"GeV")

# Crystal Ball Fit Parameters
meanJpsi = ROOT.RooRealVar("meanJpsi","The mean of the Jpsi Crystal Ball",3.1,2.8,3.9)
sigmaJpsi = ROOT.RooRealVar("sigmaJpsi","The width of the Jpsi Crystal Ball",0.3,0.0001,1.)
alphaJpsi = ROOT.RooRealVar("alphaJpsi","The alpha of the Jpsi Crystal Ball",1.5,-5.,5.)
nJpsi = ROOT.RooRealVar("nJpsi","The alpha of the Jpsi Crystal Ball",1.5,0.5,5.)


CBJpsi = ROOT.RooCBShape("CBJpsi","The Jpsi with Crystall Ball",massJpsi,meanJpsi,sigmaJpsi,alphaJpsi,nJpsi)

#Define the yields
NJpsi = ROOT.RooRealVar("NJpsi","The Jpsi signal events",1500.,0.1,10000.)



#--------------------------------------------------------------------------------------
#--------------------------------------Bkg---------------------------------------------
#--------------------------------------------------------------------------------------

# Polynomail Fit Parameters

x = ROOT.RooRealVar("x","The a1 of background",-0.7,-2.,2.)
a0 = ROOT.RooRealVar("a0","The a0 of background",0.3,-2.,2.)
a1 = ROOT.RooRealVar("a1","The a1 of background",-0.03,-2.,2.)


bkgPDF = ROOT.RooChebychev("bkgPDF","The background PDF",massJpsi,ROOT.RooArgList(x,a0,a1))

meanpsi2S = ROOT.RooRealVar("meanpsi2S","The mean of the psi(2S) Crystal Ball",3.7,3.65,3.75)

CBpsi2S = ROOT.RooCBShape("CBpsi2S","The psi(2S) Crystal Ball",massJpsi,meanpsi2S,sigmaJpsi,alphaJpsi,nJpsi)

#Define the yields
Nbkg = ROOT.RooRealVar("Nbkg","The bkg events",5000.,0.1,50000.)

# Define number of events produced to 2S using section*efficiency*luminosity (in pb)

#Lowstat sample has 0.64 pb-1

eff_psi = ROOT.RooRealVar("eff_psi","The psi efficiency",0.75,0.00001,1.)
lumi_psi  = ROOT.RooRealVar("lumi_psi","The CMS luminosity",0.64,0.00001,50.,"pb-1")
cross_psi = ROOT.RooRealVar("cross_psi","The psi xsec",3.,0.,40.,"pb")

Npsi = ROOT.RooFormulaVar("Npsi","@0*@1*@2",ROOT.RooArgList(eff_psi,lumi_psi,cross_psi))

eff_psi.setConstant(1)
lumi_psi.setConstant(1)

#--------------------------------------------------------------------------------------

#Total PDF
totalPDF = ROOT.RooAddPdf("totalPDF","The total PDF",ROOT.RooArgList(CBJpsi,CBpsi2S,bkgPDF),ROOT.RooArgList(NJpsi,Npsi,Nbkg))

#Do the actual fit
totalPDF.fitTo(dataset, ROOT.RooFit.Extended(1))



#--------------------------------------------------------------------------------------
#Canvas 1

#Now plot the data
xframe = massJpsi.frame()
dataset.plotOn(xframe)

#Draw the results
c1 = ROOT.TCanvas()
xframe.Draw()
c1.SaveAs("exercicio2.png")

#Save
w = ROOT.RooWorkspace("w")

#Writing Workspace
fOutput = ROOT.TFile("Workspace_Jpsifit.root","RECREATE")
w.Write()
fOutput.Write()
fOutput.Close()

#--------------------------------------------------------------------------------------
# Canvas 2

#Now plot the data
xframe = massJpsi.frame()
dataset.plotOn(xframe)
totalPDF.plotOn(xframe)

# Background component
totalPDF.plotOn(xframe, ROOT.RooFit.Components("bkgPDF"), ROOT.RooFit.LineStyle(ROOT.kDashed), ROOT.RooFit.LineColor(ROOT.kRed))

#Draw the results
c2 = ROOT.TCanvas()
xframe.Draw()
c2.SaveAs("exercicio2_2.png")

#Now save the data and the PDF into a Workspace, for later use for statistical analysis
w2 = ROOT.RooWorkspace("w")
#getattr(w2,'import')(dataset)
getattr(w2,'import')(totalPDF)

#Writing Workspace
fOutput = ROOT.TFile("Workspace_Jpsifit.root","RECREATE")
w2.Write()
fOutput.Write()
fOutput.Close()
