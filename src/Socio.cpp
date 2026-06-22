#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include "Socio.h"

using namespace std;

Socio::Socio(){
    _idSocio = 0;
    strcpy(_nombre, "");
    strcpy(_apellido, "");
    _dni = 0;
    strcpy(_telefono, "");
    strcpy(_email, "");
    strcpy(_domicilio, "");
    _fechaNacimiento = Fecha();
    _estado = true;
}

Socio::Socio(int idSocio, const char* nombre, const char* apellido, int dni, const char* telefono, const char* email, const char* domicilio, Fecha fechaNacimiento, bool estado){
    _idSocio = idSocio;
    strcpy(_nombre, nombre);
    strcpy(_apellido, apellido);
    _dni = dni;
    strcpy(_telefono, telefono);
    strcpy(_email, email);
    strcpy(_domicilio, domicilio);
    _fechaNacimiento = fechaNacimiento;
    _estado = estado;
}

int Socio::getIdSocio(){ return _idSocio; }
void Socio::setIdSocio(int idSocio){ _idSocio = idSocio; }

const char* Socio::getNombre(){ return _nombre; }
void Socio::setNombre(const char* nombre){ strcpy(_nombre, nombre); }

const char* Socio::getApellido(){ return _apellido; }
void Socio::setApellido(const char* apellido){ strcpy(_apellido, apellido); }

int Socio::getDNI(){ return _dni; }
void Socio::setDNI(int dni){ _dni = dni; }

const char* Socio::getTelefono(){ return _telefono; }
void Socio::setTelefono(const char* telefono){ strcpy(_telefono, telefono); }

const char* Socio::getEmail(){ return _email; }
void Socio::setEmail(const char* email){ strcpy(_email, email); }

const char* Socio::getDomicilio(){ return _domicilio; }
void Socio::setDomicilio(const char* domicilio){ strcpy(_domicilio, domicilio); }

Fecha Socio::getFechaNacimiento(){ return _fechaNacimiento; }
void Socio::setFechaNacimiento(Fecha fechaNacimiento){ _fechaNacimiento = fechaNacimiento; }

bool Socio::getEstado(){ return _estado; }
void Socio::setEstado(bool estado){ _estado = estado; }

void Socio::cargar(){
    cout << "Nombre: ";
    cin >> _nombre;

    cout << "Apellido: ";
    cin >> _apellido;

    cout << "DNI: ";
    cin >> _dni;

    cout << "Telefono: ";
    cin >> _telefono;

    cout << "Email: ";
    cin >> _email;

    cout << "Domicilio: ";
    cin >> _domicilio;

    cout << "Fecha de nacimiento:" << endl;
    _fechaNacimiento.cargar();

    _estado = true;
}

void Socio::mostrar(){
    if(_estado){
        cout << "ID Socio: " << _idSocio << endl;
        cout << "Nombre: " << _nombre << endl;
        cout << "Apellido: " << _apellido << endl;
        cout << "DNI: " << _dni << endl;
        cout << "Telefono: " << _telefono << endl;
        cout << "Email: " << _email << endl;
        cout << "Domicilio: " << _domicilio << endl;
        cout << "Fecha nacimiento: ";
        _fechaNacimiento.mostrar();
        cout << endl;
        cout << "-----------------------------" << endl;
    }
}

bool Socio::guardar(){
    FILE* pArchivo = fopen("Socios.dat", "ab");
    if(pArchivo == NULL){ return false; }

    bool ok = fwrite(this, sizeof(Socio), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

bool Socio::modificar(int posicion){
    FILE* pArchivo = fopen("Socios.dat", "rb+");
    if(pArchivo == NULL){ return false; }

    fseek(pArchivo, posicion * sizeof(Socio), SEEK_SET);
    bool ok = fwrite(this, sizeof(Socio), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

int Socio::contarRegistros(){
    FILE* pArchivo = fopen("Socios.dat", "rb");
    if(pArchivo == NULL){ return 0; }

    fseek(pArchivo, 0, SEEK_END);
    int cantidad = ftell(pArchivo) / sizeof(Socio);
    fclose(pArchivo);
    return cantidad;
}

Socio Socio::leer(int posicion){
    Socio socio;

    FILE* pArchivo = fopen("Socios.dat", "rb");
    if(pArchivo == NULL){ return socio; }

    fseek(pArchivo, posicion * sizeof(Socio), SEEK_SET);
    fread(&socio, sizeof(Socio), 1, pArchivo);
    fclose(pArchivo);
    return socio;
}

int Socio::buscarPorID(int idSocio){
    int cantidad = contarRegistros();

    for(int i = 0; i < cantidad; i++){
        Socio socio = leer(i);
        if(socio.getIdSocio() == idSocio && socio.getEstado()){
            return i;
        }
    }

    return -1;
}

bool Socio::existe(int idSocio){
    return buscarPorID(idSocio) >= 0;
}

int Socio::generarNuevoID(){
    int cantidad = contarRegistros();
    int maximo = 0;

    for(int i = 0; i < cantidad; i++){
        Socio socio = leer(i);
        if(socio.getIdSocio() > maximo){
            maximo = socio.getIdSocio();
        }
    }

    return maximo + 1;
}

void Socio::listar(){
    system("cls");

    int cantidad = contarRegistros();

    for(int i = 0; i < cantidad; i++){
        Socio socio = leer(i);
        socio.mostrar();
    }

    system("pause");
}


void Socio::listarOrdenadoPorDNI(){
    system("cls");

    int cantidad = contarRegistros();

    if(cantidad == 0){
        cout << "No hay socios cargados." << endl;
        system("pause");
        return;
    }

    Socio* socios = new Socio[cantidad];

    for(int i = 0; i < cantidad; i++){
        socios[i] = leer(i);
    }

    for(int i = 0; i < cantidad - 1; i++){
        for(int j = 0; j < cantidad - 1 - i; j++){
            if(socios[j].getDNI() > socios[j + 1].getDNI()){
                Socio aux = socios[j];
                socios[j] = socios[j + 1];
                socios[j + 1] = aux;
            }
        }
    }

    for(int i = 0; i < cantidad; i++){
        socios[i].mostrar();
    }

    delete[] socios;
    system("pause");
}

void Socio::consultarPorDNI(){
    int dni;
    bool encontro = false;

    cout << "Ingrese DNI a buscar: ";
    cin >> dni;

    system("cls");

    int cantidad = contarRegistros();

    for(int i = 0; i < cantidad; i++){
        Socio socio = leer(i);

        if(socio.getEstado() && socio.getDNI() == dni){
            socio.mostrar();
            encontro = true;
        }
    }

    if(!encontro){
        cout << "No se encontro socio con ese DNI." << endl;
    }

    system("pause");
}

void Socio::consultarPorApellido(){
    char apellido[30];
    bool encontro = false;

    cout << "Ingrese apellido a buscar: ";
    cin >> apellido;

    system("cls");

    int cantidad = contarRegistros();

    for(int i = 0; i < cantidad; i++){
        Socio socio = leer(i);

        if(socio.getEstado() && strcmp(socio.getApellido(), apellido) == 0){
            socio.mostrar();
            encontro = true;
        }
    }

    if(!encontro){
        cout << "No se encontraron socios con ese apellido." << endl;
    }

    system("pause");
}


void Socio::bajaLogica(){
    int id;

    cout << "Ingrese ID de socio a dar de baja: ";
    cin >> id;

    int pos = buscarPorID(id);

    if(pos < 0){
        cout << "No existe un socio activo con ese ID." << endl;
        system("pause");
        return;
    }

    Socio socio = leer(pos);
    socio.setEstado(false);

    if(socio.modificar(pos)){
        cout << "Socio dado de baja correctamente." << endl;
    }
    else{
        cout << "No se pudo dar de baja el socio." << endl;
    }

    system("pause");
}

void Socio::menuSocios(){
    int opcion;

    while(true){
        system("cls");
        cout << "MENU SOCIOS" << endl;
        cout << "1- Cargar socio" << endl;
        cout << "2- Listar socios" << endl;
        cout << "3- Listar socios ordenados por DNI" << endl;
        cout << "4- Consultar socio por DNI" << endl;
        cout << "5- Consultar socio por apellido" << endl;
        cout << "6- Baja logica de socio" << endl;
        cout << "0- Volver" << endl;
        cin >> opcion;

        switch(opcion){
        case 1:{
            Socio socio;
            socio.setIdSocio(generarNuevoID());
            socio.cargar();

            if(socio.guardar()){
                cout << "Socio guardado correctamente." << endl;
            }
            else{
                cout << "Error al guardar socio." << endl;
            }

            system("pause");
            break;
        }

        case 2:
            listar();
            break;

        case 3:
            listarOrdenadoPorDNI();
            break;

        case 4:
            consultarPorDNI();
            break;

        case 5:
            consultarPorApellido();
            break;

        case 6:
            bajaLogica();
            break;

        case 0:
            return;
        }
    }
}
