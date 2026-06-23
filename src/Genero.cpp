#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include "Genero.h"
#include "rlutil.h"
#include "Menus.h"
using namespace std;
using namespace rlutil;
Genero::Genero(){
    _idGenero = 0;
    strcpy(_descripcion, "");
    _estado = true;
}

Genero::Genero(int idGenero, const char* descripcion, bool estado){
    _idGenero = idGenero;
    strcpy(_descripcion, descripcion);
    _estado = estado;
}

int Genero::getIdGenero(){ return _idGenero; }
void Genero::setIdGenero(int idGenero){ _idGenero = idGenero; }

const char* Genero::getDescripcion(){ return _descripcion; }
void Genero::setDescripcion(const char* descripcion){ strcpy(_descripcion, descripcion); }

bool Genero::getEstado(){ return _estado; }
void Genero::setEstado(bool estado){ _estado = estado; }

void Genero::mostrar(int fila){
    if(_estado){
        locate(30, fila + 1);cout << "ID: " << _idGenero << endl;
        locate(30, fila + 2);cout << "Descripcion: " << _descripcion << endl;
        locate(30, fila + 3);cout << "-----------------------------" << endl;
    }
}

bool Genero::guardar(){
    FILE* pArchivo = fopen("Generos.dat", "ab");
    if(pArchivo == NULL){
        return false;
    }

    bool ok = fwrite(this, sizeof(Genero), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

int Genero::contarRegistros(){
    FILE* pArchivo = fopen("Generos.dat", "rb");
    if(pArchivo == NULL){
        return 0;
    }

    fseek(pArchivo, 0, SEEK_END);
    int cantidad = ftell(pArchivo) / sizeof(Genero);
    fclose(pArchivo);

    return cantidad;
}

Genero Genero::leer(int posicion){
    Genero genero;

    FILE* pArchivo = fopen("Generos.dat", "rb");
    if(pArchivo == NULL){
        return genero;
    }

    fseek(pArchivo, posicion * sizeof(Genero), SEEK_SET);
    fread(&genero, sizeof(Genero), 1, pArchivo);
    fclose(pArchivo);

    return genero;
}

int Genero::generarNuevoID(){
    int cantidad = contarRegistros();
    int maximo = 0;

    for(int i = 0; i < cantidad; i++){
        Genero genero = leer(i);
        if(genero.getIdGenero() > maximo){
            maximo = genero.getIdGenero();
        }
    }

    return maximo + 1;
}

void Genero::listar(){
    system("cls");

    int cantidad = contarRegistros();

    for(int i = 0; i < cantidad; i++){
        Genero genero = leer(i);
        genero.mostrar(3);
    }

    system("pause");
}

void Genero::listarOrdenadoAlfabeticamente(){
    system("cls");

    int cantidad = contarRegistros();

    if(cantidad == 0){
        cout << "No hay generos cargados." << endl;
        system("pause");
        return;
    }

    Genero* generos = new Genero[cantidad];

    for(int i = 0; i < cantidad; i++){
        generos[i] = leer(i);
    }
    int y = 0;

    for(int i = 0; i < cantidad - 1; i++){
        for(int j = 0; j < cantidad - 1 - i; j++){
            if(strcmp(generos[j].getDescripcion(), generos[j + 1].getDescripcion()) > 0){
                Genero aux = generos[j];
                generos[j] = generos[j + 1];
                generos[j + 1] = aux;
            }
        }
    }
    int alto = 10 + cantidad * 3 + 1;
    pantalla("LISTAR GENEROS", alto);
    for(int i = 0; i < cantidad; i++){
        generos[i].mostrar(10 + y * 3);
        y++;
    }

    delete[] generos;
    pausar(alto + 2);
}
