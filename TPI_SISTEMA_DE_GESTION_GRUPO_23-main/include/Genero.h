#pragma once

class Genero{

private:

    int _idGenero;
    char _descripcion[30];
    bool _estado;

public:

    Genero();
    Genero(int idGenero, const char* descripcion, bool estado);

    int getIdGenero();
    void setIdGenero(int idGenero);

    const char* getDescripcion();
    void setDescripcion(const char* descripcion);

    bool getEstado();
    void setEstado(bool estado);

    void cargar();
    void mostrar();

};
