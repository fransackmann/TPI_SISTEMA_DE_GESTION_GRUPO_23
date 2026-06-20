#pragma once
#include "Fecha.h"
class Pagos{

private:

int _idPago;
int _idSocio;
int  _idCuota;
Fecha _fechaPago;
float _importe;
bool _estado;

public:

    Pagos();
    Pagos(int idpago,int idsocio,int idcuota,Fecha fechapago,float importe, bool estado);

    int getidpago();
    void setidpago(int idPago);

    int getidsocio();
    void setidsocio(int idsocio);

    int getidcuota();
    void setidcuota(int idcuota);

    Fecha getfechapago();
    void setfechapago(Fecha fechapago);

    float getimporte();
    void setimporte(float importe);

    bool getestado();
    void setestado(bool estado);

    void cargar();
    void mostrar();
};
