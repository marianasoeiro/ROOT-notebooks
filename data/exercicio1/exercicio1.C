/*
Autor: Mariana Soeiro
About: Exercicio 1 - Lista 3 (ROOT)

          - Create a function [x]
          - Set color blue  [x]
          - Draw a function [x]
          - Function value for x = 1 [x]
          - Function derivative for x = 1 [x]
          - Integral of the function between 0 and 3 [x]

*/


// Declare function


void exercicio1()
    {
       // Function
        //TF1 * f1 = new TF1("f1","[0]sin([1]*x)/x",0,10);
        TF1 * f1 = new TF1("f1","[0]*sin([1]*x)/x",0.,10.);
        //Seting Parameters
       f1->SetParameters(2,1);
        // Line Blue
       f1->SetLineColor(4);
        // Parameters Name
       f1->SetParNames("constant","coefficient");
        
Double_t f_eval = f1->Eval(1);
Double_t f_dev = f1->Derivative(1);
Double_t f_int = f1->Integral(0,3);


              
TCanvas *c = new TCanvas("c1","function",700,500);
        f1->Draw();
        c->SetGrid();
        
        std::cout << "f_dev = " << f_dev << ",";
        std::cout << "f_int = " << f_int << " e ";
        std::cout << "f_eval = " << f_eval << " .";
        
        
    return 0;
    delete c;
        
    }
