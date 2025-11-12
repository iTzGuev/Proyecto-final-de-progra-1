#pragma once
#include <windows.h>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

// Clase para manejar gráficos y colores en consola Windows
class Graficos {
private:
    HANDLE hConsole;
    CONSOLE_SCREEN_BUFFER_INFO csbi;

public:
    // Códigos de color
    enum Color {
        NEGRO = 0,
        AZUL_OSCURO = 1,
        VERDE_OSCURO = 2,
        CYAN_OSCURO = 3,
        ROJO_OSCURO = 4,
        MAGENTA_OSCURO = 5,
        AMARILLO_OSCURO = 6,
        GRIS_CLARO = 7,
        GRIS_OSCURO = 8,
        AZUL = 9,
        VERDE = 10,
        CYAN = 11,
        ROJO = 12,
        MAGENTA = 13,
        AMARILLO = 14,
        BLANCO = 15
    };

    Graficos() {
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleScreenBufferInfo(hConsole, &csbi);

        // Configurar ventana de consola más grande
        SMALL_RECT windowSize = { 0, 0, 119, 29 };
        SetConsoleWindowInfo(hConsole, TRUE, &windowSize);

        COORD bufferSize = { 120, 30 };
        SetConsoleScreenBufferSize(hConsole, bufferSize);
    }

    // Establecer color del texto
    void setColor(int texto, int fondo = 0) {
        SetConsoleTextAttribute(hConsole, texto + (fondo * 16));
    }

    // Restaurar color original
    void resetColor() {
        SetConsoleTextAttribute(hConsole, 7); // Blanco sobre negro
    }

    // Mover cursor a posición específica
    void gotoxy(int x, int y) {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(hConsole, coord);
    }

    // Ocultar cursor parpadeante
    void ocultarCursor() {
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(hConsole, &cursorInfo);
        cursorInfo.bVisible = false;
        SetConsoleCursorInfo(hConsole, &cursorInfo);
    }

    // Mostrar cursor
    void mostrarCursor() {
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(hConsole, &cursorInfo);
        cursorInfo.bVisible = true;
        SetConsoleCursorInfo(hConsole, &cursorInfo);
    }

    // Limpiar pantalla
    void limpiar() {
        system("cls");
    }

    // Dibujar un recuadro decorativo
    void dibujarRecuadro(int x, int y, int ancho, int alto, int color) {
        setColor(color);

        // Esquina superior izquierda
        gotoxy(x, y);
        cout << (char)201;

        // Línea superior
        for (int i = 1; i < ancho - 1; i++) cout << (char)205;

        // Esquina superior derecha
        cout << (char)187;

        // Líneas laterales
        for (int i = 1; i < alto - 1; i++) {
            gotoxy(x, y + i);
            cout << (char)186;
            gotoxy(x + ancho - 1, y + i);
            cout << (char)186;
        }

        // Esquina inferior izquierda
        gotoxy(x, y + alto - 1);
        cout << (char)200;

        // Línea inferior
        for (int i = 1; i < ancho - 1; i++) cout << (char)205;

        // Esquina inferior derecha
        cout << (char)188;

        resetColor();
    }

    // Rellenar área con color
    void rellenarArea(int x, int y, int ancho, int alto, int color) {
        setColor(BLANCO, color);
        for (int i = 0; i < alto; i++) {
            gotoxy(x, y + i);
            for (int j = 0; j < ancho; j++) {
                cout << " ";
            }
        }
        resetColor();
    }

    // Dibujar texto centrado en pantalla
    void textoCentrado(string texto, int y, int color) {
        int x = (120 - texto.length()) / 2;
        setColor(color);
        gotoxy(x, y);
        cout << texto;
        resetColor();
    }

    // Dibujar texto en posición específica
    void texto(string texto, int x, int y, int color) {
        setColor(color);
        gotoxy(x, y);
        cout << texto;
        resetColor();
    }

    // Banner grande del título con pistolas
    void dibujarTitulo() {
        limpiar();
        ocultarCursor();
        rellenarArea(0, 0, 120, 30, NEGRO);

        // Pistolas en las esquinas
        setColor(GRIS_CLARO);
        texto("    ___", 5, 3, GRIS_CLARO);
        texto("   |___|", 5, 4, GRIS_CLARO);
        texto("  |=====|", 5, 5, GRIS_CLARO);
        texto("   |___|", 5, 6, GRIS_CLARO);

        texto("       ___", 105, 3, GRIS_CLARO);
        texto("      |___|", 105, 4, GRIS_CLARO);
        texto("     |=====|", 105, 5, GRIS_CLARO);
        texto("      |___|", 105, 6, GRIS_CLARO);

        // Título principal
        setColor(ROJO);
        textoCentrado("========================================", 8, ROJO);
        setColor(AMARILLO);
        textoCentrado("??????? ???   ??????????????      ??????? ", 10, AMARILLO);
        textoCentrado("???????????   ??????????????     ?????????", 11, AMARILLO);
        textoCentrado("???  ??????   ?????????  ???     ???   ???", 12, AMARILLO);
        textoCentrado("???  ??????   ?????????  ???     ???   ???", 13, AMARILLO);
        textoCentrado("??????????????????????????????????????????", 14, AMARILLO);
        textoCentrado("???????  ??????? ???????????????? ??????? ", 15, AMARILLO);

        setColor(CYAN);
        textoCentrado("DE REFLEJOS", 17, CYAN);
        setColor(ROJO);
        textoCentrado("========================================", 19, ROJO);

        resetColor();
    }

    // Animación de cuenta regresiva visual mejorada
    void animarCuentaRegresiva(int segundos) {
        for (int i = segundos; i > 0; i--) {
            limpiar();
            ocultarCursor();

            // Color cambia según el número
            int colorNum = (i == 3) ? VERDE : (i == 2) ? AMARILLO : ROJO;
            int colorFondo = (i == 3) ? VERDE_OSCURO : (i == 2) ? AMARILLO_OSCURO : ROJO_OSCURO;

            rellenarArea(0, 0, 120, 30, colorFondo);

            // Dibujar número gigante en ASCII art
            string numStr = to_string(i);

            setColor(colorNum);

            if (i == 3) {
                textoCentrado(" ????????? ??????? ", 8, colorNum);
                textoCentrado(" ????????????????? ", 9, colorNum);
                textoCentrado("    ???   ???????? ", 10, colorNum);
                textoCentrado("    ???   ???????? ", 11, colorNum);
                textoCentrado("    ???   ???????? ", 12, colorNum);
                textoCentrado("    ???   ???????  ", 13, colorNum);
            }
            else if (i == 2) {
                textoCentrado(" ???????  ", 8, colorNum);
                textoCentrado(" ???????? ", 9, colorNum);
                textoCentrado("  ??????? ", 10, colorNum);
                textoCentrado(" ???????  ", 11, colorNum);
                textoCentrado(" ???????? ", 12, colorNum);
                textoCentrado(" ???????? ", 13, colorNum);
            }
            else if (i == 1) {
                textoCentrado(" ??? ", 8, colorNum);
                textoCentrado(" ??? ", 9, colorNum);
                textoCentrado(" ??? ", 10, colorNum);
                textoCentrado(" ??? ", 11, colorNum);
                textoCentrado(" ??? ", 12, colorNum);
                textoCentrado(" ??? ", 13, colorNum);
            }

            setColor(BLANCO);
            textoCentrado("¡ P R E P A R A T E !", 16, BLANCO);

            // Efecto de pulso
            for (int j = 0; j < 4; j++) {
                this_thread::sleep_for(chrono::milliseconds(250));
            }
        }
    }

    // Pantalla de "¡DISPARA!" con efecto explosivo
    void mostrarDispara() {
        limpiar();
        ocultarCursor();

        // Efecto de parpadeo rápido
        for (int i = 0; i < 3; i++) {
            rellenarArea(0, 0, 120, 30, ROJO);
            this_thread::sleep_for(chrono::milliseconds(80));
            rellenarArea(0, 0, 120, 30, AMARILLO);
            this_thread::sleep_for(chrono::milliseconds(80));
        }

        rellenarArea(0, 0, 120, 30, ROJO_OSCURO);

        // Texto "DISPARA" en grande
        setColor(AMARILLO);
        textoCentrado("?????????  ?????????  ????????  ?????????  ????????  ?????????  ????????  ???", 7, AMARILLO);
        textoCentrado("?????????  ?????????  ????????  ?????????  ????????  ????????  ????????  ???", 8, AMARILLO);
        textoCentrado("???   ???     ???     ????????  ???   ???  ????????  ????????  ????????  ???", 9, AMARILLO);
        textoCentrado("???   ???     ???     ????????  ???   ???  ????????  ????????  ????????  ???", 10, AMARILLO);
        textoCentrado("?????????  ?????????  ????????  ?????????  ???  ???  ???  ???  ???  ???  ???", 11, AMARILLO);
        textoCentrado("?????????  ?????????  ????????  ?????????  ???  ???  ???  ???  ???  ???  ???", 12, AMARILLO);

        setColor(ROJO);
        textoCentrado("?????????????????????????????????????????????????????????????", 15, ROJO);
        setColor(BLANCO);
        textoCentrado("?           ¡ ! !   D  I  S  P  A  R  A   ! ! !            ?", 16, BLANCO);
        setColor(ROJO);
        textoCentrado("?????????????????????????????????????????????????????????????", 17, ROJO);

        resetColor();
    }

    // Dibujar jugador con estilo vaquero/duelo
    void dibujarJugador(string nombre, char tecla, int x, int y, int color, bool disparado = false) {
        // Marco del jugador
        dibujarRecuadro(x, y, 32, 10, color);

        // Dibujar figura del jugador (vaquero con sombrero)
        if (!disparado) {
            setColor(color);
            gotoxy(x + 14, y + 2);
            cout << "O";  // Cabeza
            gotoxy(x + 13, y + 3);
            cout << "/|\\"; // Cuerpo
            gotoxy(x + 13, y + 4);
            cout << "/ \\"; // Piernas
        }
        else {
            // Animación de disparo (brazos levantados)
            setColor(VERDE);
            gotoxy(x + 14, y + 2);
            cout << "O";
            gotoxy(x + 13, y + 3);
            cout << "\\|/";
            gotoxy(x + 13, y + 4);
            cout << "/ \\";

            // Destello de pistola
            setColor(AMARILLO);
            gotoxy(x + 11, y + 3);
            cout << "*";
        }

        // Nombre
        setColor(color);
        gotoxy(x + 2, y + 6);
        cout << "Jugador: " << nombre;

        // Tecla asignada
        gotoxy(x + 2, y + 7);
        cout << "Tecla: [" << tecla << "]";

        // Estado
        gotoxy(x + 2, y + 8);
        if (disparado) {
            setColor(VERDE);
            cout << ">>> BANG! <<<";
        }
        else {
            setColor(GRIS_CLARO);
            cout << "Esperando...";
        }

        resetColor();
    }

    // Mostrar resultados con animación de victoria
    void mostrarResultado(string ganador, float tiempoJ1, float tiempoJ2, string nombreJ1, string nombreJ2) {
        limpiar();
        ocultarCursor();

        // Fondo según el ganador
        bool empate = (ganador == "EMPATE" || tiempoJ1 == tiempoJ2);

        if (empate) {
            rellenarArea(0, 0, 120, 30, AMARILLO_OSCURO);
        }
        else {
            rellenarArea(0, 0, 120, 30, VERDE_OSCURO);
        }

        // Título
        setColor(AMARILLO);
        textoCentrado("????????????????????????????????????????????", 3, AMARILLO);
        textoCentrado("     R E S U L T A D O   D E L   D U E L O", 4, AMARILLO);
        textoCentrado("????????????????????????????????????????????", 5, AMARILLO);

        // Tiempos
        setColor(BLANCO);
        string tiempo1 = to_string(tiempoJ1).substr(0, 6) + "s";
        string tiempo2 = to_string(tiempoJ2).substr(0, 6) + "s";

        textoCentrado(nombreJ1 + ": " + tiempo1, 9, BLANCO);
        textoCentrado(nombreJ2 + ": " + tiempo2, 11, BLANCO);

        // Separador
        setColor(AMARILLO);
        textoCentrado("????????????????????????????????????????????", 13, AMARILLO);

        // Ganador
        if (empate) {
            setColor(CYAN);
            textoCentrado("*** ¡ E M P A T E ! ***", 16, CYAN);
        }
        else {
            setColor(VERDE);
            textoCentrado("?????????????????????????????????????????", 15, VERDE);
            textoCentrado("?     *** " + ganador + " GANA! ***      ?", 16, VERDE);
            textoCentrado("?????????????????????????????????????????", 17, VERDE);

            // Trofeo ASCII
            setColor(AMARILLO);
            textoCentrado("    ___________", 19, AMARILLO);
            textoCentrado("   '._==_==_=_.'", 20, AMARILLO);
            textoCentrado("   .-\\:      /-.", 21, AMARILLO);
            textoCentrado("  | (|:.     |) |", 22, AMARILLO);
            textoCentrado("   '-|:.     |-'", 23, AMARILLO);
            textoCentrado("     \\::.    /", 24, AMARILLO);
            textoCentrado("      '::. .'", 25, AMARILLO);
            textoCentrado("        ) (", 26, AMARILLO);
            textoCentrado("      _.' '._", 27, AMARILLO);
        }

        resetColor();
    }

    // Dibujar barra de progreso para rondas múltiples
    void dibujarBarraVictorias(int x, int y, string nombre, int victorias, int total, int color) {
        setColor(color);
        gotoxy(x, y);
        cout << nombre << ": ";

        // Dibujar barra
        for (int i = 0; i < total; i++) {
            if (i < victorias) {
                cout << (char)219; // Estrella/Victoria
            }
            else {
                cout << (char)176; // Vacío
            }
        }

        cout << " [" << victorias << "/" << total << "]";
        resetColor();
    }

    // Efecto de disparo (explosión de asteriscos)
    void efectoDisparo(int x, int y) {
        for (int tam = 1; tam <= 4; tam++) {
            setColor(AMARILLO);
            for (int i = -tam; i <= tam; i++) {
                for (int j = -tam; j <= tam; j++) {
                    if (abs(i) + abs(j) == tam) {
                        gotoxy(x + i * 2, y + j);
                        cout << "*";
                    }
                }
            }
            this_thread::sleep_for(chrono::milliseconds(100));

            // Limpiar el efecto
            for (int i = -tam; i <= tam; i++) {
                for (int j = -tam; j <= tam; j++) {
                    if (abs(i) + abs(j) == tam) {
                        gotoxy(x + i * 2, y + j);
                        cout << " ";
                    }
                }
            }
        }
        resetColor();
    }

    // Pantalla de entrada de modo torneo
    void pantallaModoPractica(string nombre, int intentos) {
        limpiar();
        ocultarCursor();
        rellenarArea(0, 0, 120, 30, AZUL_OSCURO);

        setColor(CYAN);
        textoCentrado("??????????????????????????????????????????????", 8, CYAN);
        textoCentrado("?        MODO ENTRENAMIENTO                 ?", 9, CYAN);
        textoCentrado("??????????????????????????????????????????????", 10, CYAN);

        setColor(BLANCO);
        textoCentrado("Jugador: " + nombre, 13, BLANCO);
        textoCentrado("Intentos: " + to_string(intentos), 15, BLANCO);

        setColor(AMARILLO_OSCURO);
        textoCentrado("Este modo NO afecta tus estadisticas", 18, AMARILLO_OSCURO);

        resetColor();
    }
};