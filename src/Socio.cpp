#include <iostream>
#include <cstring>

#include "Socio.h"

using namespace std;

Socio::Socio(){

    _idSocio = 0;

    strcpy(_nombre, "");
    strcpy(_apellido, "");
    strcpy(_telefono, "");
    strcpy(_email, "");
    strcpy(_domicilio, "");

    _dni = 0;

    _estado = true;

}

Socio::Socio(int idSocio,
             const char* nombre,
             const char* apellido,
             int dni,
             const char* telefono,
             const char* email,
             const char* domicilio,
             Fecha fechaNacimiento,
             bool estado){

    _idSocio = idSocio;

    strcpy(_nombre, nombre);
    strcpy(_apellido, apellido);
    strcpy(_telefono, telefono);
    strcpy(_email, email);
    strcpy(_domicilio, domicilio);

    _dni = dni;

    _fechaNacimiento = fechaNacimiento;

    _estado = estado;

}

int Socio::getIdSocio(){

    return _idSocio;

}

void Socio::setIdSocio(int idSocio){

    _idSocio = idSocio;

}

const char* Socio::getNombre(){

    return _nombre;

}

void Socio::setNombre(const char* nombre){

    strcpy(_nombre, nombre);

}

const char* Socio::getApellido(){

    return _apellido;

}

void Socio::setApellido(const char* apellido){

    strcpy(_apellido, apellido);

}

int Socio::getDNI(){

    return _dni;

}

void Socio::setDNI(int dni){

    _dni = dni;

}

const char* Socio::getTelefono(){

    return _telefono;

}

void Socio::setTelefono(const char* telefono){

    strcpy(_telefono, telefono);

}

const char* Socio::getEmail(){

    return _email;

}

void Socio::setEmail(const char* email){

    strcpy(_email, email);

}

const char* Socio::getDomicilio(){

    return _domicilio;

}

void Socio::setDomicilio(const char* domicilio){

    strcpy(_domicilio, domicilio);

}

Fecha Socio::getFechaNacimiento(){

    return _fechaNacimiento;

}

void Socio::setFechaNacimiento(Fecha fechaNacimiento){

    _fechaNacimiento = fechaNacimiento;

}

bool Socio::getEstado(){

    return _estado;

}

void Socio::setEstado(bool estado){

    _estado = estado;

}

void Socio::cargar(){

    cout << "ID Socio: ";
    cin >> _idSocio;

    cout << "Nombre: ";
    cin >> _nombre;

    cout << "Apellido: ";
    cin >> _apellido;

    cout << "DNI: ";
    cin >> _dni;

    cout << "Telefono: ";
    cin >> _telefono;

    cout << "Email: ";
    cin >> _email;

    cout << "Domicilio: ";
    cin >> _domicilio;

    cout << endl;
    cout << "Fecha de nacimiento:" << endl;

    _fechaNacimiento.cargar();

    _estado = true;

}

void Socio::mostrar(){

    if(_estado){

        cout << "ID: " << _idSocio << endl;
        cout << "Nombre: " << _nombre << endl;
        cout << "Apellido: " << _apellido << endl;
        cout << "DNI: " << _dni << endl;
        cout << "Telefono: " << _telefono << endl;
        cout << "Email: " << _email << endl;
        cout << "Domicilio: " << _domicilio << endl;

        cout << "Fecha Nacimiento: ";
        _fechaNacimiento.mostrar();

        cout << endl;
        cout << "----------------------------------" << endl;
    }

}
