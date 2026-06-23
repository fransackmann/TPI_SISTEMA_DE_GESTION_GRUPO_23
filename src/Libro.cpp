#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include "Libro.h"
#include "Autor.h"
#include "Genero.h"
#include "Menus.h"
#include "rlutil.h"
using namespace std;
using namespace rlutil;
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

void Libro::mostrar(int fila){
    if(_estado){
        Fecha f = getAnioPublicacion();
        locate(30 , fila + 1); cout << "ID: " << _idLibro << endl;
        locate(30 , fila + 2); cout << "ISBN: " << _isbn << endl;
        locate(30 , fila + 3); cout << "Titulo: " << _titulo << endl;
        locate(30 , fila + 4); cout << "ID Autor: " << _idAutor << endl;
        locate(30 , fila + 5); cout << "ID Genero: " << _idGenero << endl;
        locate(30 , fila + 6); cout << "Editorial: " << _editorial << endl;
        locate(30 , fila + 7); cout << "Fecha de Publicacion: " << f.getDia() << "/" << f.getMes() << "/" << f.getAnio() << endl;
        locate(30 , fila + 8); cout << "Stock total: " << _stockTotal << endl;
        locate(30 , fila + 9); cout << "Stock Disponible: " << _stockDisponible << endl;
        locate(30 , fila + 10); cout << "-----------------------------------" << endl;
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
    int activos = 0;

    for(int i = 0; i < cantidad; i++){
        Libro libro = leer(i);
        if(libro.getEstado()){
            activos++;
        }
    }

    if(activos == 0){
        cout << "No hay libros cargados." << endl;
        system("pause");
        return;
    }

    for(int i = 0; i < cantidad; i++){
        Libro libro = leer(i);

        if(libro.getEstado()){
            Fecha f = libro.getAnioPublicacion();

            cout << "ID: " << libro.getIdLibro() << endl;
            cout << "ISBN: " << libro.getIsbn() << endl;
            cout << "Titulo: " << libro.getTitulo() << endl;
            cout << "ID Autor: " << libro.getIdAutor() << endl;
            cout << "ID Genero: " << libro.getIdGenero() << endl;
            cout << "Editorial: " << libro.getEditorial() << endl;
            cout << "Fecha de Publicacion: " << f.getDia() << "/" << f.getMes() << "/" << f.getAnio() << endl;
            cout << "Stock total: " << libro.getStockTotal() << endl;
            cout << "Stock Disponible: " << libro.getStockDisponible() << endl;
            cout << "-----------------------------------" << endl;
        }
    }

    system("pause");
}

void Libro::listarPorAutor(){

    int idAutor;
    pantalla("BUSCAR LIBROS", 22);
    locate(30, 12);
    cout << "Ingrese ID Autor: ";
    cin >> idAutor;
    system("cls");

    int cantidad = contarRegistros();

    int suma=0;
    for(int i = 0; i < cantidad; i++){
        Libro libro = leer(i);
        if(libro.getEstado() && libro.getIdAutor() == idAutor)suma++;
        }
    int j = 0;
    int alto = 10 + suma * 11 + 1;
    pantalla("LISTAR LIBROS", alto);
    for(int i = 0; i < cantidad; i++){
        Libro libro = leer(i);
        if(libro.getEstado() && libro.getIdAutor() == idAutor){
            Fecha f = libro.getAnioPublicacion();
            int fila = 10 + j * 11;
            locate(30, fila + 1);
            cout << "ID: " << libro.getIdLibro() << endl;
            locate(30, fila + 2);
            cout << "ISBN: " << libro.getIsbn() << endl;
            locate(30, fila + 3);
            cout << "Titulo: " << libro.getTitulo() << endl;
            locate(30, fila + 4);
            cout << "ID Autor: " << libro.getIdAutor() << endl;
            locate(30, fila + 5);
            cout << "ID Genero: " << libro.getIdGenero() << endl;
            locate(30, fila + 6);
            cout << "Editorial: " << libro.getEditorial() << endl;
            locate(30, fila + 7);
            cout << "Fecha de Publicacion: " << f.getDia() << "/" << f.getMes() << "/" << f.getAnio() << endl;
            locate(30, fila + 9);
            cout << "Stock total: " << libro.getStockTotal() << endl;
            locate(30, fila + 10);
            cout << "Stock Disponible: " << libro.getStockDisponible() << endl;
            locate(30, fila + 11);
            cout << "-----------------------------------" << endl;
            j++;
        }
    }

    pausar(alto + 2);
}

void Libro::listarPorGenero(){
    int idGenero;
    pantalla("BUSCAR LIBROS", 22);
    locate(30, 12);
    cout << "Ingrese ID Genero: ";
    cin >> idGenero;

    system("cls");

    int cantidad = contarRegistros();

int suma=0;
    for(int i = 0; i < cantidad; i++){
        Libro libro = leer(i);
        if(libro.getEstado() && libro.getIdGenero() == idGenero)suma++;
        }
    int j = 0;
    int alto = 10 + suma * 11 + 1;
    pantalla("LISTAR LIBROS", alto);
    for(int i = 0; i < cantidad; i++){
        Libro libro = leer(i);
        if(libro.getEstado() && libro.getIdGenero() == idGenero){
            Fecha f = libro.getAnioPublicacion();
            int fila = 10 + j * 11;
            locate(30, fila + 1);
            cout << "ID: " << libro.getIdLibro() << endl;
            locate(30, fila + 2);
            cout << "ISBN: " << libro.getIsbn() << endl;
            locate(30, fila + 3);
            cout << "Titulo: " << libro.getTitulo() << endl;
            locate(30, fila + 4);
            cout << "ID Autor: " << libro.getIdAutor() << endl;
            locate(30, fila + 5);
            cout << "ID Genero: " << libro.getIdGenero() << endl;
            locate(30, fila + 6);
            cout << "Editorial: " << libro.getEditorial() << endl;
            locate(30, fila + 7);
            cout << "Fecha de Publicacion: " << f.getDia() << "/" << f.getMes() << "/" << f.getAnio() << endl;
            locate(30, fila + 9);
            cout << "Stock total: " << libro.getStockTotal() << endl;
            locate(30, fila + 10);
            cout << "Stock Disponible: " << libro.getStockDisponible() << endl;
            locate(30, fila + 11);
            cout << "-----------------------------------" << endl;
            j++;
        }
    }

    pausar(alto + 2);
}


void Libro::consultarPorTitulo(){
    char titulo[50];
    pantalla("BUSCAR LIBROS", 22);
    locate(30, 12); cout << "Ingrese titulo a buscar: ";
    cin >> titulo;

    int cantidad = contarRegistros();

    int cont = 0;
    for(int i = 0; i < cantidad; i++){
        Libro l = leer(i);
        if(l.getEstado() && strcmp(l.getTitulo(), titulo) == 0) cont++;
    }

    if(cont == 0){
        pantalla("RESULTADO DE BUSQUEDA", 14);
        locate(30, 12); cout << "No se encontro libro con ese titulo.";
        pausar(16);
        return;
    }

    int alto = 10 + cont * 11 + 1;
    pantalla("RESULTADO DE BUSQUEDA", alto);

    int j = 0;
    for(int i = 0; i < cantidad; i++){
        Libro l = leer(i);
        if(l.getEstado() && strcmp(l.getTitulo(), titulo) == 0){
            l.mostrar(10 + j * 11);
            j++;
        }
    }

    pausar(alto + 2);
}

void Libro::consultarPorISBN(){
    char isbn[20];
    pantalla("BUSCAR LIBROS", 22);
    locate(30, 12); cout << "Ingrese ISBN a buscar: ";
    cin >> isbn;

    int cantidad = contarRegistros();
    int pos = -1;
    for(int i = 0; i < cantidad; i++){
        Libro l = leer(i);
        if(l.getEstado() && strcmp(l.getIsbn(), isbn) == 0){
            pos = i;
            break;
        }
    }

    if(pos < 0){
        pantalla("RESULTADO DE BUSQUEDA", 14);
        locate(30, 12); cout << "No se encontro libro con ese ISBN.";
        pausar(16);
        return;
    }

    Libro l = leer(pos);
    pantalla("RESULTADO DE BUSQUEDA", 22);
    l.mostrar(10);
    pausar(24);
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
