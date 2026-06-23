#pragma once
#include "Fecha.h"

class Cuotas{

private:
    int _idCuota;
    int _idSocio;
    int _mes;
    int _anio;
    Fecha _fechaCobro;
    float _importe;
    bool _pagada;
    bool _estado;

public:
    Cuotas();
    Cuotas(int idCuota, int idSocio, int mes, int anio, Fecha fechaCobro, float importe, bool pagada, bool estado);

    int getIdCuota();
    void setIdCuota(int idCuota);

    int getIdSocio();
    void setIdSocio(int idSocio);

    int getMes();
    void setMes(int mes);

    int getAnio();
    void setAnio(int anio);

    Fecha getFechaCobro();
    void setFechaCobro(Fecha fechaCobro);

    float getImporte();
    void setImporte(float importe);

    bool getPagada();
    void setPagada(bool pagada);

    bool getEstado();
    void setEstado(bool estado);

    void marcarPagada();

    void mostrar(int fila);

    bool guardar();
    bool modificar(int posicion);
    static int contarRegistros();
    static Cuotas leer(int posicion);
    static int buscarPorID(int idCuota);
    static int generarNuevoID();
    static void listar();
    static void listarPagadas();
    static void listarPendientes();
    static void listarPendientesPorSocio();
};
