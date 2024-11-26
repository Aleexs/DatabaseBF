#ifndef SCHEMAMANAGER_H
#define SCHEMAMANAGER_H

#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class SchemaManager{
    std::unordered_map<std::string, std::vector<std::pair<std::string, std::string>>> schemas;

public:
    SchemaManager(const std::string &schemaArchivo);
    void cargarSchemas(const std::string &schemaArchivo);
    bool tablaExiste(const std::string &tablaNombre) const;
    const std::vector<std::pair<std::string, std::string>> &getTablaSchema(const std::string &tablaNombre) const;
    void displaySchemas() const;
};

#endif