#include <iostream>
#include <cstring>
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

int Genero::getIdGenero(){

    return _idGenero;

}

void Genero::setIdGenero(int idGenero){

    _idGenero = idGenero;

}

const char* Genero::getDescripcion(){

    return _descripcion;

}

void Genero::setDescripcion(const char* descripcion){

    strcpy(_descripcion, descripcion);

}

bool Genero::getEstado(){

    return _estado;

}

void Genero::setEstado(bool estado){

    _estado = estado;

}

void Genero::cargar(){
    system("cls");
    FILE* pGenero = fopen("Generos.dat", "ab");
    if(pGenero==NULL){
        cout << "No archivo" << endl;
        return;
    }
    cout << "ID Del Genero: ";
    cin >> _idGenero;
    cout << endl;

    cout << "Descripcion: ";
    cin >> _descripcion;
    cout << endl;

    _estado = true;

    fwrite(this, sizeof(Genero), 1, pGenero);
    fclose(pGenero);

    cout << "Genero Agregado!!" << endl;
    system("pause");
}

void Genero::mostrar(){
        system("cls");
    FILE* pGenero = fopen("Generos.dat", "rb");
    if(pGenero==NULL){
        cout << "No archivo" << endl;

        return;
    }
    Genero genero;
    while(fread(&genero, sizeof(Genero), 1, pGenero)==1){
        if(genero._estado==true){
            cout << "ID: " << genero._idGenero << endl;
            cout << "Descripcion: " << genero._descripcion << endl;
            cout << "-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-" << endl;
        }
    }
    fclose(pGenero);
    system("pause");
}

void Genero::mostrarGenerosAlfabeticamente(){
system("cls");
    FILE* pGenero = fopen("Generos.dat", "rb");
    if(pGenero==NULL){
        cout << "No archivo" << endl;

        return;
    }
    fseek(pGenero, 0, SEEK_END);
    int cantidadGeneros = ftell(pGenero)/sizeof(Genero);

    Genero* generos = new Genero[cantidadGeneros];
    rewind(pGenero);
    fread(generos, sizeof(Genero), cantidadGeneros, pGenero);
    fclose(pGenero);

    for(int i = 0; i < cantidadGeneros-1; i++){
        for (int x = 0; x < cantidadGeneros-1-i; x++){
            if(strcmp(generos[x].getDescripcion(),generos[x+1].getDescripcion())>0){
                Genero temp = generos[x];
                generos[x] = generos[x+1];
                generos[x+1] = temp;
            }
        }
    }
    for(int i= 0; i < cantidadGeneros; i++){
        if(generos[i].getEstado() == true){
            cout << "Descripcion: " << generos[i].getDescripcion() << endl;
            cout << "ID: " << generos[i].getIdGenero() << endl;
            cout << "-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-" << endl;


        }
    }
    delete[] generos;
    system("pause");

}

void Genero::menuGeneros(){
    int rta;
    while(true){
        system("cls");
        cout << "Menu Generos" << endl;
        cout << "-.-.-.-.-.-.-.-.-.-" << endl;
        cout << "1- Cargar Generos" << endl;
        cout << "2- Mostrar Generos" << endl;
        cout << "3- Mostrar Generos ordenados Alfabeticamente" << endl;
        cout << endl;
        cout << "0- Volver..." << endl;
        cin >> rta;
        switch(rta){
        case 1:
            Genero::cargar();
            break;
        case 2:
            Genero::mostrar();
            break;
        case 3:
            Genero::mostrarGenerosAlfabeticamente();
            break;
        case 0:
           return;
           break;
        }
    }
    cout<<endl;
    system("pause");

}
