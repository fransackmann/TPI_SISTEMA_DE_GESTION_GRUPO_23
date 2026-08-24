# Sistema de Gestión de Biblioteca

Sistema de gestión integral para una biblioteca, desarrollado en **C++** para consola. Administra catálogo de libros, socios, préstamos, cuotas y reportes, con persistencia propia en archivos binarios, sin depender de una base de datos externa.

Proyecto desarrollado en el marco de la Universidad Tecnológica Nacional (UTN - FRGP).

## Funcionalidades

El sistema está organizado en módulos accesibles desde un menú principal:

- **Libros** — alta, baja, modificación y consulta del catálogo.
- **Socios** — gestión de los socios de la biblioteca.
- **Préstamos** — registro y seguimiento de préstamos de libros.
- **Cuotas y pagos** — administración de cuotas y pagos asociados a cada socio.
- **Autores** — gestión del listado de autores.
- **Géneros** — gestión de los géneros literarios disponibles.
- **Reportes** — generación de reportes sobre el estado de la biblioteca.
- **Configuración** — ajustes generales del sistema.

Los datos se persisten en archivos binarios propios (`.dat`), sin depender de una base de datos externa.

## Tecnologías

- **C++**
- [rlutil.h](https://github.com/tapio/rlutil) para la interfaz de consola (menús, colores, posicionamiento de texto)
- Proyecto de **Code::Blocks** (`TPI_Sist_De_Gestion_Grupo_23.cbp`)
- Persistencia mediante archivos binarios (`Socios.dat`, `Autores.dat`, `Generos.dat`, etc.)

## Estructura del proyecto

```
├── main.cpp                  # Punto de entrada y menú principal
├── include/                  # Headers de cada módulo (Libro, Socio, Prestamo, Cuotas, Pagos, Autor, Genero, Fecha, Menus)
├── src/                      # Implementación de cada módulo
├── *.dat / *.bak              # Archivos de datos persistidos por el sistema
└── TPI_Sist_De_Gestion_Grupo_23.cbp   # Proyecto de Code::Blocks
```

## Cómo compilar y ejecutar

1. Abrir `TPI_Sist_De_Gestion_Grupo_23.cbp` con [Code::Blocks](http://www.codeblocks.org/) (con un compilador GCC/MinGW configurado).
2. Compilar el proyecto (`Build`).
3. Ejecutar el binario generado en `bin/Debug/`.

También se puede compilar manualmente con GCC:

```bash
g++ main.cpp src/*.cpp -Iinclude -o sistema_biblioteca
./sistema_biblioteca
```

## Desarrollo

Proyecto desarrollado en equipo. Ver [contribuidores](https://github.com/fransackmann/sistema-gestion-biblioteca-cpp/graphs/contributors).
