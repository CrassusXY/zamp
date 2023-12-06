#ifndef KLIENT_HH
#define KLIENT_HH

#include "AbstractInterp4Command.hh"
#include "AccessControl.hh"
#include "Configuration.hh"
#include "Port.hh"
#include "Reader.hh"
#include "Sender.hh"
#include "Set4LibInterfaces.hh"
#include <arpa/inet.h>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <thread>
#include <unistd.h>
#include <vector>

using namespace std;

class klient {
public:
    int exec();
};

#endif