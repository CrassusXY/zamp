#ifndef  LIBINTERFACE_HH
#define  LIBINTERFACE_HH

#include "AbstractInterp4Command.hh"
#include <dlfcn.h>
#include <map>
#include <memory>

class LibInterface {
    void * _pLibHnd = nullptr;
    AbstractInterp4Command *(*_pCreateCmd)(void) = nullptr;
  public: 
    ~LibInterface() {if(_pLibHnd) dlclose(_pLibHnd); }
    bool init(const char * sFileName);
    AbstractInterp4Command *CreateCmd() {return _pCreateCmd(); }
};

class Set4LibInterfaces {
  private:
    std::map<std::string, std::shared_ptr<LibInterface>> mSet;
  public:
    bool init();
    std::shared_ptr<LibInterface> get_interface(std::string lib_name);
};

#endif