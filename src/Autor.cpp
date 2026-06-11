#include <iostream>
#include <cstring>
#include "Autor.h"

using namespace std;

Autor::Autor(){

    _idAutor = 0;
    strcpy(_nombre, "");
    strcpy(_apellido, "");
    strcpy(_nacionalidad, "");
    _estado = true;

}

Autor::Autor(int idAutor, const char* nombre, const char* apellido, const char* nacionalidad, bool estado){

    _idAutor = idAutor;
    strcpy(_nombre, nombre);
    strcpy(_apellido, apellido);
    strcpy(_nacionalidad, nacionalidad);
    _estado = estado;

}

int Autor::getIdAutor(){

    return _idAutor;

}

void Autor::setIdAutor(int idAutor){

    _idAutor = idAutor;

}

const char* Autor::getNombre(){

    return _nombre;

}

void Autor::setNombre(const char* nombre){

    strcpy(_nombre, nombre);

}

const char* Autor::getApellido(){

    return _apellido;

}

void Autor::setApellido(const char* apellido){

    strcpy(_apellido, apellido);

}

const char* Autor::getNacionalidad(){

    return _nacionalidad;

}

void Autor::setNacionalidad(const char* nacionalidad){

    strcpy(_nacionalidad, nacionalidad);

}

bool Autor::getEstado(){

    return _estado;

}

void Autor::setEstado(bool estado){

    _estado = estado;

}

void Autor::cargar(){

    cout << "ID del autor: ";
    cin >> _idAutor;

    cout << "Nombre: ";
    cin >> _nombre;

    cout << "Apellido: ";
    cin >> _apellido;

    cout << "Nacionalidad: ";
    cin >> _nacionalidad;

    _estado = true;
}

void Autor::mostrar(){

    if(_estado == true){

        cout << "ID: " << _idAutor << endl;
        cout << "Nombre: " << _nombre << endl;
        cout << "Apellido: " << _apellido << endl;
        cout << "Nacionalidad: " << _nacionalidad << endl;
        cout << "Estado: Activo" << endl;
        cout << "-----------------------------" << endl;
    }

}
