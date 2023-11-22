#include <iostream>
#include <sstream>
#include <cassert>
#include "LibInterface.hh"

#define LIMIT 1024
using namespace std;

bool executePreprocesor(const char *file, std::istringstream &cmds)
{
  string preprocessor = "cpp -P ";
  ostringstream outStream;
  char line_buffer[LIMIT];
  
  preprocessor += file;
  FILE *pProc = popen(preprocessor.c_str(), "r");

  if (pProc) {
    while (fgets(line_buffer, LIMIT, pProc))
      outStream << line_buffer;
    cmds.str(outStream.str());
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

void executeCommands(const char* fname, Set4LibInterfaces* libs){
  istringstream cmds;
	executePreprocesor(fname,cmds);

	while(cmds.peek() != EOF) {
		string cmd;
		cmds >> cmd;

    shared_ptr<LibInterface> tmp = libs->get_interface("libInterp4"+cmd);
		if(tmp != NULL){
				AbstractInterp4Command* pCmd = tmp->CreateCmd();
				pCmd->ReadParams(cmds);
				printPluginInfo(pCmd);
				delete pCmd;
		}
    
		else cout<<"Brak biblioteki " << cmd <<endl;

		cmds.ignore(LIMIT,'\n');
	}
}

int main()
{
  Set4LibInterfaces Libs;
  Libs.init();

  executeCommands("commands.cmd", &Libs);
}
