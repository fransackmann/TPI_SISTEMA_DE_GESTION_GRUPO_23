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
using namespace rlutil;

void limpiar(){ cls(); }

void pausar(int alto){
    setColor(rlutil::YELLOW);
    locate(34,alto);
    cout << "Presione una tecla para continuar...";
    setColor(rlutil::WHITE);
    anykey();
}

void pantalla(const char* titulo, int alto){
    limpiar();
    setColor(LIGHTCYAN);

    for(int x=20; x<=95; x++){
        setColor(LIGHTCYAN);
        locate(x,4); cout << "=";
        locate(x,alto); cout << "=";
    }

    for(int y=4; y<=alto; y++){
        setColor(LIGHTCYAN);
        locate(20,y); cout << "|";
        locate(95,y); cout << "|";
    }
    setColor(YELLOW);
    locate(39,5);
    cout << "[ SISTEMA DE BIBLIOTECA ]";

    setColor(LIGHTCYAN);
    locate(38,7);
    cout << titulo;

    setColor(WHITE);
    locate(30,9);
    cout << "===================================";


    setColor(WHITE);
}

void opcion(int fila, int numero, const char* texto){
    setColor(LIGHTGREEN);
    locate(34,fila);
    cout << numero << " - ";
    setColor(WHITE);
    cout << texto;
}

void volver(int fila){
    setColor(LIGHTRED);
    locate(34,fila);
    cout << "0 - ";
    setColor(WHITE);
    cout << "Volver / Salir";
}

Fecha pedirFecha(int x, int y){
    Fecha f;
    int d,m,a;

    locate(x,y);
    cout << "Dia: ";
    cin >> d;

    locate(x,y+1);
    cout << "Mes: ";
    cin >> m;

    locate(x,y+2);
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

    locate(32,11); cout << "ID Socio: " << s.getIdSocio();

    locate(32,12); cout << "Nombre: ";
    cin >> nombre;

    locate(32,13); cout << "Apellido: ";
    cin >> apellido;

    locate(32,14); cout << "DNI: ";
    cin >> dni;

    locate(32,15); cout << "Telefono: ";
    cin >> telefono;

    locate(32,16); cout << "Email: ";
    cin >> email;

    locate(32,17); cout << "Domicilio: ";
    cin >> domicilio;

    locate(32,18); cout << "Fecha nacimiento:";
    Fecha fn = pedirFecha(54,18);

    s.setNombre(nombre);
    s.setApellido(apellido);
    s.setDNI(dni);
    s.setTelefono(telefono);
    s.setEmail(email);
    s.setDomicilio(domicilio);
    s.setFechaNacimiento(fn);
    s.setEstado(true);

    locate(32,21);
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

    locate(32,11); cout << "ID Libro: " << l.getIdLibro();

    locate(32,12); cout << "ISBN: ";
    cin >> isbn;

    locate(32,13); cout << "Titulo: ";
    cin >> tituloLibro;

    locate(32,14); cout << "ID Autor: ";
    cin >> idAutor;

    if(buscarAutorPorID(idAutor) < 0){
        locate(32,20);
        cout << "No existe ese autor.";
        pausar();
        return;
    }

    locate(32,15); cout << "ID Genero: ";
    cin >> idGenero;

    if(buscarGeneroPorID(idGenero) < 0){
        locate(32,20);
        cout << "No existe ese genero.";
        pausar();
        return;
    }

    locate(32,16); cout << "Editorial: ";
    cin >> editorial;

    locate(32,17); cout << "Fecha publicacion:";
    Fecha fp = pedirFecha(54,17);

    locate(32,20); cout << "Stock total: ";
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

    locate(32,21);
    if(l.guardar()) cout << "Libro guardado correctamente.";
    else cout << "Error al guardar libro.";

    pausar();
}

void listarAutores(){
    int cantidad = Autor::contarRegistros();
    int activos = 0;

    for(int i=0; i<cantidad; i++){
        Autor a = Autor::leer(i);
        if(a.getEstado()){
            activos++;
        }
    }

    if(activos == 0){
        pantalla("LISTA AUTORES", 14);
        locate(30, 12);
        cout << "No hay autores cargados.";
        pausar(16);
        return;
    }

    int alto = 10 + activos * 5 + 1;
    pantalla("LISTA AUTORES", alto);

    int j = 0;
    for(int i=0; i<cantidad; i++){
        Autor a = Autor::leer(i);

        if(a.getEstado()){
            locate(30, 10 + j *5);
            cout << "ID: " << a.getAutorID() << endl;
            locate(30, 11 + j *5);
            cout << "Nombre: " << a.getNombre() << endl;
            locate(30, 12 + j *5);
            cout << "Apellido: " << a.getApellido() << endl;
            locate(30, 13 + j *5);
            cout << "Nacionalidad: " << a.getNacionalidad() << endl;
            locate(30, 14 + j *5);
            cout << "-----------------------------------" << endl;
            j++;
        }
    }

    pausar(alto + 2);
}

void listarGeneros(){
    int cantidad = Genero::contarRegistros();
    int activos = 0;

    for(int i=0; i<cantidad; i++){
        Genero g = Genero::leer(i);
        if(g.getEstado()){
            activos++;
        }
    }

    if(activos == 0){
        pantalla("LISTAR GENEROS", 14);
        locate(30, 12);
        cout << "No hay generos cargados.";
        pausar(16);
        return;
    }

    int alto = 10 + activos * 3 + 1;
    pantalla("LISTAR GENEROS", alto);

    int j = 0;
    for(int i=0; i<cantidad; i++){
        Genero g = Genero::leer(i);

        if(g.getEstado()){
            int fila = 10 + j * 3;
            locate(30, fila + 1);
            cout << "ID: " << g.getIdGenero() << endl;
            locate(30, fila + 2);
            cout << "Descripcion: " << g.getDescripcion() << endl;
            locate(30, fila + 3);
            cout << "-----------------------------------" << endl;
            j++;
        }
    }

    pausar(alto + 2);
}

void listarSocios(){
    int cantidad = Socio::contarRegistros();
    int activos = 0;

    for(int i=0; i<cantidad; i++){
        Socio s = Socio::leer(i);
        if(s.getEstado()){
            activos++;
        }
    }

    if(activos == 0){
        pantalla("LISTAR SOCIOS", 14);
        locate(30, 12);
        cout << "No hay socios cargados.";
        pausar(16);
        return;
    }

    int alto = 10 + activos * 9 + 1;
    pantalla("LISTAR SOCIOS", alto);

    int j = 0;
    for(int i=0; i<cantidad; i++){
        Socio s = Socio::leer(i);

        if(s.getEstado()){
            Fecha f = s.getFechaNacimiento();
            int fila = 10 + j * 9;
            locate(30 , fila + 1);
            cout << "ID: " << s.getIdSocio() << endl;
            locate(30 , fila +  2);
            cout << "Nombre: " << s.getNombre() << endl;
            locate(30 , fila +  3);
            cout << "Apellido: " << s.getApellido() << endl;
            locate(30 , fila +  4);
            cout << "DNI: " << s.getDNI() << endl;
            locate(30 , fila +  5);
            cout << "Telefono: " << s.getTelefono() << endl;
            locate(30 , fila +  6);
            cout << "Email: " << s.getEmail() << endl;
            locate(30 , fila +  7);
            cout << "Domicilio: " << s.getDomicilio() << endl;
            locate(30 , fila +  8);
            cout << "Fecha de Nacimiento: " << f.getDia() << "/" << f.getMes() << "/" << f.getAnio() << endl;
            locate(30 , fila +  9);
            cout << "-----------------------------------" << endl;
            j++;
        }
    }

    pausar(alto + 2);
}

void listarLibros(){
    int cantidad = Libro::contarRegistros();
    int activos = 0;

    for(int i=0; i<cantidad; i++){
        Libro l = Libro::leer(i);
        if(l.getEstado()){
            activos++;
        }
    }

    if(activos == 0){
        pantalla("LISTAR LIBROS", 14);
        locate(30, 12);
        cout << "No hay libros cargados.";
        pausar(16);
        return;
    }

    int alto = 10 + activos * 11 + 1;
    pantalla("LISTAR LIBROS", alto);

    int j = 0;
    for(int i=0; i<cantidad; i++){
        Libro l = Libro::leer(i);

        if(l.getEstado()){
            Fecha f = l.getAnioPublicacion();
            int fila = 10 + j * 11;
            locate(30 , fila + 1);
            cout << "ID: " << l.getIdLibro() << endl;
            locate(30 , fila +  2);
            cout << "ISBN: " << l.getIsbn() << endl;
            locate(30 , fila +  3);
            cout << "Titulo: " << l.getTitulo() << endl;
            locate(30 , fila +  4);
            cout << "ID Autor: " << l.getIdAutor() << endl;
            locate(30 , fila +  5);
            cout << "ID Genero: " << l.getIdGenero() << endl;
            locate(30 , fila +  6);
            cout << "Editorial: " << l.getEditorial() << endl;
            locate(30 , fila +  7);
            cout << "Fecha de Publicacion: " << f.getDia() << "/" << f.getMes() << "/" << f.getAnio() << endl;
            locate(30 , fila +  9);
            cout << "Stock total: " << l.getStockTotal() << endl;
            locate(30 , fila +  10);
            cout << "Stock Disponible: " << l.getStockDisponible() << endl;
            locate(30 , fila +  11);
            cout << "-----------------------------------" << endl;
            j++;
        }
    }

    pausar(alto + 2);
}

void registrarPrestamoRetro(){
    pantalla("REGISTRAR PRESTAMO");

    int idSocio, idLibro;
    Prestamo p;

    locate(32,12); cout << "ID Socio: ";
    cin >> idSocio;

    if(buscarSocioPorID(idSocio) < 0){
        locate(32,20); cout << "No existe ese socio.";
        pausar();
        return;
    }

    locate(32,13); cout << "ID Libro: ";
    cin >> idLibro;

    int posLibro = Libro::buscarPorID(idLibro);

    if(posLibro < 0){
        locate(32,20); cout << "No existe ese libro.";
        pausar();
        return;
    }

    Libro libro = Libro::leer(posLibro);

    if(libro.getStockDisponible() <= 0){
        locate(32,20); cout << "No hay stock disponible.";
        pausar();
        return;
    }

    locate(32,15); cout << "Fecha prestamo:";
    Fecha fp = pedirFecha(54,15);

    locate(32,18); cout << "Fecha vencimiento:";
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

    locate(32,21);
    if(p.guardar() && libro.modificar(posLibro)) cout << "Prestamo registrado correctamente.";
    else cout << "Error al registrar prestamo.";

    pausar();
}

void devolverPrestamoRetro(){
    pantalla("DEVOLVER PRESTAMO");

    int idPrestamo;

    locate(32,12); cout << "ID Prestamo: ";
    cin >> idPrestamo;

    int posPrestamo = buscarPrestamoPorID(idPrestamo);

    if(posPrestamo < 0){
        locate(32,20); cout << "No existe ese prestamo.";
        pausar();
        return;
    }

    Prestamo p = Prestamo::leer(posPrestamo);

    if(p.getDevuelto()){
        locate(32,20); cout << "Ese prestamo ya fue devuelto.";
        pausar();
        return;
    }

    int posLibro = Libro::buscarPorID(p.getIdLibro());

    if(posLibro < 0){
        locate(32,20); cout << "No se encontro el libro.";
        pausar();
        return;
    }

    Libro libro = Libro::leer(posLibro);

    locate(32,14); cout << "Fecha devolucion:";
    Fecha fd = pedirFecha(54,14);

    p.setFechaDevolucion(fd);
    p.setDevuelto(true);
    libro.devolverEjemplar();

    locate(32,20);
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

    locate(32,11); cout << "ID Cuota: " << c.getIdCuota();

    locate(32,12); cout << "ID Socio: ";
    cin >> idSocio;

    if(buscarSocioPorID(idSocio) < 0){
        locate(32,20); cout << "No existe ese socio.";
        pausar();
        return;
    }

    locate(32,13); cout << "Mes: ";
    cin >> mes;

    locate(32,14); cout << "Anio: ";
    cin >> anio;

    locate(32,15); cout << "Fecha cobro:";
    Fecha fc = pedirFecha(54,15);

    locate(32,18); cout << "Importe: ";
    cin >> importe;

    c.setIdSocio(idSocio);
    c.setMes(mes);
    c.setAnio(anio);
    c.setFechaCobro(fc);
    c.setImporte(importe);
    c.setPagada(false);
    c.setEstado(true);

    locate(32,21);
    if(c.guardar()) cout << "Cuota guardada correctamente.";
    else cout << "Error al guardar cuota.";

    pausar();
}

void registrarPagoRetro(){
    pantalla("REGISTRAR PAGO");

    int idSocio, idCuota;
    float importe;

    locate(32,12); cout << "ID Socio: ";
    cin >> idSocio;

    if(buscarSocioPorID(idSocio) < 0){
        locate(32,20); cout << "No existe ese socio.";
        pausar();
        return;
    }

    locate(32,13); cout << "ID Cuota: ";
    cin >> idCuota;

    int posCuota = buscarCuotaPorID(idCuota);

    if(posCuota < 0){
        locate(32,20); cout << "No existe esa cuota.";
        pausar();
        return;
    }

    Cuotas cuota = Cuotas::leer(posCuota);

    if(cuota.getPagada()){
        locate(32,20); cout << "La cuota ya esta pagada.";
        pausar();
        return;
    }

    if(cuota.getIdSocio() != idSocio){
        locate(32,20); cout << "La cuota no corresponde al socio.";
        pausar();
        return;
    }

    locate(32,15); cout << "Fecha pago:";
    Fecha fp = pedirFecha(54,15);

    locate(32,18); cout << "Importe: ";
    cin >> importe;

    Pagos pago;
    pago.setIdPago(Pagos::generarNuevoID());
    pago.setIdSocio(idSocio);
    pago.setIdCuota(idCuota);
    pago.setFechaPago(fp);
    pago.setImporte(importe);
    pago.setEstado(true);

    cuota.marcarPagada();

    locate(32,21);
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

        locate(34,20); cout << "Seleccione una opcion: ";
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

        locate(34,20); cout << "Seleccione una opcion: ";
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

        locate(34,21); cout << "Seleccione una opcion: ";
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
        volver(19);

        locate(34,24); cout << "Seleccione una opcion: ";
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
        case 0: return;
        default: pausar(); break;
        }
    }
}

void menuPrestamos(){
    int op;
    while(true){
        pantalla("MENU PRESTAMOS");
        opcion(10,1,"Registrar prestamo");
        opcion(11,2,"Listar prestamos");
        opcion(12,3,"Marcar Vencido");
        opcion(13,4,"Devolver prestamo");
        opcion(14,5,"Listados");
        opcion(15,6,"Consultas");
        volver(18);

        locate(34,24); cout << "Seleccione una opcion: ";
        cin >> op;

        switch(op){
        case 1: registrarPrestamoRetro(); break;
        case 2: pantalla("LISTAR PRESTAMOS"); Prestamo::listar(); break;
        case 3: pantalla("MARCAR VENCIDO"); Prestamo::marcarPrestamoVencido(); break;
        case 4: devolverPrestamoRetro(); break;
        case 5: menuPrestamosListados(); break;
        case 6: menuPrestamosConsultas(); break;
        case 0: return;
        default: pausar(); break;
        }
    }
}

void menuPrestamosListados(){
    int op;
    while(true){
        pantalla("MENU CONSULTAS");
        opcion(10,1,"Prestamos Activos");
        opcion(11,2,"Prestamos Vencidos");
        opcion(12,3,"Ordenados Por Fecha");
        volver(15);

        locate(34,24); cout << "Seleccione una opcion: ";
        cin >> op;

        switch(op){
        case 1: pantalla("PRESTAMOS ACTIVOS"); Prestamo::listarActivos(); break;
        case 2: pantalla("PRESTAMOS VENCIDOS"); Prestamo::listarVencidos(); break;
        case 3: pantalla("PRESTAMOS POR FECHA"); Prestamo::listarOrdenadosPorFecha(); break;
        case 0: return;
        default: pausar(); break;
        }
    }
}

void menuPrestamosConsultas(){
    int op;
    while(true){
        pantalla("MENU CONSULTAS");
        opcion(10,1,"Consultar por socio");
        opcion(11,2,"Consultar por libro");
        opcion(12,3,"Consultar por estado");
        volver(15);

        locate(34,24); cout << "Seleccione una opcion: ";
        cin >> op;

        switch(op){
        case 1: pantalla("PRESTAMOS POR SOCIO"); Prestamo::consultarPorSocio(); break;
        case 2: pantalla("PRESTAMOS POR LIBRO"); Prestamo::consultarPorLibro(); break;
        case 3: pantalla("PRESTAMOS POR ESTADO"); Prestamo::consultarPorEstado(); break;
        case 0: return;
        default: pausar(); break;
        }
    }
}

void menuCuotas(){
    int op;
    while(true){
        pantalla("MENU CUOTAS");
        opcion(11,1,"Cargar cuota");
        opcion(12,2,"Listar cuotas");
        opcion(13,3,"Cuotas pagadas");
        opcion(14,4,"Cuotas pendientes");
        volver(17);

        locate(34,21); cout << "Seleccione una opcion: ";
        cin >> op;

        switch(op){
        case 1: altaCuota(); break;
        case 2: pantalla("LISTAR CUOTAS"); Cuotas::listar(); break;
        case 3: pantalla("CUOTAS PAGADAS"); Cuotas::listarPagadas(); break;
        case 4: pantalla("CUOTAS PENDIENTES"); Cuotas::listarPendientes(); break;
        case 0: return;
        default: pausar(); break;
        }
    }
}

void menuPagos(){
    int op;
    while(true){
        pantalla("MENU PAGOS");
        opcion(11,1,"Registrar pago");
        opcion(12,2,"Listar pagos");
        opcion(13,3,"Pagos ordenados por socio");
        opcion(14,4,"Pagos por socio");
        opcion(15,5,"Pagos por mes");
        volver(18);

        locate(34,21); cout << "Seleccione una opcion: ";
        cin >> op;

        switch(op){
        case 1: registrarPagoRetro(); break;
        case 2: pantalla("LISTAR PAGOS"); Pagos::listar(); break;
        case 3: pantalla("PAGOS ORDENADOS POR SOCIO"); Pagos::listarOrdenadosPorSocio(); break;
        case 4: pantalla("PAGOS POR SOCIO"); Pagos::listarPorSocio(); break;
        case 5: pantalla("PAGOS POR MES"); Pagos::pagosPorMes(); break;
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

        locate(34,20); cout << "Seleccione una opcion: ";
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
        locate(32,13);
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

    int activos = 0;
    for(int i=0; i<cantidadLibros; i++)
        if(Libro::buscarPorID(ids[i]) >= 0) activos++;

    int alto = 10 + activos * 5 + 1;
    pantalla("LIBROS MAS PRESTADOS", alto);

    int j = 0;
    for(int i=0; i<cantidadLibros; i++){
        int posLibro = Libro::buscarPorID(ids[i]);

        if(posLibro >= 0){
            Libro libro = Libro::leer(posLibro);
            int fila = 10 + j * 5;
            locate(30, fila + 1); cout << "Puesto " << (j + 1) << " - ID: " << libro.getIdLibro();
            locate(30, fila + 2); cout << "Titulo: " << libro.getTitulo();
            locate(30, fila + 3); cout << "Cantidad de prestamos: " << cantidades[i];
            locate(30, fila + 4); cout << "-----------------------------------";
            j++;
        }
    }

    delete[] ids;
    delete[] cantidades;

    pausar(alto + 2);
}

void menuReportes(){
    int op;

    while(true){
        pantalla("REPORTES");

        opcion(10,1,"Prestamos por rango de fechas");
        opcion(11,2,"Libros mas prestados");
        opcion(12,3,"Cuotas pendientes por socio");
        opcion(13,4,"Pagos realizados por mes");
        volver(16);

        locate(34,24);
        cout << "Seleccione una opcion: ";
        cin >> op;

        switch(op){
        case 1: pantalla("PRESTAMOS POR RANGO"); Prestamo::listarPorRangoFechas(); break;
        case 2: reporteLibrosMasPrestados(); break;
        case 3: pantalla("CUOTAS PENDIENTES POR SOCIO"); Cuotas::listarPendientesPorSocio(); break;
        case 4: pantalla("PAGOS POR MES"); Pagos::pagosPorMes(); break;
        case 0: return;
        default: pausar(); break;
        }
    }
}

void realizarBackupArchivo(const char* nombreDat, const char* nombreBak){
    pantalla("COPIA DE SEGURIDAD");

    locate(32,13);
    if(copiarArchivo(nombreDat, nombreBak)){
        cout << "Backup realizado: " << nombreBak;
    }
    else{
        cout << "No se pudo realizar backup de " << nombreDat;
    }

    pausar();
}

void restaurarBackupArchivo(const char* nombreBak, const char* nombreDat){
    pantalla("RESTAURAR BACKUP");

    locate(32,13);
    if(copiarArchivo(nombreBak, nombreDat)){
        cout << "Backup restaurado: " << nombreDat;
    }
    else{
        cout << "No se pudo restaurar " << nombreBak;
    }

    pausar();
}

void realizarBackup(){
    copiarArchivo("Autores.dat", "Autores.bak");
    copiarArchivo("Generos.dat", "Generos.bak");
    copiarArchivo("Libros.dat", "Libros.bak");
    copiarArchivo("Socios.dat", "Socios.bak");
    copiarArchivo("Prestamos.dat", "Prestamos.bak");
    copiarArchivo("Cuotas.dat", "Cuotas.bak");
    copiarArchivo("Pagos.dat", "Pagos.bak");
}

void restaurarBackup(){
    copiarArchivo("Autores.bak", "Autores.dat");
    copiarArchivo("Generos.bak", "Generos.dat");
    copiarArchivo("Libros.bak", "Libros.dat");
    copiarArchivo("Socios.bak", "Socios.dat");
    copiarArchivo("Prestamos.bak", "Prestamos.dat");
    copiarArchivo("Cuotas.bak", "Cuotas.dat");
    copiarArchivo("Pagos.bak", "Pagos.dat");
}

void menuBackup(){
    int op;

    while(true){
        pantalla("REALIZAR COPIA DE SEGURIDAD");

        opcion(10,1,"Libros");
        opcion(11,2,"Socios");
        opcion(12,3,"Autores");
        opcion(13,4,"Generos");
        opcion(14,5,"Prestamos");
        opcion(15,6,"Cuotas");
        opcion(16,7,"Pagos");
        opcion(17,8,"Todos los archivos");
        volver(20);

        locate(34,23);
        cout << "Seleccione una opcion: ";
        cin >> op;

        switch(op){
        case 1: realizarBackupArchivo("Libros.dat", "Libros.bak"); break;
        case 2: realizarBackupArchivo("Socios.dat", "Socios.bak"); break;
        case 3: realizarBackupArchivo("Autores.dat", "Autores.bak"); break;
        case 4: realizarBackupArchivo("Generos.dat", "Generos.bak"); break;
        case 5: realizarBackupArchivo("Prestamos.dat", "Prestamos.bak"); break;
        case 6: realizarBackupArchivo("Cuotas.dat", "Cuotas.bak"); break;
        case 7: realizarBackupArchivo("Pagos.dat", "Pagos.bak"); break;
        case 8:
            pantalla("COPIA DE SEGURIDAD");
            realizarBackup();
            rlutil::locate(32,13);
            cout << "Backup de todos los archivos realizado.";
            pausar();
            break;
        case 0: return;
        default: pausar(); break;
        }
    }
}

void menuRestaurarBackup(){
    int op;

    while(true){
        pantalla("RESTAURAR COPIA DE SEGURIDAD");

        opcion(10,1,"Libros");
        opcion(11,2,"Socios");
        opcion(12,3,"Autores");
        opcion(13,4,"Generos");
        opcion(14,5,"Prestamos");
        opcion(15,6,"Cuotas");
        opcion(16,7,"Pagos");
        opcion(17,8,"Todos los archivos");
        volver(20);

        locate(34,23);
        cout << "Seleccione una opcion: ";
        cin >> op;

        switch(op){
        case 1: restaurarBackupArchivo("Libros.bak", "Libros.dat"); break;
        case 2: restaurarBackupArchivo("Socios.bak", "Socios.dat"); break;
        case 3: restaurarBackupArchivo("Autores.bak", "Autores.dat"); break;
        case 4: restaurarBackupArchivo("Generos.bak", "Generos.dat"); break;
        case 5: restaurarBackupArchivo("Prestamos.bak", "Prestamos.dat"); break;
        case 6: restaurarBackupArchivo("Cuotas.bak", "Cuotas.dat"); break;
        case 7: restaurarBackupArchivo("Pagos.bak", "Pagos.dat"); break;
        case 8:
            pantalla("RESTAURAR BACKUP");
            restaurarBackup();
            locate(32,13);
            cout << "Backup de todos los archivos restaurado.";
            pausar();
            break;
        case 0: return;
        default: pausar(); break;
        }
    }
}

void menuConfiguracion(){
    int op;

    while(true){
        pantalla("CONFIGURACION");

        opcion(12,1,"Realizar copia de seguridad");
        opcion(13,2,"Restaurar copia de seguridad");
        volver(16);

        locate(34,20);
        cout << "Seleccione una opcion: ";
        cin >> op;

        switch(op){
        case 1: menuBackup(); break;
        case 2: menuRestaurarBackup(); break;
        case 0: return;
        default: pausar(); break;
        }
    }
}
