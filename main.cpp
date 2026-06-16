#include <iostream>
#include "Autor.h"
#include "Fecha.h"
#include "Genero.h"
using namespace std;

void menuLibros(){
    int rta;
    while(true){
        system("cls");
        cout << "   Menu Libros" << endl;
        cout << "-.-.-.-.-.-.-.-.-.-.-.-.-.-.-" << endl;
        cout << "1- Libros" << endl;
        cout << "2- Generos" << endl;
        cout << "3- Autores" << endl;
        cout << endl;
        cout << "0- Volver al menu principal" << endl;
        cin >> rta;
        system("cls");
        switch(rta){
        case 1:
            break;
        case 2:{
            Genero genero;
            genero.menuGeneros();
            break;
        }
        case 3:{
            Autor autor;
            autor.menuAutores();
            break;
        }
        case 0:
            return;
            break;

        }
        cout<<endl;
        system("pause");
    }


}





int main(){
    int rta;
    while(true){
        system("cls");
        cout << "   Gestion Biblioteca" << endl;
        cout << "-.-.-.-.-.-.-.-.-.-.-.-.-.-.-" << endl;
        cout << "1- Menu Libros" << endl;
        cout << "2- Menu Socios" << endl;
        cout << "3- Configuracion" << endl;
        cout << endl;
        cout << "0- Salir.." << endl;
        cin >> rta;
        system("cls");
        switch(rta){
        case 1:
            menuLibros();
            break;
        case 2:
            break;
        case 3:
            break;
        case 0:
            return 0;
            break;

        }
        cout<<endl;
        system("pause");
    }
    return 0;
}
