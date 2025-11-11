#pragma once
#include "Librerias.h"
//Clase Jugador
class Jugador {
private:
    string nombre;
    float tiempoReaccion;
    char tecla;
    int victorias;
    int partidasJugadas;
    string modoJuego;
public:
    Jugador(string n = "", char t = ' ', string modo = "clasico")
        : nombre(n), tecla(t), tiempoReaccion(0), victorias(0), partidasJugadas(0), modoJuego(modo) {
    }
    void registrarTiempo(float tiempo) { tiempoReaccion = tiempo; }
    float getTiempoReaccion() const { return tiempoReaccion; }
    string getNombre() const { return nombre; }
    char getTecla() const { return tecla; }
    int getVictorias() const { return victorias; }
    int getPartidas() const { return partidasJugadas; }
    string getModoJuego() const { return modoJuego; }
    void incrementarVictorias() { victorias++; }
    void incrementarPartidas() { partidasJugadas++; }
    void setNombre(string n) { nombre = n; }
    void setTecla(char t) { tecla = t; }
    void setVictorias(int v) { victorias = v; }
    void setPartidas(int p) { partidasJugadas = p; }
    void setModoJuego(string modo) { modoJuego = modo; }
};