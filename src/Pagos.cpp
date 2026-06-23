#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "Pagos.h"
#include "Socio.h"
#include "Cuotas.h"
#include "Menus.h"
#include "rlutil.h"

using namespace std;
using namespace rlutil;

Pagos::Pagos(){
    _idPago = 0;
    _idSocio = 0;
    _idCuota = 0;
    _fechaPago = Fecha();
    _importe = 0.0;
    _estado = true;
}

Pagos::Pagos(int idPago, int idSocio, int idCuota, Fecha fechaPago, float importe, bool estado){
    _idPago = idPago;
    _idSocio = idSocio;
    _idCuota = idCuota;
    _fechaPago = fechaPago;
    _importe = importe;
    _estado = estado;
}

int Pagos::getIdPago(){ return _idPago; }
void Pagos::setIdPago(int idPago){ _idPago = idPago; }

int Pagos::getIdSocio(){ return _idSocio; }
void Pagos::setIdSocio(int idSocio){ _idSocio = idSocio; }

int Pagos::getIdCuota(){ return _idCuota; }
void Pagos::setIdCuota(int idCuota){ _idCuota = idCuota; }

Fecha Pagos::getFechaPago(){ return _fechaPago; }
void Pagos::setFechaPago(Fecha fechaPago){ _fechaPago = fechaPago; }

float Pagos::getImporte(){ return _importe; }
void Pagos::setImporte(float importe){ _importe = importe; }

bool Pagos::getEstado(){ return _estado; }
void Pagos::setEstado(bool estado){ _estado = estado; }

void Pagos::mostrar(int fila){
    if(_estado){
        locate(30, fila + 1); cout << "ID Pago: " << _idPago;
        locate(30, fila + 2); cout << "ID Socio: " << _idSocio;
        locate(30, fila + 3); cout << "ID Cuota: " << _idCuota;
        locate(30, fila + 4); cout << "Fecha de pago: " << _fechaPago.getDia() << "/" << _fechaPago.getMes() << "/" << _fechaPago.getAnio();
        locate(30, fila + 5); cout << "Importe: " << _importe;
        locate(30, fila + 6); cout << "-----------------------------------";
    }
}

bool Pagos::guardar(){
    FILE* pArchivo = fopen("Pagos.dat", "ab");
    if(pArchivo == NULL){ return false; }

    bool ok = fwrite(this, sizeof(Pagos), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

int Pagos::contarRegistros(){
    FILE* pArchivo = fopen("Pagos.dat", "rb");
    if(pArchivo == NULL){ return 0; }

    fseek(pArchivo, 0, SEEK_END);
    int cantidad = ftell(pArchivo) / sizeof(Pagos);
    fclose(pArchivo);
    return cantidad;
}

Pagos Pagos::leer(int posicion){
    Pagos pago;

    FILE* pArchivo = fopen("Pagos.dat", "rb");
    if(pArchivo == NULL){ return pago; }

    fseek(pArchivo, posicion * sizeof(Pagos), SEEK_SET);
    fread(&pago, sizeof(Pagos), 1, pArchivo);
    fclose(pArchivo);
    return pago;
}

int Pagos::generarNuevoID(){
    int cantidad = contarRegistros();
    int maximo = 0;

    for(int i = 0; i < cantidad; i++){
        Pagos pago = leer(i);
        if(pago.getIdPago() > maximo){
            maximo = pago.getIdPago();
        }
    }

    return maximo + 1;
}

void Pagos::listar(){
    int cantidad = contarRegistros();

    int coincidencias = 0;
    for(int i = 0; i < cantidad; i++)
        if(leer(i).getEstado()) coincidencias++;

    int alto = 10 + coincidencias * 7 + 1;
    pantalla("LISTAR PAGOS", alto);

    int j = 0;
    for(int i = 0; i < cantidad; i++){
        Pagos pago = leer(i);
        if(pago.getEstado()){
            pago.mostrar(10 + j * 7);
            j++;
        }
    }

    pausar(alto + 2);
}


void Pagos::listarOrdenadosPorSocio(){
    int cantidad = contarRegistros();

    if(cantidad == 0){
        pantalla("PAGOS ORDENADOS POR SOCIO", 14);
        locate(30, 12); cout << "No hay pagos cargados.";
        pausar(16);
        return;
    }

    Pagos* pagos = new Pagos[cantidad];

    for(int i = 0; i < cantidad; i++){
        pagos[i] = leer(i);
    }

    for(int i = 0; i < cantidad - 1; i++){
        for(int j = 0; j < cantidad - 1 - i; j++){
            if(pagos[j].getIdSocio() > pagos[j + 1].getIdSocio()){
                Pagos aux = pagos[j];
                pagos[j] = pagos[j + 1];
                pagos[j + 1] = aux;
            }
        }
    }

    int alto = 10 + cantidad * 7 + 1;
    pantalla("PAGOS ORDENADOS POR SOCIO", alto);

    int j = 0;
    for(int i = 0; i < cantidad; i++){
        if(pagos[i].getEstado()){
            pagos[i].mostrar(10 + j * 7);
            j++;
        }
    }

    delete[] pagos;
    pausar(alto + 2);
}

void Pagos::listarPorSocio(){
    int idSocio;
    pantalla("PAGOS POR SOCIO", 22);
    locate(30, 12); cout << "Ingrese ID Socio: ";
    cin >> idSocio;

    int cantidad = contarRegistros();

    int coincidencias = 0;
    for(int i = 0; i < cantidad; i++){
        Pagos pago = leer(i);
        if(pago.getEstado() && pago.getIdSocio() == idSocio) coincidencias++;
    }

    int alto = 10 + coincidencias * 7 + 3;
    pantalla("PAGOS POR SOCIO", alto);

    int j = 0;
    float total = 0;
    for(int i = 0; i < cantidad; i++){
        Pagos pago = leer(i);
        if(pago.getEstado() && pago.getIdSocio() == idSocio){
            pago.mostrar(10 + j * 7);
            total += pago.getImporte();
            j++;
        }
    }

    locate(30, 10 + coincidencias * 7 + 1);
    cout << "Total pagado por el socio: " << total;
    pausar(alto + 2);
}


void Pagos::pagosPorMes(){
    int mes, anio;
    pantalla("PAGOS POR MES", 22);
    locate(30, 12); cout << "Ingrese mes: ";
    cin >> mes;
    locate(30, 13); cout << "Ingrese anio: ";
    cin >> anio;

    int cantidad = contarRegistros();

    int coincidencias = 0;
    for(int i = 0; i < cantidad; i++){
        Pagos pago = leer(i);
        if(pago.getEstado() && pago.getFechaPago().getMes() == mes && pago.getFechaPago().getAnio() == anio) coincidencias++;
    }

    int alto = 10 + coincidencias * 7 + 4;
    pantalla("PAGOS POR MES", alto);

    int j = 0;
    float total = 0;
    for(int i = 0; i < cantidad; i++){
        Pagos pago = leer(i);
        if(pago.getEstado() && pago.getFechaPago().getMes() == mes && pago.getFechaPago().getAnio() == anio){
            pago.mostrar(10 + j * 7);
            total += pago.getImporte();
            j++;
        }
    }

    locate(30, 10 + coincidencias * 7 + 1);
    cout << "Cantidad de pagos del mes: " << j;
    locate(30, 10 + coincidencias * 7 + 2);
    cout << "Total recaudado del mes: " << total;
    pausar(alto + 2);
}
