#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "Prestamo.h"
#include "Socio.h"
#include "Libro.h"

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

void Prestamo::cargar(){
    Socio::listar();
    cout << "ID Socio: ";
    cin >> _idSocio;

    Libro::listar();
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
    if(_estado){
        cout << "ID Prestamo: " << _idPrestamo << endl;
        cout << "ID Socio: " << _idSocio << endl;
        cout << "ID Libro: " << _idLibro << endl;

        cout << "Fecha de prestamo: ";
        _fechaPrestamo.mostrar();
        cout << endl;

        cout << "Fecha de vencimiento: ";
        _fechaVencimiento.mostrar();
        cout << endl;

        if(_devuelto){
            cout << "Fecha de devolucion: ";
            _fechaDevolucion.mostrar();
            cout << endl;
        }

        cout << "Devuelto: " << (_devuelto ? "Si" : "No") << endl;
        cout << "Vencido: " << (_vencido ? "Si" : "No") << endl;
        cout << "-----------------------------" << endl;
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

void Prestamo::registrarPrestamo(){
    Prestamo prestamo;
    int idSocio, idLibro;

    Socio::listar();
    cout << "ID Socio: ";
    cin >> idSocio;

    if(!Socio::existe(idSocio)){
        cout << "No existe un socio activo con ese ID." << endl;
        system("pause");
        return;
    }

    Libro::listar();
    cout << "ID Libro: ";
    cin >> idLibro;

    int posLibro = Libro::buscarPorID(idLibro);

    if(posLibro < 0){
        cout << "No existe un libro activo con ese ID." << endl;
        system("pause");
        return;
    }

    Libro libro = Libro::leer(posLibro);

    if(libro.getStockDisponible() <= 0){
        cout << "No hay stock disponible para prestar este libro." << endl;
        system("pause");
        return;
    }

    prestamo.setIdPrestamo(generarNuevoID());
    prestamo.setIdSocio(idSocio);
    prestamo.setIdLibro(idLibro);

    Fecha fechaPrestamo;
    Fecha fechaVencimiento;

    cout << "Fecha de prestamo:" << endl;
    fechaPrestamo.cargar();

    cout << "Fecha de vencimiento:" << endl;
    fechaVencimiento.cargar();

    prestamo.setFechaPrestamo(fechaPrestamo);
    prestamo.setFechaVencimiento(fechaVencimiento);
    prestamo.setDevuelto(false);
    prestamo.setVencido(false);
    prestamo.setEstado(true);

    libro.prestarEjemplar();

    if(prestamo.guardar() && libro.modificar(posLibro)){
        cout << "Prestamo registrado correctamente." << endl;
    }
    else{
        cout << "No se pudo registrar el prestamo." << endl;
    }

    system("pause");
}

void Prestamo::devolverPrestamo(){
    int idPrestamo;

    cout << "Ingrese ID de prestamo a devolver: ";
    cin >> idPrestamo;

    int posPrestamo = buscarPorID(idPrestamo);

    if(posPrestamo < 0){
        cout << "No existe un prestamo activo con ese ID." << endl;
        system("pause");
        return;
    }

    Prestamo prestamo = leer(posPrestamo);

    if(prestamo.getDevuelto()){
        cout << "Ese prestamo ya fue devuelto." << endl;
        system("pause");
        return;
    }

    int posLibro = Libro::buscarPorID(prestamo.getIdLibro());

    if(posLibro < 0){
        cout << "No se encontro el libro asociado al prestamo." << endl;
        system("pause");
        return;
    }

    Libro libro = Libro::leer(posLibro);

    Fecha fechaDevolucion;
    cout << "Fecha de devolucion:" << endl;
    fechaDevolucion.cargar();

    prestamo.setFechaDevolucion(fechaDevolucion);
    prestamo.setDevuelto(true);

    libro.devolverEjemplar();

    if(prestamo.modificar(posPrestamo) && libro.modificar(posLibro)){
        cout << "Devolucion registrada correctamente." << endl;
    }
    else{
        cout << "No se pudo registrar la devolucion." << endl;
    }

    system("pause");
}

void Prestamo::listar(){
    system("cls");

    int cantidad = contarRegistros();

    for(int i = 0; i < cantidad; i++){
        Prestamo prestamo = leer(i);
        prestamo.mostrar();
    }

    system("pause");
}

void Prestamo::listarActivos(){
    system("cls");

    int cantidad = contarRegistros();

    for(int i = 0; i < cantidad; i++){
        Prestamo prestamo = leer(i);

        if(prestamo.getEstado() && !prestamo.getDevuelto()){
            prestamo.mostrar();
        }
    }

    system("pause");
}


void Prestamo::listarVencidos(){
    system("cls");

    int cantidad = contarRegistros();

    for(int i = 0; i < cantidad; i++){
        Prestamo prestamo = leer(i);

        if(prestamo.getEstado() && prestamo.getVencido()){
            prestamo.mostrar();
        }
    }

    system("pause");
}

void Prestamo::listarOrdenadosPorFecha(){
    system("cls");

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

    for(int i = 0; i < cantidad - 1; i++){
        for(int j = 0; j < cantidad - 1 - i; j++){
            if(fechaAEntero(prestamos[j].getFechaPrestamo()) > fechaAEntero(prestamos[j + 1].getFechaPrestamo())){
                Prestamo aux = prestamos[j];
                prestamos[j] = prestamos[j + 1];
                prestamos[j + 1] = aux;
            }
        }
    }

    for(int i = 0; i < cantidad; i++){
        prestamos[i].mostrar();
    }

    delete[] prestamos;
    system("pause");
}

void Prestamo::listarPorRangoFechas(){
    Fecha desde, hasta;

    cout << "Ingrese fecha desde:" << endl;
    desde.cargar();

    cout << "Ingrese fecha hasta:" << endl;
    hasta.cargar();

    int desdeInt = fechaAEntero(desde);
    int hastaInt = fechaAEntero(hasta);

    system("cls");

    int cantidad = contarRegistros();

    for(int i = 0; i < cantidad; i++){
        Prestamo prestamo = leer(i);
        int fechaPrestamo = fechaAEntero(prestamo.getFechaPrestamo());

        if(prestamo.getEstado() && fechaPrestamo >= desdeInt && fechaPrestamo <= hastaInt){
            prestamo.mostrar();
        }
    }

    system("pause");
}

void Prestamo::marcarPrestamoVencido(){
    int idPrestamo;

    cout << "Ingrese ID de prestamo a marcar vencido: ";
    cin >> idPrestamo;

    int pos = buscarPorID(idPrestamo);

    if(pos < 0){
        cout << "No existe un prestamo activo con ese ID." << endl;
        system("pause");
        return;
    }

    Prestamo prestamo = leer(pos);
    prestamo.setVencido(true);

    if(prestamo.modificar(pos)){
        cout << "Prestamo marcado como vencido." << endl;
    }
    else{
        cout << "No se pudo modificar el prestamo." << endl;
    }

    system("pause");
}


void Prestamo::menuPrestamos(){
    int opcion;

    while(true){
        system("cls");
        cout << "MENU PRESTAMOS" << endl;
        cout << "1- Registrar prestamo" << endl;
        cout << "2- Listar prestamos" << endl;
        cout << "3- Listar prestamos activos" << endl;
        cout << "4- Listar prestamos vencidos" << endl;
        cout << "5- Listar prestamos ordenados por fecha" << endl;
        cout << "6- Prestamos por rango de fechas" << endl;
        cout << "7- Marcar prestamo vencido" << endl;
        cout << "8- Devolver prestamo" << endl;
        cout << "0- Volver" << endl;
        cin >> opcion;

        switch(opcion){
        case 1:
            registrarPrestamo();
            break;

        case 2:
            listar();
            break;

        case 3:
            listarActivos();
            break;

        case 4:
            listarVencidos();
            break;

        case 5:
            listarOrdenadosPorFecha();
            break;

        case 6:
            listarPorRangoFechas();
            break;

        case 7:
            marcarPrestamoVencido();
            break;

        case 8:
            devolverPrestamo();
            break;

        case 0:
            return;
        }
    }
}
