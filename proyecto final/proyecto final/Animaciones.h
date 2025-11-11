#pragma once
#include "Librerias.h"

// Clase para manejar animaciones ASCII
class Animaciones {
public:
    // Animación de pistola en reposo para jugador izquierdo
    static void mostrarPistolaIzquierda() {
        cout << "\n";
        cout << "        ___\n";
        cout << "       |   |\n";
        cout << "    ___|   |___\n";
        cout << "   |___________|\n";
        cout << "       |_____|\n";
        cout << "          |\n";
    }

    // Animación de pistola en reposo para jugador derecho
    static void mostrarPistolaDerecha() {
        cout << "\n";
        cout << "                                    ___\n";
        cout << "                                   |   |\n";
        cout << "                                ___|   |___\n";
        cout << "                               |___________|\n";
        cout << "                                   |_____|\n";
        cout << "                                      |\n";
    }

    // Animación de disparo para jugador izquierdo
    static void mostrarDisparoIzquierdo() {
        cout << "\n";
        cout << "        ___\n";
        cout << "       |   |\n";
        cout << "    ___|   |___  * * *\n";
        cout << "   |___________| * * * *\n";
        cout << "       |_____| * * *\n";
        cout << "          |\n";
        cout << "      ¡BANG!\n";
    }

    // Animación de disparo para jugador derecho
    static void mostrarDisparoDerecho() {
        cout << "\n";
        cout << "                                    ___\n";
        cout << "                                   |   |\n";
        cout << "                      * * *     ___|   |___\n";
        cout << "                     * * * *   |___________|\n";
        cout << "                      * * *        |_____|\n";
        cout << "                                      |\n";
        cout << "                                  ¡BANG!\n";
    }

    // Mostrar ambas pistolas en posición de espera
    static void mostrarAmbasPistolas(const string& nombreJ1, const string& nombreJ2, char teclaJ1, char teclaJ2) {
        cout << "\n";
        cout << "    " << nombreJ1 << " [" << teclaJ1 << "]";

        // Espaciado dinámico
        int espacios = 40 - nombreJ1.length();
        for (int i = 0; i < espacios; i++) cout << " ";

        cout << nombreJ2 << " [" << teclaJ2 << "]\n";
        cout << "\n";
        cout << "        ___                                 ___\n";
        cout << "       |   |                               |   |\n";
        cout << "    ___|   |___                         ___|   |___\n";
        cout << "   |___________|                       |___________|\n";
        cout << "       |_____|                             |_____|\n";
        cout << "          |                                   |\n";
    }

    // Animación de cuenta regresiva más visual
    static void mostrarCuentaRegresiva(int numero) {
        system("cls");
        cout << "\n\n\n";

        if (numero == 3) {
            cout << "        =============================\n";
            cout << "        ||                         ||\n";
            cout << "        ||          3              ||\n";
            cout << "        ||                         ||\n";
            cout << "        =============================\n";
        }
        else if (numero == 2) {
            cout << "        =============================\n";
            cout << "        ||                         ||\n";
            cout << "        ||          2              ||\n";
            cout << "        ||                         ||\n";
            cout << "        =============================\n";
        }
        else if (numero == 1) {
            cout << "        =============================\n";
            cout << "        ||                         ||\n";
            cout << "        ||          1              ||\n";
            cout << "        ||                         ||\n";
            cout << "        =============================\n";
        }
    }

    // Animación de "¡DISPAREN!"
    static void mostrarDisparen() {
        system("cls");
        cout << "\n\n\n";
        cout << "    ============================================\n";
        cout << "    ||                                        ||\n";
        cout << "    ||        ¡¡¡ DISPAREN !!!                ||\n";
        cout << "    ||                                        ||\n";
        cout << "    ============================================\n";
    }

    // Mostrar resultado con animación de ganador
    static void mostrarGanador(const string& nombreGanador, bool esEmpate = false) {
        system("cls");
        cout << "\n\n";

        if (esEmpate) {
            cout << "    ============================================\n";
            cout << "    ||                                        ||\n";
            cout << "    ||          ¡EMPATE PERFECTO!            ||\n";
            cout << "    ||                                        ||\n";
            cout << "    ||      Ambos tienen reflejos iguales    ||\n";
            cout << "    ||                                        ||\n";
            cout << "    ============================================\n";
        }
        else {
            cout << "    ============================================\n";
            cout << "    ||                                        ||\n";
            cout << "    ||           ¡¡¡ GANADOR !!!             ||\n";
            cout << "    ||                                        ||\n";
            cout << "    ||        " << nombreGanador;

            // Centrar el nombre
            int espacios = 25 - nombreGanador.length();
            for (int i = 0; i < espacios; i++) cout << " ";
            cout << "||\n";

            cout << "    ||                                        ||\n";
            cout << "    ============================================\n";

            // ASCII art de trofeo
            cout << "\n";
            cout << "                    ___________\n";
            cout << "                   '._==_==_=_.'\n";
            cout << "                   .-\\:      /-.\n";
            cout << "                  | (|:.     |) |\n";
            cout << "                   '-|:.     |-'\n";
            cout << "                     \\::.    /\n";
            cout << "                      '::. .'\n";
            cout << "                        ) (\n";
            cout << "                      _.' '._\n";
            cout << "                     '-------'\n";
        }
    }

    // Animación de disparo para modo práctica/velocidad (simplificada)
    static void mostrarDisparoSimple() {
        cout << "\n";
        cout << "            ___\n";
        cout << "           |   |\n";
        cout << "        ___|   |___  * * *\n";
        cout << "       |___________| * * * *\n";
        cout << "           |_____| * * *\n";
        cout << "              |\n";
        cout << "          ¡BANG!\n";
    }

    // Banner de torneo
    static void mostrarBannerTorneo(const string& nombreRonda, int jugadoresRestantes) {
        system("cls");
        cout << "\n\n";
        cout << "    ================================================\n";
        cout << "    ||                                            ||\n";
        cout << "    ||            MODO TORNEO                    ||\n";
        cout << "    ||                                            ||\n";
        cout << "    ||         " << nombreRonda;

        int espacios = 33 - nombreRonda.length();
        for (int i = 0; i < espacios; i++) cout << " ";
        cout << "||\n";

        cout << "    ||                                            ||\n";
        cout << "    ||    Jugadores restantes: " << jugadoresRestantes << "               ||\n";
        cout << "    ||                                            ||\n";
        cout << "    ================================================\n\n";
    }

    // Banner de campeón de torneo
    static void mostrarCampeonTorneo(const string& nombreCampeon) {
        system("cls");
        cout << "\n\n";
        cout << "    ===================================================\n";
        cout << "    ||                                               ||\n";
        cout << "    ||        ★ ★ ★  CAMPEON  ★ ★ ★                ||\n";
        cout << "    ||                                               ||\n";
        cout << "    ||              " << nombreCampeon;

        int espacios = 33 - nombreCampeon.length();
        for (int i = 0; i < espacios; i++) cout << " ";
        cout << "||\n";

        cout << "    ||                                               ||\n";
        cout << "    ===================================================\n";
        cout << "\n";
        cout << "                      .-========-.\n";
        cout << "                      \\`-._  _.~'/\n";
        cout << "                       `.  (o)  ,'\n";
        cout << "                        |  .-.  |\n";
        cout << "                        | (^^^) |\n";
        cout << "                        |  `-'  |\n";
        cout << "                       .-`.___,'-.\n";
        cout << "                      /   |`'`|   \\\n";
        cout << "                     /    |   |    \\\n";
        cout << "                    '-----------------'\n";
    }

    // Animación de "Preparense"
    static void mostrarPreparense() {
        system("cls");
        cout << "\n\n\n";
        cout << "    ============================================\n";
        cout << "    ||                                        ||\n";
        cout << "    ||          PREPARENSE...                ||\n";
        cout << "    ||                                        ||\n";
        cout << "    ============================================\n";
    }
};