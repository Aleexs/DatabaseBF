#ifndef QUERYPARSER_H
#define QUERYPARSER_H

#include "TableManager.h"
#include <string>
#include <vector>

class QueryParser{
private:
    TableManager &tableManager;

public:
    explicit QueryParser(TableManager &tm);

    void ejecutarQuery(const std::string &query);
    
    void procesarSelect(const std::string &query);
    void procesarInsert(const std::string &query);
    std::vector<std::string> obtenerValores(const std::string &query);
};

#endif
