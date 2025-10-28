#include "Librerias.h"
#include "Jugador.h"
#include "ContenedorJugadores.h"
#include "Tempo.h"

//  Clase Juego 
class Juego {
private:
    Jugador jugador1;
    Jugador jugador2;
    int tiempoCuentaRegresiva;
    bool enCurso;
    Temporizador temporizador;
    ContenedorJugadores contenedor;

public:
    Juego(Jugador j1, Jugador j2, int cuenta)
        : jugador1(j1), jugador2(j2), tiempoCuentaRegresiva(cuenta), enCurso(false) {
    }

    void iniciarJuego() {
        enCurso = true;

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
                    cout << jugador1.getNombre() << " disparó en " << tiempo << " segundos.\n";
                }
                else if (tecla == jugador2.getTecla() && !jugador2Listo) {
                    jugador2.registrarTiempo(tiempo);
                    jugador2Listo = true;
                    cout << jugador2.getNombre() << " disparó en " << tiempo << " segundos.\n";
                }
            }
        }

        determinarGanador();
    }

    void determinarGanador() {
        cout << "\n=== RESULTADOS ===\n";
        jugador1.incrementarPartidas();
        jugador2.incrementarPartidas();

        float t1 = jugador1.getTiempoReaccion();
        float t2 = jugador2.getTiempoReaccion();

        if (t1 < t2) {
            cout << jugador1.getNombre() << " gana el duelo \n";
            jugador1.incrementarVictorias();
        }
        else if (t2 < t1) {
            cout << jugador2.getNombre() << " gana el duelo \n";
            jugador2.incrementarVictorias();
        }
        else {
            cout << "¡Empate perfecto!\n";
        }

        contenedor.guardarDatos(jugador1, jugador2);

        // Preguntar si quieren volver a jugar
        char respuesta;
        cout << "\n¿Quieren jugar otra vez? (s/n): ";
        cin >> respuesta;
        cin.ignore();

        if (respuesta == 's' || respuesta == 'S') {
            // SOLUCIÓN: Reiniciar TODOS los contadores para nueva partida
            jugador1.registrarTiempo(0);
            jugador2.registrarTiempo(0);
            jugador1.setVictorias(0);    // AGREGAR ESTA LÍNEA
            jugador1.setPartidas(0);     // AGREGAR ESTA LÍNEA
            jugador2.setVictorias(0);    // AGREGAR ESTA LÍNEA
            jugador2.setPartidas(0);     // AGREGAR ESTA LÍNEA

            system("cls");
            iniciarJuego();
        }
        else {
            enCurso = false;
        }
    }
};
