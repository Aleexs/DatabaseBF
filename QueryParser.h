#ifndef QUERYPARSER_H
#define QUERYPARSER_H

#include "TableManager.h"
#include <sstream>

class QueryParser{
    TableManager &tableManager;

public:
    explicit QueryParser(TableManager &tm);
    void ejecutarQuery(const std::string &query);
};

#endif