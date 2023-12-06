#ifndef SET4LIBINTERFACES_HH
#define SET4LIBINTERFACES_HH

#include "AbstractInterp4Command.hh"
#include "LibInterface.hh"
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

class Set4LibInterfaces {
private:
    std::map<std::string, std::shared_ptr<LibInterface>> lib;
    bool parallel = false;

public:
    // Inicjalizuje interfejsy bibliotek dynamicznych na podstawie wektora nazw plików
    bool init(std::vector<std::string> lib_vector);

    // Wykonuje komendę na podstawie nazwy
    // Obsługuje komendy równoległe
    // Zwraca wskaźnik do obiektu reprezentującego komendę
    AbstractInterp4Command* execute(std::string key);
    bool isParallel() { return parallel; }
};

#endif
