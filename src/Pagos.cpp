#include <iostream>
using namespace std;
#include "Pagos.h"
Pagos::Pagos()
{

    _idPago =0;
    _idSocio =0;
    _idCuota =0;
    _fechaPago = Fecha();
    _importe =0.0;
    _estado =0;

}

Pagos::Pagos(int idpago,int idsocio,int idcuota,Fecha fechapago,float importe, bool estado)
{


    _idPago =idpago;
    _idSocio =idsocio;
    _idCuota =idcuota;
    _fechaPago = fechapago;
    _importe =importe;
    _estado =estado;
}

int Pagos::getidpago()
{
    return _idPago;
}
void Pagos::setidpago(int idPago)
{
    _idPago =idPago;
}

int Pagos::getidsocio(){
    return _idSocio;
}

void Pagos::setidsocio(int idsocio){
     _idSocio =idsocio;
}

int Pagos::getidcuota(){
    return _idCuota;
}

void Pagos::setidcuota(int idcuota){
    _idCuota =idcuota;
}

Fecha Pagos::getfechapago(){
    return _fechaPago;
}

void Pagos::setfechapago(Fecha fechapago){
    _fechaPago = fechapago;
}

float Pagos::getimporte(){
    return _importe;
}

void Pagos::setimporte(float importe){
    _importe =importe;
}

bool Pagos::getestado(){
    return _estado;
}

void Pagos::setestado(bool estado){
    _estado =estado;
}

void Pagos::cargar(){

    cout << "ID Pago: ";
    cin >> _idPago;

    cout << "ID Socio: ";
    cin >> _idSocio;

    cout << "ID Cuota: ";
    cin >> _idCuota;

    cout << "Fecha de Pago: ";
    _fechaPago.cargar();

    cout << "Importe: ";
    cin >> _importe;

    _estado = true;

}

void Pagos::mostrar(){

if(_estado){

        cout << "ID Pago: " << _idPago << endl;
        cout << "ID Socio: " << _idSocio << endl;
        cout << "ID Cuota: " << _idCuota << endl;
        cout << "Fecha de Pago: ";
        _fechaPago.mostrar();
        cout << endl;
        cout << "Importe: " << _importe << endl;

        cout << endl;
        cout << "----------------------------------" << endl;
    }
}
