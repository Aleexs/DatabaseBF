#ifndef TABLEMANAGER_H
#define TABLEMANAGER_H

#include "SchemaManager.h"
#include "BufferManager.h" // Incluir el BufferManager
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

class TableManager{
    SchemaManager &schemaManager;
    BufferManager &bufferManager;

public:
    explicit TableManager(SchemaManager &sm, BufferManager &bm);
    bool insertar(const std::string &tablaNombre, const std::vector<std::string> &valores);
    void seleccionar(const std::string &tablaNombre, const std::string &outputarchivo = "");
};

#endif
