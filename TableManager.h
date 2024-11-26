 #ifndef TableMANAGER_H
#define TableMANAGER_H

#include "SchemaManager.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <bits/stdc++.h>

class TableManager{
    SchemaManager &schemaManager;

public:
    explicit TableManager(SchemaManager &sm);
    bool insertar(const std::string &tablaNombre, const std::vector<std::string> &valores);
    void seleccionar(const std::string &tablaNombre, const std::string &outputarchivo = "");
};

#endif