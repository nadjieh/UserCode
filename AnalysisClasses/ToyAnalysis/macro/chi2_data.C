{
//=========Macro generated from canvas: Canvas_1/Canvas_1
//=========  (Wed Apr 18 15:53:57 2012) by ROOT version5.32/00
   TCanvas *Canvas_1 = new TCanvas("Canvas_1", "Canvas_1",67,53,635,638);
   Canvas_1->Range(0.2528587,984.0807,0.3488297,1038.946);
   Canvas_1->SetFillColor(0);
   Canvas_1->SetBorderMode(0);
   Canvas_1->SetBorderSize(2);
   Canvas_1->SetLeftMargin(0.1299525);
   Canvas_1->SetRightMargin(0.06973059);
   Canvas_1->SetFrameBorderMode(0);
   Canvas_1->SetFrameBorderMode(0);
   
   TGraph *graph = new TGraph(7);
   graph->SetName("chiSquared_helicity");
   graph->SetTitle("");
   graph->SetFillColor(1);
   graph->SetMarkerStyle(3);
   graph->SetPoint(0,0.3036650526,1000.864404);
   graph->SetPoint(1,0.2716735439,996.80753);
   graph->SetPoint(2,0.2843598318,995.300691);
   graph->SetPoint(3,0.2971840142,997.966637);
   graph->SetPoint(4,0.3100081965,1004.805368);
   graph->SetPoint(5,0.3228323789,1015.585063);
   graph->SetPoint(6,0.3356565612,1030.421632);
   
   TH1F *Graph_chiSquared_helicity1 = new TH1F("Graph_chiSquared_helicity1","",100,0.2653304,0.3421376);
   Graph_chiSquared_helicity1->SetMinimum(989.737);
   Graph_chiSquared_helicity1->SetMaximum(1033.667);
   Graph_chiSquared_helicity1->SetDirectory(0);
   Graph_chiSquared_helicity1->SetStats(0);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   Graph_chiSquared_helicity1->SetLineColor(ci);
   Graph_chiSquared_helicity1->GetXaxis()->SetTitle("F_{L}");
   Graph_chiSquared_helicity1->GetXaxis()->SetLabelFont(42);
   Graph_chiSquared_helicity1->GetXaxis()->SetLabelSize(0.035);
   Graph_chiSquared_helicity1->GetXaxis()->SetTitleSize(0.05);
   Graph_chiSquared_helicity1->GetXaxis()->SetTitleOffset(0.89);
   Graph_chiSquared_helicity1->GetXaxis()->SetTitleFont(42);
   Graph_chiSquared_helicity1->GetYaxis()->SetTitle("#Delta#chi^{2}");
   Graph_chiSquared_helicity1->GetYaxis()->SetLabelFont(42);
   Graph_chiSquared_helicity1->GetYaxis()->SetLabelSize(0.035);
   Graph_chiSquared_helicity1->GetYaxis()->SetTitleSize(0.05);
   Graph_chiSquared_helicity1->GetYaxis()->SetTitleOffset(1.31);
   Graph_chiSquared_helicity1->GetYaxis()->SetTitleFont(42);
   Graph_chiSquared_helicity1->GetZaxis()->SetLabelFont(42);
   Graph_chiSquared_helicity1->GetZaxis()->SetLabelSize(0.035);
   Graph_chiSquared_helicity1->GetZaxis()->SetTitleSize(0.035);
   Graph_chiSquared_helicity1->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_chiSquared_helicity1);
   
   
   TF1 *PrevFitTMP = new TF1("PrevFitTMP","pol2",0.2653304,0.3421376);
   PrevFitTMP->SetFillColor(19);
   PrevFitTMP->SetFillStyle(0);
   PrevFitTMP->SetLineColor(2);
   PrevFitTMP->SetLineWidth(2);
   PrevFitTMP->SetChisquare(0.002799312);
   PrevFitTMP->SetNDF(4);
   PrevFitTMP->GetXaxis()->SetLabelFont(42);
   PrevFitTMP->GetXaxis()->SetLabelSize(0.035);
   PrevFitTMP->GetXaxis()->SetTitleSize(0.035);
   PrevFitTMP->GetXaxis()->SetTitleFont(42);
   PrevFitTMP->GetYaxis()->SetLabelFont(42);
   PrevFitTMP->GetYaxis()->SetLabelSize(0.035);
   PrevFitTMP->GetYaxis()->SetTitleSize(0.035);
   PrevFitTMP->GetYaxis()->SetTitleFont(42);
   PrevFitTMP->SetParameter(0,1985.258);
   PrevFitTMP->SetParError(0,2.224916);
   PrevFitTMP->SetParLimits(0,0,0);
   PrevFitTMP->SetParameter(1,-7008.471);
   PrevFitTMP->SetParError(1,14.69104);
   PrevFitTMP->SetParLimits(1,0,0);
   PrevFitTMP->SetParameter(2,12403.53);
   PrevFitTMP->SetParError(2,24.17118);
   PrevFitTMP->SetParLimits(2,0,0);
   graph->GetListOfFunctions()->Add(PrevFitTMP);
   graph->Draw("ap");
   TLatex *   tex = new TLatex(0.2748451,1028.219,"F_{L} = 0.282 #pm 0.001");
   tex->SetLineWidth(2);
   tex->Draw();
   Canvas_1->Modified();
   Canvas_1->cd();
   Canvas_1->SetSelected(Canvas_1);
   Canvas_1->ToggleToolBar();
}
