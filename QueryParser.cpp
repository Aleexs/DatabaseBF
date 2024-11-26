#include "QueryParser.h"
#include <sstream>
#include <iostream>
#include <stdexcept>

QueryParser::QueryParser(TableManager &tm) : tableManager(tm){}

void QueryParser::ejecutarQuery(const std::string &query){
    if (query.find("SELECT") == 0){
        procesarSelect(query);
    } else if (query.find("INSERT") == 0){
        procesarInsert(query);
    } else{
        std::cerr<<"Consulta no reconocida: "<<query<<std::endl;
    }
}

void QueryParser::procesarSelect(const std::string &query){
    size_t fromPos = query.find("FROM");
    if (fromPos == std::string::npos){
        std::cerr<<"ERROR: Query SELECT sin la clausula FROM\n";
        return;
    }

    std::string tablaNombre = query.substr(fromPos + 4);
    tablaNombre = tablaNombre.substr(0, tablaNombre.find("#"));
    tableManager.seleccionar(tablaNombre);
}

void QueryParser::procesarInsert(const std::string &query){
    size_t intoPos = query.find("INTO");
    size_t valuesPos = query.find("VALUES");

    if (intoPos == std::string::npos || valuesPos == std::string::npos){
        std::cerr<<"ERROR: Query INSERT mal formada\n";
        return;
    }

    std::string tablaNombre = query.substr(intoPos + 4, valuesPos - (intoPos + 4));
    tablaNombre = tablaNombre.substr(0, tablaNombre.find(" "));

    std::vector<std::string> valores = obtenerValores(query);

    tableManager.insertar(tablaNombre, valores);
}

std::vector<std::string> QueryParser::obtenerValores(const std::string &query){
    std::vector<std::string> valores;
    
    size_t valuesPos = query.find("VALUES");
    std::string valoresString = query.substr(valuesPos + 6);
    valoresString = valoresString.substr(1, valoresString.length() - 2);

    std::stringstream ss(valoresString);
    std::string valor;
    while (std::getline(ss, valor, ',')){
        valores.push_back(valor);
    }

    return valores;
}
