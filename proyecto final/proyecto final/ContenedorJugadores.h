#pragma once
#include "Librerias.h"
#include "Jugador.h"

// Clase ContenedorJugadores con soporte JSON
class ContenedorJugadores {
private:
    string nombreArchivo;
    json datos;

    // Cargar datos del archivo JSON
    void cargarJSON() {
        ifstream archivo(nombreArchivo);
        if (archivo.is_open()) {
            try {
                archivo >> datos;
                archivo.close();
            }
            catch (json::parse_error& e) {
                // Si hay error, inicializar estructura vacía
                inicializarJSON();
            }
        }
        else {
            // Si no existe el archivo, crear estructura inicial
            inicializarJSON();
        }
    }

    // Inicializar estructura JSON
    void inicializarJSON() {
        datos = {
            {"juego", "Duelo de Reflejos"},
            {"version", "1.0"},
            {"jugadores", json::array()}
        };
    }

    // Guardar datos al archivo JSON
    void guardarJSON() {
        ofstream archivo(nombreArchivo);
        if (archivo.is_open()) {
            archivo << datos.dump(4); // Formato legible con indentación
            archivo.close();
        }
    }

    // Buscar índice de jugador por nombre
    int buscarJugador(const string& nombre) {
        for (size_t i = 0; i < datos["jugadores"].size(); i++) {
            if (datos["jugadores"][i]["nombre"] == nombre) {
                return i;
            }
        }
        return -1;
    }

    // Buscar índice de jugador por nombre Y modo
    int buscarJugadorPorModo(const string& nombre, const string& modo) {
        for (size_t i = 0; i < datos["jugadores"].size(); i++) {
            if (datos["jugadores"][i]["nombre"] == nombre &&
                datos["jugadores"][i]["modo_juego"] == modo) {
                return i;
            }
        }
        return -1;
    }

    // Actualizar o crear jugador
    void actualizarJugador(const Jugador& jugador) {
        int index = buscarJugador(jugador.getNombre());

        if (index == -1) {
            // Jugador nuevo - crear entrada
            json nuevoJugador = {
                {"nombre", jugador.getNombre()},
                {"victorias", jugador.getVictorias()},
                {"partidas", jugador.getPartidas()},
                {"mejor_tiempo", jugador.getTiempoReaccion()},
                {"tecla", string(1, jugador.getTecla())}
            };
            datos["jugadores"].push_back(nuevoJugador);
        }
        else {
            // Jugador existente - actualizar estadísticas
            datos["jugadores"][index]["victorias"] =
                datos["jugadores"][index]["victorias"].get<int>() + jugador.getVictorias();
            datos["jugadores"][index]["partidas"] =
                datos["jugadores"][index]["partidas"].get<int>() + jugador.getPartidas();

            // Actualizar mejor tiempo si es menor
            float mejorTiempo = datos["jugadores"][index]["mejor_tiempo"].get<float>();
            if (jugador.getTiempoReaccion() < mejorTiempo && jugador.getTiempoReaccion() > 0) {
                datos["jugadores"][index]["mejor_tiempo"] = jugador.getTiempoReaccion();
            }
        }
    }

    // Actualizar o crear jugador con modo específico
    void actualizarJugadorConModo(const Jugador& jugador) {
        int index = buscarJugadorPorModo(jugador.getNombre(), jugador.getModoJuego());

        if (index == -1) {
            // Jugador nuevo en este modo - crear entrada
            json nuevoJugador = {
                {"nombre", jugador.getNombre()},
                {"victorias", jugador.getVictorias()},
                {"partidas", jugador.getPartidas()},
                {"mejor_tiempo", jugador.getTiempoReaccion()},
                {"tecla", string(1, jugador.getTecla())},
                {"modo_juego", jugador.getModoJuego()}
            };
            datos["jugadores"].push_back(nuevoJugador);
        }
        else {
            // Jugador existente en este modo - actualizar estadísticas
            datos["jugadores"][index]["victorias"] =
                datos["jugadores"][index]["victorias"].get<int>() + jugador.getVictorias();
            datos["jugadores"][index]["partidas"] =
                datos["jugadores"][index]["partidas"].get<int>() + jugador.getPartidas();

            // Actualizar mejor tiempo si es menor
            float mejorTiempo = datos["jugadores"][index]["mejor_tiempo"].get<float>();
            if (jugador.getTiempoReaccion() < mejorTiempo && jugador.getTiempoReaccion() > 0) {
                datos["jugadores"][index]["mejor_tiempo"] = jugador.getTiempoReaccion();
            }
        }
    }

public:
    ContenedorJugadores(string archivo = "jugadores.json") : nombreArchivo(archivo) {
        cargarJSON();
    }

    // Guardar datos de una partida
    void guardarDatos(const Jugador& j1, const Jugador& j2) {
        cargarJSON(); // Recargar para tener datos actualizados

        actualizarJugadorConModo(j1);
        actualizarJugadorConModo(j2);

        guardarJSON();
        cout << "\nDatos guardados correctamente en " << nombreArchivo << endl;
    }

    // Mostrar historial completo (ranking)
    void cargarDatos() {
        cargarJSON(); // Recargar datos actuales

        if (datos["jugadores"].empty()) {
            cout << "\n=== HISTORIAL DE JUGADORES ===\n";
            cout << "No hay jugadores registrados aun.\n";
            return;
        }

        cout << "\n===============================================================\n";
        cout << "              ** HISTORIAL DE JUGADORES **                    \n";
        cout << "===============================================================\n";

        // Ordenar por victorias (de mayor a menor)
        json jugadoresOrdenados = datos["jugadores"];
        for (size_t i = 0; i < jugadoresOrdenados.size(); i++) {
            for (size_t j = i + 1; j < jugadoresOrdenados.size(); j++) {
                if (jugadoresOrdenados[i]["victorias"].get<int>() < jugadoresOrdenados[j]["victorias"].get<int>()) {
                    swap(jugadoresOrdenados[i], jugadoresOrdenados[j]);
                }
            }
        }

        for (size_t i = 0; i < jugadoresOrdenados.size(); i++) {
            auto jugador = jugadoresOrdenados[i];
            string nombre = jugador["nombre"].get<string>();
            int victorias = jugador["victorias"].get<int>();
            int partidas = jugador["partidas"].get<int>();
            float mejorTiempo = jugador["mejor_tiempo"].get<float>();

            cout << " " << (i + 1) << ". " << nombre;

            // Espaciado dinámico
            int espacios = 25 - nombre.length() - to_string(i + 1).length();
            for (int k = 0; k < espacios; k++) cout << " ";

            cout << "| Victorias: " << victorias
                << " | Partidas: " << partidas;

            if (partidas > 0) {
                double porcentaje = (victorias * 100.0) / partidas;
                cout << " | Win%: " << fixed << setprecision(1) << porcentaje << "%";
            }

            cout << "\n";
            cout << "   Mejor tiempo: " << fixed << setprecision(4) << mejorTiempo << "s\n";
            cout << "---------------------------------------------------------------\n";
        }

        cout << "===============================================================\n";
    }

    // Mostrar ranking filtrado por modo de juego
    void cargarDatosPorModo(const string& modo) {
        cargarJSON(); // Recargar datos actuales

        // Filtrar jugadores por modo
        json jugadoresFiltrados = json::array();
        for (const auto& jugador : datos["jugadores"]) {
            if (jugador.contains("modo_juego") && jugador["modo_juego"] == modo) {
                jugadoresFiltrados.push_back(jugador);
            }
        }

        if (jugadoresFiltrados.empty()) {
            cout << "\n=== RANKING: ";
            if (modo == "clasico") cout << "DUELO CLASICO";
            else if (modo == "rondas") cout << "RONDAS MULTIPLES";
            cout << " ===\n";
            cout << "No hay jugadores registrados en este modo aun.\n";
            return;
        }

        cout << "\n===============================================================\n";
        cout << "              ** RANKING: ";
        if (modo == "clasico") cout << "DUELO CLASICO";
        else if (modo == "rondas") cout << "RONDAS MULTIPLES";
        cout << " **                    \n";
        cout << "===============================================================\n";

        // Ordenar por victorias (de mayor a menor)
        for (size_t i = 0; i < jugadoresFiltrados.size(); i++) {
            for (size_t j = i + 1; j < jugadoresFiltrados.size(); j++) {
                if (jugadoresFiltrados[i]["victorias"].get<int>() < jugadoresFiltrados[j]["victorias"].get<int>()) {
                    swap(jugadoresFiltrados[i], jugadoresFiltrados[j]);
                }
            }
        }

        for (size_t i = 0; i < jugadoresFiltrados.size(); i++) {
            auto jugador = jugadoresFiltrados[i];
            string nombre = jugador["nombre"].get<string>();
            int victorias = jugador["victorias"].get<int>();
            int partidas = jugador["partidas"].get<int>();
            float mejorTiempo = jugador["mejor_tiempo"].get<float>();

            cout << " " << (i + 1) << ". " << nombre;

            // Espaciado dinámico
            int espacios = 25 - nombre.length() - to_string(i + 1).length();
            for (int k = 0; k < espacios; k++) cout << " ";

            cout << "| Victorias: " << victorias
                << " | Partidas: " << partidas;

            if (partidas > 0) {
                double porcentaje = (victorias * 100.0) / partidas;
                cout << " | Win%: " << fixed << setprecision(1) << porcentaje << "%";
            }

            cout << "\n";
            cout << "   Mejor tiempo: " << fixed << setprecision(4) << mejorTiempo << "s\n";
            cout << "---------------------------------------------------------------\n";
        }

        cout << "===============================================================\n";
    }

    // Modificar victorias de un jugador
    void modificarVictorias(const string& nombre, int nuevasVictorias) {
        cargarJSON();
        int index = buscarJugador(nombre);

        if (index == -1) {
            cout << "Jugador '" << nombre << "' no encontrado.\n";
            return;
        }

        datos["jugadores"][index]["victorias"] = nuevasVictorias;
        guardarJSON();
        cout << "Victorias de '" << nombre << "' actualizadas a " << nuevasVictorias << "\n";
    }

    // Modificar partidas de un jugador
    void modificarPartidas(const string& nombre, int nuevasPartidas) {
        cargarJSON();
        int index = buscarJugador(nombre);

        if (index == -1) {
            cout << "Jugador '" << nombre << "' no encontrado.\n";
            return;
        }

        datos["jugadores"][index]["partidas"] = nuevasPartidas;
        guardarJSON();
        cout << "Partidas de '" << nombre << "' actualizadas a " << nuevasPartidas << "\n";
    }

    // Modificar mejor tiempo de un jugador
    void modificarMejorTiempo(const string& nombre, float nuevoTiempo) {
        cargarJSON();
        int index = buscarJugador(nombre);

        if (index == -1) {
            cout << "Jugador '" << nombre << "' no encontrado.\n";
            return;
        }

        datos["jugadores"][index]["mejor_tiempo"] = nuevoTiempo;
        guardarJSON();
        cout << "Mejor tiempo de '" << nombre << "' actualizado a " << nuevoTiempo << "s\n";
    }

    // Eliminar un jugador
    void eliminarJugador(const string& nombre) {
        cargarJSON();
        int index = buscarJugador(nombre);

        if (index == -1) {
            cout << "Jugador '" << nombre << "' no encontrado.\n";
            return;
        }

        datos["jugadores"].erase(datos["jugadores"].begin() + index);
        guardarJSON();
        cout << "Jugador '" << nombre << "' eliminado del historial.\n";
    }

    // Resetear todas las estadísticas
    void resetearEstadisticas() {
        inicializarJSON();
        guardarJSON();
        cout << "Todas las estadisticas han sido reseteadas.\n";
    }
};