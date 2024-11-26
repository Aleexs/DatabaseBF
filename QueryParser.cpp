#include "QueryParser.h"

QueryParser::QueryParser(TableManager &tm) : tableManager(tm){}

void QueryParser::ejecutarQuery(const std::string &query){
    if(query.back() != '#' && query.substr(query.size() - 2) != "##"){
        std::cerr<<"Error: El final de la linea debe de contener # o ##.\n";
        return;
    }

    bool guardarArchivo = query.substr(query.size() - 2) == "##";
    std::string processedQuery = guardarArchivo ? query.substr(0, query.size() - 2) : query.substr(0, query.size() - 1);

    std::stringstream ss(processedQuery);
    std::string comando, tablaNombre;
    ss >> comando;

    if(comando == "INSERT"){
        ss >> comando; //
        if(comando != "INTO"){
            std::cerr<<"Error: INTO no reconocido\n";
            return;
        }
        ss >> tablaNombre;

        size_t openParen = processedQuery.find('(');
        size_t closeParen = processedQuery.find(')', openParen);

        if(openParen == std::string::npos || closeParen == std::string::npos || openParen > closeParen){
            std::cerr<<"Error: Sintaxis invalidaa\n";
            return;
        }

        std::string valores = processedQuery.substr(openParen + 1, closeParen - openParen - 1); // Extraer los valores
        std::stringstream valueStream(valores);
        std::vector<std::string> parsedValores;
        std::string value;

        while(std::getline(valueStream, value, ',')){
            value.erase(0, value.find_first_not_of(" \t'\"")); // Inicio
            value.erase(value.find_last_not_of(" \t'\"") + 1); // Fin
            parsedValores.push_back(value);
        }

        if(!tableManager.insertar(tablaNombre, parsedValores)){
            std::cerr<<"ERROR: insercion erronea"<<tablaNombre<<".\n";
        }
    } else if(comando == "SELECT"){
        ss >> comando; // *
        if(comando != "*"){
            std::cerr<<"Solo valido SELECT\n";
            return;
        }
        ss >> comando; // FROM
        if(comando != "FROM"){
            std::cerr<<"Solo valido FROM\n";
            return;
        }
        ss >> tablaNombre;

        if(guardarArchivo){
            std::cout<<"Nombre del archivo: ";
            std::string outputFile;
            std::cin >> outputFile;
            tableManager.seleccionar(tablaNombre, outputFile);
        } else{
            tableManager.seleccionar(tablaNombre);
        }
    } else{
        std::cerr<<"Error: comando invalido '"<<comando<<"'.\n";
    }
}