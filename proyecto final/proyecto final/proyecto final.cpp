#include "Jugador.h"
#include "ContenedorJugadores.h"
#include "Librerias.h"
#include "Juego.h"
#include "Tempo.h"

// Funci�n para validar entrada num�rica
int leerOpcionSegura(int min, int max) {
    int opcion;
    while (true) {
        if (cin >> opcion) {
            cin.ignore();
            if (opcion >= min && opcion <= max) {
                return opcion;
            }
            else {
                cout << "Opcion fuera de rango. Ingrese entre " << min << " y " << max << ": ";
            }
        }
        else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida. Ingrese un numero entre " << min << " y " << max << ": ";
        }
    }
}

// Funci�n para validar que los nombres no sean vac�os ni duplicados
bool validarNombres(string& nombre1, string& nombre2) {
    if (nombre1.empty() || nombre2.empty()) {
        cout << "\nError: Los nombres no pueden estar vacios.\n";
        return false;
    }

    if (nombre1 == nombre2) {
        cout << "\nError: Los jugadores deben tener nombres diferentes.\n";
        return false;
    }

    return true;
}

// Funci�n para el submen� de modos de juego
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

        opcion = leerOpcionSegura(1, 6);

        switch (opcion) {
        case 1: {
            // Duelo Cl�sico 1v1
            system("cls");
            string nombre1, nombre2;
            cout << "=== DUELO CLASICO ===\n\n";

            do {
                cout << "Ingrese nombre del Jugador 1: ";
                getline(cin, nombre1);
                cout << "Ingrese nombre del Jugador 2: ";
                getline(cin, nombre2);
            } while (!validarNombres(nombre1, nombre2));

            Jugador j1(nombre1, 'a');
            Jugador j2(nombre2, 'l');

            Juego juego(j1, j2, 3);
            juego.modoDueloClasico();

            cout << "\nPresione Enter para volver al menu...";
            cin.ignore();
            break;
        }

        case 2: {
            // Rondas M�ltiples
            system("cls");
            string nombre1, nombre2;
            int numRondas;

            cout << "=== RONDAS MULTIPLES ===\n\n";

            do {
                cout << "Ingrese nombre del Jugador 1: ";
                getline(cin, nombre1);
                cout << "Ingrese nombre del Jugador 2: ";
                getline(cin, nombre2);
            } while (!validarNombres(nombre1, nombre2));

            cout << "\nSeleccione cantidad de rondas:\n";
            cout << "1. Mejor de 3\n";
            cout << "2. Mejor de 5\n";
            cout << "3. Mejor de 7\n";
            cout << "Opcion: ";

            numRondas = leerOpcionSegura(1, 3);

            int rondasTotal;
            switch (numRondas) {
            case 1: rondasTotal = 3; break;
            case 2: rondasTotal = 5; break;
            case 3: rondasTotal = 7; break;
            default: rondasTotal = 3;
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
            // Modo Pr�ctica
            system("cls");
            string nombre;
            int numIntentos;

            cout << "=== MODO PRACTICA ===\n\n";
            cout << "Este modo te permite entrenar sin afectar tus estadisticas.\n\n";

            do {
                cout << "Ingrese su nombre: ";
                getline(cin, nombre);
                if (nombre.empty()) {
                    cout << "El nombre no puede estar vacio.\n";
                }
            } while (nombre.empty());

            cout << "\nCuantos intentos deseas realizar?\n";
            cout << "1. 3 intentos\n";
            cout << "2. 5 intentos\n";
            cout << "3. 10 intentos\n";
            cout << "Opcion: ";

            numIntentos = leerOpcionSegura(1, 3);

            int intentosTotal;
            switch (numIntentos) {
            case 1: intentosTotal = 3; break;
            case 2: intentosTotal = 5; break;
            case 3: intentosTotal = 10; break;
            default: intentosTotal = 5;
            }

            Jugador jugador(nombre, 'a');

            Juego juego(jugador, jugador, 3);
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
            // Volver al men� principal
            break;

        default:
            cout << "Opcion invalida. Intente de nuevo.\n";
            this_thread::sleep_for(chrono::seconds(2));
            break;
        }
    } while (opcion != 6);
}

// Funci�n del men� principal
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

        opcion = leerOpcionSegura(1, 6);

        switch (opcion) {
        case 1: {
            // Llamar al submen� de modos de juego
            menuModosJuego();
            break;
        }

        case 2: {
            // Submen� de Rankings
            int opcionRanking = 0;
            do {
                system("cls");
                cout << "=============================\n";
                cout << "       VER RANKING         \n";
                cout << "=============================\n";
                cout << "1. Duelo Clasico\n";
                cout << "2. Rondas Multiples\n";
                cout << "3. Ranking General (Todos los modos)\n";
                cout << "4. Volver al menu principal\n";
                cout << "=============================\n";
                cout << "Seleccione una opcion: ";

                opcionRanking = leerOpcionSegura(1, 4);

                system("cls");
                switch (opcionRanking) {
                case 1:
                    contenedor.cargarDatosPorModo("clasico");
                    cout << "\nPresione Enter para volver...";
                    cin.ignore();
                    break;
                case 2:
                    contenedor.cargarDatosPorModo("rondas");
                    cout << "\nPresione Enter para volver...";
                    cin.ignore();
                    break;
                case 3:
                    contenedor.cargarDatos();
                    cout << "\nPresione Enter para volver...";
                    cin.ignore();
                    break;
                case 4:
                    break;
                default:
                    cout << "Opcion invalida.\n";
                    this_thread::sleep_for(chrono::seconds(1));
                }
            } while (opcionRanking != 4);
            break;
        }

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

            subOpcion = leerOpcionSegura(1, 3);

            if (subOpcion == 1) {
                int victorias;
                cout << "Nuevas victorias: ";
                victorias = leerOpcionSegura(0, 9999);
                contenedor.modificarVictorias(nombre, victorias);
            }
            else if (subOpcion == 2) {
                int partidas;
                cout << "Nuevas partidas: ";
                partidas = leerOpcionSegura(0, 9999);
                contenedor.modificarPartidas(nombre, partidas);
            }
            else if (subOpcion == 3) {
                float tiempo;
                cout << "Nuevo mejor tiempo: ";
                while (!(cin >> tiempo) || tiempo < 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Ingrese un tiempo valido (mayor o igual a 0): ";
                }
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

// Funci�n principal
int main() {
    menuPrincipal();
    return 0;
}