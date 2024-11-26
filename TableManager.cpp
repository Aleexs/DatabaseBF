#include "TableManager.h"

TableManager::TableManager(SchemaManager &sm) : schemaManager(sm){}

bool TableManager::insertar(const std::string &tablaNombre, const std::vector<std::string> &valores){
    if(!schemaManager.tablaExiste(tablaNombre)){
        std::cerr<<"Tabla incorrecta.\n";
        return false;
    }

    const auto &schema = schemaManager.getTablaSchema(tablaNombre);
    if(valores.size() != schema.size()){
        std::cerr<<"Atributo incorrecto\n";
        return false;
    }

    std::ofstream Tablaarchivo(tablaNombre + ".txt", std::ios::app);
    for(const auto &value : valores){
        Tablaarchivo<<value<<"#";
    }
    Tablaarchivo<<"\n";
    return true;
}

void TableManager::seleccionar(const std::string &tablaNombre, const std::string &outputarchivo){
    if(!schemaManager.tablaExiste(tablaNombre)){
        std::cerr<<"No existe la tabla\n";
        return;
    }

    std::ifstream Tablaarchivo(tablaNombre + ".txt");
    if(!Tablaarchivo){
        std::cerr<<"No existe la tabla"<<tablaNombre<<".\n";
        return;
    }

    std::string linea;
    std::vector<std::string> resultados;

    while(std::getline(Tablaarchivo, linea)){
        std::string displaylinea = linea;
        std::replace(displaylinea.begin(), displaylinea.end(), '#', ' ');
        resultados.push_back(displaylinea);
    }

    for(const auto &guardar : resultados){
        std::cout<<guardar<<"\n";
    }

    if(!outputarchivo.empty()){
        std::ofstream outarchivo(outputarchivo);
        for(const auto &guardar : resultados){
            std::string savelinea = guardar;
            std::replace(savelinea.begin(), savelinea.end(), ' ', '#');
            outarchivo<<savelinea<<"\n";
        }
        std::cout<<"Guardar en: "<<outputarchivo<<"\n";
    }
}