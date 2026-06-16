#pragma once

class Autor{
private:
    int _idAutor;
    char _nombre[30];
    char _apellido[30];
    char _nacionalidad[30];
    bool _estado;
public:
    Autor();
    Autor(int,const char*,const char*,const char*, bool);

    const char* getNombre();
    void setNombre(const char*);

    const char* getApellido();
    void setApellido(const char*);

    int getAutorID();
    void setAutorID(int);

    const char* getNacionalidad();
    void setNacionalidad(const char*);

    bool getEstado();
    void setEstado(bool);


    void cargar();
    void mostrar();
    void mostrarAutoresOrdenadosPorApellido();

    void menuAutores();
};


