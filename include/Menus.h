#pragma once

#include "Fecha.h"

void limpiar();
void pausar();

void marco();
void pantalla(const char* titulo);

void opcion(int fila,int numero,const char* texto);
void volver(int fila);

Fecha pedirFecha(int x,int y);

void menuAutores();
void menuGeneros();
void menuSocios();
void menuLibros();
void menuPrestamos();
void menuCuotas();
void menuPagos();
void menuCuotasPagos();
void menuReportes();
void menuConfiguracion();

void realizarBackup();
void restaurarBackup();
