#include "Jugador.h"
#include "ContenedorJugadores.h"
#include "Librerias.h"
#include "Juego.h"
#include "Tempo.h"
#include "Graficos.h"

// Función para validar entrada numérica
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

// Función para validar que los nombres no sean vacíos ni duplicados
bool validarNombres(string& nombre1, string& nombre2) {
    if (nombre1.empty() || nombre2.empty()) {
        cout << "\nError: Los nombres no pueden estar vacios.\n";
        this_thread::sleep_for(chrono::seconds(2));
        return false;
    }

    if (nombre1 == nombre2) {
        cout << "\nError: Los jugadores deben tener nombres diferentes.\n";
        this_thread::sleep_for(chrono::seconds(2));
        return false;
    }

    return true;
}

// Función para el submenú de modos de juego - MEJORADO CON GRÁFICOS
void menuModosJuego() {
    Graficos gfx; // Crear objeto de gráficos local
    int opcion = 0;

    do {
        gfx.limpiar();
        gfx.ocultarCursor();
        gfx.rellenarArea(0, 0, 120, 30, Graficos::AZUL_OSCURO);

        gfx.textoCentrado("????????????????????????????????????????????", 5, Graficos::AMARILLO);
        gfx.textoCentrado("          M O D O S   D E   J U E G O", 7, Graficos::AMARILLO);
        gfx.textoCentrado("????????????????????????????????????????????", 9, Graficos::AMARILLO);

        gfx.texto("1. Duelo Clasico (1 vs 1)", 40, 12, Graficos::VERDE);
        gfx.texto("2. Rondas Multiples (Mejor de X)", 40, 14, Graficos::CYAN);
        gfx.texto("3. Modo Practica", 40, 16, Graficos::MAGENTA);
        gfx.texto("4. Torneo", 40, 18, Graficos::ROJO);
        gfx.texto("5. Desafio de Velocidad (Proximamente)", 40, 20, Graficos::GRIS_CLARO);
        gfx.texto("6. Volver al menu principal", 40, 22, Graficos::AMARILLO_OSCURO);

        gfx.mostrarCursor();
        gfx.texto("Seleccione un modo: ", 40, 25, Graficos::BLANCO);
        gfx.gotoxy(61, 25);

        opcion = leerOpcionSegura(1, 6);

        switch (opcion) {
        case 1: {
            gfx.limpiar();
            gfx.rellenarArea(0, 0, 120, 30, Graficos::VERDE_OSCURO);
            gfx.textoCentrado("=== DUELO CLASICO ===", 8, Graficos::AMARILLO);

            string nombre1, nombre2;
            do {
                gfx.mostrarCursor();
                gfx.texto("Ingrese nombre del Jugador 1: ", 35, 12, Graficos::CYAN);
                gfx.gotoxy(66, 12);
                getline(cin, nombre1);

                gfx.texto("Ingrese nombre del Jugador 2: ", 35, 14, Graficos::MAGENTA);
                gfx.gotoxy(66, 14);
                getline(cin, nombre2);
            } while (!validarNombres(nombre1, nombre2));

            Jugador j1(nombre1, 'a');
            Jugador j2(nombre2, 'l');

            Juego juego(j1, j2, 3);
            juego.modoDueloClasico();

            gfx.textoCentrado("Presione Enter para volver al menu...", 27, Graficos::BLANCO);
            cin.ignore();
            break;
        }

        case 2: {
            gfx.limpiar();
            gfx.rellenarArea(0, 0, 120, 30, Graficos::MAGENTA_OSCURO);
            gfx.textoCentrado("=== RONDAS MULTIPLES ===", 8, Graficos::AMARILLO);

            string nombre1, nombre2;
            int numRondas;

            do {
                gfx.mostrarCursor();
                gfx.texto("Ingrese nombre del Jugador 1: ", 35, 11, Graficos::CYAN);
                gfx.gotoxy(66, 11);
                getline(cin, nombre1);

                gfx.texto("Ingrese nombre del Jugador 2: ", 35, 13, Graficos::MAGENTA);
                gfx.gotoxy(66, 13);
                getline(cin, nombre2);
            } while (!validarNombres(nombre1, nombre2));

            gfx.texto("Seleccione cantidad de rondas:", 35, 16, Graficos::BLANCO);
            gfx.texto("1. Mejor de 3", 40, 17, Graficos::VERDE);
            gfx.texto("2. Mejor de 5", 40, 18, Graficos::AMARILLO);
            gfx.texto("3. Mejor de 7", 40, 19, Graficos::ROJO);
            gfx.texto("Opcion: ", 40, 21, Graficos::BLANCO);
            gfx.gotoxy(49, 21);

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

            gfx.textoCentrado("Presione Enter para volver al menu...", 27, Graficos::BLANCO);
            cin.ignore();
            break;
        }

        case 3: {
            gfx.limpiar();
            gfx.rellenarArea(0, 0, 120, 30, Graficos::CYAN_OSCURO);
            gfx.textoCentrado("=== MODO PRACTICA ===", 8, Graficos::AMARILLO);
            gfx.textoCentrado("Este modo te permite entrenar sin afectar tus estadisticas.", 10, Graficos::BLANCO);

            string nombre;
            int numIntentos;

            do {
                gfx.mostrarCursor();
                gfx.texto("Ingrese su nombre: ", 40, 13, Graficos::BLANCO);
                gfx.gotoxy(60, 13);
                getline(cin, nombre);
                if (nombre.empty()) {
                    gfx.texto("El nombre no puede estar vacio.", 38, 15, Graficos::ROJO);
                    this_thread::sleep_for(chrono::seconds(1));
                    gfx.texto("                                ", 38, 15, Graficos::ROJO);
                }
            } while (nombre.empty());

            gfx.texto("Cuantos intentos deseas realizar?", 35, 16, Graficos::BLANCO);
            gfx.texto("1. 3 intentos", 40, 17, Graficos::VERDE);
            gfx.texto("2. 5 intentos", 40, 18, Graficos::AMARILLO);
            gfx.texto("3. 10 intentos", 40, 19, Graficos::ROJO);
            gfx.texto("Opcion: ", 40, 21, Graficos::BLANCO);
            gfx.gotoxy(49, 21);

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

            gfx.textoCentrado("Presione Enter para volver al menu...", 27, Graficos::BLANCO);
            cin.ignore();
            break;
        }

        case 4: {
            gfx.limpiar();
            gfx.rellenarArea(0, 0, 120, 30, Graficos::ROJO_OSCURO);
            gfx.textoCentrado("=== MODO TORNEO ===", 8, Graficos::AMARILLO);
            gfx.textoCentrado("Sistema de eliminacion directa", 10, Graficos::BLANCO);

            int numJugadores;

            gfx.texto("Seleccione cantidad de jugadores:", 35, 13, Graficos::BLANCO);
            gfx.texto("1. 4 jugadores", 40, 14, Graficos::VERDE);
            gfx.texto("2. 8 jugadores", 40, 15, Graficos::AMARILLO);
            gfx.texto("3. 16 jugadores", 40, 16, Graficos::ROJO);
            gfx.mostrarCursor();
            gfx.texto("Opcion: ", 40, 18, Graficos::BLANCO);
            gfx.gotoxy(49, 18);

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

            gfx.limpiar();
            gfx.rellenarArea(0, 0, 120, 30, Graficos::ROJO_OSCURO);
            gfx.textoCentrado("--- Ingrese los nombres de los jugadores ---", 6, Graficos::AMARILLO);

            for (int i = 1; i <= cantidadJugadores; i++) {
                string nombre;
                bool nombreValido = false;

                while (!nombreValido) {
                    gfx.mostrarCursor();
                    string prompt = "Jugador " + to_string(i) + ": ";
                    gfx.texto(prompt, 40, 8 + i, Graficos::CYAN);
                    gfx.gotoxy(40 + prompt.length(), 8 + i);
                    getline(cin, nombre);

                    if (nombre.empty()) {
                        gfx.texto("El nombre no puede estar vacio.                    ", 35, 8 + cantidadJugadores + 3, Graficos::ROJO);
                        this_thread::sleep_for(chrono::seconds(1));
                        gfx.texto("                                                   ", 35, 8 + cantidadJugadores + 3, Graficos::ROJO);
                    }
                    else if (nombresUnicos.find(nombre) != nombresUnicos.end()) {
                        gfx.texto("Ese nombre ya fue usado. Ingrese otro.             ", 35, 8 + cantidadJugadores + 3, Graficos::ROJO);
                        this_thread::sleep_for(chrono::seconds(1));
                        gfx.texto("                                                   ", 35, 8 + cantidadJugadores + 3, Graficos::ROJO);
                    }
                    else {
                        nombreValido = true;
                        nombresJugadores.push_back(nombre);
                        nombresUnicos.insert(nombre);
                    }
                }
            }

            gfx.textoCentrado("¡Torneo configurado! Presiona Enter para comenzar...", 25, Graficos::VERDE);
            cin.ignore();

            Jugador temp1("temp1", 'a');
            Jugador temp2("temp2", 'l');
            Juego juego(temp1, temp2, 3);
            juego.modoTorneo(nombresJugadores);

            gfx.textoCentrado("Presione Enter para volver al menu...", 27, Graficos::BLANCO);
            cin.ignore();
            break;
        }

        case 5:
            gfx.limpiar();
            gfx.rellenarArea(0, 0, 120, 30, Graficos::GRIS_OSCURO);
            gfx.textoCentrado("=== PROXIMAMENTE ===", 13, Graficos::AMARILLO);
            gfx.textoCentrado("Este modo de juego estara disponible pronto.", 15, Graficos::BLANCO);
            gfx.mostrarCursor();
            gfx.textoCentrado("Presione Enter para volver...", 20, Graficos::BLANCO);
            cin.ignore();
            break;

        case 6:
            break;

        default:
            gfx.textoCentrado("Opcion invalida. Intente de nuevo.", 25, Graficos::ROJO);
            this_thread::sleep_for(chrono::seconds(2));
            break;
        }
    } while (opcion != 6);
}

// Función del menú principal - MEJORADA CON GRÁFICOS
void menuPrincipal() {
    Graficos gfx; // Crear objeto de gráficos local
    ContenedorJugadores contenedor("jugadores.json");
    int opcion = 0;

    do {
        gfx.dibujarTitulo();

        gfx.texto("1. Jugar", 48, 22, Graficos::VERDE);
        gfx.texto("2. Ver ranking", 48, 23, Graficos::CYAN);
        gfx.texto("3. Modificar estadisticas", 48, 24, Graficos::AMARILLO);
        gfx.texto("4. Eliminar jugador", 48, 25, Graficos::ROJO);
        gfx.texto("5. Resetear todo", 48, 26, Graficos::MAGENTA);
        gfx.texto("6. Salir", 48, 27, Graficos::GRIS_CLARO);

        gfx.mostrarCursor();
        gfx.texto("Seleccione una opcion: ", 42, 29, Graficos::BLANCO);
        gfx.gotoxy(66, 29);

        opcion = leerOpcionSegura(1, 6);

        switch (opcion) {
        case 1: {
            menuModosJuego();
            break;
        }

        case 2: {
            int opcionRanking = 0;
            do {
                gfx.limpiar();
                gfx.ocultarCursor();
                gfx.rellenarArea(0, 0, 120, 30, Graficos::VERDE_OSCURO);

                gfx.textoCentrado("????????????????????????????????????????????", 6, Graficos::AMARILLO);
                gfx.textoCentrado("           V E R   R A N K I N G", 8, Graficos::AMARILLO);
                gfx.textoCentrado("????????????????????????????????????????????", 10, Graficos::AMARILLO);

                gfx.texto("1. Duelo Clasico", 45, 13, Graficos::CYAN);
                gfx.texto("2. Rondas Multiples", 45, 15, Graficos::MAGENTA);
                gfx.texto("3. Torneos", 45, 17, Graficos::ROJO);
                gfx.texto("4. Ranking General (Todos los modos)", 45, 19, Graficos::AMARILLO);
                gfx.texto("5. Volver al menu principal", 45, 21, Graficos::GRIS_CLARO);

                gfx.mostrarCursor();
                gfx.texto("Seleccione una opcion: ", 40, 24, Graficos::BLANCO);
                gfx.gotoxy(64, 24);

                opcionRanking = leerOpcionSegura(1, 5);

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
                    contenedor.cargarDatosPorModo("torneo");
                    cout << "\nPresione Enter para volver...";
                    cin.ignore();
                    break;
                case 4:
                    contenedor.cargarDatos();
                    cout << "\nPresione Enter para volver...";
                    cin.ignore();
                    break;
                case 5:
                    break;
                default:
                    cout << "Opcion invalida.\n";
                    this_thread::sleep_for(chrono::seconds(1));
                }
            } while (opcionRanking != 5);
            break;
        }

        case 3: {
            gfx.limpiar();
            gfx.rellenarArea(0, 0, 120, 30, Graficos::AMARILLO_OSCURO);
            gfx.textoCentrado("=== MODIFICAR ESTADISTICAS ===", 8, Graficos::AMARILLO);

            string nombre;
            int subOpcion;

            gfx.mostrarCursor();
            gfx.texto("Ingrese el nombre del jugador: ", 35, 11, Graficos::BLANCO);
            gfx.gotoxy(67, 11);
            getline(cin, nombre);

            gfx.texto("Que desea modificar?", 35, 14, Graficos::BLANCO);
            gfx.texto("1. Victorias", 40, 15, Graficos::VERDE);
            gfx.texto("2. Partidas", 40, 16, Graficos::CYAN);
            gfx.texto("3. Mejor tiempo", 40, 17, Graficos::MAGENTA);
            gfx.texto("Opcion: ", 40, 19, Graficos::BLANCO);
            gfx.gotoxy(49, 19);

            subOpcion = leerOpcionSegura(1, 3);

            if (subOpcion == 1) {
                int victorias;
                gfx.texto("Nuevas victorias: ", 40, 21, Graficos::BLANCO);
                gfx.gotoxy(59, 21);
                victorias = leerOpcionSegura(0, 9999);
                contenedor.modificarVictorias(nombre, victorias);
            }
            else if (subOpcion == 2) {
                int partidas;
                gfx.texto("Nuevas partidas: ", 40, 21, Graficos::BLANCO);
                gfx.gotoxy(58, 21);
                partidas = leerOpcionSegura(0, 9999);
                contenedor.modificarPartidas(nombre, partidas);
            }
            else if (subOpcion == 3) {
                float tiempo;
                gfx.texto("Nuevo mejor tiempo: ", 40, 21, Graficos::BLANCO);
                gfx.gotoxy(61, 21);
                while (!(cin >> tiempo) || tiempo < 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    gfx.texto("Ingrese un tiempo valido (mayor o igual a 0): ", 35, 23, Graficos::ROJO);
                    gfx.gotoxy(82, 23);
                }
                cin.ignore();
                contenedor.modificarMejorTiempo(nombre, tiempo);
            }

            gfx.textoCentrado("Presione Enter para volver al menu...", 26, Graficos::BLANCO);
            cin.ignore();
            break;
        }

        case 4: {
            gfx.limpiar();
            gfx.rellenarArea(0, 0, 120, 30, Graficos::ROJO_OSCURO);
            gfx.textoCentrado("=== ELIMINAR JUGADOR ===", 10, Graficos::AMARILLO);

            string nombre;
            gfx.mostrarCursor();
            gfx.texto("Ingrese el nombre del jugador a eliminar: ", 30, 13, Graficos::BLANCO);
            gfx.gotoxy(73, 13);
            getline(cin, nombre);

            char confirmacion;
            gfx.texto("Esta seguro? (s/n): ", 40, 16, Graficos::ROJO);
            gfx.gotoxy(61, 16);
            cin >> confirmacion;
            cin.ignore();

            if (confirmacion == 's' || confirmacion == 'S') {
                contenedor.eliminarJugador(nombre);
            }
            else {
                gfx.textoCentrado("Operacion cancelada.", 19, Graficos::AMARILLO);
            }

            gfx.textoCentrado("Presione Enter para volver al menu...", 25, Graficos::BLANCO);
            cin.ignore();
            break;
        }

        case 5: {
            gfx.limpiar();
            gfx.rellenarArea(0, 0, 120, 30, Graficos::MAGENTA_OSCURO);
            gfx.textoCentrado("=== RESETEAR ESTADISTICAS ===", 10, Graficos::AMARILLO);

            char confirmacion;
            gfx.textoCentrado("ADVERTENCIA: Se borraran TODAS las estadisticas!", 13, Graficos::ROJO);
            gfx.mostrarCursor();
            gfx.texto("Esta seguro? (s/n): ", 45, 16, Graficos::BLANCO);
            gfx.gotoxy(66, 16);
            cin >> confirmacion;
            cin.ignore();

            if (confirmacion == 's' || confirmacion == 'S') {
                contenedor.resetearEstadisticas();
            }
            else {
                gfx.textoCentrado("Operacion cancelada.", 19, Graficos::VERDE);
            }

            gfx.textoCentrado("Presione Enter para volver al menu...", 24, Graficos::BLANCO);
            cin.ignore();
            break;
        }

        case 6:
            gfx.limpiar();
            gfx.rellenarArea(0, 0, 120, 30, Graficos::NEGRO);
            gfx.textoCentrado("Saliendo del juego... Hasta pronto!", 14, Graficos::AMARILLO);
            this_thread::sleep_for(chrono::seconds(2));
            break;

        default:
            gfx.textoCentrado("Opcion invalida. Intente de nuevo.", 29, Graficos::ROJO);
            this_thread::sleep_for(chrono::seconds(2));
            break;
        }
    } while (opcion != 6);

    gfx.resetColor();
    gfx.mostrarCursor();
}

// Función principal
int main() {
    menuPrincipal();
    return 0;
}