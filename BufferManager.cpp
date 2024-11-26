#include "BufferManager.h"

void BufferManager::cargarBloque(int id, const std::vector<std::string>& datos){
    buffer[id] = datos;
}

bool BufferManager::obtenerBloque(int id, std::vector<std::string>& datos) const{
    if (bloqueExiste(id)){
        datos = buffer.at(id);
        return true;
    }
    return false;
}

bool BufferManager::bloqueExiste(int id) const{
    return buffer.find(id) != buffer.end();
}

void BufferManager::limpiarBuffer(){
    buffer.clear();
}
