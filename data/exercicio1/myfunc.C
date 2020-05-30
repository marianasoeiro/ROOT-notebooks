/*
 Autor: Mariana Soeiro
 About: Create a function
 
 */

// Declare function


Double_t myfunction(Double_t *x, Double_t *par)
{
   Float_t xx =x[0];
   Double_t f = par[0]*sin(par[1]*xx)/xx; // no absolut values
   return f;
}

void myfunc()
    {
       // Function
        
       TF1 *f1 = new TF1("myfunc",myfunction,-4,10,4);
        //Seting Parameters
       f1->SetParameters(2,1);
        // Line Blue
       f1->SetLineColor(4);
        // Parameters Name
       f1->SetParNames("constant","coefficient");
        
TF1 *f2 = new TF1("myfunc",myfunction,-4,10,4);
//Double_t f_int = f2->Integral(0,3);
Double_t f_dev = f2->Derivative(1);
Double_t f_eval = f2->eval(1);

              
TCanvas *c = new TCanvas("c1","function",700,500);
        f1->Draw();
        c->SetGrid();
        
        std::cout << f_int;
        
        
    return 0;
    delete c;
        
    }
