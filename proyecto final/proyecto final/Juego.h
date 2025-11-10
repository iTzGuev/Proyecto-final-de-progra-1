#pragma once
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
    void finalizarPartida(int ganador, const string& modo) {
        cout << "\n=== RESULTADOS ===\n";

        // Establecer el modo de juego antes de guardar
        jugador1.setModoJuego(modo);
        jugador2.setModoJuego(modo);

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

    // MODO 1: Duelo Clásico (una sola ronda) - CORREGIDO SIN RECURSIVIDAD
    void modoDueloClasico() {
        bool quiereJugar = true;

        while (quiereJugar) {
            enCurso = true;
            ejecutarRonda();

            int ganador = determinarGanadorRonda();
            finalizarPartida(ganador, "clasico");

            // Preguntar si quieren volver a jugar
            char respuesta;
            cout << "\n¿Quieren jugar otra vez? (s/n): ";
            cin >> respuesta;
            cin.ignore();

            if (respuesta == 's' || respuesta == 'S') {
                // Resetear para nueva partida
                jugador1.registrarTiempo(0);
                jugador2.registrarTiempo(0);
                jugador1.setVictorias(0);
                jugador1.setPartidas(0);
                jugador2.setVictorias(0);
                jugador2.setPartidas(0);
                system("cls");
            }
            else {
                quiereJugar = false;
            }
        }

        enCurso = false;
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

        finalizarPartida(ganadorFinal, "rondas");
        enCurso = false;
    }

    // MODO 3: Modo Práctica (un solo jugador, sin guardar estadísticas)
    void modoPractica(Jugador& jugador, int numeroIntentos = 5) {
        enCurso = true;
        float mejorTiempo = 0;
        float tiempoPromedio = 0;
        int intentosCompletados = 0;

        cout << "\n========================================\n";
        cout << "         MODO PRACTICA\n";
        cout << "========================================\n";
        cout << "Jugador: " << jugador.getNombre() << "\n";
        cout << "Intentos: " << numeroIntentos << "\n";
        cout << "Tecla: [" << jugador.getTecla() << "]\n";
        cout << "========================================\n";
        cout << "\nEste modo NO afecta tus estadisticas.\n";
        cout << "Presiona Enter para comenzar...";
        cin.ignore();

        for (int intento = 1; intento <= numeroIntentos; intento++) {
            system("cls");
            cout << "\n========================================\n";
            cout << "    INTENTO " << intento << " DE " << numeroIntentos << "\n";
            cout << "========================================\n";

            if (mejorTiempo > 0) {
                cout << "Mejor tiempo hasta ahora: " << fixed << setprecision(4) << mejorTiempo << "s\n";
            }

            cout << "\nPresiona [" << jugador.getTecla() << "] cuando veas ¡DISPARA!\n";
            cout << "\nPreparate...\n";

            // Cuenta regresiva
            for (int i = tiempoCuentaRegresiva; i > 0; --i) {
                cout << i << "...\n";
                this_thread::sleep_for(chrono::seconds(1));
            }
            cout << "\n¡DISPARA!\n";

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

                        cout << "\nTiempo de reaccion: " << fixed << setprecision(4) << tiempoReaccion << " segundos\n";

                        // Actualizar mejor tiempo
                        if (mejorTiempo == 0 || tiempoReaccion < mejorTiempo) {
                            mejorTiempo = tiempoReaccion;
                            cout << "*** ¡NUEVO RECORD PERSONAL! ***\n";
                        }

                        // Feedback según el tiempo
                        if (tiempoReaccion < 0.2) {
                            cout << "¡INCREIBLE! Reflejos de campeon!\n";
                        }
                        else if (tiempoReaccion < 0.3) {
                            cout << "¡Excelente! Muy rapido!\n";
                        }
                        else if (tiempoReaccion < 0.4) {
                            cout << "¡Bien! Buen tiempo.\n";
                        }
                        else if (tiempoReaccion < 0.5) {
                            cout << "No esta mal, puedes mejorar.\n";
                        }
                        else {
                            cout << "Necesitas mas practica.\n";
                        }
                    }
                    else {
                        cout << "\nTecla incorrecta. Presiona [" << jugador.getTecla() << "]\n";
                    }
                }
            }

            if (intento < numeroIntentos) {
                cout << "\nPresiona Enter para el siguiente intento...";
                cin.ignore();
            }
        }

        // Mostrar resumen final
        system("cls");
        cout << "\n========================================\n";
        cout << "      RESUMEN DE PRACTICA\n";
        cout << "========================================\n";
        cout << "Jugador: " << jugador.getNombre() << "\n";
        cout << "Intentos completados: " << intentosCompletados << "\n";
        cout << "----------------------------------------\n";
        cout << "Mejor tiempo: " << fixed << setprecision(4) << mejorTiempo << " segundos\n";

        if (intentosCompletados > 0) {
            float promedio = tiempoPromedio / intentosCompletados;
            cout << "Tiempo promedio: " << fixed << setprecision(4) << promedio << " segundos\n";
        }

        cout << "========================================\n";
        cout << "\nRecuerda: Este modo NO afecta tu ranking.\n";

        enCurso = false;
    }

    // MODO 4: Torneo (eliminación directa)
    void modoTorneo(vector<string>& nombresJugadores) {
        if (nombresJugadores.size() < 4 || nombresJugadores.size() > 16) {
            cout << "Error: El torneo requiere entre 4 y 16 jugadores.\n";
            return;
        }

        // Validar que el número sea potencia de 2
        int numJugadores = nombresJugadores.size();
        if ((numJugadores & (numJugadores - 1)) != 0) {
            cout << "Error: El numero de jugadores debe ser 4, 8 o 16.\n";
            return;
        }

        enCurso = true;
        vector<string> jugadoresActuales = nombresJugadores;
        int ronda = 1;

        // Determinar nombre de la ronda
        auto obtenerNombreRonda = [](int jugadoresRestantes) -> string {
            if (jugadoresRestantes == 2) return "FINAL";
            if (jugadoresRestantes == 4) return "SEMIFINALES";
            if (jugadoresRestantes == 8) return "CUARTOS DE FINAL";
            if (jugadoresRestantes == 16) return "OCTAVOS DE FINAL";
            return "RONDA " + to_string(jugadoresRestantes / 2);
            };

        // Bucle principal del torneo
        while (jugadoresActuales.size() > 1) {
            system("cls");
            cout << "\n============================================\n";
            cout << "     " << obtenerNombreRonda(jugadoresActuales.size()) << "\n";
            cout << "============================================\n";
            cout << "Jugadores restantes: " << jugadoresActuales.size() << "\n";
            cout << "============================================\n\n";

            vector<string> ganadores;

            // Enfrentar a los jugadores en pares
            for (size_t i = 0; i < jugadoresActuales.size(); i += 2) {
                cout << "\n--- Duelo " << (i / 2 + 1) << " ---\n";
                cout << jugadoresActuales[i] << " vs " << jugadoresActuales[i + 1] << "\n";
                cout << "Presiona Enter para comenzar...";
                cin.ignore();

                // Crear jugadores temporales
                Jugador j1(jugadoresActuales[i], 'a');
                Jugador j2(jugadoresActuales[i + 1], 'l');

                // Asignar a los atributos de la clase
                jugador1 = j1;
                jugador2 = j2;

                // Ejecutar duelo
                system("cls");
                cout << "\n=== " << jugadoresActuales[i] << " vs " << jugadoresActuales[i + 1] << " ===\n";
                ejecutarRonda();

                // Determinar ganador
                int ganador = determinarGanadorRonda();
                string nombreGanador;

                if (ganador == 1) {
                    nombreGanador = jugadoresActuales[i];
                    cout << "\n*** " << nombreGanador << " avanza a la siguiente ronda! ***\n";
                }
                else if (ganador == 2) {
                    nombreGanador = jugadoresActuales[i + 1];
                    cout << "\n*** " << nombreGanador << " avanza a la siguiente ronda! ***\n";
                }
                else {
                    // En caso de empate, elegir al primero
                    nombreGanador = jugadoresActuales[i];
                    cout << "\n¡Empate! " << nombreGanador << " avanza por orden.\n";
                }

                ganadores.push_back(nombreGanador);

                cout << "\nPresiona Enter para continuar...";
                cin.ignore();
            }

            jugadoresActuales = ganadores;
            ronda++;
        }

        // Anunciar campeón
        system("cls");
        cout << "\n";
        cout << "================================================\n";
        cout << "                                                \n";
        cout << "     *** CAMPEON DEL TORNEO ***                \n";
        cout << "                                                \n";
        cout << "           " << jugadoresActuales[0] << "           \n";
        cout << "                                                \n";
        cout << "================================================\n";
        cout << "\n¡Felicidades! Has ganado el torneo!\n";

        // Guardar estadísticas del campeón
        Jugador campeon(jugadoresActuales[0], 'a');
        campeon.incrementarVictorias();
        campeon.incrementarPartidas();
        campeon.setModoJuego("torneo");
        campeon.registrarTiempo(0.1f);

        Jugador dummy("", 'l');
        dummy.setModoJuego("torneo");

        contenedor.guardarDatos(campeon, dummy);

        enCurso = false;
    }

    // MODO 5: Desafío de Velocidad (rondas rápidas con dificultad progresiva)
    void modoDesafioVelocidad(Jugador& jugador, int numeroRondas = 10) {
        enCurso = true;
        float tiempoEspera = 3.0f;
        int puntosTotales = 0;
        int rondasCompletadas = 0;
        int errores = 0;
        float mejorTiempo = 0;

        cout << "\n============================================\n";
        cout << "      DESAFIO DE VELOCIDAD\n";
        cout << "============================================\n";
        cout << "Jugador: " << jugador.getNombre() << "\n";
        cout << "Rondas: " << numeroRondas << "\n";
        cout << "Tecla: [" << jugador.getTecla() << "]\n";
        cout << "============================================\n";
        cout << "\nReglas:\n";
        cout << "- Reacciona lo mas rapido posible\n";
        cout << "- La dificultad aumenta cada ronda\n";
        cout << "- Mas rapido = Mas puntos\n";
        cout << "- Los errores restan puntos\n";
        cout << "\nPresiona Enter para comenzar...";
        cin.ignore();

        // Sistema de rondas progresivas
        for (int ronda = 1; ronda <= numeroRondas; ronda++) {
            system("cls");
            cout << "\n============================================\n";
            cout << "    RONDA " << ronda << " DE " << numeroRondas << "\n";
            cout << "============================================\n";
            cout << "Puntos actuales: " << puntosTotales << "\n";
            cout << "Errores: " << errores << "\n";
            if (mejorTiempo > 0) {
                cout << "Mejor tiempo: " << fixed << setprecision(4) << mejorTiempo << "s\n";
            }
            cout << "============================================\n\n";

            cout << "Preparate...\n";

            // Espera aleatoria para evitar anticipación
            int esperaAleatoria = (rand() % 2000) + 1000; // Entre 1-3 segundos
            this_thread::sleep_for(chrono::milliseconds(esperaAleatoria));

            cout << "\n¡AHORA!\n";

            temporizador.iniciar();
            bool teclaPresionada = false;
            bool teclaCorrecta = false;
            float tiempoReaccion = 0;

            // Esperar respuesta (máximo 2 segundos)
            auto tiempoLimite = high_resolution_clock::now() + chrono::seconds(2);

            while (!teclaPresionada && high_resolution_clock::now() < tiempoLimite) {
                if (_kbhit()) {
                    char tecla = _getch();
                    temporizador.detener();
                    tiempoReaccion = temporizador.obtenerDiferencia();
                    teclaPresionada = true;

                    if (tecla == jugador.getTecla()) {
                        teclaCorrecta = true;
                    }
                }
            }

            // Calcular puntos
            int puntosRonda = 0;

            if (!teclaPresionada) {
                cout << "\n¡Muy lento! No respondiste a tiempo.\n";
                puntosRonda = -50;
                errores++;
            }
            else if (!teclaCorrecta) {
                cout << "\n¡Tecla incorrecta!\n";
                puntosRonda = -30;
                errores++;
            }
            else {
                rondasCompletadas++;
                cout << "\nTiempo: " << fixed << setprecision(4) << tiempoReaccion << "s\n";

                // Actualizar mejor tiempo
                if (mejorTiempo == 0 || tiempoReaccion < mejorTiempo) {
                    mejorTiempo = tiempoReaccion;
                }

                // Sistema de puntuación basado en velocidad
                if (tiempoReaccion < 0.15) {
                    puntosRonda = 200;
                    cout << "¡INCREIBLE! +200 puntos\n";
                }
                else if (tiempoReaccion < 0.20) {
                    puntosRonda = 150;
                    cout << "¡EXCELENTE! +150 puntos\n";
                }
                else if (tiempoReaccion < 0.30) {
                    puntosRonda = 100;
                    cout << "¡MUY BIEN! +100 puntos\n";
                }
                else if (tiempoReaccion < 0.40) {
                    puntosRonda = 75;
                    cout << "¡BIEN! +75 puntos\n";
                }
                else if (tiempoReaccion < 0.50) {
                    puntosRonda = 50;
                    cout << "¡ACEPTABLE! +50 puntos\n";
                }
                else {
                    puntosRonda = 25;
                    cout << "¡LENTO! +25 puntos\n";
                }

                // Bonus por racha perfecta
                if (errores == 0 && ronda >= 5) {
                    int bonus = 50;
                    puntosRonda += bonus;
                    cout << "¡RACHA PERFECTA! +" << bonus << " puntos bonus\n";
                }
            }

            puntosTotales += puntosRonda;
            if (puntosRonda > 0) {
                cout << "\n++" << puntosRonda << " puntos\n";
            }
            else {
                cout << "\n" << puntosRonda << " puntos\n";
            }

            cout << "Total: " << puntosTotales << " puntos\n";

            // Reducir tiempo entre rondas para aumentar dificultad
            tiempoEspera = max(0.5f, tiempoEspera - 0.1f);

            if (ronda < numeroRondas) {
                cout << "\nPresiona Enter para la siguiente ronda...";
                cin.ignore();
            }
        }

        // Resumen final
        system("cls");
        cout << "\n================================================\n";
        cout << "      DESAFIO DE VELOCIDAD COMPLETADO\n";
        cout << "================================================\n";
        cout << "Jugador: " << jugador.getNombre() << "\n";
        cout << "------------------------------------------------\n";
        cout << "Rondas completadas: " << rondasCompletadas << "/" << numeroRondas << "\n";
        cout << "Errores: " << errores << "\n";
        cout << "Mejor tiempo: " << fixed << setprecision(4) << mejorTiempo << "s\n";
        cout << "------------------------------------------------\n";
        cout << "PUNTUACION FINAL: " << puntosTotales << " puntos\n";
        cout << "================================================\n\n";

        // Clasificación final
        if (puntosTotales >= 1500) {
            cout << "¡MAESTRO DE LA VELOCIDAD! Eres increible!\n";
        }
        else if (puntosTotales >= 1000) {
            cout << "¡EXPERTO! Excelentes reflejos!\n";
        }
        else if (puntosTotales >= 700) {
            cout << "¡COMPETENTE! Buen desempeno!\n";
        }
        else if (puntosTotales >= 400) {
            cout << "¡PRINCIPIANTE! Sigue practicando!\n";
        }
        else {
            cout << "¡NOVATO! Necesitas mas entrenamiento!\n";
        }

        // Guardar estadísticas (puntos como "victorias", rondas como "partidas")
        jugador.setVictorias(puntosTotales);
        jugador.setPartidas(numeroRondas);
        jugador.registrarTiempo(mejorTiempo);
        jugador.setModoJuego("velocidad");

        Jugador dummy("", 'l');
        dummy.setModoJuego("velocidad");

        contenedor.guardarDatos(jugador, dummy);

        enCurso = false;
    }

    // Método legacy para mantener compatibilidad
    void iniciarJuego() {
        modoDueloClasico();
    }
};