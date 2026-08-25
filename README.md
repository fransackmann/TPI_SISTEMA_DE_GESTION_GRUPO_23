# Sistema de Gestión de Biblioteca

*[English version below](#library-management-system)*

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
- Proyecto de **Code::Blocks** (`SistemaGestionBiblioteca.cbp`)
- Persistencia mediante archivos binarios (`Socios.dat`, `Autores.dat`, `Generos.dat`, etc.)

## Estructura del proyecto

```
├── main.cpp                  # Punto de entrada y menú principal
├── include/                  # Headers de cada módulo (Libro, Socio, Prestamo, Cuotas, Pagos, Autor, Genero, Fecha, Menus)
├── src/                      # Implementación de cada módulo
├── *.dat / *.bak              # Archivos de datos persistidos por el sistema
└── SistemaGestionBiblioteca.cbp   # Proyecto de Code::Blocks
```

## Cómo compilar y ejecutar

1. Abrir `SistemaGestionBiblioteca.cbp` con [Code::Blocks](http://www.codeblocks.org/) (con un compilador GCC/MinGW configurado).
2. Compilar el proyecto (`Build`).
3. Ejecutar el binario generado en `bin/Debug/`.

También se puede compilar manualmente con GCC:

```bash
g++ main.cpp src/*.cpp -Iinclude -o sistema_biblioteca
./sistema_biblioteca
```

## Desarrollo

Proyecto desarrollado en equipo. Ver [contribuidores](https://github.com/fransackmann/sistema-gestion-biblioteca-cpp/graphs/contributors).

---

## Library Management System

Comprehensive management system for a library, built in **C++** for the console. Handles the book catalog, members, loans, dues and reports, with its own persistence in binary files, with no external database dependency.

Developed as part of the Universidad Tecnológica Nacional (UTN - FRGP).

### Features

The system is organized into modules accessible from a main menu:

- **Books** — add, remove, update and browse the catalog.
- **Members** — library member management.
- **Loans** — registration and tracking of book loans.
- **Dues and payments** — management of dues and payments per member.
- **Authors** — author list management.
- **Genres** — management of available literary genres.
- **Reports** — generates reports on the library's status.
- **Settings** — general system configuration.

Data is persisted in the system's own binary files (`.dat`), with no external database dependency.

### Technologies

- **C++**
- [rlutil.h](https://github.com/tapio/rlutil) for the console interface (menus, colors, text positioning)
- **Code::Blocks** project (`SistemaGestionBiblioteca.cbp`)
- Persistence via binary files (`Socios.dat`, `Autores.dat`, `Generos.dat`, etc.)

### Project structure

```
├── main.cpp                  # Entry point and main menu
├── include/                  # Headers for each module (Libro, Socio, Prestamo, Cuotas, Pagos, Autor, Genero, Fecha, Menus)
├── src/                      # Implementation of each module
├── *.dat / *.bak              # Data files persisted by the system
└── SistemaGestionBiblioteca.cbp   # Code::Blocks project
```

### How to build and run

1. Open `SistemaGestionBiblioteca.cbp` with [Code::Blocks](http://www.codeblocks.org/) (with a GCC/MinGW compiler configured).
2. Build the project.
3. Run the binary generated in `bin/Debug/`.

You can also compile it manually with GCC:

```bash
g++ main.cpp src/*.cpp -Iinclude -o library_system
./library_system
```

### Team

Developed as a team project. See [contributors](https://github.com/fransackmann/sistema-gestion-biblioteca-cpp/graphs/contributors).
