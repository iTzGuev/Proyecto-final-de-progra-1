#pragma once
#include "Librerias.h"
#include "Jugador.h"
#include "ContenedorJugadores.h"
#include "Tempo.h"
#include "Graficos.h"  // ← NUEVO

// Clase Juego con diferentes modos - MEJORADA CON GRÁFICOS
class Juego {
private:
    Jugador jugador1;
    Jugador jugador2;
    int tiempoCuentaRegresiva;
    bool enCurso;
    Temporizador temporizador;
    ContenedorJugadores contenedor;
    Graficos gfx;  // ← NUEVO: Objeto de gráficos

    // Método privado para ejecutar una sola ronda - MEJORADO CON GRÁFICOS
    void ejecutarRonda() {
        gfx.limpiar();
        gfx.ocultarCursor();

        // Dibujar fondo y título del duelo
        gfx.rellenarArea(0, 0, 120, 30, Graficos::AZUL_OSCURO);
        gfx.textoCentrado("════════════════════════════════════════════", 2, Graficos::AMARILLO);
        gfx.textoCentrado("          D U E L O   D E   R E F L E J O S", 3, Graficos::AMARILLO);
        gfx.textoCentrado("════════════════════════════════════════════", 4, Graficos::AMARILLO);

        // Dibujar jugadores en posiciones opuestas (como vaqueros)
        gfx.dibujarJugador(jugador1.getNombre(), jugador1.getTecla(), 8, 8, Graficos::CYAN);
        gfx.dibujarJugador(jugador2.getNombre(), jugador2.getTecla(), 80, 8, Graficos::MAGENTA);

        // VS en el centro
        gfx.texto("V", 57, 12, Graficos::ROJO);
        gfx.texto("S", 62, 12, Graficos::ROJO);

        // Mensaje de preparación
        gfx.textoCentrado("¡ Preparense para el duelo !", 22, Graficos::BLANCO);
        this_thread::sleep_for(chrono::milliseconds(2000));

        // Cuenta regresiva animada
        gfx.animarCuentaRegresiva(tiempoCuentaRegresiva);

        // Pantalla de DISPARA con efecto
        gfx.mostrarDispara();

        temporizador.iniciar();
        bool jugador1Listo = false;
        bool jugador2Listo = false;

        // Redibujar jugadores en modo "esperando disparo"
        gfx.limpiar();
        gfx.rellenarArea(0, 0, 120, 30, Graficos::ROJO_OSCURO);
        gfx.textoCentrado("¡¡¡ D I S P A R E N !!!", 2, Graficos::AMARILLO);

        gfx.dibujarJugador(jugador1.getNombre(), jugador1.getTecla(), 8, 8, Graficos::CYAN, false);
        gfx.dibujarJugador(jugador2.getNombre(), jugador2.getTecla(), 80, 8, Graficos::MAGENTA, false);

        while (!jugador1Listo || !jugador2Listo) {
            if (_kbhit()) {
                char tecla = _getch();
                temporizador.detener();
                float tiempo = temporizador.obtenerDiferencia();

                if (tecla == jugador1.getTecla() && !jugador1Listo) {
                    jugador1.registrarTiempo(tiempo);
                    jugador1Listo = true;

                    // Efecto visual de disparo
                    gfx.efectoDisparo(24, 12);
                    gfx.dibujarJugador(jugador1.getNombre(), jugador1.getTecla(), 8, 8, Graficos::VERDE, true);

                    string msg = jugador1.getNombre() + " disparo en " + to_string(tiempo).substr(0, 6) + "s";
                    gfx.texto(msg, 8, 20, Graficos::VERDE);
                }
                else if (tecla == jugador2.getTecla() && !jugador2Listo) {
                    jugador2.registrarTiempo(tiempo);
                    jugador2Listo = true;

                    // Efecto visual de disparo
                    gfx.efectoDisparo(96, 12);
                    gfx.dibujarJugador(jugador2.getNombre(), jugador2.getTecla(), 80, 8, Graficos::VERDE, true);

                    string msg = jugador2.getNombre() + " disparo en " + to_string(tiempo).substr(0, 6) + "s";
                    gfx.texto(msg, 8, 22, Graficos::VERDE);
                }
            }
        }

        this_thread::sleep_for(chrono::milliseconds(2000));
    }

    // Método privado para determinar ganador de una ronda
    int determinarGanadorRonda() {
        float t1 = jugador1.getTiempoReaccion();
        float t2 = jugador2.getTiempoReaccion();

        if (t1 < t2) return 1;
        else if (t2 < t1) return 2;
        else return 0;
    }

    // Método privado para mostrar resultado final - MEJORADO CON GRÁFICOS
    void finalizarPartida(int ganador, const string& modo) {
        jugador1.setModoJuego(modo);
        jugador2.setModoJuego(modo);

        jugador1.incrementarPartidas();
        jugador2.incrementarPartidas();

        string nombreGanador;
        if (ganador == 1) {
            nombreGanador = jugador1.getNombre();
            jugador1.incrementarVictorias();
        }
        else if (ganador == 2) {
            nombreGanador = jugador2.getNombre();
            jugador2.incrementarVictorias();
        }
        else {
            nombreGanador = "EMPATE";
        }

        // Mostrar resultado con gráficos
        gfx.mostrarResultado(
            nombreGanador,
            jugador1.getTiempoReaccion(),
            jugador2.getTiempoReaccion(),
            jugador1.getNombre(),
            jugador2.getNombre()
        );

        contenedor.guardarDatos(jugador1, jugador2);

        gfx.mostrarCursor();
        gfx.textoCentrado("Presiona Enter para continuar...", 27, Graficos::BLANCO);
    }

public:
    Juego(Jugador j1, Jugador j2, int cuenta = 3)
        : jugador1(j1), jugador2(j2), tiempoCuentaRegresiva(cuenta), enCurso(false) {
    }

    // MODO 1: Duelo Clásico - MEJORADO CON GRÁFICOS
    void modoDueloClasico() {
        bool quiereJugar = true;

        while (quiereJugar) {
            enCurso = true;
            ejecutarRonda();

            int ganador = determinarGanadorRonda();
            finalizarPartida(ganador, "clasico");

            // Preguntar si quieren volver a jugar
            char respuesta;
            cin >> respuesta;
            cin.ignore();

            if (respuesta == 's' || respuesta == 'S' || respuesta == '\n' || respuesta == '\r') {
                // Resetear para nueva partida
                jugador1.registrarTiempo(0);
                jugador2.registrarTiempo(0);
                jugador1.setVictorias(0);
                jugador1.setPartidas(0);
                jugador2.setVictorias(0);
                jugador2.setPartidas(0);
            }
            else {
                quiereJugar = false;
            }
        }

        gfx.mostrarCursor();
        gfx.resetColor();
        enCurso = false;
    }

    // MODO 2: Rondas Múltiples - MEJORADO CON GRÁFICOS
    void modoRondasMultiples(int totalRondas) {
        enCurso = true;
        int victoriasJ1 = 0;
        int victoriasJ2 = 0;
        int rondasNecesarias = (totalRondas / 2) + 1;

        float mejorTiempoJ1 = 0;
        float mejorTiempoJ2 = 0;

        for (int ronda = 1; ronda <= totalRondas; ronda++) {
            if (victoriasJ1 >= rondasNecesarias || victoriasJ2 >= rondasNecesarias) {
                break;
            }

            // Pantalla de información de ronda con gráficos
            gfx.limpiar();
            gfx.ocultarCursor();
            gfx.rellenarArea(0, 0, 120, 30, Graficos::MAGENTA_OSCURO);

            gfx.textoCentrado("════════════════════════════════════════════", 8, Graficos::AMARILLO);
            string textoRonda = "RONDA " + to_string(ronda) + " DE " + to_string(totalRondas);
            gfx.textoCentrado(textoRonda, 10, Graficos::AMARILLO);
            gfx.textoCentrado("════════════════════════════════════════════", 12, Graficos::AMARILLO);

            // Mostrar victorias con barras
            gfx.dibujarBarraVictorias(30, 15, jugador1.getNombre(), victoriasJ1, rondasNecesarias, Graficos::CYAN);
            gfx.dibujarBarraVictorias(30, 17, jugador2.getNombre(), victoriasJ2, rondasNecesarias, Graficos::MAGENTA);

            gfx.mostrarCursor();
            gfx.textoCentrado("Presiona Enter para comenzar...", 22, Graficos::BLANCO);
            cin.ignore();

            ejecutarRonda();

            int ganadorRonda = determinarGanadorRonda();

            // Mostrar ganador de la ronda
            gfx.limpiar();
            gfx.rellenarArea(0, 0, 120, 30, Graficos::VERDE_OSCURO);
            gfx.textoCentrado("--- Resultado de la ronda ---", 10, Graficos::AMARILLO);

            if (ganadorRonda == 1) {
                gfx.textoCentrado(jugador1.getNombre() + " GANA la ronda!", 13, Graficos::VERDE);
                victoriasJ1++;
            }
            else if (ganadorRonda == 2) {
                gfx.textoCentrado(jugador2.getNombre() + " GANA la ronda!", 13, Graficos::VERDE);
                victoriasJ2++;
            }
            else {
                gfx.textoCentrado("¡Empate en esta ronda!", 13, Graficos::CYAN);
            }

            float t1 = jugador1.getTiempoReaccion();
            float t2 = jugador2.getTiempoReaccion();

            if (t1 > 0 && (mejorTiempoJ1 == 0 || t1 < mejorTiempoJ1)) {
                mejorTiempoJ1 = t1;
            }
            if (t2 > 0 && (mejorTiempoJ2 == 0 || t2 < mejorTiempoJ2)) {
                mejorTiempoJ2 = t2;
            }

            gfx.mostrarCursor();
            gfx.textoCentrado("Presiona Enter para continuar...", 20, Graficos::BLANCO);
            cin.ignore();
        }

        if (mejorTiempoJ1 > 0) jugador1.registrarTiempo(mejorTiempoJ1);
        if (mejorTiempoJ2 > 0) jugador2.registrarTiempo(mejorTiempoJ2);

        // Resultado final con gráficos
        gfx.limpiar();
        gfx.ocultarCursor();
        gfx.rellenarArea(0, 0, 120, 30, Graficos::AZUL_OSCURO);

        gfx.textoCentrado("════════════════════════════════════════════", 7, Graficos::AMARILLO);
        gfx.textoCentrado("        R E S U L T A D O   F I N A L", 9, Graficos::AMARILLO);
        gfx.textoCentrado("════════════════════════════════════════════", 11, Graficos::AMARILLO);

        gfx.texto(jugador1.getNombre() + ": " + to_string(victoriasJ1) + " rondas ganadas", 35, 14, Graficos::CYAN);
        gfx.texto(jugador2.getNombre() + ": " + to_string(victoriasJ2) + " rondas ganadas", 35, 16, Graficos::MAGENTA);

        int ganadorFinal = 0;
        if (victoriasJ1 > victoriasJ2) {
            gfx.textoCentrado("*** " + jugador1.getNombre() + " GANA EL MATCH! ***", 19, Graficos::VERDE);
            ganadorFinal = 1;
        }
        else if (victoriasJ2 > victoriasJ1) {
            gfx.textoCentrado("*** " + jugador2.getNombre() + " GANA EL MATCH! ***", 19, Graficos::VERDE);
            ganadorFinal = 2;
        }
        else {
            gfx.textoCentrado("*** EMPATE PERFECTO! ***", 19, Graficos::CYAN);
        }

        finalizarPartida(ganadorFinal, "rondas");
        gfx.mostrarCursor();
        enCurso = false;
    }

    // MODO 3: Modo Práctica - MEJORADO CON GRÁFICOS
    void modoPractica(Jugador& jugador, int numeroIntentos = 5) {
        enCurso = true;
        float mejorTiempo = 0;
        float tiempoPromedio = 0;
        int intentosCompletados = 0;

        gfx.pantallaModoPractica(jugador.getNombre(), numeroIntentos);
        gfx.mostrarCursor();
        gfx.textoCentrado("Presiona Enter para comenzar...", 22, Graficos::BLANCO);
        cin.ignore();

        for (int intento = 1; intento <= numeroIntentos; intento++) {
            gfx.limpiar();
            gfx.ocultarCursor();
            gfx.rellenarArea(0, 0, 120, 30, Graficos::CYAN_OSCURO);

            string textoIntento = "INTENTO " + to_string(intento) + " DE " + to_string(numeroIntentos);
            gfx.textoCentrado("════════════════════════════════════════════", 6, Graficos::AMARILLO);
            gfx.textoCentrado(textoIntento, 8, Graficos::AMARILLO);
            gfx.textoCentrado("════════════════════════════════════════════", 10, Graficos::AMARILLO);

            if (mejorTiempo > 0) {
                string mejor = "Mejor tiempo: " + to_string(mejorTiempo).substr(0, 6) + "s";
                gfx.textoCentrado(mejor, 13, Graficos::VERDE);
            }

            gfx.textoCentrado("Presiona [" + string(1, jugador.getTecla()) + "] cuando veas ¡DISPARA!", 16, Graficos::BLANCO);
            this_thread::sleep_for(chrono::milliseconds(2000));

            // Cuenta regresiva
            gfx.animarCuentaRegresiva(tiempoCuentaRegresiva);

            gfx.limpiar();
            gfx.rellenarArea(0, 0, 120, 30, Graficos::ROJO);
            gfx.textoCentrado("¡ D I S P A R A !", 13, Graficos::AMARILLO);

            temporizador.iniciar();
            bool teclaPresionada = false;
            float tiempoReaccion = 0;

            while (!teclaPresionada) {
                if (_kbhit()) {
                    char tecla = _getch();
                    temporizador.detener();
                    tiempoReaccion = temporizador.obtenerDiferencia();

                    if (tecla == jugador.getTecla()) {
                        teclaPresionada = true;
                        intentosCompletados++;
                        tiempoPromedio += tiempoReaccion;

                        gfx.limpiar();
                        gfx.rellenarArea(0, 0, 120, 30, Graficos::VERDE_OSCURO);

                        string msg = "Tiempo de reaccion: " + to_string(tiempoReaccion).substr(0, 6) + "s";
                        gfx.textoCentrado(msg, 12, Graficos::BLANCO);

                        if (mejorTiempo == 0 || tiempoReaccion < mejorTiempo) {
                            mejorTiempo = tiempoReaccion;
                            gfx.textoCentrado("*** ¡NUEVO RECORD PERSONAL! ***", 14, Graficos::AMARILLO);
                        }

                        // Feedback según el tiempo
                        if (tiempoReaccion < 0.2) {
                            gfx.textoCentrado("¡INCREIBLE! Reflejos de campeon!", 17, Graficos::VERDE);
                        }
                        else if (tiempoReaccion < 0.3) {
                            gfx.textoCentrado("¡Excelente! Muy rapido!", 17, Graficos::VERDE);
                        }
                        else if (tiempoReaccion < 0.4) {
                            gfx.textoCentrado("¡Bien! Buen tiempo.", 17, Graficos::CYAN);
                        }
                        else if (tiempoReaccion < 0.5) {
                            gfx.textoCentrado("No esta mal, puedes mejorar.", 17, Graficos::AMARILLO);
                        }
                        else {
                            gfx.textoCentrado("Necesitas mas practica.", 17, Graficos::ROJO);
                        }
                    }
                    else {
                        gfx.textoCentrado("Tecla incorrecta. Presiona [" + string(1, jugador.getTecla()) + "]", 19, Graficos::ROJO);
                    }
                }
            }

            if (intento < numeroIntentos) {
                gfx.mostrarCursor();
                gfx.textoCentrado("Presiona Enter para el siguiente intento...", 23, Graficos::BLANCO);
                cin.ignore();
            }
        }

        // Mostrar resumen final
        gfx.limpiar();
        gfx.ocultarCursor();
        gfx.rellenarArea(0, 0, 120, 30, Graficos::AZUL_OSCURO);

        gfx.textoCentrado("════════════════════════════════════════════", 7, Graficos::AMARILLO);
        gfx.textoCentrado("      R E S U M E N   D E   P R A C T I C A", 9, Graficos::AMARILLO);
        gfx.textoCentrado("════════════════════════════════════════════", 11, Graficos::AMARILLO);

        gfx.texto("Jugador: " + jugador.getNombre(), 40, 14, Graficos::BLANCO);
        gfx.texto("Intentos completados: " + to_string(intentosCompletados), 40, 16, Graficos::BLANCO);

        string mejor = "Mejor tiempo: " + to_string(mejorTiempo).substr(0, 6) + " segundos";
        gfx.texto(mejor, 40, 18, Graficos::VERDE);

        if (intentosCompletados > 0) {
            float promedio = tiempoPromedio / intentosCompletados;
            string prom = "Tiempo promedio: " + to_string(promedio).substr(0, 6) + " segundos";
            gfx.texto(prom, 40, 20, Graficos::CYAN);
        }

        gfx.textoCentrado("Recuerda: Este modo NO afecta tu ranking.", 23, Graficos::AMARILLO_OSCURO);

        gfx.mostrarCursor();
        enCurso = false;
    }

    // MODO 4: Torneo - MEJORADO CON GRÁFICOS
    void modoTorneo(vector<string>& nombresJugadores) {
        if (nombresJugadores.size() < 4 || nombresJugadores.size() > 16) {
            cout << "Error: El torneo requiere entre 4 y 16 jugadores.\n";
            return;
        }

        int numJugadores = nombresJugadores.size();
        if ((numJugadores & (numJugadores - 1)) != 0) {
            cout << "Error: El numero de jugadores debe ser 4, 8 o 16.\n";
            return;
        }

        enCurso = true;
        vector<string> jugadoresActuales = nombresJugadores;
        int ronda = 1;

        auto obtenerNombreRonda = [](int jugadoresRestantes) -> string {
            if (jugadoresRestantes == 2) return "FINAL";
            if (jugadoresRestantes == 4) return "SEMIFINALES";
            if (jugadoresRestantes == 8) return "CUARTOS DE FINAL";
            if (jugadoresRestantes == 16) return "OCTAVOS DE FINAL";
            return "RONDA " + to_string(jugadoresRestantes / 2);
            };

        while (jugadoresActuales.size() > 1) {
            gfx.limpiar();
            gfx.ocultarCursor();
            gfx.rellenarArea(0, 0, 120, 30, Graficos::MAGENTA_OSCURO);

            string nombreRonda = obtenerNombreRonda(jugadoresActuales.size());
            gfx.textoCentrado("════════════════════════════════════════════", 6, Graficos::AMARILLO);
            gfx.textoCentrado(nombreRonda, 8, Graficos::AMARILLO);
            gfx.textoCentrado("════════════════════════════════════════════", 10, Graficos::AMARILLO);

            string jugadores = "Jugadores restantes: " + to_string(jugadoresActuales.size());
            gfx.textoCentrado(jugadores, 13, Graficos::BLANCO);

            vector<string> ganadores;

            for (size_t i = 0; i < jugadoresActuales.size(); i += 2) {
                gfx.limpiar();
                gfx.rellenarArea(0, 0, 120, 30, Graficos::ROJO_OSCURO);

                string duelo = "--- Duelo " + to_string(i / 2 + 1) + " ---";
                gfx.textoCentrado(duelo, 10, Graficos::AMARILLO);

                string vs = jugadoresActuales[i] + " VS " + jugadoresActuales[i + 1];
                gfx.textoCentrado(vs, 13, Graficos::BLANCO);

                gfx.mostrarCursor();
                gfx.textoCentrado("Presiona Enter para comenzar...", 18, Graficos::VERDE);
                cin.ignore();

                Jugador j1(jugadoresActuales[i], 'a');
                Jugador j2(jugadoresActuales[i + 1], 'l');

                jugador1 = j1;
                jugador2 = j2;

                ejecutarRonda();

                int ganador = determinarGanadorRonda();
                string nombreGanador;

                if (ganador == 1) {
                    nombreGanador = jugadoresActuales[i];
                }
                else if (ganador == 2) {
                    nombreGanador = jugadoresActuales[i + 1];
                }
                else {
                    nombreGanador = jugadoresActuales[i];
                }

                gfx.limpiar();
                gfx.rellenarArea(0, 0, 120, 30, Graficos::VERDE_OSCURO);
                gfx.textoCentrado("*** " + nombreGanador + " avanza a la siguiente ronda! ***", 13, Graficos::VERDE);

                ganadores.push_back(nombreGanador);

                gfx.mostrarCursor();
                gfx.textoCentrado("Presiona Enter para continuar...", 20, Graficos::BLANCO);
                cin.ignore();
            }

            jugadoresActuales = ganadores;
            ronda++;
        }

        // Anunciar campeón con gráficos
        gfx.limpiar();
        gfx.ocultarCursor();
        gfx.rellenarArea(0, 0, 120, 30, Graficos::AMARILLO_OSCURO);

        gfx.textoCentrado("════════════════════════════════════════════════════════", 5, Graficos::AMARILLO);
        gfx.textoCentrado("                                                       ", 6, Graficos::AMARILLO);
        gfx.textoCentrado("     *** CAMPEON DEL TORNEO ***                       ", 7, Graficos::AMARILLO);
        gfx.textoCentrado("                                                       ", 8, Graficos::AMARILLO);
        gfx.textoCentrado("           " + jugadoresActuales[0] + "                ", 9, Graficos::VERDE);
        gfx.textoCentrado("                                                       ", 10, Graficos::AMARILLO);
        gfx.textoCentrado("════════════════════════════════════════════════════════", 11, Graficos::AMARILLO);

        // Trofeo ASCII
        gfx.textoCentrado("       ___________", 14, Graficos::AMARILLO);
        gfx.textoCentrado("      '._==_==_=_.'", 15, Graficos::AMARILLO);
        gfx.textoCentrado("      .-\\:      /-.", 16, Graficos::AMARILLO);
        gfx.textoCentrado("     | (|:.     |) |", 17, Graficos::AMARILLO);
        gfx.textoCentrado("      '-|:.     |-'", 18, Graficos::AMARILLO);
        gfx.textoCentrado("        \\::.    /", 19, Graficos::AMARILLO);
        gfx.textoCentrado("         '::. .'", 20, Graficos::AMARILLO);
        gfx.textoCentrado("           ) (", 21, Graficos::AMARILLO);
        gfx.textoCentrado("         _.' '._", 22, Graficos::AMARILLO);

        gfx.textoCentrado("¡Felicidades! Has ganado el torneo!", 24, Graficos::VERDE);

        Jugador campeon(jugadoresActuales[0], 'a');
        campeon.incrementarVictorias();
        campeon.incrementarPartidas();
        campeon.setModoJuego("torneo");
        campeon.registrarTiempo(0.1f);

        Jugador dummy("", 'l');
        dummy.setModoJuego("torneo");

        contenedor.guardarDatos(campeon, dummy);

        gfx.mostrarCursor();
        gfx.resetColor();
        enCurso = false;
    }

    // Método legacy
    void iniciarJuego() {
        modoDueloClasico();
    }
};