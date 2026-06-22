#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include "Genero.h"

using namespace std;

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

void Genero::cargar(){
    cout << "Descripcion: ";
    cin >> _descripcion;

    _estado = true;
}

void Genero::mostrar(){
    if(_estado){
        cout << "ID: " << _idGenero << endl;
        cout << "Descripcion: " << _descripcion << endl;
        cout << "-----------------------------" << endl;
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
        genero.mostrar();
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

    for(int i = 0; i < cantidad - 1; i++){
        for(int j = 0; j < cantidad - 1 - i; j++){
            if(strcmp(generos[j].getDescripcion(), generos[j + 1].getDescripcion()) > 0){
                Genero aux = generos[j];
                generos[j] = generos[j + 1];
                generos[j + 1] = aux;
            }
        }
    }

    for(int i = 0; i < cantidad; i++){
        generos[i].mostrar();
    }

    delete[] generos;
    system("pause");
}

void Genero::menuGeneros(){
    int opcion;

    while(true){
        system("cls");
        cout << "MENU GENEROS" << endl;
        cout << "1- Cargar genero" << endl;
        cout << "2- Listar generos" << endl;
        cout << "3- Listar generos ordenados alfabeticamente" << endl;
        cout << "0- Volver" << endl;
        cin >> opcion;

        switch(opcion){
        case 1:{
            Genero genero;
            genero.setIdGenero(generarNuevoID());
            genero.cargar();

            if(genero.guardar()){
                cout << "Genero guardado correctamente." << endl;
            }
            else{
                cout << "Error al guardar genero." << endl;
            }

            system("pause");
            break;
        }

        case 2:
            listar();
            break;

        case 3:
            listarOrdenadoAlfabeticamente();
            break;

        case 0:
            return;
        }
    }
}
