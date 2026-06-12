#include <iostream>
#include <cstring>
#include "Genero.h"

using namespace std;

Genero::Genero(){

    _idGenero = 0;
    strcpy(_descripcion, "");
    _estado = true;

}

Genero::Genero(int idGenero, const char* descripcion, bool estado){

    _idGenero = idGenero;
    strcpy(_descripcion, descripcion);
    _estado = estado;

}

int Genero::getIdGenero(){

    return _idGenero;

}

void Genero::setIdGenero(int idGenero){

    _idGenero = idGenero;

}

const char* Genero::getDescripcion(){

    return _descripcion;

}

void Genero::setDescripcion(const char* descripcion){

    strcpy(_descripcion, descripcion);

}

bool Genero::getEstado(){

    return _estado;

}

void Genero::setEstado(bool estado){

    _estado = estado;

}

void Genero::cargar(){

    cout << "ID del genero: ";
    cin >> _idGenero;

    cout << "Descripcion: ";
    cin >> _descripcion;

    _estado = true;

}

void Genero::mostrar(){

    if(_estado == true){

        cout << "ID Genero: " << _idGenero << endl;
        cout << "Descripcion: " << _descripcion << endl;
        cout << "Estado: Activo" << endl;
        cout << "-----------------------------" << endl;

    }

}
