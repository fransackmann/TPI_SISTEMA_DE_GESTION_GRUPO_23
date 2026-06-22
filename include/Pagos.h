#pragma once
#include "Fecha.h"

class Pagos{

private:
    int _idPago;
    int _idSocio;
    int _idCuota;
    Fecha _fechaPago;
    float _importe;
    bool _estado;

public:
    Pagos();
    Pagos(int idPago, int idSocio, int idCuota, Fecha fechaPago, float importe, bool estado);

    int getIdPago();
    void setIdPago(int idPago);

    int getIdSocio();
    void setIdSocio(int idSocio);

    int getIdCuota();
    void setIdCuota(int idCuota);

    Fecha getFechaPago();
    void setFechaPago(Fecha fechaPago);

    float getImporte();
    void setImporte(float importe);

    bool getEstado();
    void setEstado(bool estado);

    void cargar();
    void mostrar();

    bool guardar();
    static int contarRegistros();
    static Pagos leer(int posicion);
    static int generarNuevoID();
    static void registrarPago();
    static void listar();
    static void listarPorSocio();
    static void pagosPorMes();
    static void menuPagos();
};
