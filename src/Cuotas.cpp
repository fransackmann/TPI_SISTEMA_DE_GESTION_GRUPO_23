#include <iostream>
#include <cstring>
using namespace std;
#include "Cuotas.h"
#include "Fecha.h"

Cuotas::Cuotas()
{
    _idCuota=0;
    _idSocio = 0;
    _mes = Fecha();
    _anio = Fecha();
    _fechacobro = Fecha();
    _importe = 0.0;
    _pagada = 0;
    _estado= 1;

}


Cuotas::Cuotas(int idCuota,int idSocio,Fecha mes,Fecha anio,Fecha fechaCobro,float importe,bool pagada,bool estado)
{
    _idCuota = idCuota;
    _idSocio = idSocio;
    _mes = mes;
    _anio = anio;
    _fechacobro = fechaCobro;
    _importe = importe;
    _pagada = pagada;
    _estado = estado;
}

int Cuotas::getidcuota()
{
    return _idCuota;
}
void Cuotas::setidcouta(int idCuota)
{
    _idCuota = idCuota;
}

int Cuotas::getidsocio()
{
    return _idSocio;
}
void Cuotas::setidsocio(int idSocio)
{
    _idSocio = idSocio;
}

Fecha Cuotas::getmes()
{
    return _mes;
}
void Cuotas::setmes(Fecha mes)
{
    _mes = mes;
}

Fecha Cuotas::getanio()
{
    return _anio;
}
void Cuotas::setanio(Fecha anio)
{
    _anio = anio;
}

Fecha Cuotas::getfechacobro()
{
    return _fechacobro;
}
void Cuotas::setfechacobro(Fecha fechacobro)
{
    _fechacobro = fechacobro;
}

float Cuotas::getimporte()
{
    return _importe;
}
void Cuotas::setimporte(float importe)
{
    _importe = importe;
}

bool Cuotas::getpagada()
{
    return _pagada;
}
void Cuotas::setpagada(bool pagada)
{
    _pagada = pagada;
}

bool Cuotas::getestado()
{
   return _estado;
}
void Cuotas::setestado(bool estado)
{
    _estado = estado;
}

void Cuotas::cargar(){
    cout << "Id de cuota: " << endl;
    cin >> _idCuota;
    cout << "Id de socio: " << endl;
    cin >> _idSocio;
    int dia=0,mes=0,anio=0;
    cout << "mes: " << endl;
    cin >> mes;
    _mes.cargar(dia,mes,anio);
    cout << "anio: " << endl;
    cin >> anio;
    _anio.cargar(dia,dia,anio);
    cout << "fecha de cobro: " << endl;
    cin >> dia,mes,anio;
    _fechacobro.cargar(dia,mes,anio);
    cout << "importe: " << endl;
    cin >> _importe;
    cout << "pagada: " << endl;
    cin >> _pagada;
    cout << "estado: " << endl;
    cin >> _estado;
}
void Cuotas::mostrar(){
    cout << "Id de cuota " << _idCuota << endl;
    cout << "Id de socio " << _idSocio << endl;
    cout << "mes ";
    _mes.mostrar();
    cout << "anio ";
    _anio.mostrar();
    cout << "fecha de cobro ";
    _fechacobro.mostrar();
    cout << "importe " << _importe << endl;
    cout << "pagada " << _pagada << endl;
    cout << "estado " << _estado << endl;
    cout << "______________________ " << endl;


}
