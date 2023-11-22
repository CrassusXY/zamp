#ifndef  LIBINTERFACE_HH
#define  LIBINTERFACE_HH

#include "AbstractInterp4Command.hh"
#include <dlfcn.h>

class LibInterface {
    void * _pLibHnd = nullptr;
    AbstractInterp4Command *(*_pCreateCmd)(void) = nullptr;
  public: 
    ~LibInterface() {if(_pLibHnd) dlclose(_pLibHnd); }
    bool init(const char * sFileName);
    AbstractInterp4Command *CreateCmd() {return _pCreateCmd(); }
};



#endif