// Base.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 五 11月 18 19:24:01 2016 (+0800)
// Last-Updated: 六 11月 19 12:24:21 2016 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 20
// URL: http://wuhongyi.cn 

#include "Base.hh"
#include "Global.hh"

#include "pixie16app_export.h"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

Base::Base(const TGWindow * p, const TGWindow * main, char *name, int columns, int rows, int NumModules)
  : Table(p, main, columns, rows, name,NumModules)
{
  char n[10];
  cl0->SetText("ch #");
  for (int i = 0; i < rows; i++)
    {
      sprintf (n, "%2d", i);
      Labels[i]->SetText(n);
    }
  CLabel[0]->SetText("DCOffset");
  CLabel[0]->SetAlignment(kTextCenterX);
  CLabel[1]->SetText("BLcut");
  CLabel[1]->SetAlignment(kTextCenterX);
  CLabel[2]->SetText("Baseline[%]");
  CLabel[2]->SetAlignment(kTextCenterX);
  CLabel[3]->SetText("Thresh. [ADC u]");
  CLabel[3]->SetAlignment(kTextCenterX);
  CLabel[4]->SetText("Trace Length[us]");
  CLabel[4]->SetAlignment(kTextCenterX);
  CLabel[5]->SetText("Trace Delay[us]");
  CLabel[5]->SetAlignment(kTextCenterX);

  

  ColumnGain = new TGVerticalFrame(mn, 200, 300);
  mn->AddFrame(ColumnGain, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));

  TGTextEntry *LabelGain =
    new TGTextEntry(ColumnGain, new TGTextBuffer(100), 10000,
		    LabelGain->GetDefaultGC()(),
		    LabelGain->GetDefaultFontStruct(),
		    kRaisedFrame | kDoubleBorder, GetWhitePixel());
  LabelGain->SetFont("-adobe-helvetica-bold-r-*-*-10-*-*-*-*-*-iso8859-1", false);

  LabelGain->Resize(80, 20);
  LabelGain->SetEnabled(kFALSE);
  LabelGain->SetFrameDrawn(kTRUE);
  ColumnGain->AddFrame(LabelGain, new TGLayoutHints(kLHintsCenterX, 0, 0, 10, 0));
  LabelGain->SetText("Gain");
  LabelGain->SetAlignment(kTextCenterX);
  LabelGain->SetToolTipText((char*)"Control input relay: => Gain Smaller/Larger", 400);
  for (int i = 0; i < 16; i++)
    {
      ColumnGain->AddFrame(lstBoxGain[i] = new TGComboBox(ColumnGain, 2755 + i), new TGLayoutHints(kLHintsCenterX, 0, 0, 0, 0));
      lstBoxGain[i]->Associate(this);
      lstBoxGain[i]->AddEntry("Larger", 0);
      lstBoxGain[i]->AddEntry("Smaller", 1);
      lstBoxGain[i]->Resize(80, 20);
    }

  ColumnSign = new TGVerticalFrame(mn, 200, 300);
  mn->AddFrame(ColumnSign, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));

  TGTextEntry *LabelSign =
    new TGTextEntry(ColumnSign, new TGTextBuffer(100), 10000,
		    LabelSign->GetDefaultGC()(),
		    LabelSign->GetDefaultFontStruct(),
		    kRaisedFrame | kDoubleBorder, GetWhitePixel());
  LabelSign->SetFont("-adobe-helvetica-bold-r-*-*-10-*-*-*-*-*-iso8859-1", false);

  LabelSign->Resize(40, 20);
  LabelSign->SetEnabled(kFALSE);
  LabelSign->SetFrameDrawn(kTRUE);
  ColumnSign->AddFrame(LabelSign, new TGLayoutHints(kLHintsCenterX, 0, 0, 10, 0));
  LabelSign->SetText("Sign");
  LabelSign->SetAlignment(kTextCenterX);
  LabelSign->SetToolTipText((char*)"Input signal polarity control", 400);
  for (int i = 0; i < 16; i++)
    {
      ColumnSign->AddFrame(lstBox[i] = new TGComboBox(ColumnSign, 2555 + i), new TGLayoutHints(kLHintsCenterX, 0, 0, 0, 0));
      lstBox[i]->Associate(this);

      lstBox[i]->AddEntry("+", 0);
      lstBox[i]->AddEntry("-", 1);
      lstBox[i]->Resize(40, 20);
    }

  ColumnGC = new TGVerticalFrame(mn, 200, 300);
  mn->AddFrame(ColumnGC, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
  TGTextEntry *LabelGC =
    new TGTextEntry(ColumnGC, new TGTextBuffer(100), 10000,
		    LabelGC->GetDefaultGC()(),
		    LabelGC->GetDefaultFontStruct(),
		    kRaisedFrame | kDoubleBorder, GetWhitePixel());
  LabelGC->SetFont("-adobe-helvetica-bold-r-*-*-10-*-*-*-*-*-iso8859-1", false);
  LabelGC->Resize(40, 20);
  LabelGC->SetEnabled(kFALSE);
  LabelGC->SetFrameDrawn(kTRUE);
  ColumnGC->AddFrame(LabelGC, new TGLayoutHints(kLHintsCenterX, 0, 0, 10, 0));
  LabelGC->SetText("GC");
  LabelGC->SetAlignment(kTextCenterX);
  LabelGC->SetToolTipText((char*)"Good channel", 400);
  for (int i = 0; i < 16; i++)
    {
      ColumnGC->AddFrame(ckGC[i] = new TGCheckButton(ColumnGC,"", -1), new TGLayoutHints(kLHintsCenterX, 0, 0, 3, 2));
      ckGC[i]->Associate(this);
    }


  ColumnTC = new TGVerticalFrame(mn, 200, 300);
  mn->AddFrame(ColumnTC, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
  TGTextEntry *LabelTC =
    new TGTextEntry(ColumnTC, new TGTextBuffer(100), 10000,
		    LabelTC->GetDefaultGC()(),
		    LabelTC->GetDefaultFontStruct(),
		    kRaisedFrame | kDoubleBorder, GetWhitePixel());
  LabelTC->SetFont("-adobe-helvetica-bold-r-*-*-10-*-*-*-*-*-iso8859-1", false);
  LabelTC->Resize(40, 20);
  LabelTC->SetEnabled(kFALSE);
  LabelTC->SetFrameDrawn(kTRUE);
  ColumnTC->AddFrame(LabelTC, new TGLayoutHints(kLHintsCenterX, 0, 0, 10, 0));
  LabelTC->SetText("TC");
  LabelTC->SetAlignment(kTextCenterX);
  LabelTC->SetToolTipText((char*)"Trace capture and associated header data", 400);
  for (int i = 0; i < 16; i++)
    {
      ColumnTC->AddFrame(ckTC[i] = new TGCheckButton(ColumnTC,"", -1), new TGLayoutHints(kLHintsCenterX, 0, 0, 3, 2));
      ckTC[i]->Associate(this);
    }
  
  ColumnEQS = new TGVerticalFrame(mn, 200, 300);
  mn->AddFrame(ColumnEQS, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
  TGTextEntry *LabelEQS =
    new TGTextEntry(ColumnEQS, new TGTextBuffer(100), 10000,
		    LabelEQS->GetDefaultGC()(),
		    LabelEQS->GetDefaultFontStruct(),
		    kRaisedFrame | kDoubleBorder, GetWhitePixel());
  LabelEQS->SetFont("-adobe-helvetica-bold-r-*-*-10-*-*-*-*-*-iso8859-1", false);
  LabelEQS->Resize(40, 20);
  LabelEQS->SetEnabled(kFALSE);
  LabelEQS->SetFrameDrawn(kTRUE);
  ColumnEQS->AddFrame(LabelEQS, new TGLayoutHints(kLHintsCenterX, 0, 0, 10, 0));
  LabelEQS->SetText("EQS");
  LabelEQS->SetAlignment(kTextCenterX);
  LabelEQS->SetToolTipText((char*)"QDC summing and associated header data", 400);
  for (int i = 0; i < 16; i++)
    {
      ColumnEQS->AddFrame(ckEQS[i] = new TGCheckButton(ColumnEQS,"", -1), new TGLayoutHints(kLHintsCenterX, 0, 0, 3, 2));
      ckEQS[i]->Associate(this);
    }

  ColumnECT = new TGVerticalFrame(mn, 200, 300);
  mn->AddFrame(ColumnECT, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));  
  TGTextEntry *LabelECT =
    new TGTextEntry(ColumnECT, new TGTextBuffer(100), 10000,
		    LabelECT->GetDefaultGC()(),
		    LabelECT->GetDefaultFontStruct(),
		    kRaisedFrame | kDoubleBorder, GetWhitePixel());
  LabelECT->SetFont("-adobe-helvetica-bold-r-*-*-10-*-*-*-*-*-iso8859-1", false);
  LabelECT->Resize(40, 20);
  LabelECT->SetEnabled(kFALSE);
  LabelECT->SetFrameDrawn(kTRUE);
  ColumnECT->AddFrame(LabelECT, new TGLayoutHints(kLHintsCenterX, 0, 0, 10, 0));
  LabelECT->SetText("ECT");
  LabelECT->SetAlignment(kTextCenterX);
  LabelECT->SetToolTipText((char*)"CFD for real time, trace capture and QDC capture", 400);
  for (int i = 0; i < 16; i++)
    {
      ColumnECT->AddFrame(ckECT[i] = new TGCheckButton(ColumnECT,"", -1), new TGLayoutHints(kLHintsCenterX, 0, 0, 3, 2));
      ckECT[i]->Associate(this);
    }

  ColumnERB = new TGVerticalFrame(mn, 200, 300);
  mn->AddFrame(ColumnERB, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
  TGTextEntry *LabelERB =
    new TGTextEntry(ColumnERB, new TGTextBuffer(100), 10000,
		    LabelERB->GetDefaultGC()(),
		    LabelERB->GetDefaultFontStruct(),
		    kRaisedFrame | kDoubleBorder, GetWhitePixel());
  LabelERB->SetFont("-adobe-helvetica-bold-r-*-*-10-*-*-*-*-*-iso8859-1", false);
  LabelERB->Resize(40, 20);
  LabelERB->SetEnabled(kFALSE);
  LabelERB->SetFrameDrawn(kTRUE);
  ColumnERB->AddFrame(LabelERB, new TGLayoutHints(kLHintsCenterX, 0, 0, 10, 0));
  LabelERB->SetText("ERB");
  LabelERB->SetAlignment(kTextCenterX);
  LabelERB->SetToolTipText((char*)"Record raw energy sums and baseline in event header", 400);
  for (int i = 0; i < 16; i++)
    {
      ColumnERB->AddFrame(ckERB[i] = new TGCheckButton(ColumnERB,"", -1), new TGLayoutHints(kLHintsCenterX, 0, 0, 3, 2));
      ckERB[i]->Associate(this);
    }
  
  
  ////////////////Copy Button//////////////////////////////////////////////
  TGHorizontal3DLine *ln2 = new TGHorizontal3DLine(mn_vert, 200, 2);
  mn_vert->AddFrame(ln2, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 10, 10));
  TGHorizontalFrame *CopyButton = new TGHorizontalFrame(mn_vert, 400, 300);
  mn_vert->AddFrame(CopyButton, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));

  TGLabel *Copy = new TGLabel(CopyButton, "Select channel #");

  chanCopy = new TGNumberEntry(CopyButton, 0, 4, MODNUMBER+1000, (TGNumberFormat::EStyle) 0, (TGNumberFormat::EAttribute) 1, (TGNumberFormat::ELimit) 3/*kNELLimitMinMax*/, 0, 3);
  chanCopy->SetButtonToNum(0);
  chanCopy->IsEditable();
  chanCopy->SetIntNumber(0);
  CopyButton->AddFrame(Copy, new TGLayoutHints(kLHintsCenterX, 5, 10, 3, 0));
  CopyButton->AddFrame(chanCopy, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 20, 0, 0));

  chanCopy->Associate(this);

  ////////////////////Copy button per se///////////////////
  TGTextButton *copyB = new TGTextButton(CopyButton, "C&opy", COPYBUTTON+1000);
  copyB->Associate(this);
  copyB->SetToolTipText("Copy the setup of the selected channel to all channels of the module", 0);
  CopyButton->AddFrame(copyB, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 20, 0, 0));


  chanNumber = 0;

  TGTextButton *adjustB = new TGTextButton(CopyButton, "&AdjustOffset",COPYBUTTON+2000);
  adjustB->Associate(this);
  adjustB->SetToolTipText(" Adjust the DC offset of this module automatically by module!");
  CopyButton->AddFrame(adjustB,new TGLayoutHints(kLHintsTop|kLHintsLeft,0,20,0,0));
  ///////////////////////////////////////////////////////////////////////
  MapSubwindows();
  Resize();			// resize to default size

  modNumber = 0;
  Load_Once = true; 
}

Base::~Base()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


Bool_t Base::ProcessMessage(Long_t msg, Long_t parm1, Long_t parm2)
{
  switch (GET_MSG(msg))
    {
    case kC_COMMAND:
      switch (GET_SUBMSG(msg))
	{
	case kCM_BUTTON:
	  switch (parm1)
	    {
	    case (MODNUMBER):
	      if (parm2 == 0)
		{
		  if (modNumber != numModules-1)
		    {
		      ++modNumber;
		      numericMod->SetIntNumber(modNumber);
		      load_info(modNumber);
		    }
		}
	      else
		{
		  if (modNumber != 0)
		    {
		      if (--modNumber == 0)
			modNumber = 0;
		      numericMod->SetIntNumber(modNumber);
		      load_info(modNumber);
		    }
		}
	      break;
	      /////////////////////////////
	    case (MODNUMBER+1000):
	      if (parm2 == 0)
		{
		  if (chanNumber != 15)
		    {
		      ++chanNumber;
		      chanCopy->SetIntNumber(chanNumber);
		    }
		}
	      else
		{
		  if (chanNumber != 0)
		    {
		      if (--chanNumber == 0)
			chanNumber = 0;
		      chanCopy->SetIntNumber(chanNumber);
			   
		    }
		}
	      break;
	      /////////////////////////////////////
	    case LOAD:
	      {
		Load_Once = true;
		load_info(modNumber);
	      }
	      break;
	    case APPLY:
	      if (Load_Once)
		change_values(modNumber);
	      else
		std::cout << "please load once first !\n";
	      break;
	    case CANCEL:	/// Cancel Button
	      DeleteWindow();
	      break;
	    case (COPYBUTTON+1000):
	      for(int i  =0;i < 16;i++)
		{
		  if(i != (chanNumber))
		    {
		      lstBox[i]->Select(lstBox[chanNumber]->GetSelected());
		      lstBoxGain[i]->Select(lstBoxGain[chanNumber]->GetSelected());
		      if(ckGC[chanNumber]->IsDown()) 
			ckGC[i]->SetState(kButtonDown);
		      else 
			ckGC[i]->SetState(kButtonUp);
		      
		      if(ckTC[chanNumber]->IsDown()) 
			ckTC[i]->SetState(kButtonDown);
		      else 
			ckTC[i]->SetState(kButtonUp);

		      if(ckEQS[chanNumber]->IsDown()) 
			ckEQS[i]->SetState(kButtonDown);
		      else 
			ckEQS[i]->SetState(kButtonUp);

		      if(ckECT[chanNumber]->IsDown()) 
			ckECT[i]->SetState(kButtonDown);
		      else 
			ckECT[i]->SetState(kButtonUp);

		      if(ckERB[chanNumber]->IsDown()) 
			ckERB[i]->SetState(kButtonDown);
		      else 
			ckERB[i]->SetState(kButtonUp);
		      
		      sprintf(tmp,"%1.3f",NumEntry[1][chanNumber]->GetNumber());
		      NumEntry[1][i]->SetText(tmp);
		      sprintf(tmp,"%1.3f",NumEntry[2][chanNumber]->GetNumber());
		      NumEntry[2][i]->SetText(tmp);	
		      sprintf(tmp,"%1.3f",NumEntry[3][chanNumber]->GetNumber());
		      NumEntry[3][i]->SetText(tmp);
		      sprintf(tmp,"%1.3f",NumEntry[4][chanNumber]->GetNumber());
		      NumEntry[4][i]->SetText(tmp);
		      sprintf(tmp,"%1.3f",NumEntry[5][chanNumber]->GetNumber());
		      NumEntry[5][i]->SetText(tmp);
		      sprintf(tmp,"%1.3f",NumEntry[6][chanNumber]->GetNumber());
		      NumEntry[6][i]->SetText(tmp);
		    }
		}  
		    
	      break;
	    case (COPYBUTTON+2000) :
	      {
		int retval = Pixie16AdjustOffsets(modNumber);
		if(retval < 0){
		  ErrorInfo("Base.cc", "ProcessMessage(...)", "Pixie16AdjustOffsets", retval);
		  break;
		}
		load_info(modNumber);
	      }
	      break;
	    default:
	      break;
	    }
	  break;
	default:
	  break;
	}
    // case kC_TEXTENTRY:
    //   switch (GET_SUBMSG(msg))
    // 	{
    // 	case kTE_TAB:
    // 	  if (parm1 < 16)
    // 	    NumEntry[3][parm1]->SetFocus();
    // 	  if (parm1 > 15 && parm1 < 32)
    // 	    {
    // 	      if ((parm1 - 16) + 1 < 16)
    // 		NumEntry[1][(parm1 - 16) + 1]->SetFocus();
    // 	    }
    // 	  break;
    // 	}
      break;
    default:
      break;
    }

  return kTRUE;
}


int Base::load_info(Long_t mod)
{
  double ChanParData = -1;

  int retval;
  char text[20];
  unsigned short gain;
  unsigned short pol;
  unsigned short gt;
  
  for (int i = 0; i < 16; i++)
    {
      retval = Pixie16ReadSglChanPar((char*)"CHANNEL_CSRA", &ChanParData, mod, i);
      if(retval < 0)
	ErrorInfo("Base.cc", "load_info(...)", "Pixie16ReadSglChanPar/CHANNEL_CSRA", retval);
      gain = APP32_TstBit(14, (unsigned int) ChanParData);
      if (gain == 1)
	lstBoxGain[i]->Select(0);
      else if (gain == 0)
	lstBoxGain[i]->Select(1);

      pol = APP32_TstBit(5, (unsigned int) ChanParData);
      if (pol == 1)
	lstBox[i]->Select(0);
      else if (pol == 0)
	lstBox[i]->Select(1);

      gt = APP32_TstBit(2, ChanParData);
      if(gt==0) 
        ckGC[i]->SetState(kButtonUp);
      else 
	ckGC[i]->SetState(kButtonDown);

      gt = APP32_TstBit(8, ChanParData);
      if(gt==0) 
        ckTC[i]->SetState(kButtonUp);
      else 
	ckTC[i]->SetState(kButtonDown);

      gt = APP32_TstBit(9, ChanParData);
      if(gt==0) 
        ckEQS[i]->SetState(kButtonUp);
      else 
	ckEQS[i]->SetState(kButtonDown);

      gt = APP32_TstBit(10, ChanParData);
      if(gt==0) 
        ckECT[i]->SetState(kButtonUp);
      else 
	ckECT[i]->SetState(kButtonDown);

      gt = APP32_TstBit(12, ChanParData);
      if(gt==0) 
        ckERB[i]->SetState(kButtonUp);
      else 
	ckERB[i]->SetState(kButtonDown);
      
      retval = Pixie16ReadSglChanPar((char*)"VOFFSET", &ChanParData, mod, i);
      if(retval < 0)
	ErrorInfo("Base.cc", "load_info(...)", "Pixie16ReadSglChanPar/VOFFSET", retval);
      sprintf(text, "%1.3f", ChanParData);
      NumEntry[1][i]->SetText(text);

      retval = Pixie16ReadSglChanPar((char*)"BLCUT", &ChanParData, mod, i);
      if(retval < 0) ErrorInfo("Base.cc", "load_info(...)", "Pixie16ReadSglChanPar/BLCUT", retval);  
      sprintf(text, "%d", (int)ChanParData);
      NumEntry[2][i]->SetText(text);

      retval = Pixie16ReadSglChanPar((char*)"BASELINE_PERCENT", &ChanParData, mod, i);
      if(retval < 0) ErrorInfo("Base.cc", "load_info(...)", "Pixie16ReadSglChanPar/BASELINE_PERCENT", retval);  
      sprintf(text, "%d", (int)ChanParData);
      NumEntry[3][i]->SetText(text);

      retval = Pixie16ReadSglChanPar((char*)"TRIGGER_THRESHOLD", &ChanParData, mod, i);
      if(retval < 0) ErrorInfo("Base.cc", "load_info(...)", "Pixie16ReadSglChanPar/TRIGGER_THRESHOLD", retval);
      sprintf(text, "%d", (int)ChanParData);
      NumEntry[4][i]->SetText(text);

      retval = Pixie16ReadSglChanPar((char*)"TRACE_LENGTH", &ChanParData, mod, i);
      if(retval < 0) ErrorInfo("Base.cc", "load_info(...)", "Pixie16ReadSglChanPar/TRACE_LENGTH", retval);
      sprintf (text, "%1.2f", ChanParData);
      NumEntry[5][i]->SetText(text);

      retval = Pixie16ReadSglChanPar((char*)"TRACE_DELAY", &ChanParData, mod, i);
      if(retval < 0) ErrorInfo("Base.cc", "load_info(...)", "Pixie16ReadSglChanPar/TRACE_DELAY", retval);
      sprintf(text, "%1.2f", ChanParData);
      NumEntry[6][i]->SetText(text);

      
    }
  return 1;
}

int Base::change_values(Long_t mod)
{
  int retval;
  double offset;
  double ChanParData = -1;
  double gain;
  int pol = 0;
  double cut;
  double percent;
  double thresh;
  double length;
  double delay;
  
  for (int i = 0; i < 16; i++)
    {
      offset = NumEntry[1][i]->GetNumber();
      retval = Pixie16WriteSglChanPar((char*)"VOFFSET", offset, mod, i);
      if(retval < 0) ErrorInfo("Base.cc", "change_values(...)", "Pixie16WriteSglChanPar/VOFFSET", retval);
      
      retval = Pixie16ReadSglChanPar((char*)"CHANNEL_CSRA", &ChanParData, mod, i);
      if(retval < 0) ErrorInfo("Base.cc", "change_values(...)", "Pixie16ReadSglChanPar/CHANNEL_CSRA", retval);
      
      pol = lstBox[i]->GetSelected();
      if (pol == 0)
	ChanParData = APP32_SetBit(5, (unsigned int) ChanParData);
      else
	ChanParData = APP32_ClrBit(5, (unsigned int) ChanParData);

      
      gain = lstBoxGain[i]->GetSelected();
      if (gain == 1)
	ChanParData = APP32_ClrBit(14, (unsigned int) ChanParData); 
      else
	ChanParData = APP32_SetBit(14, (unsigned int) ChanParData); 

      
      if (ckGC[i]->IsDown())
	ChanParData = APP32_SetBit(2, (unsigned int) ChanParData);
      else
	ChanParData = APP32_ClrBit(2, (unsigned int) ChanParData);

      
      if (ckTC[i]->IsDown())
	ChanParData = APP32_SetBit(8, (unsigned int) ChanParData);
      else
	ChanParData = APP32_ClrBit(8, (unsigned int) ChanParData);

      if (ckEQS[i]->IsDown())
	ChanParData = APP32_SetBit(9, (unsigned int) ChanParData);
      else
	ChanParData = APP32_ClrBit(9, (unsigned int) ChanParData);

      if (ckECT[i]->IsDown())
	ChanParData = APP32_SetBit(10, (unsigned int) ChanParData);
      else
	ChanParData = APP32_ClrBit(10, (unsigned int) ChanParData);


      if (ckERB[i]->IsDown())
	ChanParData = APP32_SetBit(12, (unsigned int) ChanParData);
      else
	ChanParData = APP32_ClrBit(12, (unsigned int) ChanParData);
      
      
      retval = Pixie16WriteSglChanPar((char*)"CHANNEL_CSRA", ChanParData, mod, i);
      if(retval < 0) ErrorInfo("Base.cc", "change_values(...)", "Pixie16WriteSglChanPar/CHANNEL_CSRA", retval);

      
      cut = NumEntry[2][i]->GetNumber();
      retval = Pixie16WriteSglChanPar((char*)"BLCUT", cut, mod, i);
      if(retval < 0) ErrorInfo("Base.cc", "change_values(...)", "Pixie16WriteSglChanPar/BLCUT", retval);  
      percent = NumEntry[3][i]->GetNumber();
      retval = Pixie16WriteSglChanPar((char*)"BASELINE_PERCENT", percent, mod, i);
      if(retval < 0) ErrorInfo("Base.cc", "change_values(...)", "Pixie16WriteSglChanPar/BASELINE_PERCENT", retval);  

      thresh = NumEntry[4][i]->GetNumber();
      retval = Pixie16WriteSglChanPar((char*)"TRIGGER_THRESHOLD", thresh, mod, i);
      if(retval < 0) ErrorInfo("Base.cc", "change_values(...)", "Pixie16WriteSglChanPar/TRIGGER_THRESHOLD", retval);


      length = NumEntry[5][i]->GetNumber();
      retval = Pixie16WriteSglChanPar((char*)"TRACE_LENGTH", length, mod, i);
      if(retval < 0) ErrorInfo("Base.cc", "change_values(...)", "Pixie16WriteSglChanPar/TRACE_LENGTH", retval);
      delay = NumEntry[6][i]->GetNumber();
      retval = Pixie16WriteSglChanPar((char*)"TRACE_DELAY", delay, mod, i);
      if(retval < 0) ErrorInfo("Base.cc", "change_values(...)", "Pixie16WriteSglChanPar/TRACE_DELAY", retval);


    }
  return 1;
}


// 
// Base.cc ends here