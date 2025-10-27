#include "Librerias.h"

//Clase Jugador
class Jugador {
private:
    string nombre;
    float tiempoReaccion;
    char tecla;
    int victorias;
    int partidasJugadas;

public:
    Jugador(string n = "", char t = ' ')
        : nombre(n), tecla(t), tiempoReaccion(0), victorias(0), partidasJugadas(0) {
    }

    void registrarTiempo(float tiempo) { tiempoReaccion = tiempo; }

    float getTiempoReaccion() const { return tiempoReaccion; }
    string getNombre() const { return nombre; }
    char getTecla() const { return tecla; }
    int getVictorias() const { return victorias; }
    int getPartidas() const { return partidasJugadas; }

    void incrementarVictorias() { victorias++; }
    void incrementarPartidas() { partidasJugadas++; }

    void setNombre(string n) { nombre = n; }
    void setTecla(char t) { tecla = t; }
    void setVictorias(int v) { victorias = v; }
    void setPartidas(int p) { partidasJugadas = p; }
};
#pragma once
