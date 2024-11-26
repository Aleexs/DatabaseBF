#ifndef BUFFERMANAGER_H
#define BUFFERMANAGER_H

#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>

class BufferManager{
private:
    std::unordered_map<int, std::vector<std::string>> buffer;

public:
    void cargarBloque(int id, const std::vector<std::string>& datos);

    bool obtenerBloque(int id, std::vector<std::string>& datos) const;

    bool bloqueExiste(int id) const;

    void limpiarBuffer();
};

#endif
