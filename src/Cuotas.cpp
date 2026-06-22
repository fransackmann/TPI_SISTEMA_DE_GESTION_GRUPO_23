#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "Cuotas.h"
#include "Socio.h"

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

void Cuotas::cargar(){
    int mes, anio, pagada;
    float importe;

    Socio::listar();
    cout << "ID Socio: ";
    cin >> _idSocio;

    cout << "Mes: ";
    cin >> mes;
    setMes(mes);

    cout << "Anio: ";
    cin >> anio;
    setAnio(anio);

    cout << "Fecha de cobro:" << endl;
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
    if(_estado){
        cout << "ID Cuota: " << _idCuota << endl;
        cout << "ID Socio: " << _idSocio << endl;
        cout << "Mes: " << _mes << endl;
        cout << "Anio: " << _anio << endl;
        cout << "Fecha de cobro: ";
        _fechaCobro.mostrar();
        cout << endl;
        cout << "Importe: " << _importe << endl;
        cout << "Pagada: " << (_pagada ? "Si" : "No") << endl;
        cout << "-----------------------------" << endl;
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
    system("cls");

    int cantidad = contarRegistros();

    for(int i = 0; i < cantidad; i++){
        Cuotas cuota = leer(i);
        cuota.mostrar();
    }

    system("pause");
}

void Cuotas::listarPendientesPorSocio(){
    int idSocio;

    cout << "Ingrese ID Socio: ";
    cin >> idSocio;

    system("cls");

    int cantidad = contarRegistros();

    for(int i = 0; i < cantidad; i++){
        Cuotas cuota = leer(i);

        if(cuota.getEstado() && cuota.getIdSocio() == idSocio && !cuota.getPagada()){
            cuota.mostrar();
        }
    }

    system("pause");
}

void Cuotas::menuCuotas(){
    int opcion;

    while(true){
        system("cls");
        cout << "MENU CUOTAS" << endl;
        cout << "1- Cargar cuota" << endl;
        cout << "2- Listar cuotas" << endl;
        cout << "3- Cuotas pendientes por socio" << endl;
        cout << "0- Volver" << endl;
        cin >> opcion;

        switch(opcion){
        case 1:{
            Cuotas cuota;
            cuota.setIdCuota(generarNuevoID());
            cuota.cargar();

            if(cuota.guardar()){
                cout << "Cuota guardada correctamente." << endl;
            }
            else{
                cout << "Error al guardar cuota." << endl;
            }

            system("pause");
            break;
        }

        case 2:
            listar();
            break;

        case 3:
            listarPendientesPorSocio();
            break;

        case 0:
            return;
        }
    }
}
