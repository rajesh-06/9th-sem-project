{
{
   auto gr = new TGraph();
   gr->SetTitle("Gain;$\Delta_v$;gain");
   for (int i=0; i<20; i++) gr->AddPoint(i*0.1, 10*sin(i*0.1+0.2));
   gr->Draw();
   gr->GetXaxis()->CenterTitle()
}
   
}