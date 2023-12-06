#ifndef LIBINTERFACE_HH
#define LIBINTERFACE_HH

#include "AbstractInterp4Command.hh"
#include <cassert>
#include <dlfcn.h>
#include <iostream>

class LibInterface {
private:
    void* _LibHandler;
    std::string _CmdName;
    AbstractInterp4Command* (*_pCreateCmd)(void);

public:
    ~LibInterface();
    bool init(std::string libraryName);
    AbstractInterp4Command* CreateCmd();
};
#endif
