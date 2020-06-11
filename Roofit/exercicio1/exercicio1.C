/*
 
Autor: Mariana Soeiro
About: Exercicio 1 - Lista 5 (Roofit)
 
       -    Create a Gaussian p.d.f [x]
       -    Generate some toy data and fit it[x];

 */
{
    
    RooWorkspace w("w");
    // define a Gaussian pdf
    w.factory("Gaussian:g(x[-5,5],mu[0,-10,10],sigma[1,0,1000])");
    // create extend pdf with number of events
    w.factory("ExtendPdf:model(g,nevt[100,0,100000])");

    RooAbsPdf * pdf = w.pdf("model");   // access object from workspace
    RooRealVar * x = w.var("x");   // access object from workspace
    RooDataSet * data = nullptr;
    
    RooPlot * pl = nullptr;
    data = pdf->generate(*x, 1000);



    pl = x->frame();
    pdf->plotOn(pl);
    pl->Draw(); c1->Draw();
    
    data->plotOn(pl);
    pl->Draw(); c1->Draw();
    
    
    // Print Information
    pdf->Print("t")

}
