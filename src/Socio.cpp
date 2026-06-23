#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include "Socio.h"
#include "Menus.h"
#include "rlutil.h"

using namespace rlutil;
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


void Socio::mostrar(int fila){
    if(_estado){
        Fecha f = _fechaNacimiento;
        locate(30, fila + 1);cout << "ID Socio: " << _idSocio << endl;
        locate(30, fila + 2);cout << "Nombre: " << _nombre << endl;
        locate(30, fila + 3);cout << "Apellido: " << _apellido << endl;
        locate(30, fila + 4);cout << "DNI: " << _dni << endl;
        locate(30, fila + 5);cout << "Telefono: " << _telefono << endl;
        locate(30, fila + 6);cout << "Email: " << _email << endl;
        locate(30, fila + 7);cout << "Domicilio: " << _domicilio << endl;
        locate(30, fila + 8);cout << "Fecha nacimiento: " << f.getDia() << "/" << f.getMes() << "/" << f.getAnio() << endl;
        locate(30, fila + 9);cout << "-----------------------------" << endl;
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

    int activo = 0;

    for (int i = 0; i < cantidad; i++){
        if (socios[i].getEstado()) activo++;
    }



    int alto = 10 + activo * 11 + 1, y = 0;
    pantalla("LISTAR SOCIOS", alto);
    for(int i = 0; i < cantidad; i++){
        Socio s = socios[i];
        if (s.getEstado()){
            Fecha f = s.getFechaNacimiento();
            int fila = 10 + y * 11;
            locate(30, fila + 1); cout << "ID: " << s.getIdSocio() << endl;
            locate(30, fila + 2); cout << "Nombre: " << s.getNombre() << endl;
            locate(30, fila + 3); cout << "Apellido: " << s.getApellido() << endl;
            locate(30, fila + 4); cout << "DNI: " << s.getDNI() << endl;
            locate(30, fila + 5); cout << "Domicilio: " << s.getDomicilio() << endl;
            locate(30, fila + 6); cout << "Email: " << s.getEmail() << endl;
            locate(30, fila + 7); cout << "Fecha de Nacimiento: " << f.getDia() << "/" << f.getMes() << "/" << f.getAnio() << endl;
            locate(30, fila + 9); cout << "Telefono: " << s.getTelefono() << endl;
            locate(30, fila + 10); cout << "-----------------------------------" << endl;
            y++;
        }
    }

    delete[] socios;
    pausar(alto + 2);
}

void Socio::consultarPorDNI(){
    int dni;
    pantalla("BUSCAR SOCIOS", 22);
    locate(30, 12);
    cout << "Ingrese DNI a buscar: ";
    cin >> dni;

    int cantidad = contarRegistros();
    int pos = -1;
    for(int i = 0; i < cantidad; i++){
        Socio s = leer(i);
        if(s.getEstado() && s.getDNI() == dni){
            pos = i;
            break;
        }
    }

    if(pos < 0){
        pantalla("RESULTADO DE BUSQUEDA", 14);
        locate(30, 12); cout << "No se encontro socio con ese DNI.";
        pausar(16);
        return;
    }

    Socio s = leer(pos);
    pantalla("RESULTADO DE BUSQUEDA", 22);
    s.mostrar(10);
    pausar(24);
}

void Socio::consultarPorApellido(){
    char apellido[30];
    bool encontro = false;

    pantalla("BUSCAR SOCIOS", 22);
    locate(30, 12);
    cout << "Ingrese apellido a buscar: ";
    cin >> apellido;

    system("cls");

    int cantidad = contarRegistros();

    int cont = 0;
    for(int i = 0; i < cantidad; i++){
        Socio s = leer(i);
        if(s.getEstado() && strcmp(s.getApellido(), apellido) == 0) cont++;
    }

    if(cont == 0){
        pantalla("BUSCAR SOCIOS", 14);
        locate(30, 11); cout << "No se encontraron socios con ese apellido.";
        pausar(16);
        return;
    }

    int alto = 10 + cont * 10 + 1;
    pantalla("SOCIOS POR APELLIDO", alto);

    int j = 0;
    for(int i = 0; i < cantidad; i++){
        Socio s = leer(i);
        if(s.getEstado() && strcmp(s.getApellido(), apellido) == 0){
            s.mostrar(10 + j * 10);
            j++;
        }
    }

    pausar(alto + 2);
}

void Socio::bajaLogica(){
    pantalla("BAJA LOGICA", 22);
    int id;
    locate(30,11);cout << "Ingrese ID de socio a dar de baja: ";
    cin >> id;

    int pos = buscarPorID(id);

    if(pos < 0){
        locate(30, 14);cout << "No existe un socio activo con ese ID." << endl;
        pausar(24);
        return;
    }

    Socio socio = leer(pos);
    socio.setEstado(false);

    if(socio.modificar(pos)){
        locate(30, 14);cout << "Socio dado de baja correctamente." << endl;
    }
    else{
        locate(30, 14);cout << "No se pudo dar de baja el socio." << endl;
    }

    pausar(24);
}
