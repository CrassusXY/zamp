#include "LibInterface.hh"

bool LibInterface::init(const char * sFileName)
{
  _pLibHnd = dlopen(sFileName,RTLD_LAZY);
  if (!_pLibHnd) {
    std::cerr << "!!! Brak biblioteki: " << sFileName << std::endl;
    return false;
  }

  void *pFun = dlsym(_pLibHnd,"CreateCmd");
  
  if (!pFun) {
    std::cerr << "!!! Nie znaleziono funkcji CreateCmd" << std::endl;
    return 1;
  }
  
  _pCreateCmd = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFun);

  return true;
}