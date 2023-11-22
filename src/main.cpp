#include <iostream>
#include <sstream>
#include <cassert>
#include "LibInterface.hh"

#define LIMIT 1024
using namespace std;

bool ExecutePreprocessor(const char *sFileName, std::istringstream &issCommands)
{
  string preprocessor = "cpp -P ";
  ostringstream outStream;
  char line_buffer[LIMIT];
  
  preprocessor += sFileName;
  FILE *pProc = popen(preprocessor.c_str(), "r");

  if (pProc) {
    while (fgets(line_buffer, LIMIT, pProc))
      outStream << line_buffer;
    issCommands.str(outStream.str());
    return pclose(pProc) == 0;
  }
  
  return false;  
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
