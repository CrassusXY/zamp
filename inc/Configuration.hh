#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH

#include <cassert>
#include <cstdio>
#include <dlfcn.h>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

// #include "LibInterface.hh"

#include "MobileObjConfig.hh"

using namespace std;

class Configuration {
public:
    std::vector<MobileObjConfig> _ObjectsConfig;
    std::vector<std::string> libs;
};

#endif
