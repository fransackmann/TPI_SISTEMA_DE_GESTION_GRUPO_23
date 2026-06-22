#pragma once
#include "Fecha.h"

class Libro{

private:
    int _idLibro;
    char _isbn[20];
    char _titulo[50];
    int _idAutor;
    int _idGenero;
    char _editorial[30];
    Fecha _anioPublicacion;
    int _stockTotal;
    int _stockDisponible;
    bool _estado;

public:
    Libro();
    Libro(int idLibro, const char* isbn, const char* titulo, int idAutor, int idGenero, const char* editorial, Fecha anioPublicacion, int stockTotal, int stockDisponible, bool estado);

    int getIdLibro();
    void setIdLibro(int idLibro);

    const char* getIsbn();
    void setIsbn(const char* isbn);

    const char* getTitulo();
    void setTitulo(const char* titulo);

    int getIdAutor();
    void setIdAutor(int idAutor);

    int getIdGenero();
    void setIdGenero(int idGenero);

    const char* getEditorial();
    void setEditorial(const char* editorial);

    Fecha getAnioPublicacion();
    void setAnioPublicacion(Fecha anioPublicacion);

    int getStockTotal();
    void setStockTotal(int stockTotal);

    int getStockDisponible();
    void setStockDisponible(int stockDisponible);

    bool getEstado();
    void setEstado(bool estado);

    void prestarEjemplar();
    void devolverEjemplar();

    void cargar();
    void mostrar();

    bool guardar();
    bool modificar(int posicion);
    static int contarRegistros();
    static Libro leer(int posicion);
    static int buscarPorID(int idLibro);
    static bool existe(int idLibro);
    static int generarNuevoID();
    static void listar();
    static void listarPorAutor();
    static void listarPorGenero();
    static void consultarPorTitulo();
    static void consultarPorISBN();
    static void bajaLogica();
    static void modificarLibro();
    static void menuLibros();
};
