#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include "Libro.h"
#include "Autor.h"
#include "Genero.h"

using namespace std;

Libro::Libro(){
    _idLibro = 0;
    strcpy(_isbn, "");
    strcpy(_titulo, "");
    _idAutor = 0;
    _idGenero = 0;
    strcpy(_editorial, "");
    _anioPublicacion = Fecha();
    _stockTotal = 0;
    _stockDisponible = 0;
    _estado = true;
}

Libro::Libro(int idLibro, const char* isbn, const char* titulo, int idAutor, int idGenero, const char* editorial, Fecha anioPublicacion, int stockTotal, int stockDisponible, bool estado){
    _idLibro = idLibro;
    strcpy(_isbn, isbn);
    strcpy(_titulo, titulo);
    _idAutor = idAutor;
    _idGenero = idGenero;
    strcpy(_editorial, editorial);
    _anioPublicacion = anioPublicacion;
    _stockTotal = stockTotal;
    _stockDisponible = stockDisponible;
    _estado = estado;
}

int Libro::getIdLibro(){ return _idLibro; }
void Libro::setIdLibro(int idLibro){ _idLibro = idLibro; }

const char* Libro::getIsbn(){ return _isbn; }
void Libro::setIsbn(const char* isbn){ strcpy(_isbn, isbn); }

const char* Libro::getTitulo(){ return _titulo; }
void Libro::setTitulo(const char* titulo){ strcpy(_titulo, titulo); }

int Libro::getIdAutor(){ return _idAutor; }
void Libro::setIdAutor(int idAutor){ _idAutor = idAutor; }

int Libro::getIdGenero(){ return _idGenero; }
void Libro::setIdGenero(int idGenero){ _idGenero = idGenero; }

const char* Libro::getEditorial(){ return _editorial; }
void Libro::setEditorial(const char* editorial){ strcpy(_editorial, editorial); }

Fecha Libro::getAnioPublicacion(){ return _anioPublicacion; }
void Libro::setAnioPublicacion(Fecha anioPublicacion){ _anioPublicacion = anioPublicacion; }

int Libro::getStockTotal(){ return _stockTotal; }
void Libro::setStockTotal(int stockTotal){ _stockTotal = stockTotal; }

int Libro::getStockDisponible(){ return _stockDisponible; }
void Libro::setStockDisponible(int stockDisponible){ _stockDisponible = stockDisponible; }

bool Libro::getEstado(){ return _estado; }
void Libro::setEstado(bool estado){ _estado = estado; }

void Libro::prestarEjemplar(){
    if(_stockDisponible > 0){
        _stockDisponible--;
    }
}

void Libro::devolverEjemplar(){
    if(_stockDisponible < _stockTotal){
        _stockDisponible++;
    }
}

void Libro::cargar(){
    cout << "ISBN: ";
    cin >> _isbn;

    cout << "Titulo: ";
    cin >> _titulo;

    Autor::listar();
    cout << "ID Autor: ";
    cin >> _idAutor;

    Genero::listar();
    cout << "ID Genero: ";
    cin >> _idGenero;

    cout << "Editorial: ";
    cin >> _editorial;

    cout << "Fecha / anio de publicacion:" << endl;
    _anioPublicacion.cargar();

    cout << "Stock total: ";
    cin >> _stockTotal;

    _stockDisponible = _stockTotal;
    _estado = true;
}

void Libro::mostrar(){
    if(_estado){
        cout << "ID Libro: " << _idLibro << endl;
        cout << "ISBN: " << _isbn << endl;
        cout << "Titulo: " << _titulo << endl;
        cout << "ID Autor: " << _idAutor << endl;
        cout << "ID Genero: " << _idGenero << endl;
        cout << "Editorial: " << _editorial << endl;
        cout << "Fecha / anio de publicacion: ";
        _anioPublicacion.mostrar();
        cout << endl;
        cout << "Stock total: " << _stockTotal << endl;
        cout << "Stock disponible: " << _stockDisponible << endl;
        cout << "-----------------------------" << endl;
    }
}

bool Libro::guardar(){
    FILE* pArchivo = fopen("Libros.dat", "ab");
    if(pArchivo == NULL){ return false; }

    bool ok = fwrite(this, sizeof(Libro), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

bool Libro::modificar(int posicion){
    FILE* pArchivo = fopen("Libros.dat", "rb+");
    if(pArchivo == NULL){ return false; }

    fseek(pArchivo, posicion * sizeof(Libro), SEEK_SET);
    bool ok = fwrite(this, sizeof(Libro), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

int Libro::contarRegistros(){
    FILE* pArchivo = fopen("Libros.dat", "rb");
    if(pArchivo == NULL){ return 0; }

    fseek(pArchivo, 0, SEEK_END);
    int cantidad = ftell(pArchivo) / sizeof(Libro);
    fclose(pArchivo);
    return cantidad;
}

Libro Libro::leer(int posicion){
    Libro libro;

    FILE* pArchivo = fopen("Libros.dat", "rb");
    if(pArchivo == NULL){ return libro; }

    fseek(pArchivo, posicion * sizeof(Libro), SEEK_SET);
    fread(&libro, sizeof(Libro), 1, pArchivo);
    fclose(pArchivo);
    return libro;
}

int Libro::buscarPorID(int idLibro){
    int cantidad = contarRegistros();

    for(int i = 0; i < cantidad; i++){
        Libro libro = leer(i);
        if(libro.getIdLibro() == idLibro && libro.getEstado()){
            return i;
        }
    }

    return -1;
}

bool Libro::existe(int idLibro){
    return buscarPorID(idLibro) >= 0;
}

int Libro::generarNuevoID(){
    int cantidad = contarRegistros();
    int maximo = 0;

    for(int i = 0; i < cantidad; i++){
        Libro libro = leer(i);
        if(libro.getIdLibro() > maximo){
            maximo = libro.getIdLibro();
        }
    }

    return maximo + 1;
}

void Libro::listar(){
    system("cls");

    int cantidad = contarRegistros();

    for(int i = 0; i < cantidad; i++){
        Libro libro = leer(i);
        libro.mostrar();
    }

    system("pause");
}

void Libro::listarPorAutor(){
    int idAutor;

    cout << "Ingrese ID Autor: ";
    cin >> idAutor;

    system("cls");

    int cantidad = contarRegistros();

    for(int i = 0; i < cantidad; i++){
        Libro libro = leer(i);

        if(libro.getEstado() && libro.getIdAutor() == idAutor){
            libro.mostrar();
        }
    }

    system("pause");
}

void Libro::listarPorGenero(){
    int idGenero;

    cout << "Ingrese ID Genero: ";
    cin >> idGenero;

    system("cls");

    int cantidad = contarRegistros();

    for(int i = 0; i < cantidad; i++){
        Libro libro = leer(i);

        if(libro.getEstado() && libro.getIdGenero() == idGenero){
            libro.mostrar();
        }
    }

    system("pause");
}


void Libro::consultarPorTitulo(){
    char titulo[50];
    bool encontro = false;

    cout << "Ingrese titulo a buscar: ";
    cin >> titulo;

    system("cls");

    int cantidad = contarRegistros();

    for(int i = 0; i < cantidad; i++){
        Libro libro = leer(i);

        if(libro.getEstado() && strcmp(libro.getTitulo(), titulo) == 0){
            libro.mostrar();
            encontro = true;
        }
    }

    if(!encontro){
        cout << "No se encontro libro con ese titulo." << endl;
    }

    system("pause");
}

void Libro::consultarPorISBN(){
    char isbn[20];
    bool encontro = false;

    cout << "Ingrese ISBN a buscar: ";
    cin >> isbn;

    system("cls");

    int cantidad = contarRegistros();

    for(int i = 0; i < cantidad; i++){
        Libro libro = leer(i);

        if(libro.getEstado() && strcmp(libro.getIsbn(), isbn) == 0){
            libro.mostrar();
            encontro = true;
        }
    }

    if(!encontro){
        cout << "No se encontro libro con ese ISBN." << endl;
    }

    system("pause");
}


void Libro::bajaLogica(){
    int id;

    cout << "Ingrese ID de libro a dar de baja: ";
    cin >> id;

    int pos = buscarPorID(id);

    if(pos < 0){
        cout << "No existe un libro activo con ese ID." << endl;
        system("pause");
        return;
    }

    Libro libro = leer(pos);
    libro.setEstado(false);

    if(libro.modificar(pos)){
        cout << "Libro dado de baja correctamente." << endl;
    }
    else{
        cout << "No se pudo dar de baja el libro." << endl;
    }

    system("pause");
}

void Libro::modificarLibro(){
    int id;

    cout << "Ingrese ID de libro a modificar: ";
    cin >> id;

    int pos = buscarPorID(id);

    if(pos < 0){
        cout << "No existe un libro activo con ese ID." << endl;
        system("pause");
        return;
    }

    Libro libro = leer(pos);

    cout << "Cargue los nuevos datos del libro:" << endl;
    libro.cargar();
    libro.setIdLibro(id);

    if(libro.modificar(pos)){
        cout << "Libro modificado correctamente." << endl;
    }
    else{
        cout << "No se pudo modificar el libro." << endl;
    }

    system("pause");
}

void Libro::menuLibros(){
    int opcion;

    while(true){
        system("cls");
        cout << "MENU LIBROS" << endl;
        cout << "1- Cargar libro" << endl;
        cout << "2- Listar libros" << endl;
        cout << "3- Listar libros por autor" << endl;
        cout << "4- Listar libros por genero" << endl;
        cout << "5- Consultar libro por titulo" << endl;
        cout << "6- Consultar libro por ISBN" << endl;
        cout << "7- Modificar libro" << endl;
        cout << "8- Baja logica de libro" << endl;
        cout << "9- Menu autores" << endl;
        cout << "10- Menu generos" << endl;
        cout << "0- Volver" << endl;
        cin >> opcion;

        switch(opcion){
        case 1:{
            Libro libro;
            libro.setIdLibro(generarNuevoID());
            libro.cargar();

            if(libro.guardar()){
                cout << "Libro guardado correctamente." << endl;
            }
            else{
                cout << "Error al guardar libro." << endl;
            }

            system("pause");
            break;
        }

        case 2:
            listar();
            break;

        case 3:
            listarPorAutor();
            break;

        case 4:
            listarPorGenero();
            break;

        case 5:
            consultarPorTitulo();
            break;

        case 6:
            consultarPorISBN();
            break;

        case 7:
            modificarLibro();
            break;

        case 8:
            bajaLogica();
            break;

        case 9:
            Autor::menuAutores();
            break;

        case 10:
            Genero::menuGeneros();
            break;

        case 0:
            return;
        }
    }
}
