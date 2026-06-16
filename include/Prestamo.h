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

    void cargar();
    void mostrar();

};
