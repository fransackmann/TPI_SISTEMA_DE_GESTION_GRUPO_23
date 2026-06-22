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
    Autor(int idAutor, const char* nombre, const char* apellido, const char* nacionalidad, bool estado);

    int getAutorID();
    void setAutorID(int idAutor);

    const char* getNombre();
    void setNombre(const char* nombre);

    const char* getApellido();
    void setApellido(const char* apellido);

    const char* getNacionalidad();
    void setNacionalidad(const char* nacionalidad);

    bool getEstado();
    void setEstado(bool estado);

    void cargar();
    void mostrar();

    bool guardar();
    static int contarRegistros();
    static Autor leer(int posicion);
    static int generarNuevoID();
    static void listar();
    static void listarOrdenadoPorApellido();
    static void menuAutores();
};
