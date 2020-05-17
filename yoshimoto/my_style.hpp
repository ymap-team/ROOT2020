#ifndef YSTYLE_HPP
#define YSTYLE_HPP

#define SHOW_STSTS

#pragma warning(disable:4996)

#include <TStyle.h>
#include <TROOT.h>
#include <TColor.h>

#include <sstream>
#include <iostream>

TStyle* MyStyle();

void SetMyStyle()
{
    std::cout << "\nApplying MyStyle settings...\n" << std::endl;
    TStyle* Style = MyStyle();

    gROOT->SetStyle("Plain");
    gROOT->SetStyle("MyStyle");
    gROOT->ForceStyle();
}

TStyle* MyStyle()
{
    TStyle *MyStyle = new TStyle("MyStyle", "Based on Atlas style");

    //http://kkuatx.hep.kyokyo-u.ac.jp/~ryuichi/doxy-tbmon2/html/_atlas_style_8cc_source.html

    // use plain black on white colors
    int icol = 0; // WHITE
    short scol = 0;
    MyStyle->SetFrameBorderMode(icol);
    MyStyle->SetFrameFillColor(scol);
    MyStyle->SetCanvasBorderMode(icol);
    MyStyle->SetCanvasColor(scol);
    MyStyle->SetPadBorderMode(icol);
    MyStyle->SetPadColor(scol);
    MyStyle->SetStatColor(scol);
    //MyStyle->SetFillColor(icol); // don't use: white fill color floa *all* objects

    MyStyle->SetStatBorderSize(1);
    MyStyle->SetTitleBorderSize(1);

    // set the paper
    //MyStyle->SetPaperSize(20,26);

    // set the margin sizes 0.12 to 0.15
    float margin = 0.12;
    MyStyle->SetPadTopMargin(margin);
    MyStyle->SetPadRightMargin(margin + 0.03f);
    MyStyle->SetPadBottomMargin(margin);
    MyStyle->SetPadLeftMargin(margin);

    // set title offsets (for axis label)
    MyStyle->SetTitleXOffset(1.3f);
    MyStyle->SetTitleYOffset(1.3f);

    // use large fonts
    short font = 42; // Helvetica
    float tsize = 0.04f;
    MyStyle->SetTextFont(font);

    MyStyle->SetTextSize(tsize);
    MyStyle->SetLabelFont(font, "x");
    MyStyle->SetTitleFont(font, "x");
    MyStyle->SetLabelFont(font, "y");
    MyStyle->SetTitleFont(font, "y");
    MyStyle->SetLabelFont(font, "z");
    MyStyle->SetTitleFont(font, "z");

    MyStyle->SetLabelSize(tsize, "x");
    MyStyle->SetTitleSize(tsize, "x");
    MyStyle->SetLabelSize(tsize, "y");
    MyStyle->SetTitleSize(tsize, "y");
    MyStyle->SetLabelSize(tsize, "z");
    MyStyle->SetTitleSize(tsize, "z");

    MyStyle->SetLabelOffset(tsize / 4, "x");
    MyStyle->SetLabelOffset(tsize / 4, "y");
    MyStyle->SetTitleOffset(1.3f, "z");

    // use bold lines and markers
    MyStyle->SetMarkerStyle(1);
    MyStyle->SetMarkerSize(1.0f);
    //MyStyle->SetHistLineWidth(2);
    //MyStyle->SetLineStyleString(2, "[12 12]"); // postscript dashes
    MyStyle->SetHistLineWidth(2);
    MyStyle->SetLineStyleString(1, "[]"); // postscript solid

    // Fit line SetHistLineWidth
    MyStyle->SetLineWidth(2);
    MyStyle->SetFuncWidth(2);

    //Legend add on 20170210
    MyStyle->SetLegendBorderSize(1);
    MyStyle->SetLegendFillColor(0);
    MyStyle->SetLegendFont(font);
    //MyStyle->SetLegendTextSize(tsize);

    //Stats size
    //MyStyle->SetStatH(0.25);
    //MyStyle->SetStatW(0.25);

    // get rid of X error bars and y error bar caps
    //MyStyle->SetErrorX(0.001);

    // do not display any of the standard histogram decorations
    MyStyle->SetTitleFillColor(0);
    MyStyle->SetOptTitle(1); //title =0, not display
#ifdef SHOW_STSTS
    MyStyle->SetOptStat(1111); //statsを消さない場合
    MyStyle->SetOptFit(1111);
#else
    MyStyle->SetOptStat(kFALSE); //statsを消す場合
    MyStyle->SetOptFit(kFALSE);
#endif

    // put tick marks on top and RHS of plots
    MyStyle->SetPadTickX(1);
    MyStyle->SetPadTickY(1);

    MyStyle->SetPalette(1);

    return MyStyle;

}
#endif