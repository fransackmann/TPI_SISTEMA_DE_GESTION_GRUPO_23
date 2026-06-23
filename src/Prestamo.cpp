#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "Prestamo.h"
#include "Socio.h"
#include "Libro.h"
#include "Menus.h"
#include "rlutil.h"
using namespace rlutil;
using namespace std;

int fechaAEntero(Fecha fecha){
    return fecha.getAnio() * 10000 + fecha.getMes() * 100 + fecha.getDia();
}


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

int Prestamo::getIdPrestamo(){ return _idPrestamo; }
void Prestamo::setIdPrestamo(int idPrestamo){ _idPrestamo = idPrestamo; }

int Prestamo::getIdSocio(){ return _idSocio; }
void Prestamo::setIdSocio(int idSocio){ _idSocio = idSocio; }

int Prestamo::getIdLibro(){ return _idLibro; }
void Prestamo::setIdLibro(int idLibro){ _idLibro = idLibro; }

Fecha Prestamo::getFechaPrestamo(){ return _fechaPrestamo; }
void Prestamo::setFechaPrestamo(Fecha fechaPrestamo){ _fechaPrestamo = fechaPrestamo; }

Fecha Prestamo::getFechaVencimiento(){ return _fechaVencimiento; }
void Prestamo::setFechaVencimiento(Fecha fechaVencimiento){ _fechaVencimiento = fechaVencimiento; }

Fecha Prestamo::getFechaDevolucion(){ return _fechaDevolucion; }
void Prestamo::setFechaDevolucion(Fecha fechaDevolucion){ _fechaDevolucion = fechaDevolucion; }

bool Prestamo::getDevuelto(){ return _devuelto; }
void Prestamo::setDevuelto(bool devuelto){ _devuelto = devuelto; }

bool Prestamo::getVencido(){ return _vencido; }
void Prestamo::setVencido(bool vencido){ _vencido = vencido; }

bool Prestamo::getEstado(){ return _estado; }
void Prestamo::setEstado(bool estado){ _estado = estado; }

void Prestamo::mostrar(int fila){
    if(_estado){
        locate(30, fila + 1);
        cout << "ID Prestamo: " << _idPrestamo;
        locate(30, fila + 2);
        cout << "ID Socio: " << _idSocio;
        locate(30, fila + 3);
        cout << "ID Libro: " << _idLibro;
        locate(30, fila + 4);
        cout << "Fecha de prestamo: " << _fechaPrestamo.getDia() << "/" << _fechaPrestamo.getMes() << "/" << _fechaPrestamo.getAnio();
        locate(30, fila + 5);
        cout << "Fecha de vencimiento: " << _fechaVencimiento.getDia() << "/" << _fechaVencimiento.getMes() << "/" << _fechaVencimiento.getAnio();
        locate(30, fila + 6);
        cout << "Devuelto: " << (_devuelto ? "Si" : "No");
        locate(30, fila + 7);
        cout << "Vencido: " << (_vencido ? "Si" : "No");
        locate(30, fila + 8);
        cout << "-----------------------------------";
    }
}

bool Prestamo::guardar(){
    FILE* pArchivo = fopen("Prestamos.dat", "ab");
    if(pArchivo == NULL){ return false; }

    bool ok = fwrite(this, sizeof(Prestamo), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

bool Prestamo::modificar(int posicion){
    FILE* pArchivo = fopen("Prestamos.dat", "rb+");
    if(pArchivo == NULL){ return false; }

    fseek(pArchivo, posicion * sizeof(Prestamo), SEEK_SET);
    bool ok = fwrite(this, sizeof(Prestamo), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

int Prestamo::contarRegistros(){
    FILE* pArchivo = fopen("Prestamos.dat", "rb");
    if(pArchivo == NULL){ return 0; }

    fseek(pArchivo, 0, SEEK_END);
    int cantidad = ftell(pArchivo) / sizeof(Prestamo);
    fclose(pArchivo);
    return cantidad;
}

Prestamo Prestamo::leer(int posicion){
    Prestamo prestamo;

    FILE* pArchivo = fopen("Prestamos.dat", "rb");
    if(pArchivo == NULL){ return prestamo; }

    fseek(pArchivo, posicion * sizeof(Prestamo), SEEK_SET);
    fread(&prestamo, sizeof(Prestamo), 1, pArchivo);
    fclose(pArchivo);
    return prestamo;
}

int Prestamo::buscarPorID(int idPrestamo){
    int cantidad = contarRegistros();

    for(int i = 0; i < cantidad; i++){
        Prestamo prestamo = leer(i);
        if(prestamo.getIdPrestamo() == idPrestamo && prestamo.getEstado()){
            return i;
        }
    }

    return -1;
}

int Prestamo::generarNuevoID(){
    int cantidad = contarRegistros();
    int maximo = 0;

    for(int i = 0; i < cantidad; i++){
        Prestamo prestamo = leer(i);
        if(prestamo.getIdPrestamo() > maximo){
            maximo = prestamo.getIdPrestamo();
        }
    }

    return maximo + 1;
}

void Prestamo::listar(){
    int cantidad = contarRegistros();
    int alto = 10 + cantidad * 9 + 1;
    pantalla("LISTAR PRESTAMOS", alto);
    int j = 0;
    for(int i = 0; i < cantidad; i++){
        Prestamo prestamo = leer(i);
        if (prestamo.getEstado()){
            prestamo.mostrar(10 + j * 9);
            j++;
        }
    }

    pausar(alto + 2);
}

void Prestamo::listarActivos(){
    int cantidad = contarRegistros();

    int cont = 0;
    for(int i= 0; i< cantidad; i++){
        Prestamo p = leer(i);
        if(p.getEstado() && !p.getDevuelto()) cont++;
    }

    int alto = 10 + cont * 9 + 1;
    pantalla("LISTAR ACTIVOS", alto);
    int j = 0;
    for(int i= 0; i< cantidad; i++){
        Prestamo p = leer(i);
        if(p.getEstado() && !p.getDevuelto()){
            p.mostrar(10 + j * 9);
            j++;
        }
    }
    pausar(alto + 2);
}

void Prestamo::listarVencidos(){
    int cantidad = contarRegistros();

    int cont = 0;
    for(int i= 0; i< cantidad; i++){
        Prestamo p = leer(i);
        if(p.getEstado() && p.getVencido()) cont++;
    }

    int alto = 10 + cont * 9 + 1;
    pantalla("LISTAR VENCIDOS", alto);
    int j = 0;
    for(int i= 0; i< cantidad; i++){
        Prestamo p = leer(i);
        if(p.getEstado() && p.getVencido()){
            p.mostrar(10 + j * 9);
            j++;
        }
    }
    pausar(alto + 2);
}

void Prestamo::listarOrdenadosPorFecha(){
    int cantidad = contarRegistros();

    if(cantidad == 0){
        cout << "No hay prestamos cargados." << endl;
        system("pause");
        return;
    }

    Prestamo* prestamos = new Prestamo[cantidad];

    for(int i = 0; i < cantidad; i++){
        prestamos[i] = leer(i);
    }

    int y = 0;

    for(int i = 0; i < cantidad - 1; i++){
        for(int j = 0; j < cantidad - 1 - i; j++){
            if(fechaAEntero(prestamos[j].getFechaPrestamo()) > fechaAEntero(prestamos[j + 1].getFechaPrestamo())){
                Prestamo aux = prestamos[j];
                prestamos[j] = prestamos[j + 1];
                prestamos[j + 1] = aux;
            }
        }
    }
    int alto = 10 + cantidad * 9 + 1;
    pantalla("LISTAR PRESTAMOS", alto);
   for(int i = 0; i < cantidad; i++){
        Prestamo prestamo = prestamos[i];
        if (prestamo.getEstado()){
            prestamo.mostrar(10 + y * 9);
            y++;
        }

}
    delete[] prestamos;
    pausar(alto + 2);
}

void Prestamo::listarPorRangoFechas(){
    Fecha desde, hasta;
    pantalla("PRESTAMOS POR RANGO", 22);
    locate(30, 11); cout << "Fecha desde:";
    desde = pedirFecha(54, 11);
    locate(30, 15); cout << "Fecha hasta:";
    hasta = pedirFecha(54, 15);

    int desdeInt = fechaAEntero(desde);
    int hastaInt = fechaAEntero(hasta);

    int cantidad = contarRegistros();

    int coincidencias = 0;
    for(int i = 0; i < cantidad; i++){
        Prestamo p = leer(i);
        int f = fechaAEntero(p.getFechaPrestamo());
        if(p.getEstado() && f >= desdeInt && f <= hastaInt) coincidencias++;
    }

    if(coincidencias == 0){
        pantalla("PRESTAMOS POR RANGO", 14);
        locate(30, 12); cout << "No hay prestamos en ese rango.";
        pausar(16);
        return;
    }

    int alto = 10 + coincidencias * 9 + 1;
    pantalla("PRESTAMOS POR RANGO", alto);

    int j = 0;
    for(int i = 0; i < cantidad; i++){
        Prestamo p = leer(i);
        int f = fechaAEntero(p.getFechaPrestamo());
        if(p.getEstado() && f >= desdeInt && f <= hastaInt){
            p.mostrar(10 + j * 9);
            j++;
        }
    }

    pausar(alto + 2);
}

void Prestamo::consultarPorSocio(){
    int idSocio;
    pantalla("PRESTAMOS POR SOCIO", 22);
    locate(30, 12); cout << "Ingrese ID Socio: ";
    cin >> idSocio;

    int cantidad = contarRegistros();

    int coincidencias = 0;
    for(int i = 0; i < cantidad; i++){
        Prestamo p = leer(i);
        if(p.getEstado() && p.getIdSocio() == idSocio) coincidencias++;
    }

    if(coincidencias == 0){
        pantalla("PRESTAMOS POR SOCIO", 14);
        locate(30, 12); cout << "No se encontraron prestamos para ese socio.";
        pausar(16);
        return;
    }

    int alto = 10 + coincidencias * 9 + 1;
    pantalla("PRESTAMOS POR SOCIO", alto);

    int j = 0;
    for(int i = 0; i < cantidad; i++){
        Prestamo p = leer(i);
        if(p.getEstado() && p.getIdSocio() == idSocio){
            p.mostrar(10 + j * 9);
            j++;
        }
    }

    pausar(alto + 2);
}

void Prestamo::consultarPorLibro(){
    int idLibro;
    pantalla("PRESTAMOS POR LIBRO", 22);
    locate(30, 12); cout << "Ingrese ID Libro: ";
    cin >> idLibro;

    int cantidad = contarRegistros();

    int coincidencias = 0;
    for(int i = 0; i < cantidad; i++){
        Prestamo p = leer(i);
        if(p.getEstado() && p.getIdLibro() == idLibro) coincidencias++;
    }

    if(coincidencias == 0){
        pantalla("PRESTAMOS POR LIBRO", 14);
        locate(30, 12); cout << "No se encontraron prestamos para ese libro.";
        pausar(16);
        return;
    }

    int alto = 10 + coincidencias * 9 + 1;
    pantalla("PRESTAMOS POR LIBRO", alto);

    int j = 0;
    for(int i = 0; i < cantidad; i++){
        Prestamo p = leer(i);
        if(p.getEstado() && p.getIdLibro() == idLibro){
            p.mostrar(10 + j * 9);
            j++;
        }
    }

    pausar(alto + 2);
}

void Prestamo::consultarPorEstado(){
    int opcion;
    pantalla("PRESTAMOS POR ESTADO", 22);
    locate(30, 11); cout << "Estado a consultar:";
    locate(30, 12); cout << "1 - Activos";
    locate(30, 13); cout << "2 - Devueltos";
    locate(30, 14); cout << "3 - Vencidos";
    locate(30, 16); cout << "Opcion: ";
    cin >> opcion;

    int cantidad = contarRegistros();

    int coincidencias = 0;
    for(int i = 0; i < cantidad; i++){
        Prestamo p = leer(i);
        if(p.getEstado()){
            if((opcion == 1 && !p.getDevuelto()) ||
               (opcion == 2 && p.getDevuelto()) ||
               (opcion == 3 && p.getVencido())) coincidencias++;
        }
    }

    if(coincidencias == 0){
        pantalla("PRESTAMOS POR ESTADO", 14);
        locate(30, 12); cout << "No se encontraron prestamos para ese estado.";
        pausar(16);
        return;
    }

    int alto = 10 + coincidencias * 9 + 1;
    pantalla("PRESTAMOS POR ESTADO", alto);

    int j = 0;
    for(int i = 0; i < cantidad; i++){
        Prestamo p = leer(i);
        if(p.getEstado()){
            bool coincide = (opcion == 1 && !p.getDevuelto()) ||
                            (opcion == 2 && p.getDevuelto()) ||
                            (opcion == 3 && p.getVencido());
            if(coincide){
                p.mostrar(10 + j * 9);
                j++;
            }
        }
    }

    pausar(alto + 2);
}

void Prestamo::marcarPrestamoVencido(){
    int idPrestamo;

    locate(30, 11);cout << "Ingrese ID de prestamo a marcar vencido: ";
    cin >> idPrestamo;

    int pos = buscarPorID(idPrestamo);

    if(pos < 0){
        locate(30, 20); cout << "No existe un prestamo activo con ese ID." << endl;
        pausar(24);
        return;
    }

    Prestamo prestamo = leer(pos);
    prestamo.setVencido(true);

    if(prestamo.modificar(pos)){
        locate(30, 20); cout << "Prestamo marcado como vencido." << endl;
    }
    else{
       locate(30, 20);  cout << "No se pudo modificar el prestamo." << endl;
    }

    pausar(24);
}
