#pragma once
#include "Librerias.h"
#include "Jugador.h"
//  Clase ContenedorJugadores
class ContenedorJugadores {
private:
    string nombreArchivo;

public:
    ContenedorJugadores(string archivo = "jugadores.txt") : nombreArchivo(archivo) {}

    void guardarDatos(const Jugador& j1, const Jugador& j2) {
        ofstream archivo(nombreArchivo, ios::app); // modo append
        if (archivo.is_open()) {
            archivo << "Jugador: " << j1.getNombre()
                << " | Victorias: " << j1.getVictorias()
                << " | Partidas: " << j1.getPartidas() << "\n";
            archivo << "Jugador: " << j2.getNombre()
                << " | Victorias: " << j2.getVictorias()
                << " | Partidas: " << j2.getPartidas() << "\n";
            archivo << "------------------------\n";
            archivo.close();
            cout << "\nDatos guardados correctamente en " << nombreArchivo << endl;
        }
        else {
            cout << "Error al abrir el archivo para guardar los datos.\n";
        }
    }

    void cargarDatos() {
        ifstream archivo(nombreArchivo);
        if (archivo.is_open()) {
            string linea;
            cout << "\n=== HISTORIAL DE JUGADORES ===\n";
            while (getline(archivo, linea)) {
                cout << linea << endl;
            }
            archivo.close();
        }
        else {
            cout << "No se pudo abrir el archivo o no existe.\n";
        }
    }
};