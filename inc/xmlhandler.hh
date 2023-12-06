#ifndef XMLHANDLER_HH
#define XMLHANDLER_HH

#include "xmlinterp.hh"
#include <iostream>
#include <list>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/util/XMLString.hpp>

#include "Configuration.hh"

bool ReadFile(const char* sFileName, Configuration& rConfig);

#endif