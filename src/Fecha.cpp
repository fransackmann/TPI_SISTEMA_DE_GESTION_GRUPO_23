#include <iostream>
using namespace std;
#include "Fecha.h"


Fecha::Fecha(){

    _dia = 1;
    _mes = 1;
    _anio = 2026;

}
int Fecha::getDia(){

    return _dia;

}

void Fecha::setDia(int dia){

    if(dia >= 1 && dia <= 31){
        _dia = dia;

    }

}

int Fecha::getMes(){

    return _mes;

}

void Fecha::setMes(int mes){

    if(mes >= 1 && mes <= 12){

        _mes = mes;

    }

}

int Fecha::getAnio(){

    return _anio;

}

void Fecha::setAnio(int anio){

    if(anio > 0){

        _anio = anio;

    }

}

void Fecha::cargar(){

    int dia, mes, anio;
    cout << "Dia: ";
    cin >> dia;

    cout << "Mes: ";
    cin >> mes;

    cout << "Anio: ";
    cin >> anio;

    setDia(dia);
    setMes(mes);
    setAnio(anio);

}

void Fecha::mostrar(){

    cout << _dia << "/" << _mes << "/" << _anio;

}
