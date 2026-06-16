#include <iostream>
#include "Prestamo.h"

using namespace std;

Prestamo::Prestamo(){

    _idPrestamo = 0;
    _idSocio = 0;
    _idLibro = 0;
    _fechaPrestamo = Fecha();
    _fechaVencimiento = Fecha();
    _fechaDevolucion = Fecha();
    _devuelto = false;
    _vencido = false;
    _estado = true;

}

Prestamo::Prestamo(int idPrestamo, int idSocio, int idLibro, Fecha fechaPrestamo, Fecha fechaVencimiento, Fecha fechaDevolucion, bool devuelto, bool vencido, bool estado){

    _idPrestamo = idPrestamo;
    _idSocio = idSocio;
    _idLibro = idLibro;
    _fechaPrestamo = fechaPrestamo;
    _fechaVencimiento = fechaVencimiento;
    _fechaDevolucion = fechaDevolucion;
    _devuelto = devuelto;
    _vencido = vencido;
    _estado = estado;

}

int Prestamo::getIdPrestamo(){
    return _idPrestamo;
}

void Prestamo::setIdPrestamo(int idPrestamo){
    _idPrestamo = idPrestamo;
}

int Prestamo::getIdSocio(){
    return _idSocio;
}

void Prestamo::setIdSocio(int idSocio){
    _idSocio = idSocio;
}

int Prestamo::getIdLibro(){
    return _idLibro;
}

void Prestamo::setIdLibro(int idLibro){
    _idLibro = idLibro;
}

Fecha Prestamo::getFechaPrestamo(){
    return _fechaPrestamo;
}

void Prestamo::setFechaPrestamo(Fecha fechaPrestamo){
    _fechaPrestamo = fechaPrestamo;
}

Fecha Prestamo::getFechaVencimiento(){
    return _fechaVencimiento;
}

void Prestamo::setFechaVencimiento(Fecha fechaVencimiento){
    _fechaVencimiento = fechaVencimiento;
}

Fecha Prestamo::getFechaDevolucion(){
    return _fechaDevolucion;
}

void Prestamo::setFechaDevolucion(Fecha fechaDevolucion){
    _fechaDevolucion = fechaDevolucion;
}

bool Prestamo::getDevuelto(){
    return _devuelto;
}

void Prestamo::setDevuelto(bool devuelto){
    _devuelto = devuelto;
}

bool Prestamo::getVencido(){
    return _vencido;
}

void Prestamo::setVencido(bool vencido){
    _vencido = vencido;
}

bool Prestamo::getEstado(){
    return _estado;
}

void Prestamo::setEstado(bool estado){
    _estado = estado;
}

void Prestamo::cargar(){

    cout << "ID Prestamo: ";
    cin >> _idPrestamo;

    cout << "ID Socio: ";
    cin >> _idSocio;

    cout << "ID Libro: ";
    cin >> _idLibro;

    cout << "Fecha de prestamo:" << endl;
    _fechaPrestamo.cargar();

    cout << "Fecha de vencimiento:" << endl;
    _fechaVencimiento.cargar();

    _fechaDevolucion = Fecha();

    _devuelto = false;
    _vencido = false;
    _estado = true;

}

void Prestamo::mostrar(){

    if(_estado == true){

        cout << "ID Prestamo: " << _idPrestamo << endl;
        cout << "ID Socio: " << _idSocio << endl;
        cout << "ID Libro: " << _idLibro << endl;

        cout << "Fecha de prestamo: ";
        _fechaPrestamo.mostrar();
        cout << endl;

        cout << "Fecha de vencimiento: ";
        _fechaVencimiento.mostrar();
        cout << endl;

        cout << "Fecha de devolucion: ";
        _fechaDevolucion.mostrar();
        cout << endl;

        if(_devuelto){
            cout << "Devuelto: Si" << endl;
        }
        else{
            cout << "Devuelto: No" << endl;
        }

        if(_vencido){
            cout << "Vencido: Si" << endl;
        }
        else{
            cout << "Vencido: No" << endl;
        }

        cout << "Estado: Activo" << endl;
        cout << "-----------------------------" << endl;

    }

}
