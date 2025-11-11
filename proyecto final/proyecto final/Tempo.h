#pragma once
#include "Librerias.h"
class Temporizador {
private:
    high_resolution_clock::time_point tiempoInicio;
    high_resolution_clock::time_point tiempoFin;
public:
    void iniciar() { tiempoInicio = high_resolution_clock::now(); }
    void detener() { tiempoFin = high_resolution_clock::now(); }
    float obtenerDiferencia() {
        duration<float> duracion = tiempoFin - tiempoInicio;
        return duracion.count();
    }
};