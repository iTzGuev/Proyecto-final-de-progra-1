#include "Jugador.h"
#include "ContenedorJugadores.h"
#include "Librerias.h"
#include "Juego.h"
#include "Tempo.h"

//Función del menú principal
void menuPrincipal() {
    ContenedorJugadores contenedor("jugadores.json");
    int opcion = 0;

    do {
        system("cls");
        cout << "=============================\n";
        cout << "     DUELO DE REFLEJOS    \n";
        cout << "=============================\n";
        cout << "1. Jugar\n";
        cout << "2. Ver ranking\n";
        cout << "3. Modificar estadisticas\n";
        cout << "4. Eliminar jugador\n";
        cout << "5. Resetear todo\n";
        cout << "6. Salir\n";
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

            cout << "\nPresione Enter para volver al menu...";
            cin.ignore();
            break;
        }

        case 2:
            system("cls");
            contenedor.cargarDatos();
            cout << "\nPresione Enter para volver al menu...";
            cin.ignore();
            break;

        case 3: {
            system("cls");
            string nombre;
            int subOpcion;

            cout << "Ingrese el nombre del jugador: ";
            getline(cin, nombre);

            cout << "\nQue desea modificar?\n";
            cout << "1. Victorias\n";
            cout << "2. Partidas\n";
            cout << "3. Mejor tiempo\n";
            cout << "Opcion: ";
            cin >> subOpcion;
            cin.ignore();

            if (subOpcion == 1) {
                int victorias;
                cout << "Nuevas victorias: ";
                cin >> victorias;
                cin.ignore();
                contenedor.modificarVictorias(nombre, victorias);
            }
            else if (subOpcion == 2) {
                int partidas;
                cout << "Nuevas partidas: ";
                cin >> partidas;
                cin.ignore();
                contenedor.modificarPartidas(nombre, partidas);
            }
            else if (subOpcion == 3) {
                float tiempo;
                cout << "Nuevo mejor tiempo: ";
                cin >> tiempo;
                cin.ignore();
                contenedor.modificarMejorTiempo(nombre, tiempo);
            }

            cout << "\nPresione Enter para volver al menu...";
            cin.ignore();
            break;
        }

        case 4: {
            system("cls");
            string nombre;
            cout << "Ingrese el nombre del jugador a eliminar: ";
            getline(cin, nombre);

            char confirmacion;
            cout << "Esta seguro? (s/n): ";
            cin >> confirmacion;
            cin.ignore();

            if (confirmacion == 's' || confirmacion == 'S') {
                contenedor.eliminarJugador(nombre);
            }
            else {
                cout << "Operacion cancelada.\n";
            }

            cout << "\nPresione Enter para volver al menu...";
            cin.ignore();
            break;
        }

        case 5: {
            system("cls");
            char confirmacion;
            cout << "ADVERTENCIA: Se borraran TODAS las estadisticas!\n";
            cout << "Esta seguro? (s/n): ";
            cin >> confirmacion;
            cin.ignore();

            if (confirmacion == 's' || confirmacion == 'S') {
                contenedor.resetearEstadisticas();
            }
            else {
                cout << "Operacion cancelada.\n";
            }

            cout << "\nPresione Enter para volver al menu...";
            cin.ignore();
            break;
        }

        case 6:
            cout << "\nSaliendo del juego... Hasta pronto!\n";
            break;

        default:
            cout << "Opcion invalida. Intente de nuevo.\n";
            this_thread::sleep_for(chrono::seconds(2));
            break;
        }
    } while (opcion != 6);
}

// Función principal - AQUÍ ESTÁ EL MAIN
int main() {
    menuPrincipal();
    return 0;
}