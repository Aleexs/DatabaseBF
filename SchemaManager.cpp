#include "SchemaManager.h"

SchemaManager::SchemaManager(const std::string &schemaArchivo){
    cargarSchemas(schemaArchivo);
}

void SchemaManager::cargarSchemas(const std::string &schemaArchivo){
    std::ifstream archivo(schemaArchivo);
    std::string linea;

    while(std::getline(archivo, linea)){
        std::stringstream ss(linea);
        std::string tablaNombre, atributo, tipo;
        std::vector<std::pair<std::string, std::string>> atributos;

        std::getline(ss, tablaNombre, '#');
        while(std::getline(ss, atributo, '#') && std::getline(ss, tipo, '#')){
            atributos.emplace_back(atributo, tipo);
        }
        schemas[tablaNombre] = atributos;
    }
}

bool SchemaManager::tablaExiste(const std::string &tablaNombre) const{
    return schemas.find(tablaNombre) != schemas.end();
}

const std::vector<std::pair<std::string, std::string>> &SchemaManager::getTablaSchema(const std::string &tablaNombre) const{
    return schemas.at(tablaNombre);
}

void SchemaManager::displaySchemas() const{
    for(const auto &[tablaNombre, atributos] : schemas){
        std::cout<<"Tabla: "<<tablaNombre<<"\natributos:\n";
        for(const auto &[atributoNombre, atributoTipo] : atributos){
            std::cout<<"  - "<<atributoNombre<<"("<<atributoTipo<<")\n";
        }
    }
}