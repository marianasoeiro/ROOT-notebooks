/*
 
Autor: Mariana Soeiro
About: Exercicio 1 - Lista 5 (Roofit)
 
       -    Create a Gaus p.d.f [x]
       -    Generate some toy data and fit it[x];

 */
{
    
    RooWorkspace w("w");
    // define a Exponetial pdf
    w.factory("Gaussian:g(x[-5,5],mu[0,-10,10],sigma[1,0,1000])");
    // create extend pdf with number of events
    w.factory("ExtendPdf:model(g,nevt[100,0,100000])");
    
    

    RooAbsPdf * pdf = w.pdf("model");   // access object from workspace
    RooRealVar * x = w.var("x");   // access object from workspace
    RooDataSet * data = nullptr;
    data = pdf->generate(*x, 1000);
    
    res = pdf->fitTo(*data, RooFit::Minimizer("Minuit2","Migrad"), RooFit::Save(1) );
   w.writeToFile("GaussianModel.root", true);
    
    
    //Data Visualization (Plot PDF)
    RooPlot * pl = nullptr;
    pl = x->frame();
    pdf->plotOn(pl);
    data->plotOn(pl);
    pl->Draw(); c1->Draw();
    
    pdf->plotOn(pl);
    pdf->paramOn(pl);
    pl->Draw();
    c1->Draw();
    
    
    
    // Print Information
    pdf->Print("t");
    res->Print()

}
