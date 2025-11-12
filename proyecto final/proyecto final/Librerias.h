#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <conio.h>     // Para _kbhit() y _getch()
#include <fstream>     // Para manejo de archivos
#include <iomanip>     // Para formateo de salida (necesario para setprecision)
#include <nlohmann/json.hpp>  // Para JSON
#include <vector>
#include <set>
#include <windows.h>   // NUEVO: Para gráficos en consola Windows

using namespace std;
using namespace std::chrono;
using json = nlohmann::json;  // Alias para facilitar el uso de JSONSON