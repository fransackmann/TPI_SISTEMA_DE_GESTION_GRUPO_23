#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "Pagos.h"
#include "Socio.h"
#include "Cuotas.h"

using namespace std;

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

void Pagos::cargar(){
    Socio::listar();
    cout << "ID Socio: ";
    cin >> _idSocio;

    Cuotas::listar();
    cout << "ID Cuota: ";
    cin >> _idCuota;

    cout << "Fecha de pago:" << endl;
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
        cout << "Fecha de pago: ";
        _fechaPago.mostrar();
        cout << endl;
        cout << "Importe: " << _importe << endl;
        cout << "-----------------------------" << endl;
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

void Pagos::registrarPago(){
    int idSocio, idCuota;
    float importe;
    Fecha fechaPago;

    Socio::listar();
    cout << "ID Socio: ";
    cin >> idSocio;

    if(!Socio::existe(idSocio)){
        cout << "No existe un socio activo con ese ID." << endl;
        system("pause");
        return;
    }

    Cuotas::listar();
    cout << "ID Cuota: ";
    cin >> idCuota;

    int posCuota = Cuotas::buscarPorID(idCuota);

    if(posCuota < 0){
        cout << "No existe una cuota activa con ese ID." << endl;
        system("pause");
        return;
    }

    Cuotas cuota = Cuotas::leer(posCuota);

    if(cuota.getPagada()){
        cout << "Esa cuota ya esta pagada." << endl;
        system("pause");
        return;
    }

    if(cuota.getIdSocio() != idSocio){
        cout << "La cuota no corresponde al socio seleccionado." << endl;
        system("pause");
        return;
    }

    cout << "Fecha de pago:" << endl;
    fechaPago.cargar();

    cout << "Importe: ";
    cin >> importe;

    Pagos pago;
    pago.setIdPago(generarNuevoID());
    pago.setIdSocio(idSocio);
    pago.setIdCuota(idCuota);
    pago.setFechaPago(fechaPago);
    pago.setImporte(importe);
    pago.setEstado(true);

    cuota.marcarPagada();

    if(pago.guardar() && cuota.modificar(posCuota)){
        cout << "Pago registrado correctamente y cuota marcada como pagada." << endl;
    }
    else{
        cout << "No se pudo registrar el pago." << endl;
    }

    system("pause");
}

void Pagos::listar(){
    system("cls");

    int cantidad = contarRegistros();

    for(int i = 0; i < cantidad; i++){
        Pagos pago = leer(i);
        pago.mostrar();
    }

    system("pause");
}

void Pagos::listarPorSocio(){
    int idSocio;

    cout << "Ingrese ID Socio: ";
    cin >> idSocio;

    system("cls");

    int cantidad = contarRegistros();
    float total = 0;

    for(int i = 0; i < cantidad; i++){
        Pagos pago = leer(i);

        if(pago.getEstado() && pago.getIdSocio() == idSocio){
            pago.mostrar();
            total += pago.getImporte();
        }
    }

    cout << "Total pagado por el socio: " << total << endl;
    system("pause");
}


void Pagos::pagosPorMes(){
    int mes, anio;
    int cantidadPagos = 0;
    float total = 0;

    cout << "Ingrese mes: ";
    cin >> mes;

    cout << "Ingrese anio: ";
    cin >> anio;

    system("cls");

    int cantidad = contarRegistros();

    for(int i = 0; i < cantidad; i++){
        Pagos pago = leer(i);

        if(pago.getEstado() && pago.getFechaPago().getMes() == mes && pago.getFechaPago().getAnio() == anio){
            pago.mostrar();
            cantidadPagos++;
            total += pago.getImporte();
        }
    }

    cout << "Cantidad de pagos del mes: " << cantidadPagos << endl;
    cout << "Total recaudado del mes: " << total << endl;

    system("pause");
}


void Pagos::menuPagos(){
    int opcion;

    while(true){
        system("cls");
        cout << "MENU PAGOS" << endl;
        cout << "1- Registrar pago" << endl;
        cout << "2- Listar pagos" << endl;
        cout << "3- Listar pagos por socio" << endl;
        cout << "4- Pagos realizados por mes" << endl;
        cout << "0- Volver" << endl;
        cin >> opcion;

        switch(opcion){
        case 1:
            registrarPago();
            break;

        case 2:
            listar();
            break;

        case 3:
            listarPorSocio();
            break;

        case 4:
            pagosPorMes();
            break;

        case 0:
            return;
        }
    }
}
