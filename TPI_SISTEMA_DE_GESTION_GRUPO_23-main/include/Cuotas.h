#pragma once
#include "Fecha.h"


class Cuotas{

private:

    int _idCuota;
    int _idSocio;
    Fecha _mes;
    Fecha _anio;
    Fecha _fechacobro;
    float _importe;
    bool _pagada;
    bool _estado;

public:
    Cuotas();
    Cuotas(int idCuota,
        int idSocio,
        Fecha mes,
        Fecha anio,
        Fecha fechaCobro,
        float importe,
        bool pagada,
        bool estado);

    int getidcuota();
    void setidcouta(int idCuota);

    int getidsocio();
    void setidsocio(int idSocio);

    Fecha getmes();
    void setmes(Fecha mes);

    Fecha getanio();
    void setanio(Fecha anio);

    Fecha getfechacobro();
    void setfechacobro(Fecha fechacobro);

    float getimporte();
    void setimporte(float importe);

    bool getpagada();
    void setpagada(bool pagada);

    bool getestado();
    void setestado(bool estado);

    void cargar();
    void mostrar();
};

