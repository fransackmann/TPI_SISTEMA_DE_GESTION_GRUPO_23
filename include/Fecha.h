#pragma once

class Fecha
{
private:

    int _dia;
    int _mes;
    int _anio;

public:

    Fecha();

    int getDia();
    void setDia(int dia);

    int getMes();
    void setMes(int mes);

    int getAnio();
    void setAnio(int anio);

    void cargar();
    void mostrar();

};
