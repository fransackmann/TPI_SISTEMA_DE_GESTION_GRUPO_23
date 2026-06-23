#pragma once

#include "Fecha.h"

void limpiar();
void pausar(int alto = 25);

void pantalla(const char* titulo, int alto = 22);

void opcion(int fila,int numero,const char* texto);
void volver(int fila);

Fecha pedirFecha(int x,int y);

void menuAutores();
void menuGeneros();
void menuSocios();
void menuLibros();
void menuPrestamos();
void menuPrestamosConsultas();
void menuPrestamosListados();
void menuCuotas();
void menuPagos();
void menuCuotasPagos();
void menuReportes();
void menuConfiguracion();
void menuBackup();
void menuRestaurarBackup();

void realizarBackup();
void restaurarBackup();
