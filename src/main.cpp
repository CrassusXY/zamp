#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <map>
#include <memory>
#include "LibInterface.hh"

using namespace std;


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

void printPluginInfo(AbstractInterp4Command* pCmd){
  cout << endl;
  cout << pCmd->GetCmdName() << endl;
  cout << endl;
  pCmd->PrintSyntax();
  cout << endl;
  pCmd->PrintCmd();
  cout << endl;
}

int main()
{
  Set4LibInterfaces Libs;
  Libs.init();

  shared_ptr<LibInterface> tmp = Libs.get_interface("libInterp4Move");
  printPluginInfo(tmp->CreateCmd());
  tmp = Libs.get_interface("libInterp4Set");
  printPluginInfo(tmp->CreateCmd());
}
