#pragma once
#include "Fecha.h"

class Prestamo{

private:
    int _idPrestamo;
    int _idSocio;
    int _idLibro;
    Fecha _fechaPrestamo;
    Fecha _fechaVencimiento;
    Fecha _fechaDevolucion;
    bool _devuelto;
    bool _vencido;
    bool _estado;

public:
    Prestamo();
    Prestamo(int idPrestamo, int idSocio, int idLibro, Fecha fechaPrestamo, Fecha fechaVencimiento, Fecha fechaDevolucion, bool devuelto, bool vencido, bool estado);

    int getIdPrestamo();
    void setIdPrestamo(int idPrestamo);

    int getIdSocio();
    void setIdSocio(int idSocio);

    int getIdLibro();
    void setIdLibro(int idLibro);

    Fecha getFechaPrestamo();
    void setFechaPrestamo(Fecha fechaPrestamo);

    Fecha getFechaVencimiento();
    void setFechaVencimiento(Fecha fechaVencimiento);

    Fecha getFechaDevolucion();
    void setFechaDevolucion(Fecha fechaDevolucion);

    bool getDevuelto();
    void setDevuelto(bool devuelto);

    bool getVencido();
    void setVencido(bool vencido);

    bool getEstado();
    void setEstado(bool estado);

    void mostrar(int fila = 10);

    bool guardar();
    bool modificar(int posicion);
    static int contarRegistros();
    static Prestamo leer(int posicion);
    static int buscarPorID(int idPrestamo);
    static int generarNuevoID();
    static void listar();
    static void listarActivos();
    static void listarVencidos();
    static void listarOrdenadosPorFecha();
    static void listarPorRangoFechas();
    static void consultarPorSocio();
    static void consultarPorLibro();
    static void consultarPorEstado();
    static void marcarPrestamoVencido();
};
