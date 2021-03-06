// Manager.hh --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 一 8月 15 22:17:54 2016 (+0800)
// Last-Updated: 五 11月 11 13:51:03 2016 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 12
// URL: http://wuhongyi.cn 

#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "pixie16app_export.h"
#include <cstring>
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>

class Detector;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class Manager
{
public:
  Manager();
  virtual ~Manager();


  bool BootSystem();
 
  // void StartLSRun();

  void RunManager();
  
protected:
  void CheckKeyboard();
  void SetLSFileName();
  // void LSRunReadData();
  void SetLSonlinedataf();
  
private:
  
  char Filename[PRESET_MAX_MODULES][256];
  char  Histogramname[PRESET_MAX_MODULES][256];
  
  std::string filepathtext;
  std::string filenametext;
  std::string filerunnum;
  int runnum;

  bool fonlinedata;
  bool fstartdaq;
  bool fstopdaq;
  
  Detector *detector;

  //run manager
  bool Quit;//true:exit  false:run
  bool AcqRun;//true:start  false:stop
  char Key;//
  bool WriteFlag;//true:write  false:not write
};

#endif /* _MANAGER_H_ */
// 
// Manager.hh ends here
