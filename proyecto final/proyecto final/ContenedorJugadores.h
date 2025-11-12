#pragma once
#include "Librerias.h"
#include "Jugador.h"

// Clase ContenedorJugadores con soporte JSON mejorado
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
            {"version", "2.0"},
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

    // Buscar índice de jugador por nombre (sin importar modo)
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

    // Actualizar o crear jugador con modo específico
    void actualizarJugadorConModo(const Jugador& jugador) {
        int index = buscarJugadorPorModo(jugador.getNombre(), jugador.getModoJuego());

        if (index == -1) {
            // Jugador nuevo en este modo - crear entrada
            float tiempoAGuardar = jugador.getTiempoReaccion();
            if (tiempoAGuardar <= 0) {
                tiempoAGuardar = 999.9f;
            }

            json nuevoJugador = {
                {"nombre", jugador.getNombre()},
                {"victorias", jugador.getVictorias()},
                {"partidas", jugador.getPartidas()},
                {"mejor_tiempo", tiempoAGuardar},
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

            float mejorTiempo = datos["jugadores"][index]["mejor_tiempo"].get<float>();
            float nuevoTiempo = jugador.getTiempoReaccion();

            if (nuevoTiempo > 0 && nuevoTiempo < mejorTiempo) {
                datos["jugadores"][index]["mejor_tiempo"] = nuevoTiempo;
            }
        }
    }

    // Obtener encabezado según modo
    string obtenerEncabezadoModo(const string& modo) {
        if (modo == "clasico") return "DUELO CLASICO";
        else if (modo == "rondas") return "RONDAS MULTIPLES";
        else if (modo == "torneo") return "TORNEOS";
        else if (modo == "velocidad") return "DESAFIO DE VELOCIDAD";
        else if (modo == "practica") return "MODO PRACTICA";
        return "RANKING GENERAL";
    }

    // Mostrar estadísticas según el modo
    void mostrarEstadisticasPorModo(const json& jugador, const string& modo, int posicion) {
        string nombre = jugador["nombre"].get<string>();
        int victorias = jugador["victorias"].get<int>();
        int partidas = jugador["partidas"].get<int>();
        float mejorTiempo = jugador["mejor_tiempo"].get<float>();

        // Línea con número de posición y nombre
        cout << " " << posicion << ". " << nombre;

        int espacios = 25 - nombre.length() - to_string(posicion).length();
        for (int k = 0; k < espacios; k++) cout << " ";

        // Mostrar estadísticas según el modo
        if (modo == "velocidad") {
            // Modo velocidad: mostrar puntuación y rondas
            cout << "| Puntuacion: " << setw(5) << victorias
                << " | Rondas: " << setw(3) << partidas;
        }
        else if (modo == "torneo") {
            // Modo torneo: mostrar campeonatos ganados
            cout << "| Campeonatos: " << setw(3) << victorias
                << " | Torneos: " << setw(3) << partidas;
        }
        else if (modo == "practica") {
            // Modo práctica: solo mejor tiempo
            cout << "| Intentos: " << setw(4) << partidas;
        }
        else {
            // Modos clásico y rondas múltiples: victorias y win%
            cout << "| Victorias: " << setw(3) << victorias
                << " | Partidas: " << setw(3) << partidas;

            if (partidas > 0) {
                double porcentaje = (victorias * 100.0) / partidas;
                cout << " | Win%: " << fixed << setprecision(1) << setw(5) << porcentaje << "%";
            }
            else {
                cout << " | Win%:   N/A";
            }
        }

        cout << "\n";

        // Mostrar mejor tiempo si es válido
        if (mejorTiempo > 0 && mejorTiempo < 999) {
            cout << "   Mejor tiempo: " << fixed << setprecision(4) << mejorTiempo << "s";

            // Agregar calificación del tiempo
            if (modo == "velocidad") {
                if (mejorTiempo < 0.15) cout << " [LEGENDARIO]";
                else if (mejorTiempo < 0.20) cout << " [EXCELENTE]";
                else if (mejorTiempo < 0.30) cout << " [MUY BUENO]";
                else if (mejorTiempo < 0.40) cout << " [BUENO]";
            }
            else {
                if (mejorTiempo < 0.20) cout << " [ELITE]";
                else if (mejorTiempo < 0.30) cout << " [EXPERTO]";
                else if (mejorTiempo < 0.40) cout << " [AVANZADO]";
                else if (mejorTiempo < 0.50) cout << " [INTERMEDIO]";
            }
            cout << "\n";
        }
        else {
            cout << "   Mejor tiempo: N/A\n";
        }
    }

public:
    ContenedorJugadores(string archivo = "jugadores.json") : nombreArchivo(archivo) {
        cargarJSON();
    }

    // Guardar datos de una partida
    void guardarDatos(const Jugador& j1, const Jugador& j2) {
        cargarJSON();

        actualizarJugadorConModo(j1);
        // Solo actualizar j2 si tiene un nombre válido (no es dummy)
        if (!j2.getNombre().empty()) {
            actualizarJugadorConModo(j2);
        }

        guardarJSON();
        cout << "\nDatos guardados correctamente en " << nombreArchivo << endl;
    }

    // Mostrar historial completo (ranking general) - CORREGIDO PARA C++14
    void cargarDatos() {
        cargarJSON();

        if (datos["jugadores"].empty()) {
            cout << "\n=== HISTORIAL DE JUGADORES ===\n";
            cout << "No hay jugadores registrados aun.\n";
            return;
        }

        cout << "\n===============================================================\n";
        cout << "              ** RANKING GENERAL **                    \n";
        cout << "       (Victorias reales en duelos/torneos)                    \n";
        cout << "===============================================================\n";

        // Estructura para estadísticas globales
        struct EstadisticasGlobales {
            int victoriasReales;
            int partidasReales;
            int campeonatos;
            int torneosJugados;
            int puntuacionVelocidad;
            int rondasVelocidad;
            float mejorTiempo;
        };

        map<string, EstadisticasGlobales> estadisticasGlobales;

        // Recopilar estadísticas separadas por modo
        for (const auto& jugador : datos["jugadores"]) {
            string nombre = jugador["nombre"].get<string>();
            string modo = jugador["modo_juego"].get<string>();
            int victorias = jugador["victorias"].get<int>();
            int partidas = jugador["partidas"].get<int>();
            float tiempo = jugador["mejor_tiempo"].get<float>();

            // Inicializar si es nuevo
            if (estadisticasGlobales.find(nombre) == estadisticasGlobales.end()) {
                EstadisticasGlobales temp = { 0, 0, 0, 0, 0, 0, 999.9f };
                estadisticasGlobales[nombre] = temp;
            }

            EstadisticasGlobales& stats = estadisticasGlobales[nombre];

            // Separar según modo
            if (modo == "clasico" || modo == "rondas") {
                stats.victoriasReales += victorias;
                stats.partidasReales += partidas;
            }
            else if (modo == "torneo") {
                stats.campeonatos += victorias;
                stats.torneosJugados += partidas;
            }
            else if (modo == "velocidad") {
                stats.puntuacionVelocidad += victorias;
                stats.rondasVelocidad += partidas;
            }

            // Actualizar mejor tiempo
            if (tiempo > 0 && tiempo < 999 && tiempo < stats.mejorTiempo) {
                stats.mejorTiempo = tiempo;
            }
        }

        // Convertir a vector para ordenar
        vector<pair<string, EstadisticasGlobales>> ranking;
        for (map<string, EstadisticasGlobales>::iterator it = estadisticasGlobales.begin();
            it != estadisticasGlobales.end(); ++it) {
            ranking.push_back(*it);
        }

        // Ordenar por victorias reales, luego por campeonatos
        sort(ranking.begin(), ranking.end(),
            [](const pair<string, EstadisticasGlobales>& a, const pair<string, EstadisticasGlobales>& b) {
                int totalA = a.second.victoriasReales + a.second.campeonatos;
                int totalB = b.second.victoriasReales + b.second.campeonatos;

                if (totalA != totalB) return totalA > totalB;
                return a.second.victoriasReales > b.second.victoriasReales;
            });

        // Mostrar ranking
        for (size_t i = 0; i < ranking.size(); i++) {
            string nombre = ranking[i].first;
            EstadisticasGlobales stats = ranking[i].second;

            cout << " " << (i + 1) << ". " << nombre;

            int espacios = 25 - nombre.length() - to_string(i + 1).length();
            for (int k = 0; k < espacios; k++) cout << " ";

            int victoriasTotal = stats.victoriasReales + stats.campeonatos;
            cout << "| Total: " << setw(3) << victoriasTotal << " victorias\n";

            // Desglose detallado
            if (stats.victoriasReales > 0 || stats.partidasReales > 0) {
                cout << "   Duelos: " << stats.victoriasReales << " victorias / "
                    << stats.partidasReales << " partidas";
                if (stats.partidasReales > 0) {
                    double porcentaje = (stats.victoriasReales * 100.0) / stats.partidasReales;
                    cout << " (" << fixed << setprecision(1) << porcentaje << "%)";
                }
                cout << "\n";
            }

            if (stats.campeonatos > 0) {
                cout << "   Torneos: " << stats.campeonatos << " campeonatos ganados / "
                    << stats.torneosJugados << " torneos\n";
            }

            if (stats.puntuacionVelocidad > 0) {
                cout << "   Velocidad: " << stats.puntuacionVelocidad << " puntos / "
                    << stats.rondasVelocidad << " rondas\n";
            }

            // Mejor tiempo global
            if (stats.mejorTiempo < 999) {
                cout << "   Mejor tiempo: " << fixed << setprecision(4) << stats.mejorTiempo << "s";

                if (stats.mejorTiempo < 0.20) cout << " [ELITE]";
                else if (stats.mejorTiempo < 0.30) cout << " [EXPERTO]";
                else if (stats.mejorTiempo < 0.40) cout << " [AVANZADO]";
                else if (stats.mejorTiempo < 0.50) cout << " [INTERMEDIO]";

                cout << "\n";
            }

            cout << "---------------------------------------------------------------\n";
        }

        cout << "===============================================================\n";

        // Mostrar resumen general
        int totalVictorias = 0;
        int totalCampeonatos = 0;
        int totalPuntos = 0;

        for (size_t i = 0; i < ranking.size(); i++) {
            totalVictorias += ranking[i].second.victoriasReales;
            totalCampeonatos += ranking[i].second.campeonatos;
            totalPuntos += ranking[i].second.puntuacionVelocidad;
        }

        cout << "\nResumen del servidor:\n";
        cout << "- Total victorias en duelos: " << totalVictorias << "\n";
        cout << "- Total campeonatos ganados: " << totalCampeonatos << "\n";
        cout << "- Total puntos en velocidad: " << totalPuntos << "\n";
    }

    // Mostrar ranking filtrado por modo de juego
    void cargarDatosPorModo(const string& modo) {
        cargarJSON();

        json jugadoresFiltrados = json::array();
        for (const auto& jugador : datos["jugadores"]) {
            if (jugador.contains("modo_juego") && jugador["modo_juego"] == modo) {
                jugadoresFiltrados.push_back(jugador);
            }
        }

        if (jugadoresFiltrados.empty()) {
            cout << "\n=== RANKING: " << obtenerEncabezadoModo(modo) << " ===\n";
            cout << "No hay jugadores registrados en este modo aun.\n";
            return;
        }

        cout << "\n===============================================================\n";
        cout << "              ** RANKING: " << obtenerEncabezadoModo(modo) << " **\n";
        cout << "===============================================================\n";

        // Ordenar según el criterio del modo
        if (modo == "velocidad") {
            sort(jugadoresFiltrados.begin(), jugadoresFiltrados.end(),
                [](const json& a, const json& b) {
                    return a["victorias"].get<int>() > b["victorias"].get<int>();
                });
        }
        else if (modo == "torneo") {
            sort(jugadoresFiltrados.begin(), jugadoresFiltrados.end(),
                [](const json& a, const json& b) {
                    return a["victorias"].get<int>() > b["victorias"].get<int>();
                });
        }
        else {
            sort(jugadoresFiltrados.begin(), jugadoresFiltrados.end(),
                [](const json& a, const json& b) {
                    int victA = a["victorias"].get<int>();
                    int victB = b["victorias"].get<int>();
                    if (victA != victB) return victA > victB;

                    int partA = a["partidas"].get<int>();
                    int partB = b["partidas"].get<int>();
                    if (partA == 0) return false;
                    if (partB == 0) return true;

                    double winA = (victA * 100.0) / partA;
                    double winB = (victB * 100.0) / partB;
                    return winA > winB;
                });
        }

        // Mostrar jugadores ordenados
        for (size_t i = 0; i < jugadoresFiltrados.size(); i++) {
            mostrarEstadisticasPorModo(jugadoresFiltrados[i], modo, i + 1);
            cout << "---------------------------------------------------------------\n";
        }

        cout << "===============================================================\n";

        // Mostrar estadísticas adicionales del modo
        if (modo == "velocidad") {
            int puntuacionTotal = 0;
            for (const auto& j : jugadoresFiltrados) {
                puntuacionTotal += j["victorias"].get<int>();
            }
            cout << "\nPuntuacion total acumulada: " << puntuacionTotal << " puntos\n";
        }
        else if (modo == "torneo") {
            cout << "\nTotal de torneos completados: " << jugadoresFiltrados.size() << "\n";
        }
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

        bool encontrado = false;
        for (int i = datos["jugadores"].size() - 1; i >= 0; i--) {
            if (datos["jugadores"][i]["nombre"] == nombre) {
                datos["jugadores"].erase(datos["jugadores"].begin() + i);
                encontrado = true;
            }
        }

        if (!encontrado) {
            cout << "Jugador '" << nombre << "' no encontrado.\n";
            return;
        }

        guardarJSON();
        cout << "Jugador '" << nombre << "' eliminado del historial (todos los modos).\n";
    }

    // Resetear todas las estadísticas
    void resetearEstadisticas() {
        inicializarJSON();
        guardarJSON();
        cout << "Todas las estadisticas han sido reseteadas.\n";
    }
};