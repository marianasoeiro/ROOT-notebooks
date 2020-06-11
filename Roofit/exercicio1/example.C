/*
 
Autor: Mariana Soeiro
About: Exercicio 1 - Lista 5 (Roofit)

 */
{
   using namespace RooFit;

   RooWorkspace w("myWorkspace", true);
   w.factory("Gaussian::gauss(mes[5.20,5.30],mean[5.28,5.2,5.3],width[0.0027,0.001,1])");
   w.factory("ArgusBG::argus(mes,5.291,argpar[-20,-100,-1])");
   w.factory("SUM::sum(nsig[200,0,10000]*gauss,nbkg[800,0,10000]*argus)");

   // Retrieve pointers to variables and pdfs for later use
   auto sum = w.pdf("sum"); // Returns as RooAbsPdf*
   auto mes = w.var("mes"); // Returns as RooRealVar*

   // --- Generate a toyMC sample from composite PDF ---
   RooDataSet *data = sum->generate(*mes, 2000);

   // --- Perform extended ML fit of composite PDF to toy data ---
   sum->fitTo(*data);

   // --- Plot toy data and composite PDF overlaid ---
   auto mesframe = mes->frame();
   data->plotOn(mesframe);
   sum->plotOn(mesframe);
   sum->plotOn(mesframe, Components(*w.pdf("argus")), LineStyle(kDashed));

   mesframe->Draw();
}
