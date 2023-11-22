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

bool Set4LibInterfaces::init() 
{
  std::string libs[] = {"libInterp4Set", "libInterp4Move"};
  std::string lib_path;
  for (size_t i = 0; i < sizeof(libs) / sizeof(libs[0]); i++)
  {
    std::shared_ptr<LibInterface> tmp(new LibInterface());
    lib_path = libs[i] + ".so";
    tmp->init(lib_path.c_str());
    mSet.emplace(libs[i], tmp);
  }
  return true;
}

std::shared_ptr<LibInterface> Set4LibInterfaces::get_interface(std::string lib_name)
{
  return mSet[lib_name];
}