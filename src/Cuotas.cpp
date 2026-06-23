#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "Cuotas.h"
#include "Socio.h"
#include "Menus.h"
#include "rlutil.h"

using namespace std;
using namespace rlutil;

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

int Cuotas::getIdCuota(){ return _idCuota; }
void Cuotas::setIdCuota(int idCuota){ _idCuota = idCuota; }

int Cuotas::getIdSocio(){ return _idSocio; }
void Cuotas::setIdSocio(int idSocio){ _idSocio = idSocio; }

int Cuotas::getMes(){ return _mes; }
void Cuotas::setMes(int mes){ if(mes >= 1 && mes <= 12){ _mes = mes; } }

int Cuotas::getAnio(){ return _anio; }
void Cuotas::setAnio(int anio){ if(anio > 0){ _anio = anio; } }

Fecha Cuotas::getFechaCobro(){ return _fechaCobro; }
void Cuotas::setFechaCobro(Fecha fechaCobro){ _fechaCobro = fechaCobro; }

float Cuotas::getImporte(){ return _importe; }
void Cuotas::setImporte(float importe){ if(importe >= 0){ _importe = importe; } }

bool Cuotas::getPagada(){ return _pagada; }
void Cuotas::setPagada(bool pagada){ _pagada = pagada; }

bool Cuotas::getEstado(){ return _estado; }
void Cuotas::setEstado(bool estado){ _estado = estado; }

void Cuotas::marcarPagada(){
    _pagada = true;
}

void Cuotas::mostrar(int fila){
    if(_estado){
        locate(30, fila + 1); cout << "ID Cuota: " << _idCuota;
        locate(30, fila + 2); cout << "ID Socio: " << _idSocio;
        locate(30, fila + 3); cout << "Mes: " << _mes;
        locate(30, fila + 4); cout << "Anio: " << _anio;
        locate(30, fila + 5); cout << "Fecha de cobro: " << _fechaCobro.getDia() << "/" << _fechaCobro.getMes() << "/" << _fechaCobro.getAnio();
        locate(30, fila + 6); cout << "Importe: " << _importe;
        locate(30, fila + 7); cout << "Pagada: " << (_pagada ? "Si" : "No");
        locate(30, fila + 8); cout << "-----------------------------------";
    }
}

bool Cuotas::guardar(){
    FILE* pArchivo = fopen("Cuotas.dat", "ab");
    if(pArchivo == NULL){
        return false;
    }

    bool ok = fwrite(this, sizeof(Cuotas), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

bool Cuotas::modificar(int posicion){
    FILE* pArchivo = fopen("Cuotas.dat", "rb+");
    if(pArchivo == NULL){
        return false;
    }

    fseek(pArchivo, posicion * sizeof(Cuotas), SEEK_SET);
    bool ok = fwrite(this, sizeof(Cuotas), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

int Cuotas::contarRegistros(){
    FILE* pArchivo = fopen("Cuotas.dat", "rb");
    if(pArchivo == NULL){
        return 0;
    }

    fseek(pArchivo, 0, SEEK_END);
    int cantidad = ftell(pArchivo) / sizeof(Cuotas);
    fclose(pArchivo);

    return cantidad;
}

Cuotas Cuotas::leer(int posicion){
    Cuotas cuota;

    FILE* pArchivo = fopen("Cuotas.dat", "rb");
    if(pArchivo == NULL){
        return cuota;
    }

    fseek(pArchivo, posicion * sizeof(Cuotas), SEEK_SET);
    fread(&cuota, sizeof(Cuotas), 1, pArchivo);
    fclose(pArchivo);

    return cuota;
}

int Cuotas::buscarPorID(int idCuota){
    int cantidad = contarRegistros();

    for(int i = 0; i < cantidad; i++){
        Cuotas cuota = leer(i);

        if(cuota.getIdCuota() == idCuota && cuota.getEstado()){
            return i;
        }
    }

    return -1;
}

int Cuotas::generarNuevoID(){
    int cantidad = contarRegistros();
    int maximo = 0;

    for(int i = 0; i < cantidad; i++){
        Cuotas cuota = leer(i);
        if(cuota.getIdCuota() > maximo){
            maximo = cuota.getIdCuota();
        }
    }

    return maximo + 1;
}

void Cuotas::listar(){
    int cantidad = contarRegistros();

    int coincidencias = 0;
    for(int i = 0; i < cantidad; i++)
        if(leer(i).getEstado()) coincidencias++;

    int alto = 10 + coincidencias * 9 + 1;
    pantalla("LISTAR CUOTAS", alto);

    int j = 0;
    for(int i = 0; i < cantidad; i++){
        Cuotas cuota = leer(i);
        if(cuota.getEstado()){
            cuota.mostrar(10 + j * 9);
            j++;
        }
    }

    pausar(alto + 2);
}


void Cuotas::listarPagadas(){
    int cantidad = contarRegistros();

    int coincidencias = 0;
    for(int i = 0; i < cantidad; i++){
        Cuotas cuota = leer(i);
        if(cuota.getEstado() && cuota.getPagada()) coincidencias++;
    }

    if(coincidencias == 0){
        pantalla("CUOTAS PAGADAS", 14);
        locate(30, 12); cout << "No hay cuotas pagadas.";
        pausar(16);
        return;
    }

    int alto = 10 + coincidencias * 9 + 1;
    pantalla("CUOTAS PAGADAS", alto);

    int j = 0;
    for(int i = 0; i < cantidad; i++){
        Cuotas cuota = leer(i);
        if(cuota.getEstado() && cuota.getPagada()){
            cuota.mostrar(10 + j * 9);
            j++;
        }
    }

    pausar(alto + 2);
}

void Cuotas::listarPendientes(){
    int cantidad = contarRegistros();

    int coincidencias = 0;
    for(int i = 0; i < cantidad; i++){
        Cuotas cuota = leer(i);
        if(cuota.getEstado() && !cuota.getPagada()) coincidencias++;
    }

    if(coincidencias == 0){
        pantalla("CUOTAS PENDIENTES", 14);
        locate(30, 12); cout << "No hay cuotas pendientes.";
        pausar(16);
        return;
    }

    int alto = 10 + coincidencias * 9 + 1;
    pantalla("CUOTAS PENDIENTES", alto);

    int j = 0;
    for(int i = 0; i < cantidad; i++){
        Cuotas cuota = leer(i);
        if(cuota.getEstado() && !cuota.getPagada()){
            cuota.mostrar(10 + j * 9);
            j++;
        }
    }

    pausar(alto + 2);
}

void Cuotas::listarPendientesPorSocio(){
    int idSocio;
    pantalla("PENDIENTES POR SOCIO", 22);
    locate(30, 12); cout << "Ingrese ID Socio: ";
    cin >> idSocio;

    int cantidad = contarRegistros();

    int coincidencias = 0;
    for(int i = 0; i < cantidad; i++){
        Cuotas cuota = leer(i);
        if(cuota.getEstado() && cuota.getIdSocio() == idSocio && !cuota.getPagada()) coincidencias++;
    }

    if(coincidencias == 0){
        pantalla("PENDIENTES POR SOCIO", 14);
        locate(30, 12); cout << "No hay cuotas pendientes para ese socio.";
        pausar(16);
        return;
    }

    int alto = 10 + coincidencias * 9 + 1;
    pantalla("PENDIENTES POR SOCIO", alto);

    int j = 0;
    for(int i = 0; i < cantidad; i++){
        Cuotas cuota = leer(i);
        if(cuota.getEstado() && cuota.getIdSocio() == idSocio && !cuota.getPagada()){
            cuota.mostrar(10 + j * 9);
            j++;
        }
    }

    pausar(alto + 2);
}
