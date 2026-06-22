#pragma once
#include "Fecha.h"

class Socio{

private:
    int _idSocio;
    char _nombre[30];
    char _apellido[30];
    int _dni;
    char _telefono[20];
    char _email[40];
    char _domicilio[50];
    Fecha _fechaNacimiento;
    bool _estado;

public:
    Socio();
    Socio(int idSocio, const char* nombre, const char* apellido, int dni, const char* telefono, const char* email, const char* domicilio, Fecha fechaNacimiento, bool estado);

    int getIdSocio();
    void setIdSocio(int idSocio);

    const char* getNombre();
    void setNombre(const char* nombre);

    const char* getApellido();
    void setApellido(const char* apellido);

    int getDNI();
    void setDNI(int dni);

    const char* getTelefono();
    void setTelefono(const char* telefono);

    const char* getEmail();
    void setEmail(const char* email);

    const char* getDomicilio();
    void setDomicilio(const char* domicilio);

    Fecha getFechaNacimiento();
    void setFechaNacimiento(Fecha fechaNacimiento);

    bool getEstado();
    void setEstado(bool estado);

    void cargar();
    void mostrar();

    bool guardar();
    bool modificar(int posicion);

    static int contarRegistros();
    static Socio leer(int posicion);
    static int buscarPorID(int idSocio);
    static bool existe(int idSocio);
    static int generarNuevoID();
    static void listar();
    static void listarOrdenadoPorDNI();
    static void consultarPorDNI();
    static void consultarPorApellido();
    static void bajaLogica();
    static void menuSocios();
};
