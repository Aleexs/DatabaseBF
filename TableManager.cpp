#include "TableManager.h"

TableManager::TableManager(SchemaManager &sm, BufferManager &bm)
    : schemaManager(sm), bufferManager(bm){}

bool TableManager::insertar(const std::string &tablaNombre, const std::vector<std::string> &valores){
    if (!schemaManager.tablaExiste(tablaNombre)){
        std::cerr<<"Tabla incorrecta.\n";
        return false;
    }

    const auto &schema = schemaManager.getTablaSchema(tablaNombre);
    if (valores.size() != schema.size()){
        std::cerr<<"Atributo incorrecto\n";
        return false;
    }

    static int nextBlockId = 0;  
    int blockId = nextBlockId++;

    std::vector<std::string> datos;
    for (const auto &value : valores){
        datos.push_back(value);
    }
    bufferManager.cargarBloque(blockId, datos);

    std::ofstream Tablaarchivo(tablaNombre + ".txt", std::ios::app);
    for (const auto &value : valores){
        Tablaarchivo<<value<<"#";
    }
    Tablaarchivo<<"\n";

    return true;
}

void TableManager::seleccionar(const std::string &tablaNombre, const std::string &outputarchivo){
    static int nextBlockId = 0; 
    int blockId = nextBlockId++;
    if (!schemaManager.tablaExiste(tablaNombre)){
        std::cerr<<"No existe la tabla\n";
        return;
    }

    std::vector<std::string> datosRecuperados;
    if (bufferManager.obtenerBloque(blockId, datosRecuperados)){
        for (const auto &dato : datosRecuperados){
            std::cout<<dato<<" ";
        }
        std::cout<<std::endl;
    } else{
        std::ifstream Tablaarchivo(tablaNombre + ".txt");
        std::string linea;
        while (std::getline(Tablaarchivo, linea)){
            std::cout<<linea<<std::endl;
        }
    }

    if (!outputarchivo.empty()){
        std::ofstream outarchivo(outputarchivo);
        for (const auto &dato : datosRecuperados){
            outarchivo<<dato<<"#";
        }
    }
}
