#include "Librerias.h"
#include "Jugador.h"
#include "ContenedorJugadores.h"
#include "Tempo.h"

// Clase Juego con diferentes modos
class Juego {
private:
    Jugador jugador1;
    Jugador jugador2;
    int tiempoCuentaRegresiva;
    bool enCurso;
    Temporizador temporizador;
    ContenedorJugadores contenedor;

    // Método privado para ejecutar una sola ronda
    void ejecutarRonda() {
        cout << "\n=== DUELO DE REFLEJOS ===\n\n";
        cout << jugador1.getNombre() << " presiona [" << jugador1.getTecla() << "]\n";
        cout << jugador2.getNombre() << " presiona [" << jugador2.getTecla() << "]\n\n";
        cout << "Preparense...\n";

        // Cuenta regresiva
        for (int i = tiempoCuentaRegresiva; i > 0; --i) {
            cout << i << "...\n";
            this_thread::sleep_for(chrono::seconds(1));
        }
        cout << "¡DISPAREN!\n";

        temporizador.iniciar();
        bool jugador1Listo = false;
        bool jugador2Listo = false;

        while (!jugador1Listo || !jugador2Listo) {
            if (_kbhit()) {
                char tecla = _getch();
                temporizador.detener();
                float tiempo = temporizador.obtenerDiferencia();

                if (tecla == jugador1.getTecla() && !jugador1Listo) {
                    jugador1.registrarTiempo(tiempo);
                    jugador1Listo = true;
                    cout << jugador1.getNombre() << " disparó en " << fixed << setprecision(4) << tiempo << " segundos.\n";
                }
                else if (tecla == jugador2.getTecla() && !jugador2Listo) {
                    jugador2.registrarTiempo(tiempo);
                    jugador2Listo = true;
                    cout << jugador2.getNombre() << " disparó en " << fixed << setprecision(4) << tiempo << " segundos.\n";
                }
            }
        }
    }

    // Método privado para determinar ganador de una ronda
    int determinarGanadorRonda() {
        float t1 = jugador1.getTiempoReaccion();
        float t2 = jugador2.getTiempoReaccion();

        if (t1 < t2) return 1;      // Gana jugador 1
        else if (t2 < t1) return 2; // Gana jugador 2
        else return 0;              // Empate
    }

    // Método privado para mostrar resultado final y guardar
    void finalizarPartida(int ganador) {
        cout << "\n=== RESULTADOS ===\n";
        jugador1.incrementarPartidas();
        jugador2.incrementarPartidas();

        if (ganador == 1) {
            cout << jugador1.getNombre() << " gana el duelo!\n";
            jugador1.incrementarVictorias();
        }
        else if (ganador == 2) {
            cout << jugador2.getNombre() << " gana el duelo!\n";
            jugador2.incrementarVictorias();
        }
        else {
            cout << "¡Empate perfecto!\n";
        }

        contenedor.guardarDatos(jugador1, jugador2);
    }

public:
    Juego(Jugador j1, Jugador j2, int cuenta = 3)
        : jugador1(j1), jugador2(j2), tiempoCuentaRegresiva(cuenta), enCurso(false) {
    }

    // MODO 1: Duelo Clásico (una sola ronda)
    void modoDueloClasico() {
        enCurso = true;
        ejecutarRonda();

        int ganador = determinarGanadorRonda();
        finalizarPartida(ganador);

        // Preguntar si quieren volver a jugar
        char respuesta;
        cout << "\n¿Quieren jugar otra vez? (s/n): ";
        cin >> respuesta;
        cin.ignore();

        if (respuesta == 's' || respuesta == 'S') {
            jugador1.registrarTiempo(0);
            jugador2.registrarTiempo(0);
            jugador1.setVictorias(0);
            jugador1.setPartidas(0);
            jugador2.setVictorias(0);
            jugador2.setPartidas(0);
            system("cls");
            modoDueloClasico();
        }
        else {
            enCurso = false;
        }
    }

    // MODO 2: Rondas Múltiples (mejor de X)
    void modoRondasMultiples(int totalRondas) {
        enCurso = true;
        int victoriasJ1 = 0;
        int victoriasJ2 = 0;
        int rondasNecesarias = (totalRondas / 2) + 1;

        // Variables para guardar el mejor tiempo de cada jugador
        float mejorTiempoJ1 = 0;
        float mejorTiempoJ2 = 0;

        for (int ronda = 1; ronda <= totalRondas; ronda++) {
            // Verificar si alguien ya ganó
            if (victoriasJ1 >= rondasNecesarias || victoriasJ2 >= rondasNecesarias) {
                break;
            }

            system("cls");
            cout << "\n========================================\n";
            cout << "         RONDA " << ronda << " DE " << totalRondas << "\n";
            cout << "========================================\n";
            cout << jugador1.getNombre() << ": " << victoriasJ1 << " victorias\n";
            cout << jugador2.getNombre() << ": " << victoriasJ2 << " victorias\n";
            cout << "========================================\n\n";

            ejecutarRonda();

            // Determinar ganador de la ronda
            int ganadorRonda = determinarGanadorRonda();

            cout << "\n--- Resultado de la ronda ---\n";
            if (ganadorRonda == 1) {
                cout << jugador1.getNombre() << " GANA la ronda!\n";
                victoriasJ1++;
            }
            else if (ganadorRonda == 2) {
                cout << jugador2.getNombre() << " GANA la ronda!\n";
                victoriasJ2++;
            }
            else {
                cout << "¡Empate en esta ronda!\n";
            }

            // Guardar mejor tiempo de cada jugador
            float t1 = jugador1.getTiempoReaccion();
            float t2 = jugador2.getTiempoReaccion();

            if (t1 > 0 && (mejorTiempoJ1 == 0 || t1 < mejorTiempoJ1)) {
                mejorTiempoJ1 = t1;
            }
            if (t2 > 0 && (mejorTiempoJ2 == 0 || t2 < mejorTiempoJ2)) {
                mejorTiempoJ2 = t2;
            }

            cout << "\nPresione Enter para continuar...";
            cin.ignore();
        }

        // Establecer el mejor tiempo de todo el match
        if (mejorTiempoJ1 > 0) jugador1.registrarTiempo(mejorTiempoJ1);
        if (mejorTiempoJ2 > 0) jugador2.registrarTiempo(mejorTiempoJ2);

        // Resultado final
        system("cls");
        cout << "\n========================================\n";
        cout << "         RESULTADO FINAL\n";
        cout << "========================================\n";
        cout << jugador1.getNombre() << ": " << victoriasJ1 << " rondas ganadas\n";
        cout << jugador2.getNombre() << ": " << victoriasJ2 << " rondas ganadas\n";
        cout << "========================================\n\n";

        // Determinar ganador del match
        int ganadorFinal = 0;
        if (victoriasJ1 > victoriasJ2) {
            cout << "*** " << jugador1.getNombre() << " GANA EL MATCH! ***\n";
            ganadorFinal = 1;
        }
        else if (victoriasJ2 > victoriasJ1) {
            cout << "*** " << jugador2.getNombre() << " GANA EL MATCH! ***\n";
            ganadorFinal = 2;
        }
        else {
            cout << "*** EMPATE PERFECTO! ***\n";
        }

        finalizarPartida(ganadorFinal);
        enCurso = false;
    }

    // Método legacy para mantener compatibilidad
    void iniciarJuego() {
        modoDueloClasico();
    }
};