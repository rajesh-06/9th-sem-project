{
   Int_t n = 4;
//    Double_t x[3], y[3];
//    for (Int_t i=0;i<n;i++) {
//       x[i] = i*0.1;
//       y[i] = 10*sin(x[i]+0.2);
//    }
   Double_t x[4] = {950,1000,1050,1100};
   Double_t y[4] = {36.4,70.77,125,238};
   // create graph
   TGraph *gr  = new TGraph(n,x,y);
   TCanvas *c1 = new TCanvas();
	gr->SetTitle(";#DeltaV_{bias} (V);Gain");
   // draw the graph with axis, continuous line, and put
   // a * at each point
   c1->SetLogy();
   c1->SetGridx();
   c1->SetGridy();
   TF1 *fit = new TF1("fit", "expo",940,1110);

   gr->Fit("fit");
   gr->Draw("Ap*");
   TLegend *leg = new TLegend(0.7,0.7,0.9,0.9);
   leg->AddEntry(gr, "Gain", "p");
   leg->AddEntry(fit, "Fit","l");
   leg->Draw();
   //gr->Legend(true);
}
