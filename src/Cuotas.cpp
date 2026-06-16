#include <iostream>
#include "Cuotas.h"

using namespace std;

Cuotas::Cuotas(){

    _idCuota = 0;
    _idSocio = 0;
    _mes = 1;
    _anio = 2026;
    _fechaCobro = Fecha();
    _importe = 0.0;
    _pagada = false;
    _estado = true;

}

Cuotas::Cuotas(int idCuota, int idSocio, int mes, int anio, Fecha fechaCobro, float importe, bool pagada, bool estado){

    _idCuota = idCuota;
    _idSocio = idSocio;
    _mes = mes;
    _anio = anio;
    _fechaCobro = fechaCobro;
    _importe = importe;
    _pagada = pagada;
    _estado = estado;

}

int Cuotas::getIdCuota(){

    return _idCuota;

}

void Cuotas::setIdCuota(int idCuota){

    _idCuota = idCuota;

}

int Cuotas::getIdSocio(){

    return _idSocio;

}

void Cuotas::setIdSocio(int idSocio){

    _idSocio = idSocio;

}

int Cuotas::getMes(){

    return _mes;

}

void Cuotas::setMes(int mes){

    if(mes >= 1 && mes <= 12){
        _mes = mes;
    }

}

int Cuotas::getAnio(){

    return _anio;

}

void Cuotas::setAnio(int anio){

    if(anio > 0){
        _anio = anio;
    }

}

Fecha Cuotas::getFechaCobro(){

    return _fechaCobro;

}

void Cuotas::setFechaCobro(Fecha fechaCobro){

    _fechaCobro = fechaCobro;

}

float Cuotas::getImporte(){

    return _importe;

}

void Cuotas::setImporte(float importe){

    if(importe >= 0){
        _importe = importe;
    }

}

bool Cuotas::getPagada(){

    return _pagada;

}

void Cuotas::setPagada(bool pagada){

    _pagada = pagada;

}

bool Cuotas::getEstado(){

    return _estado;

}

void Cuotas::setEstado(bool estado){

    _estado = estado;

}

void Cuotas::cargar(){

    int mes, anio;
    float importe;
    int pagada;

    cout << "ID de cuota: ";
    cin >> _idCuota;

    cout << "ID de socio: ";
    cin >> _idSocio;

    cout << "Mes: ";
    cin >> mes;
    setMes(mes);

    cout << "Anio: ";
    cin >> anio;
    setAnio(anio);

    cout << "Fecha de cobro: " << endl;
    _fechaCobro.cargar();

    cout << "Importe: ";
    cin >> importe;
    setImporte(importe);

    cout << "Pagada? 1-Si / 0-No: ";
    cin >> pagada;
    _pagada = pagada;

    _estado = true;

}

void Cuotas::mostrar(){

    if(_estado == true){

        cout << "ID de cuota: " << _idCuota << endl;
        cout << "ID de socio: " << _idSocio << endl;
        cout << "Mes: " << _mes << endl;
        cout << "Anio: " << _anio << endl;

        cout << "Fecha de cobro: ";
        _fechaCobro.mostrar();
        cout << endl;

        cout << "Importe: " << _importe << endl;

        if(_pagada){
            cout << "Pagada: Si" << endl;
        }
        else{
            cout << "Pagada: No" << endl;
        }

        cout << "Estado: Activo" << endl;
        cout << "-----------------------------" << endl;
    }

}
