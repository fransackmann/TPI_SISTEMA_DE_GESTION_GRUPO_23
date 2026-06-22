#include "Menus.h"

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

using namespace std;

void limpiar(){ rlutil::cls(); }

void pausar(){
    rlutil::setColor(rlutil::YELLOW);
    rlutil::locate(34,25);
    cout << "Presione una tecla para continuar...";
    rlutil::setColor(rlutil::WHITE);
    rlutil::anykey();
}

void marco(){
    rlutil::setColor(rlutil::LIGHTCYAN);

    for(int x=20; x<=95; x++){
        rlutil::locate(x,4); cout << "=";
        rlutil::locate(x,22); cout << "=";
    }

    for(int y=4; y<=22; y++){
        rlutil::locate(20,y); cout << "|";
        rlutil::locate(95,y); cout << "|";
    }

    rlutil::setColor(rlutil::WHITE);
}

void pantalla(const char* titulo){
    limpiar();
    marco();

    rlutil::setColor(rlutil::YELLOW);
    rlutil::locate(39,5);
    cout << "[ SISTEMA DE BIBLIOTECA ]";

    rlutil::setColor(rlutil::LIGHTCYAN);
    rlutil::locate(38,7);
    cout << titulo;

    rlutil::setColor(rlutil::WHITE);
    rlutil::locate(30,9);
    cout << "===================================";
}

void opcion(int fila, int numero, const char* texto){
    rlutil::setColor(rlutil::LIGHTGREEN);
    rlutil::locate(34,fila);
    cout << numero << " - ";
    rlutil::setColor(rlutil::WHITE);
    cout << texto;
}

void volver(int fila){
    rlutil::setColor(rlutil::LIGHTRED);
    rlutil::locate(34,fila);
    cout << "0 - ";
    rlutil::setColor(rlutil::WHITE);
    cout << "Volver / Salir";
}

Fecha pedirFecha(int x, int y){
    Fecha f;
    int d,m,a;

    rlutil::locate(x,y);
    cout << "Dia: ";
    cin >> d;

    rlutil::locate(x,y+1);
    cout << "Mes: ";
    cin >> m;

    rlutil::locate(x,y+2);
    cout << "Anio: ";
    cin >> a;

    f.setDia(d);
    f.setMes(m);
    f.setAnio(a);

    return f;
}

int buscarAutorPorID(int id){
    int cant = Autor::contarRegistros();

    for(int i=0; i<cant; i++){
        Autor a = Autor::leer(i);
        if(a.getAutorID() == id && a.getEstado()){
            return i;
        }
    }
    return -1;
}

int buscarGeneroPorID(int id){
    int cant = Genero::contarRegistros();

    for(int i=0; i<cant; i++){
        Genero g = Genero::leer(i);
        if(g.getIdGenero() == id && g.getEstado()){
            return i;
        }
    }
    return -1;
}

int buscarSocioPorID(int id){
    int cant = Socio::contarRegistros();

    for(int i=0; i<cant; i++){
        Socio s = Socio::leer(i);
        if(s.getIdSocio() == id && s.getEstado()){
            return i;
        }
    }
    return -1;
}

int buscarCuotaPorID(int id){
    int cant = Cuotas::contarRegistros();

    for(int i=0; i<cant; i++){
        Cuotas c = Cuotas::leer(i);
        if(c.getIdCuota() == id && c.getEstado()){
            return i;
        }
    }
    return -1;
}

int buscarPrestamoPorID(int id){
    int cant = Prestamo::contarRegistros();

    for(int i=0; i<cant; i++){
        Prestamo p = Prestamo::leer(i);
        if(p.getIdPrestamo() == id && p.getEstado()){
            return i;
        }
    }
    return -1;
}

bool copiarArchivo(const char* origen, const char* destino){
    FILE* pOrigen = fopen(origen, "rb");
    if(pOrigen == NULL) return false;

    FILE* pDestino = fopen(destino, "wb");
    if(pDestino == NULL){
        fclose(pOrigen);
        return false;
    }

    char buffer[1024];
    int leidos;

    while((leidos = fread(buffer, 1, 1024, pOrigen)) > 0){
        fwrite(buffer, 1, leidos, pDestino);
    }

    fclose(pOrigen);
    fclose(pDestino);

    return true;
}

void altaAutor(){
    pantalla("CARGAR AUTOR");

    Autor a;
    char nombre[30], apellido[30], nacionalidad[30];

    a.setAutorID(Autor::generarNuevoID());

    rlutil::locate(32,12); cout << "ID Autor: " << a.getAutorID();

    rlutil::locate(32,14); cout << "Nombre: ";
    cin >> nombre;

    rlutil::locate(32,15); cout << "Apellido: ";
    cin >> apellido;

    rlutil::locate(32,16); cout << "Nacionalidad: ";
    cin >> nacionalidad;

    a.setNombre(nombre);
    a.setApellido(apellido);
    a.setNacionalidad(nacionalidad);
    a.setEstado(true);

    rlutil::locate(32,19);
    if(a.guardar()) cout << "Autor guardado correctamente.";
    else cout << "Error al guardar autor.";

    pausar();
}

void altaGenero(){
    pantalla("CARGAR GENERO");

    Genero g;
    char descripcion[30];

    g.setIdGenero(Genero::generarNuevoID());

    rlutil::locate(32,12); cout << "ID Genero: " << g.getIdGenero();

    rlutil::locate(32,14); cout << "Descripcion: ";
    cin >> descripcion;

    g.setDescripcion(descripcion);
    g.setEstado(true);

    rlutil::locate(32,18);
    if(g.guardar()) cout << "Genero guardado correctamente.";
    else cout << "Error al guardar genero.";

    pausar();
}

void altaSocio(){
    pantalla("CARGAR SOCIO");

    Socio s;
    char nombre[30], apellido[30], telefono[20], email[40], domicilio[50];
    int dni;

    s.setIdSocio(Socio::generarNuevoID());

    rlutil::locate(32,11); cout << "ID Socio: " << s.getIdSocio();

    rlutil::locate(32,12); cout << "Nombre: ";
    cin >> nombre;

    rlutil::locate(32,13); cout << "Apellido: ";
    cin >> apellido;

    rlutil::locate(32,14); cout << "DNI: ";
    cin >> dni;

    rlutil::locate(32,15); cout << "Telefono: ";
    cin >> telefono;

    rlutil::locate(32,16); cout << "Email: ";
    cin >> email;

    rlutil::locate(32,17); cout << "Domicilio: ";
    cin >> domicilio;

    rlutil::locate(32,18); cout << "Fecha nacimiento:";
    Fecha fn = pedirFecha(54,18);

    s.setNombre(nombre);
    s.setApellido(apellido);
    s.setDNI(dni);
    s.setTelefono(telefono);
    s.setEmail(email);
    s.setDomicilio(domicilio);
    s.setFechaNacimiento(fn);
    s.setEstado(true);

    rlutil::locate(32,21);
    if(s.guardar()) cout << "Socio guardado correctamente.";
    else cout << "Error al guardar socio.";

    pausar();
}

void altaLibro(){
    pantalla("CARGAR LIBRO");

    Libro l;
    char isbn[20], tituloLibro[50], editorial[30];
    int idAutor, idGenero, stock;

    l.setIdLibro(Libro::generarNuevoID());

    rlutil::locate(32,11); cout << "ID Libro: " << l.getIdLibro();

    rlutil::locate(32,12); cout << "ISBN: ";
    cin >> isbn;

    rlutil::locate(32,13); cout << "Titulo: ";
    cin >> tituloLibro;

    rlutil::locate(32,14); cout << "ID Autor: ";
    cin >> idAutor;

    if(buscarAutorPorID(idAutor) < 0){
        rlutil::locate(32,20);
        cout << "No existe ese autor.";
        pausar();
        return;
    }

    rlutil::locate(32,15); cout << "ID Genero: ";
    cin >> idGenero;

    if(buscarGeneroPorID(idGenero) < 0){
        rlutil::locate(32,20);
        cout << "No existe ese genero.";
        pausar();
        return;
    }

    rlutil::locate(32,16); cout << "Editorial: ";
    cin >> editorial;

    rlutil::locate(32,17); cout << "Fecha publicacion:";
    Fecha fp = pedirFecha(54,17);

    rlutil::locate(32,20); cout << "Stock total: ";
    cin >> stock;

    l.setIsbn(isbn);
    l.setTitulo(tituloLibro);
    l.setIdAutor(idAutor);
    l.setIdGenero(idGenero);
    l.setEditorial(editorial);
    l.setAnioPublicacion(fp);
    l.setStockTotal(stock);
    l.setStockDisponible(stock);
    l.setEstado(true);

    rlutil::locate(32,21);
    if(l.guardar()) cout << "Libro guardado correctamente.";
    else cout << "Error al guardar libro.";

    pausar();
}

void listarAutores(){
    pantalla("LISTAR AUTORES");
    rlutil::locate(1,24);

    for(int i=0; i<Autor::contarRegistros(); i++){
        Autor::leer(i).mostrar();
    }

    pausar();
}

void listarGeneros(){
    pantalla("LISTAR GENEROS");
    rlutil::locate(1,24);

    for(int i=0; i<Genero::contarRegistros(); i++){
        Genero::leer(i).mostrar();
    }

    pausar();
}

void listarSocios(){
    pantalla("LISTAR SOCIOS");
    rlutil::locate(1,24);

    for(int i=0; i<Socio::contarRegistros(); i++){
        Socio::leer(i).mostrar();
    }

    pausar();
}

void listarLibros(){
    pantalla("LISTAR LIBROS");
    rlutil::locate(1,24);

    for(int i=0; i<Libro::contarRegistros(); i++){
        Libro::leer(i).mostrar();
    }

    pausar();
}

void registrarPrestamoRetro(){
    pantalla("REGISTRAR PRESTAMO");

    int idSocio, idLibro;
    Prestamo p;

    rlutil::locate(32,12); cout << "ID Socio: ";
    cin >> idSocio;

    if(buscarSocioPorID(idSocio) < 0){
        rlutil::locate(32,20); cout << "No existe ese socio.";
        pausar();
        return;
    }

    rlutil::locate(32,13); cout << "ID Libro: ";
    cin >> idLibro;

    int posLibro = Libro::buscarPorID(idLibro);

    if(posLibro < 0){
        rlutil::locate(32,20); cout << "No existe ese libro.";
        pausar();
        return;
    }

    Libro libro = Libro::leer(posLibro);

    if(libro.getStockDisponible() <= 0){
        rlutil::locate(32,20); cout << "No hay stock disponible.";
        pausar();
        return;
    }

    rlutil::locate(32,15); cout << "Fecha prestamo:";
    Fecha fp = pedirFecha(54,15);

    rlutil::locate(32,18); cout << "Fecha vencimiento:";
    Fecha fv = pedirFecha(54,18);

    p.setIdPrestamo(Prestamo::generarNuevoID());
    p.setIdSocio(idSocio);
    p.setIdLibro(idLibro);
    p.setFechaPrestamo(fp);
    p.setFechaVencimiento(fv);
    p.setDevuelto(false);
    p.setVencido(false);
    p.setEstado(true);

    libro.prestarEjemplar();

    rlutil::locate(32,21);
    if(p.guardar() && libro.modificar(posLibro)) cout << "Prestamo registrado correctamente.";
    else cout << "Error al registrar prestamo.";

    pausar();
}

void devolverPrestamoRetro(){
    pantalla("DEVOLVER PRESTAMO");

    int idPrestamo;

    rlutil::locate(32,12); cout << "ID Prestamo: ";
    cin >> idPrestamo;

    int posPrestamo = buscarPrestamoPorID(idPrestamo);

    if(posPrestamo < 0){
        rlutil::locate(32,20); cout << "No existe ese prestamo.";
        pausar();
        return;
    }

    Prestamo p = Prestamo::leer(posPrestamo);

    if(p.getDevuelto()){
        rlutil::locate(32,20); cout << "Ese prestamo ya fue devuelto.";
        pausar();
        return;
    }

    int posLibro = Libro::buscarPorID(p.getIdLibro());

    if(posLibro < 0){
        rlutil::locate(32,20); cout << "No se encontro el libro.";
        pausar();
        return;
    }

    Libro libro = Libro::leer(posLibro);

    rlutil::locate(32,14); cout << "Fecha devolucion:";
    Fecha fd = pedirFecha(54,14);

    p.setFechaDevolucion(fd);
    p.setDevuelto(true);
    libro.devolverEjemplar();

    rlutil::locate(32,20);
    if(p.modificar(posPrestamo) && libro.modificar(posLibro)) cout << "Devolucion registrada correctamente.";
    else cout << "Error al registrar devolucion.";

    pausar();
}

void altaCuota(){
    pantalla("CARGAR CUOTA");

    Cuotas c;
    int idSocio, mes, anio;
    float importe;

    c.setIdCuota(Cuotas::generarNuevoID());

    rlutil::locate(32,11); cout << "ID Cuota: " << c.getIdCuota();

    rlutil::locate(32,12); cout << "ID Socio: ";
    cin >> idSocio;

    if(buscarSocioPorID(idSocio) < 0){
        rlutil::locate(32,20); cout << "No existe ese socio.";
        pausar();
        return;
    }

    rlutil::locate(32,13); cout << "Mes: ";
    cin >> mes;

    rlutil::locate(32,14); cout << "Anio: ";
    cin >> anio;

    rlutil::locate(32,15); cout << "Fecha cobro:";
    Fecha fc = pedirFecha(54,15);

    rlutil::locate(32,18); cout << "Importe: ";
    cin >> importe;

    c.setIdSocio(idSocio);
    c.setMes(mes);
    c.setAnio(anio);
    c.setFechaCobro(fc);
    c.setImporte(importe);
    c.setPagada(false);
    c.setEstado(true);

    rlutil::locate(32,21);
    if(c.guardar()) cout << "Cuota guardada correctamente.";
    else cout << "Error al guardar cuota.";

    pausar();
}

void registrarPagoRetro(){
    pantalla("REGISTRAR PAGO");

    int idSocio, idCuota;
    float importe;

    rlutil::locate(32,12); cout << "ID Socio: ";
    cin >> idSocio;

    if(buscarSocioPorID(idSocio) < 0){
        rlutil::locate(32,20); cout << "No existe ese socio.";
        pausar();
        return;
    }

    rlutil::locate(32,13); cout << "ID Cuota: ";
    cin >> idCuota;

    int posCuota = buscarCuotaPorID(idCuota);

    if(posCuota < 0){
        rlutil::locate(32,20); cout << "No existe esa cuota.";
        pausar();
        return;
    }

    Cuotas cuota = Cuotas::leer(posCuota);

    if(cuota.getPagada()){
        rlutil::locate(32,20); cout << "La cuota ya esta pagada.";
        pausar();
        return;
    }

    if(cuota.getIdSocio() != idSocio){
        rlutil::locate(32,20); cout << "La cuota no corresponde al socio.";
        pausar();
        return;
    }

    rlutil::locate(32,15); cout << "Fecha pago:";
    Fecha fp = pedirFecha(54,15);

    rlutil::locate(32,18); cout << "Importe: ";
    cin >> importe;

    Pagos pago;
    pago.setIdPago(Pagos::generarNuevoID());
    pago.setIdSocio(idSocio);
    pago.setIdCuota(idCuota);
    pago.setFechaPago(fp);
    pago.setImporte(importe);
    pago.setEstado(true);

    cuota.marcarPagada();

    rlutil::locate(32,21);
    if(pago.guardar() && cuota.modificar(posCuota)) cout << "Pago registrado correctamente.";
    else cout << "Error al registrar pago.";

    pausar();
}

void menuAutores(){
    int op;
    while(true){
        pantalla("MENU AUTORES");
        opcion(12,1,"Cargar autor");
        opcion(13,2,"Listar autores");
        opcion(14,3,"Ordenar por apellido");
        volver(17);

        rlutil::locate(34,20); cout << "Seleccione una opcion: ";
        cin >> op;

        switch(op){
        case 1: altaAutor(); break;
        case 2: listarAutores(); break;
        case 3: Autor::listarOrdenadoPorApellido(); break;
        case 0: return;
        default: pausar(); break;
        }
    }
}

void menuGeneros(){
    int op;
    while(true){
        pantalla("MENU GENEROS");
        opcion(12,1,"Cargar genero");
        opcion(13,2,"Listar generos");
        opcion(14,3,"Ordenar alfabeticamente");
        volver(17);

        rlutil::locate(34,20); cout << "Seleccione una opcion: ";
        cin >> op;

        switch(op){
        case 1: altaGenero(); break;
        case 2: listarGeneros(); break;
        case 3: Genero::listarOrdenadoAlfabeticamente(); break;
        case 0: return;
        default: pausar(); break;
        }
    }
}

void menuSocios(){
    int op;
    while(true){
        pantalla("MENU SOCIOS");
        opcion(11,1,"Cargar socio");
        opcion(12,2,"Listar socios");
        opcion(13,3,"Ordenar por DNI");
        opcion(14,4,"Consultar por DNI");
        opcion(15,5,"Consultar por apellido");
        opcion(16,6,"Baja logica");
        volver(19);

        rlutil::locate(34,21); cout << "Seleccione una opcion: ";
        cin >> op;

        switch(op){
        case 1: altaSocio(); break;
        case 2: listarSocios(); break;
        case 3: Socio::listarOrdenadoPorDNI(); break;
        case 4: Socio::consultarPorDNI(); break;
        case 5: Socio::consultarPorApellido(); break;
        case 6: Socio::bajaLogica(); break;
        case 0: return;
        default: pausar(); break;
        }
    }
}

void menuLibros(){
    int op;
    while(true){
        pantalla("MENU LIBROS");
        opcion(10,1,"Cargar libro");
        opcion(11,2,"Listar libros");
        opcion(12,3,"Libros por autor");
        opcion(13,4,"Libros por genero");
        opcion(14,5,"Consultar por titulo");
        opcion(15,6,"Consultar por ISBN");
        opcion(16,7,"Modificar libro");
        opcion(17,8,"Baja logica");
        opcion(18,9,"Autores");
        opcion(19,10,"Generos");
        volver(21);

        rlutil::locate(34,24); cout << "Seleccione una opcion: ";
        cin >> op;

        switch(op){
        case 1: altaLibro(); break;
        case 2: listarLibros(); break;
        case 3: Libro::listarPorAutor(); break;
        case 4: Libro::listarPorGenero(); break;
        case 5: Libro::consultarPorTitulo(); break;
        case 6: Libro::consultarPorISBN(); break;
        case 7: Libro::modificarLibro(); break;
        case 8: Libro::bajaLogica(); break;
        case 9: menuAutores(); break;
        case 10: menuGeneros(); break;
        case 0: return;
        default: pausar(); break;
        }
    }
}

void menuPrestamos(){
    int op;
    while(true){
        pantalla("MENU PRESTAMOS");
        opcion(11,1,"Registrar prestamo");
        opcion(12,2,"Listar prestamos");
        opcion(13,3,"Prestamos activos");
        opcion(14,4,"Prestamos vencidos");
        opcion(15,5,"Ordenados por fecha");
        opcion(16,6,"Por rango de fechas");
        opcion(17,7,"Devolver prestamo");
        volver(20);

        rlutil::locate(34,23); cout << "Seleccione una opcion: ";
        cin >> op;

        switch(op){
        case 1: registrarPrestamoRetro(); break;
        case 2: Prestamo::listar(); break;
        case 3: Prestamo::listarActivos(); break;
        case 4: Prestamo::listarVencidos(); break;
        case 5: Prestamo::listarOrdenadosPorFecha(); break;
        case 6: Prestamo::listarPorRangoFechas(); break;
        case 7: devolverPrestamoRetro(); break;
        case 0: return;
        default: pausar(); break;
        }
    }
}

void menuCuotas(){
    int op;
    while(true){
        pantalla("MENU CUOTAS");
        opcion(12,1,"Cargar cuota");
        opcion(13,2,"Listar cuotas");
        opcion(14,3,"Pendientes por socio");
        volver(17);

        rlutil::locate(34,20); cout << "Seleccione una opcion: ";
        cin >> op;

        switch(op){
        case 1: altaCuota(); break;
        case 2: Cuotas::listar(); break;
        case 3: Cuotas::listarPendientesPorSocio(); break;
        case 0: return;
        default: pausar(); break;
        }
    }
}

void menuPagos(){
    int op;
    while(true){
        pantalla("MENU PAGOS");
        opcion(12,1,"Registrar pago");
        opcion(13,2,"Listar pagos");
        opcion(14,3,"Pagos por socio");
        opcion(15,4,"Pagos por mes");
        volver(18);

        rlutil::locate(34,21); cout << "Seleccione una opcion: ";
        cin >> op;

        switch(op){
        case 1: registrarPagoRetro(); break;
        case 2: Pagos::listar(); break;
        case 3: Pagos::listarPorSocio(); break;
        case 4: Pagos::pagosPorMes(); break;
        case 0: return;
        default: pausar(); break;
        }
    }
}

void menuCuotasPagos(){
    int op;
    while(true){
        pantalla("CUOTAS Y PAGOS");
        opcion(12,1,"Cuotas");
        opcion(13,2,"Pagos");
        volver(16);

        rlutil::locate(34,20); cout << "Seleccione una opcion: ";
        cin >> op;

        switch(op){
        case 1: menuCuotas(); break;
        case 2: menuPagos(); break;
        case 0: return;
        default: pausar(); break;
        }
    }
}


void reporteLibrosMasPrestados(){
    pantalla("LIBROS MAS PRESTADOS");

    int cantidadLibros = Libro::contarRegistros();
    int cantidadPrestamos = Prestamo::contarRegistros();

    if(cantidadLibros == 0){
        rlutil::locate(32,13);
        cout << "No hay libros cargados.";
        pausar();
        return;
    }

    int* ids = new int[cantidadLibros];
    int* cantidades = new int[cantidadLibros];

    for(int i=0; i<cantidadLibros; i++){
        Libro libro = Libro::leer(i);
        ids[i] = libro.getIdLibro();
        cantidades[i] = 0;
    }

    for(int i=0; i<cantidadPrestamos; i++){
        Prestamo prestamo = Prestamo::leer(i);

        if(prestamo.getEstado()){
            for(int j=0; j<cantidadLibros; j++){
                if(prestamo.getIdLibro() == ids[j]){
                    cantidades[j]++;
                }
            }
        }
    }

    for(int i=0; i<cantidadLibros-1; i++){
        for(int j=0; j<cantidadLibros-1-i; j++){
            if(cantidades[j] < cantidades[j+1]){
                int auxCantidad = cantidades[j];
                cantidades[j] = cantidades[j+1];
                cantidades[j+1] = auxCantidad;

                int auxId = ids[j];
                ids[j] = ids[j+1];
                ids[j+1] = auxId;
            }
        }
    }

    limpiar();
    rlutil::setColor(rlutil::LIGHTCYAN);
    cout << "LIBROS MAS PRESTADOS" << endl;
    cout << "====================" << endl << endl;
    rlutil::setColor(rlutil::WHITE);

    for(int i=0; i<cantidadLibros; i++){
        int posLibro = Libro::buscarPorID(ids[i]);

        if(posLibro >= 0){
            Libro libro = Libro::leer(posLibro);
            libro.mostrar();
            cout << "Cantidad de prestamos: " << cantidades[i] << endl;
            cout << "-----------------------------" << endl;
        }
    }

    delete[] ids;
    delete[] cantidades;

    system("pause");
}

void menuReportes(){
    int op;

    while(true){
        pantalla("REPORTES");

        opcion(10,1,"Prestamos por rango de fechas");
        opcion(11,2,"Libros mas prestados");
        opcion(12,3,"Cuotas pendientes por socio");
        opcion(13,4,"Pagos realizados por mes");
        opcion(14,5,"Prestamos activos");
        opcion(15,6,"Prestamos vencidos");
        opcion(16,7,"Prestamos ordenados por fecha");
        volver(19);

        rlutil::locate(34,22);
        cout << "Seleccione una opcion: ";
        cin >> op;

        switch(op){
        case 1: Prestamo::listarPorRangoFechas(); break;
        case 2: reporteLibrosMasPrestados(); break;
        case 3: Cuotas::listarPendientesPorSocio(); break;
        case 4: Pagos::pagosPorMes(); break;
        case 5: Prestamo::listarActivos(); break;
        case 6: Prestamo::listarVencidos(); break;
        case 7: Prestamo::listarOrdenadosPorFecha(); break;
        case 0: return;
        default: pausar(); break;
        }
    }
}

void realizarBackup(){
    pantalla("COPIA DE SEGURIDAD");

    copiarArchivo("Autores.dat", "Autores.bak");
    copiarArchivo("Generos.dat", "Generos.bak");
    copiarArchivo("Libros.dat", "Libros.bak");
    copiarArchivo("Socios.dat", "Socios.bak");
    copiarArchivo("Prestamos.dat", "Prestamos.bak");
    copiarArchivo("Cuotas.dat", "Cuotas.bak");
    copiarArchivo("Pagos.dat", "Pagos.bak");

    rlutil::locate(32,14);
    cout << "Backup realizado correctamente.";
    pausar();
}

void restaurarBackup(){
    pantalla("RESTAURAR BACKUP");

    copiarArchivo("Autores.bak", "Autores.dat");
    copiarArchivo("Generos.bak", "Generos.dat");
    copiarArchivo("Libros.bak", "Libros.dat");
    copiarArchivo("Socios.bak", "Socios.dat");
    copiarArchivo("Prestamos.bak", "Prestamos.dat");
    copiarArchivo("Cuotas.bak", "Cuotas.dat");
    copiarArchivo("Pagos.bak", "Pagos.dat");

    rlutil::locate(32,14);
    cout << "Backup restaurado correctamente.";
    pausar();
}

void menuConfiguracion(){
    int op;
    while(true){
        pantalla("CONFIGURACION");
        opcion(12,1,"Realizar backup");
        opcion(13,2,"Restaurar backup");
        volver(16);

        rlutil::locate(34,20); cout << "Seleccione una opcion: ";
        cin >> op;

        switch(op){
        case 1: realizarBackup(); break;
        case 2: restaurarBackup(); break;
        case 0: return;
        default: pausar(); break;
        }
    }
}
