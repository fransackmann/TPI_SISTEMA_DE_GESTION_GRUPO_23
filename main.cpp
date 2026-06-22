#include <iostream>
#include <cstdio>
#include <cstring>
#include "rlutil.h"

#include "Autor.h"
#include "Genero.h"
#include "Socio.h"
#include "Libro.h"
#include "Prestamo.h"
#include "Cuotas.h"
#include "Pagos.h"
#include "Fecha.h"
#include "Menus.h"

using namespace std;

int main(){
    int op;

    rlutil::saveDefaultColor();
    rlutil::setConsoleTitle("Sistema de Gestion de Biblioteca");

    while(true){
        pantalla("SISTEMA DE GESTION DE BIBLIOTECA");

        opcion(11,1,"Libros");
        opcion(12,2,"Socios");
        opcion(13,3,"Prestamos");
        opcion(14,4,"Cuotas y pagos");
        opcion(15,5,"Autores");
        opcion(16,6,"Generos");
        opcion(17,7,"Reportes");
        opcion(18,8,"Configuracion");
        volver(20);

        rlutil::locate(34,24);
        cout << "Seleccione una opcion: ";
        cin >> op;

        switch(op){
        case 1: menuLibros(); break;
        case 2: menuSocios(); break;
        case 3: menuPrestamos(); break;
        case 4: menuCuotasPagos(); break;
        case 5: menuAutores(); break;
        case 6: menuGeneros(); break;
        case 7: menuReportes(); break;
        case 8: menuConfiguracion(); break;

        case 0:
            pantalla("FIN DEL PROGRAMA");
            rlutil::locate(39,13);
            cout << "Gracias por usar el sistema.";
            pausar();
            rlutil::resetColor();
            return 0;

        default:
            pausar();
            break;
        }
    }

    rlutil::resetColor();
    return 0;
}
