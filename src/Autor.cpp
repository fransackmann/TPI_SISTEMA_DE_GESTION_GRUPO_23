#include <iostream>
#include <cstring>
#include "Autor.h"

using namespace std;

Autor::Autor(){
    _idAutor = 0;
    strcpy(_nombre, "");
    strcpy(_apellido, "");
    strcpy(_nacionalidad, "");
    _estado = true;
}
Autor::Autor(int ID,const char nombre[30],const char apellido[30],const char nacionalidad[30],bool estado){
    _idAutor = ID;
    strcpy(_nombre, nombre);
    strcpy(_apellido, apellido);
    strcpy(_nacionalidad, nacionalidad);
    _estado = estado;
}
int Autor::getAutorID(){
    return _idAutor;
}
const char* Autor::getNombre(){
    return _nombre;
}
const char* Autor::getApellido(){
    return _apellido;
}
const char* Autor::getNacionalidad(){
    return _nacionalidad;
}
bool Autor::getEstado(){
    return _estado;
}
void Autor::setAutorID(int ID){
    _idAutor = ID;
}
void Autor::setNombre(const char nombre[30]){
    strcpy(_nombre, nombre);
}
void Autor::setApellido(const char apellido[30]){
    strcpy(_apellido, apellido);
}
void Autor::setNacionalidad(const char nacionalidad[30]){
    strcpy(_nacionalidad, nacionalidad);
}
void Autor::setEstado(bool estado){
    _estado = estado;
}
void Autor::cargar(){
    system("cls");
    FILE* pAutor = fopen("Autores.dat", "ab");
    if(pAutor==NULL){
        cout << "No archivo" << endl;
        return;
    }
    cout << "ID Del Autor: ";
    cin >> _idAutor;
    cout << endl;

    cout << "Nombre: ";
    cin >> _nombre;
    cout << endl;

    cout << "Apellido: ";
    cin >> _apellido;
    cout << endl;

    cout << "Nacionalidad: ";
    cin >> _nacionalidad;
    cout << endl;

    _estado = true;

    fwrite(this, sizeof(Autor), 1, pAutor);
    fclose(pAutor);

    cout << "Autor Agregado!!" << endl;
    system("pause");
}
void Autor::mostrar(){
    system("cls");
    FILE* pAutor = fopen("Autores.dat", "rb");
    if(pAutor==NULL){
        cout << "No archivo" << endl;

        return;
    }
    Autor autor;
    while(fread(&autor, sizeof(Autor), 1, pAutor)==1){
        if(autor._estado==true){
            cout << "ID: " << autor._idAutor << endl;
            cout << "Nombre: " << autor._nombre << endl;
            cout << "Apellido: " << autor._apellido << endl;
            cout << "Nacionalidad: " << autor._nacionalidad << endl;
            cout << "-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-" << endl;


        }
    }
    fclose(pAutor);
    system("pause");
}
void Autor::mostrarAutoresOrdenadosPorApellido(){
    system("cls");
    FILE* pAutor = fopen("Autores.dat", "rb");
    if(pAutor==NULL){
        cout << "No archivo" << endl;

        return;
    }
    fseek(pAutor, 0, SEEK_END);
    int cantidadAutores = ftell(pAutor)/sizeof(Autor);

    Autor* autores = new Autor[cantidadAutores];
    rewind(pAutor);
    fread(autores, sizeof(Autor), cantidadAutores, pAutor);
    fclose(pAutor);

    for(int i = 0; i < cantidadAutores-1; i++){
        for (int x = 0; x < cantidadAutores-1-i; x++){
            if(strcmp(autores[x].getApellido(),autores[x+1].getApellido())>0){
                Autor temp = autores[x];
                autores[x] = autores[x+1];
                autores[x+1] = temp;
            }
        }
    }
    for(int i= 0; i < cantidadAutores; i++){
        if(autores[i].getEstado() == true){
            cout << "Apellido: " << autores[i].getApellido() << endl;
            cout << "Nombre: " << autores[i].getNombre() << endl;
            cout << "ID: " << autores[i].getAutorID() << endl;
            cout << "Nacionalidad: " << _nacionalidad << endl;
            cout << "-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-" << endl;


        }
    }
    delete[] autores;
    system("pause");
}
void Autor::menuAutores(){
    int rta;
    while(true){
        system("cls");
        cout << "Menu Autores" << endl;
        cout << "-.-.-.-.-.-.-.-.-.-" << endl;
        cout << "1- Cargar Autores" << endl;
        cout << "2- Mostrar Autores" << endl;
        cout << "3- Mostrar Autores por Apellido" << endl;
        cout << endl;
        cout << "0- Volver..." << endl;
        cin >> rta;
        switch(rta){
        case 1:
            Autor::cargar();
            break;
        case 2:
            Autor::mostrar();
            break;
        case 3:
            Autor::mostrarAutoresOrdenadosPorApellido();
            break;
        case 0:
           return;
           break;
        }
    }
    cout<<endl;
    system("pause");

}
