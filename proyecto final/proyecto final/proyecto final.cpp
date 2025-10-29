#include "Jugador.h"
#include "ContenedorJugadores.h"
#include "Librerias.h"
#include "Juego.h"
#include "Tempo.h"

// Función para el submenú de modos de juego
void menuModosJuego() {
    int opcion = 0;

    do {
        system("cls");
        cout << "=============================\n";
        cout << "      MODOS DE JUEGO       \n";
        cout << "=============================\n";
        cout << "1. Duelo Clasico (1 vs 1)\n";
        cout << "2. Rondas Multiples (Mejor de X)\n";
        cout << "3. Modo Practica\n";
        cout << "4. Torneo (Proximamente)\n";
        cout << "5. Desafio de Velocidad (Proximamente)\n";
        cout << "6. Volver al menu principal\n";
        cout << "=============================\n";
        cout << "Seleccione un modo: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case 1: {
            // Duelo Clásico 1v1
            system("cls");
            string nombre1, nombre2;
            cout << "=== DUELO CLASICO ===\n\n";
            cout << "Ingrese nombre del Jugador 1: ";
            getline(cin, nombre1);
            cout << "Ingrese nombre del Jugador 2: ";
            getline(cin, nombre2);

            Jugador j1(nombre1, 'a');
            Jugador j2(nombre2, 'l');

            Juego juego(j1, j2, 3);
            juego.modoDueloClasico();

            cout << "\nPresione Enter para volver al menu...";
            cin.ignore();
            break;
        }

        case 2: {
            // Rondas Múltiples
            system("cls");
            string nombre1, nombre2;
            int numRondas;

            cout << "=== RONDAS MULTIPLES ===\n\n";
            cout << "Ingrese nombre del Jugador 1: ";
            getline(cin, nombre1);
            cout << "Ingrese nombre del Jugador 2: ";
            getline(cin, nombre2);

            cout << "\nSeleccione cantidad de rondas:\n";
            cout << "1. Mejor de 3\n";
            cout << "2. Mejor de 5\n";
            cout << "3. Mejor de 7\n";
            cout << "Opcion: ";
            cin >> numRondas;
            cin.ignore();

            int rondasTotal;
            switch (numRondas) {
            case 1: rondasTotal = 3; break;
            case 2: rondasTotal = 5; break;
            case 3: rondasTotal = 7; break;
            default:
                cout << "Opcion invalida, usando mejor de 3.\n";
                rondasTotal = 3;
                this_thread::sleep_for(chrono::seconds(1));
            }

            Jugador j1(nombre1, 'a');
            Jugador j2(nombre2, 'l');

            Juego juego(j1, j2, 3);
            juego.modoRondasMultiples(rondasTotal);

            cout << "\nPresione Enter para volver al menu...";
            cin.ignore();
            break;
        }
        case 3: {
            // Modo Práctica
            system("cls");
            string nombre;
            int numIntentos;

            cout << "=== MODO PRACTICA ===\n\n";
            cout << "Este modo te permite entrenar sin afectar tus estadisticas.\n\n";
            cout << "Ingrese su nombre: ";
            getline(cin, nombre);

            cout << "\nCuantos intentos deseas realizar?\n";
            cout << "1. 3 intentos\n";
            cout << "2. 5 intentos\n";
            cout << "3. 10 intentos\n";
            cout << "Opcion: ";
            cin >> numIntentos;
            cin.ignore();

            int intentosTotal;
            switch (numIntentos) {
            case 1: intentosTotal = 3; break;
            case 2: intentosTotal = 5; break;
            case 3: intentosTotal = 10; break;
            default:
                cout << "Opcion invalida, usando 5 intentos.\n";
                intentosTotal = 5;
                this_thread::sleep_for(chrono::seconds(1));
            }

            Jugador jugador(nombre, 'a'); // Tecla 'a' por defecto

            Juego juego(jugador, jugador, 3); // Se pasa el mismo jugador dos veces (no se usa el segundo)
            juego.modoPractica(jugador, intentosTotal);

            cout << "\nPresione Enter para volver al menu...";
            cin.ignore();
            break;
        }
        case 4:
        case 5:
            system("cls");
            cout << "\n=== PROXIMAMENTE ===\n";
            cout << "Este modo de juego estara disponible pronto.\n";
            cout << "\nPresione Enter para volver...";
            cin.ignore();
            break;

        case 6:
            // Volver al menú principal
            break;

        default:
            cout << "Opcion invalida. Intente de nuevo.\n";
            this_thread::sleep_for(chrono::seconds(2));
            break;
        }
    } while (opcion != 6);
}

// Función del menú principal
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
            // Llamar al submenú de modos de juego
            menuModosJuego();
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

// Función principal
int main() {
    menuPrincipal();
    return 0;
}