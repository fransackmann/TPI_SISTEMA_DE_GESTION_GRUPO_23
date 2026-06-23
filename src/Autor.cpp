/// biblotecas a usar
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include "rlutil.h"
#include "Menus.h"
/// incluimos el .h donde estan declarados los atributos y metodos de Autor
#include "Autor.h"

using namespace std;
using namespace rlutil;
/// constructor vacio para que el objeto pueda existir en memoria aunque todavía no tenga datos reales
Autor::Autor(){

    /// inicializacion de atributos en cero
    _idAutor = 0;
    strcpy(_nombre, "");
    strcpy(_apellido, "");
    strcpy(_nacionalidad, "");
    _estado = true;
}

/// contructor con parametros para hacer pruebas
Autor::Autor(int idAutor, const char* nombre, const char* apellido, const char* nacionalidad, bool estado){

    /// asignamos los atributos a variables para mandar los valores por pametros
    _idAutor = idAutor;
    strcpy(_nombre, nombre);
    strcpy(_apellido, apellido);
    strcpy(_nacionalidad, nacionalidad);
    _estado = estado;
}

/// Get: permite obtener (leer) el valor de un atributo privado
/// Set: permite modificar o actualizar el valor de un atributo privado
int Autor::getAutorID(){ return _idAutor; }
void Autor::setAutorID(int idAutor){ _idAutor = idAutor; }

// usamos const para indicar que el texto recibido, puede leerse pero no modificarse
//usamos char* porque almacena la direccion de memoria, donde comienza la cadena de caracteres
// usamos strcpy para copiar los caracteres, y guardar lo ingresado
const char* Autor::getNombre(){ return _nombre; }
void Autor::setNombre(const char* nombre){ strcpy(_nombre, nombre); }

// usamos const para indicar que el texto recibido, puede leerse pero no modificarse
// usamos char* porque almacena la direccion de memoria, donde comienza la cadena de caracteres
// usamos strcpy para copiar los caracteres, y guardar lo ingresado
const char* Autor::getApellido(){ return _apellido; }
void Autor::setApellido(const char* apellido){ strcpy(_apellido, apellido); }

// usamos const para indicar que el texto recibido, puede leerse pero no modificarse
// usamos char* porque almacena la direccion de memoria, donde comienza la cadena de caracteres
// usamos strcpy para copiar los caracteres, y guardar lo ingresado
const char* Autor::getNacionalidad(){ return _nacionalidad; }
void Autor::setNacionalidad(const char* nacionalidad){ strcpy(_nacionalidad, nacionalidad); }

bool Autor::getEstado(){ return _estado; }
void Autor::setEstado(bool estado){ _estado = estado; }

/// Metodo para mostrar las variables simples cargadas
void Autor::mostrar(int fila){

    /// si estado es true mostramos lo cargado
    if(_estado){
        locate(30, fila + 1);cout << "ID: " << _idAutor << endl;
        locate(30, fila + 2);cout << "Nombre: " << _nombre << endl;
        locate(30, fila + 3);cout << "Apellido: " << _apellido << endl;
        locate(30, fila + 4);cout << "Nacionalidad: " << _nacionalidad << endl;
        locate(30, fila + 5);cout << "-----------------------------" << endl;
    }
}

/// Guardamos en un arc.dat (binario) los datos cargados
bool Autor::guardar(){

    /// usamos FILE* pq es una varialbe de tipo puntero a archivo
    /// pArchivo es el nombre de la variable que maneja el archivo
    /// fopen para abrir ese arc y mandamos como parametros el nombre que queremos
    /// y "ab" que abre el arc y agrega los datos al final
    FILE* pArchivo = fopen("Autores.dat", "ab");

    /// si es igual a null (null = no se pudo abrir el arc)
    if(pArchivo == NULL){

        /// rtn false indicando que no se pudo guardar los datos ingresados
        return false;
    }

    /// usamos fwrite para escribir los datos
    /// usamos this para que identifique el objeto actual
    /// usamos sizeof es el tamño del objeto autor
    /// usamos 1 por que guarda un registro a la vez en el arc pArchivo
    bool ok = fwrite(this, sizeof(Autor), 1, pArchivo);

    /// usamos fclose para cerrar el arc con todos los datos guardados
    fclose(pArchivo);

    /// rtn true
    return ok;
}

/// Metodo para contar cant. de registros o de autor en si
int Autor::contarRegistros(){

    /// lo abrimos en modo lectura (rb)
    FILE* pArchivo = fopen("Autores.dat", "rb");

    /// si es igual null no se pudo abrir el arc
    if(pArchivo == NULL){

        /// un rtn 0 para indicar que no se pudo abrir el arc
        return 0;
    }

    /// fseek para mover la posicion del cursor
    /// usamos pArchivo porque es el archivo sobre el cual moveremos el cursor
    /// usamos 0 para desplazarlo 0 bytes
    /// usamos SEEK_END para ir al final del arc
    fseek(pArchivo, 0, SEEK_END);

    /// usamos ftell y le mandamos el arc pq nos da la cant de bytes totales
    /// entonces lo dividimos usando sizeof que nos da el tam del objeto
    /// esa division la guardamos en la variable
    int cantidad = ftell(pArchivo) / sizeof(Autor);

    /// cerramos el arc
    fclose(pArchivo);

    /// retornamos la cantidad
    return cantidad;
}

/// Metodo para leer un objeto Autor
Autor Autor::leer(int posicion){

    /// creamos un objeto autor (con el constructor vacio)
    Autor autor;

    /// lo abrimos en modo lectura
    FILE* pArchivo = fopen("Autores.dat", "rb");

    /// si es igual null no se pudo abrir el arc
    if(pArchivo == NULL){

        /// rtn del objeto vacio
        return autor;
    }

    /// usamos fseek en este caso para poner el cursor desde el principio (SEEK_SET)
    /// le mandamos como parametro pArchvio para leerlo
    /// y posicion * sizeof Autor para leer en el arc esa posicion en especifico
    fseek(pArchivo, posicion * sizeof(Autor), SEEK_SET);

    /// usamos fread para leer el registro completo
    /// pasamos la direccion de memoria del objeto autor, para que se carguen ahi los datos leidos
    /// mandamos su tamaña, la cant. de registro (1) y el arc que estamos leyendo
    fread(&autor, sizeof(Autor), 1, pArchivo);

    /// cerramos el arc
    fclose(pArchivo);

    /// retornamos el objeto
    return autor;
}

/// Metodo para generar nuevos IDs
int Autor::generarNuevoID(){

    /// inicializamos las variables
    /// cantidad = cantidad de autores guardados en el archivo
    int cantidad = contarRegistros();
    int maximo = 0;

    /// recorremos todos los registros del archivo
    for(int i = 0; i < cantidad; i++){

        /// creamos un objeto temporal autor
        /// leer(i) devuelve el autor ubicado en la posicion i
        /// y lo guardamos en el objeto para poder consultar sus datos
        Autor autor = leer(i);

        /// si el ID del autor es mayor al maximo actual
        if(autor.getAutorID() > maximo){

            /// actualizamos el valor maximo encontrado
            maximo = autor.getAutorID();
        }
    }

    /// devolvemos el siguiente ID disponible
    /// para evitar IDs repetidos
    return maximo + 1;
}

/// Metodo para mostrar la lista de autores
void Autor::listar(){

    /// limpiamos la pantalla
    system("cls");

    /// obtenemos la cantidad de autores guardados en el archivo
    int cantidad = contarRegistros();

    /// recorremos todos los registros del archivo
    for(int i = 0; i < cantidad; i++){

        /// leemos el autor ubicado en la posicion i
        /// y lo guardamos en un objeto temporal
        Autor autor = leer(i);

        /// mostramos los datos del autor leido
        autor.mostrar(5);
    }

    /// pausamos la pantalla para visualizar los resultados
    system("pause");
}

/// Metodo para listar ordenado por apellido
void Autor::listarOrdenadoPorApellido(){

    /// limpiamos pantalla
    system("cls");

    /// inicializamos variable
    /// cantidad es igual a la cant. de registros
    int cantidad = contarRegistros();

    /// si cantidad es igual 0
    if(cantidad == 0){

        /// mostramos cartel avisando q no hay autores cargados
        cout << "No hay autores cargados." << endl;

        /// pausamos la pantalla para visualizar el resultado
        system("pause");
        return;
    }

    /// Creamos un vector dinámico de objetos Autor
    /// autores apunta al primer elemento del vector
    Autor* autores = new Autor[cantidad];

    /// leemos todos los autores del archivo y los cargamos en el vector
    for(int i = 0; i < cantidad; i++){
        autores[i] = leer(i);
    }
    int y = 0;
    /// ciclo para controlar la cant. de pasadas
    for(int i = 0; i < cantidad - 1; i++){

        /// ciclo para comparar autores
        for(int j = 0; j < cantidad - 1 - i; j++){

            /// strcmp compara los apellidos por orden alfabetico
            /// comparamos el primero con el que le sigue y asi sucesivamente
            /// si devuelve un valor mayor a 0
            /// significa que el apellido de la izquierda
            /// viene despues alfabeticamente que el de la derecha
            if(strcmp(autores[j].getApellido(), autores[j + 1].getApellido()) > 0){
                Autor aux = autores[j];
                autores[j] = autores[j + 1];
                autores[j + 1] = aux;
            }
        }
    }
    int alto = 10 + cantidad * 5 + 1;
    pantalla("LISTAR AUTORES", alto);
    /// mostramos los autores ordenados
    for(int i = 0; i < cantidad; i++){
        autores[i].mostrar(10 + y * 5);
        y++;
    }

    /// liberamos memoria
    delete[] autores;

    /// pausa de pantalla
    pausar(alto + 2);
}
