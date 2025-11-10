#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <conio.h>     // Para _kbhit() y _getch()
#include <fstream>     // Para manejo de archivos
#include <iomanip>     // Para formateo de salida (necesario para setprecision)
#include <vector>      // Para modo torneo
#include <set>         // Para validar nombres únicos en torneo
#include <cstdlib>     // Para rand() y srand()
#include <ctime>       // Para time()
#include <nlohmann/json.hpp>  // Para JSON
using namespace std;
using namespace std::chrono;
using json = nlohmann::json;  // Alias para facilitar el uso de JSON
