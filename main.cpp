#include "SchemaManager.h"
#include "TableManager.h"
#include "QueryParser.h"

int main(){
    SchemaManager schemaManager("Schemes.txt");
    TableManager tableManager(schemaManager);
    QueryParser queryParser(tableManager);

    std::string query;
    while(true){
        std::cout<<"$> ";
        std::getline(std::cin, query);
        if(query == "SALIR#") break;
        queryParser.ejecutarQuery(query);
    }

    return 0;
}