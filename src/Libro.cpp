#include <iostream>
#include <cstring>
#include "Libro.h"

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

int Libro::getIdLibro(){
    return _idLibro;
}

void Libro::setIdLibro(int idLibro){
    _idLibro = idLibro;
}

const char* Libro::getIsbn(){
    return _isbn;
}

void Libro::setIsbn(const char* isbn){
    strcpy(_isbn, isbn);
}

const char* Libro::getTitulo(){
    return _titulo;
}

void Libro::setTitulo(const char* titulo){
    strcpy(_titulo, titulo);
}

int Libro::getIdAutor(){
    return _idAutor;
}

void Libro::setIdAutor(int idAutor){
    _idAutor = idAutor;
}

int Libro::getIdGenero(){
    return _idGenero;
}

void Libro::setIdGenero(int idGenero){
    _idGenero = idGenero;
}

const char* Libro::getEditorial(){
    return _editorial;
}

void Libro::setEditorial(const char* editorial){
    strcpy(_editorial, editorial);
}

Fecha Libro::getAnioPublicacion(){
    return _anioPublicacion;
}

void Libro::setAnioPublicacion(Fecha anioPublicacion){
    _anioPublicacion = anioPublicacion;
}

int Libro::getStockTotal(){
    return _stockTotal;
}

void Libro::setStockTotal(int stockTotal){
    _stockTotal = stockTotal;
}

int Libro::getStockDisponible(){
    return _stockDisponible;
}

void Libro::setStockDisponible(int stockDisponible){
    _stockDisponible = stockDisponible;
}

bool Libro::getEstado(){
    return _estado;
}

void Libro::setEstado(bool estado){
    _estado = estado;
}

void Libro::cargar(){

    cout << "ID Libro: ";
    cin >> _idLibro;

    cout << "ISBN: ";
    cin >> _isbn;

    cout << "Titulo: ";
    cin >> _titulo;

    cout << "ID Autor: ";
    cin >> _idAutor;

    cout << "ID Genero: ";
    cin >> _idGenero;

    cout << "Editorial: ";
    cin >> _editorial;

    cout << "Fecha / anio de publicacion:" << endl;
    _anioPublicacion.cargar();

    cout << "Stock total: ";
    cin >> _stockTotal;

    cout << "Stock disponible: ";
    cin >> _stockDisponible;

    _estado = true;

}

void Libro::mostrar(){

    if(_estado == true){

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
        cout << "Estado: Activo" << endl;
        cout << "-----------------------------" << endl;

    }

}
