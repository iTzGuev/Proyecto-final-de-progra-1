#include "Jugador.h"
#include "ContenedorJugadores.h"
#include "Librerias.h"
#include "Juego.h"
#include "Tempo.h"

//Función del menú principal
void menuPrincipal() {
    ContenedorJugadores contenedor;
    int opcion = 0;

    do {
        system("cls");
        cout << "=============================\n";
        cout << "     DUELO DE REFLEJOS    \n";
        cout << "=============================\n";
        cout << "1. Jugar\n";
        cout << "2. Ver puntajes\n";
        cout << "3. Salir\n";
        cout << "=============================\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case 1: {
            system("cls");
            string nombre1, nombre2;
            cout << "Ingrese nombre del Jugador 1: ";
            getline(cin, nombre1);
            cout << "Ingrese nombre del Jugador 2: ";
            getline(cin, nombre2);

            Jugador j1(nombre1, 'a');
            Jugador j2(nombre2, 'l');

            Juego juego(j1, j2, 3);
            juego.iniciarJuego();

            cout << "\nPresione Enter para volver al menú...";
            cin.ignore();
            break;
        }
        case 2:
            system("cls");
            contenedor.cargarDatos();
            cout << "\nPresione Enter para volver al menú...";
            cin.ignore();
            break;

        case 3:
            cout << "\nSaliendo del juego... ¡Hasta pronto!\n";
            break;

        default:
            cout << "Opción inválida. Intente de nuevo.\n";
            this_thread::sleep_for(chrono::seconds(2));
            break;
        }
    } while (opcion != 3);
}

// Función principal 
int main() {
    menuPrincipal();
    return 0;
}
