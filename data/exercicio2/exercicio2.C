/*
 Autor: Mariana Soeiro
 About: Exercicio 2 - Lista 3 (ROOT)
 
           - Open data on graphdata.txt [x]
           - Plot his points using the class TGraph [x]
           - Use a black box marker poit [x]
           - Use TGraphPainter to plot a line connecting the points [x]
           - Make a TGraphError and display it using tha attached dataset graphdata_error.txt for x and y [x]
 
 */



int exercicio2(){
    
    // Add Style
    gStyle->SetOptFit(1111);
    
    //Open Canvas
    TCanvas *c = new TCanvas("c1","multigraph",700,500);
    c->SetGrid();
    
    
    //Open data on graphdata.txt
    //TGraph *graph = new TGraph("./graphdata.txt","%lg %lg");
    TGraphErrors *graph = new TGraphErrors("./graphdata.txt","%lg %lg");
    //auto graph = new TGraphErrors("./graphdata_error.txt","%lg %lg %lg %lg %lg");
    
    const Int_t n = 10;
    Double_t x[n]  = {-0.22, 0.05, 0.25, 0.35, 0.5, 0.61,0.7,0.85,0.89,0.95};
    Double_t y[n]  = {1,2.9,5.6,7.4,9,9.6,8.7,6.3,4.5,1};
    Double_t ex[n] = {.05,.1,.07,.07,.04,.05,.06,.07,.08,.05};
    Double_t ey[n] = {.8,.7,.6,.5,.4,.4,.5,.6,.7,.8};
    auto gr = new TGraphErrors(n,x,y,ex,ey);
    
    //auto gr = new TGraphErrors(n,x,y,ex,ey);
    graph->SetFillColor(0);
    graph->SetTitle("");
    
    

    //Line points
    graph->SetMarkerStyle(21);
    graph->Draw("ALP");
    gr->Draw("Same");
    c->Print("output_exercicio2.pdf");
    
    return 0;
    
}

