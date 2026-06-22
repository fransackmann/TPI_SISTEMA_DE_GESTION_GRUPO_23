#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include "Autor.h"

using namespace std;

Autor::Autor(){
    _idAutor = 0;
    strcpy(_nombre, "");
    strcpy(_apellido, "");
    strcpy(_nacionalidad, "");
    _estado = true;
}

Autor::Autor(int idAutor, const char* nombre, const char* apellido, const char* nacionalidad, bool estado){
    _idAutor = idAutor;
    strcpy(_nombre, nombre);
    strcpy(_apellido, apellido);
    strcpy(_nacionalidad, nacionalidad);
    _estado = estado;
}

int Autor::getAutorID(){ return _idAutor; }
void Autor::setAutorID(int idAutor){ _idAutor = idAutor; }

const char* Autor::getNombre(){ return _nombre; }
void Autor::setNombre(const char* nombre){ strcpy(_nombre, nombre); }

const char* Autor::getApellido(){ return _apellido; }
void Autor::setApellido(const char* apellido){ strcpy(_apellido, apellido); }

const char* Autor::getNacionalidad(){ return _nacionalidad; }
void Autor::setNacionalidad(const char* nacionalidad){ strcpy(_nacionalidad, nacionalidad); }

bool Autor::getEstado(){ return _estado; }
void Autor::setEstado(bool estado){ _estado = estado; }

void Autor::cargar(){
    cout << "Nombre: ";
    cin >> _nombre;

    cout << "Apellido: ";
    cin >> _apellido;

    cout << "Nacionalidad: ";
    cin >> _nacionalidad;

    _estado = true;
}

void Autor::mostrar(){
    if(_estado){
        cout << "ID: " << _idAutor << endl;
        cout << "Nombre: " << _nombre << endl;
        cout << "Apellido: " << _apellido << endl;
        cout << "Nacionalidad: " << _nacionalidad << endl;
        cout << "-----------------------------" << endl;
    }
}

bool Autor::guardar(){
    FILE* pArchivo = fopen("Autores.dat", "ab");
    if(pArchivo == NULL){
        return false;
    }

    bool ok = fwrite(this, sizeof(Autor), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

int Autor::contarRegistros(){
    FILE* pArchivo = fopen("Autores.dat", "rb");
    if(pArchivo == NULL){
        return 0;
    }

    fseek(pArchivo, 0, SEEK_END);
    int cantidad = ftell(pArchivo) / sizeof(Autor);
    fclose(pArchivo);

    return cantidad;
}

Autor Autor::leer(int posicion){
    Autor autor;

    FILE* pArchivo = fopen("Autores.dat", "rb");
    if(pArchivo == NULL){
        return autor;
    }

    fseek(pArchivo, posicion * sizeof(Autor), SEEK_SET);
    fread(&autor, sizeof(Autor), 1, pArchivo);
    fclose(pArchivo);

    return autor;
}

int Autor::generarNuevoID(){
    int cantidad = contarRegistros();
    int maximo = 0;

    for(int i = 0; i < cantidad; i++){
        Autor autor = leer(i);
        if(autor.getAutorID() > maximo){
            maximo = autor.getAutorID();
        }
    }

    return maximo + 1;
}

void Autor::listar(){
    system("cls");

    int cantidad = contarRegistros();

    for(int i = 0; i < cantidad; i++){
        Autor autor = leer(i);
        autor.mostrar();
    }

    system("pause");
}

void Autor::listarOrdenadoPorApellido(){
    system("cls");

    int cantidad = contarRegistros();

    if(cantidad == 0){
        cout << "No hay autores cargados." << endl;
        system("pause");
        return;
    }

    Autor* autores = new Autor[cantidad];

    for(int i = 0; i < cantidad; i++){
        autores[i] = leer(i);
    }

    for(int i = 0; i < cantidad - 1; i++){
        for(int j = 0; j < cantidad - 1 - i; j++){
            if(strcmp(autores[j].getApellido(), autores[j + 1].getApellido()) > 0){
                Autor aux = autores[j];
                autores[j] = autores[j + 1];
                autores[j + 1] = aux;
            }
        }
    }

    for(int i = 0; i < cantidad; i++){
        autores[i].mostrar();
    }

    delete[] autores;
    system("pause");
}

void Autor::menuAutores(){
    int opcion;

    while(true){
        system("cls");
        cout << "MENU AUTORES" << endl;
        cout << "1- Cargar autor" << endl;
        cout << "2- Listar autores" << endl;
        cout << "3- Listar autores ordenados por apellido" << endl;
        cout << "0- Volver" << endl;
        cin >> opcion;

        switch(opcion){
        case 1:{
            Autor autor;
            autor.setAutorID(generarNuevoID());
            autor.cargar();

            if(autor.guardar()){
                cout << "Autor guardado correctamente." << endl;
            }
            else{
                cout << "Error al guardar autor." << endl;
            }

            system("pause");
            break;
        }

        case 2:
            listar();
            break;

        case 3:
            listarOrdenadoPorApellido();
            break;

        case 0:
            return;
        }
    }
}
