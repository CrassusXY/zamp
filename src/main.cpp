#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <map>
#include <memory>
#include "AbstractInterp4Command.hh"

using namespace std;

class LibInterface {
    void * _pLibHnd = nullptr;
    AbstractInterp4Command *(*_pCreateCmd)(void) = nullptr;
  public: 
    ~LibInterface() {if(_pLibHnd) dlclose(_pLibHnd); }
    bool init(const char * sFileName);
    AbstractInterp4Command *CreateCmd() {return _pCreateCmd(); }
};

bool LibInterface::init(const char * sFileName)
{
  _pLibHnd = dlopen(sFileName,RTLD_LAZY);
  if (!_pLibHnd) {
    cerr << "!!! Brak biblioteki: " << sFileName << endl;
    return false;
  }

  void *pFun = dlsym(_pLibHnd,"CreateCmd");
  
  if (!pFun) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }
  
  _pCreateCmd = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFun);

  return true;
}


class Set4LibInterfaces {
  private:
    map<string, shared_ptr<LibInterface>> mSet;
  public:
    bool init();
    shared_ptr<LibInterface> get_interface(string lib_name);
};

bool Set4LibInterfaces::init() 
{
  string libs[] = {"libInterp4Set", "libInterp4Move"};
  string lib_path;
  for (size_t i = 0; i < sizeof(libs) / sizeof(libs[0]); i++)
  {
    shared_ptr<LibInterface> tmp(new LibInterface());
    lib_path = libs[i] + ".so";
    tmp->init(lib_path.c_str());
    mSet.emplace(libs[i], tmp);
  }
  return true;
}

shared_ptr<LibInterface> Set4LibInterfaces::get_interface(string lib_name)
{
  return mSet[lib_name];
}

int main()
{
  Set4LibInterfaces dupa;
  dupa.init();

  shared_ptr<LibInterface> tmp = dupa.get_interface("libInterp4Move");
  AbstractInterp4Command *pCmd = tmp->CreateCmd();
  
  tmp = dupa.get_interface("libInterp4Set");
  AbstractInterp4Command *pCmdA = tmp->CreateCmd();
 
  cout << endl;
  cout << pCmd->GetCmdName() << endl;
  cout << endl;
  pCmd->PrintSyntax();
  cout << endl;
  pCmd->PrintCmd();
  cout << endl;

  cout << endl;
  cout << pCmdA->GetCmdName() << endl;
  cout << endl;
  pCmdA->PrintSyntax();
  cout << endl;
  pCmdA->PrintCmd();
  cout << endl;

  delete pCmd;
  delete pCmdA;
}
