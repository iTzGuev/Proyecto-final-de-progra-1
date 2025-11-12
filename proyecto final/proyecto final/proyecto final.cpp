#include "Jugador.h"
#include "ContenedorJugadores.h"
#include "Librerias.h"
#include "Juego.h"
#include "Tempo.h"
#include "Animaciones.h"

// Función para validar entrada numérica
int leerOpcionSegura(int min, int max) {
    int opcion;
    while (true) {
        if (cin >> opcion) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
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

// Función para validar que el nombre solo contenga letras y espacios
bool nombreValido(const string& nombre) {
    if (nombre.empty()) {
        return false;
    }

    for (size_t i = 0; i < nombre.length(); i++) {
        char c = nombre[i];
        // Permitir letras (mayúsculas y minúsculas) y espacios
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' ')) {
            return false;
        }
    }

    // Verificar que no sea solo espacios
    bool tieneLetras = false;
    for (size_t i = 0; i < nombre.length(); i++) {
        if (nombre[i] != ' ') {
            tieneLetras = true;
            break;
        }
    }

    return tieneLetras;
}

// Función para validar que los nombres no sean vacíos ni duplicados
bool validarNombres(string& nombre1, string& nombre2) {
    if (nombre1.empty() || nombre2.empty()) {
        cout << "\nError: Los nombres no pueden estar vacios.\n";
        return false;
    }

    if (!nombreValido(nombre1)) {
        cout << "\nError: El nombre del Jugador 1 solo puede contener letras y espacios.\n";
        return false;
    }

    if (!nombreValido(nombre2)) {
        cout << "\nError: El nombre del Jugador 2 solo puede contener letras y espacios.\n";
        return false;
    }

    if (nombre1 == nombre2) {
        cout << "\nError: Los jugadores deben tener nombres diferentes.\n";
        return false;
    }

    return true;
}

// Función para limpiar el buffer de entrada
void limpiarBuffer() {
    if (cin.rdbuf()->in_avail() > 0) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Función para esperar Enter
void esperarEnter() {
    cout << "\nPresione Enter para continuar...";
    cin.get();
}

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
        cout << "4. Torneo\n";
        cout << "5. Desafio de Velocidad\n";
        cout << "6. Volver al menu principal\n";
        cout << "=============================\n";
        cout << "Seleccione un modo: ";

        opcion = leerOpcionSegura(1, 6);

        switch (opcion) {
        case 1: {
            // Duelo Clásico 1v1
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

            esperarEnter();
            break;
        }

        case 2: {
            // Rondas Múltiples
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

            esperarEnter();
            break;
        }

        case 3: {
            // Modo Práctica
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
                else if (!nombreValido(nombre)) {
                    cout << "El nombre solo puede contener letras y espacios.\n";
                }
            } while (nombre.empty() || !nombreValido(nombre));

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

            esperarEnter();
            break;
        }

        case 4: {
            // Modo Torneo
            system("cls");
            int numJugadores;

            cout << "=== MODO TORNEO ===\n\n";
            cout << "Sistema de eliminacion directa\n\n";
            cout << "Seleccione cantidad de jugadores:\n";
            cout << "1. 4 jugadores\n";
            cout << "2. 8 jugadores\n";
            cout << "3. 16 jugadores\n";
            cout << "Opcion: ";

            numJugadores = leerOpcionSegura(1, 3);

            int cantidadJugadores;
            switch (numJugadores) {
            case 1: cantidadJugadores = 4; break;
            case 2: cantidadJugadores = 8; break;
            case 3: cantidadJugadores = 16; break;
            default: cantidadJugadores = 4;
            }

            vector<string> nombresJugadores;
            set<string> nombresUnicos;

            cout << "\n--- Ingrese los nombres de los jugadores ---\n";
            for (int i = 1; i <= cantidadJugadores; i++) {
                string nombre;
                bool nombreValidoFlag = false;

                while (!nombreValidoFlag) {
                    cout << "Jugador " << i << ": ";
                    getline(cin, nombre);

                    if (nombre.empty()) {
                        cout << "El nombre no puede estar vacio.\n";
                    }
                    else if (!nombreValido(nombre)) {
                        cout << "El nombre solo puede contener letras y espacios.\n";
                    }
                    else if (nombresUnicos.find(nombre) != nombresUnicos.end()) {
                        cout << "Ese nombre ya fue usado. Ingrese otro.\n";
                    }
                    else {
                        nombreValidoFlag = true;
                        nombresJugadores.push_back(nombre);
                        nombresUnicos.insert(nombre);
                    }
                }
            }

            cout << "\n¡Torneo configurado! Presiona Enter para comenzar...";
            cin.get();

            Jugador temp1("temp1", 'a');
            Jugador temp2("temp2", 'l');
            Juego juego(temp1, temp2, 3);
            juego.modoTorneo(nombresJugadores);

            esperarEnter();
            break;
        }

        case 5: {
            // Desafío de Velocidad
            system("cls");
            string nombre;
            int numRondas;

            cout << "=== DESAFIO DE VELOCIDAD ===\n\n";
            cout << "Pon a prueba tus reflejos en multiples rondas rapidas!\n";
            cout << "La dificultad aumenta progresivamente.\n\n";

            do {
                cout << "Ingrese su nombre: ";
                getline(cin, nombre);
                if (nombre.empty()) {
                    cout << "El nombre no puede estar vacio.\n";
                }
                else if (!nombreValido(nombre)) {
                    cout << "El nombre solo puede contener letras y espacios.\n";
                }
            } while (nombre.empty() || !nombreValido(nombre));

            cout << "\nSeleccione cantidad de rondas:\n";
            cout << "1. 5 rondas (Rapido)\n";
            cout << "2. 10 rondas (Normal)\n";
            cout << "3. 15 rondas (Extremo)\n";
            cout << "Opcion: ";

            numRondas = leerOpcionSegura(1, 3);

            int rondasTotal;
            switch (numRondas) {
            case 1: rondasTotal = 5; break;
            case 2: rondasTotal = 10; break;
            case 3: rondasTotal = 15; break;
            default: rondasTotal = 10;
            }

            Jugador jugador(nombre, 'a');

            Juego juego(jugador, jugador, 3);
            juego.modoDesafioVelocidad(jugador, rondasTotal);

            esperarEnter();
            break;
        }

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

        opcion = leerOpcionSegura(1, 6);

        switch (opcion) {
        case 1: {
            // Llamar al submenú de modos de juego
            menuModosJuego();
            break;
        }

        case 2: {
            // Submenú de Rankings
            int opcionRanking = 0;
            do {
                system("cls");
                cout << "=============================\n";
                cout << "       VER RANKING         \n";
                cout << "=============================\n";
                cout << "1. Duelo Clasico\n";
                cout << "2. Rondas Multiples\n";
                cout << "3. Torneos\n";
                cout << "4. Desafio de Velocidad\n";
                cout << "5. Ranking General (Todos los modos)\n";
                cout << "6. Volver al menu principal\n";
                cout << "=============================\n";
                cout << "Seleccione una opcion: ";

                opcionRanking = leerOpcionSegura(1, 6);

                system("cls");
                switch (opcionRanking) {
                case 1:
                    contenedor.cargarDatosPorModo("clasico");
                    esperarEnter();
                    break;
                case 2:
                    contenedor.cargarDatosPorModo("rondas");
                    esperarEnter();
                    break;
                case 3:
                    contenedor.cargarDatosPorModo("torneo");
                    esperarEnter();
                    break;
                case 4:
                    contenedor.cargarDatosPorModo("velocidad");
                    esperarEnter();
                    break;
                case 5:
                    contenedor.cargarDatos();
                    esperarEnter();
                    break;
                case 6:
                    break;
                default:
                    cout << "Opcion invalida.\n";
                    this_thread::sleep_for(chrono::seconds(1));
                }
            } while (opcionRanking != 6);
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
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                contenedor.modificarMejorTiempo(nombre, tiempo);
            }

            esperarEnter();
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
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (confirmacion == 's' || confirmacion == 'S') {
                contenedor.eliminarJugador(nombre);
            }
            else {
                cout << "Operacion cancelada.\n";
            }

            esperarEnter();
            break;
        }

        case 5: {
            system("cls");
            char confirmacion;
            cout << "ADVERTENCIA: Se borraran TODAS las estadisticas!\n";
            cout << "Esta seguro? (s/n): ";
            cin >> confirmacion;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (confirmacion == 's' || confirmacion == 'S') {
                contenedor.resetearEstadisticas();
            }
            else {
                cout << "Operacion cancelada.\n";
            }

            esperarEnter();
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
    srand(static_cast<unsigned int>(time(0)));  // Inicializar generador aleatorio
    menuPrincipal();
    return 0;
}