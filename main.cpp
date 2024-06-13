#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "json.hpp"
#include <filesystem>
#include <vector>
#include "CircularDoubleList.h"
#include "CircularList.h"
#include "DoubleLinkedList.h"
#include "Airplane.h"
#include "Passenger.h"
#include "Queue.h"
#include "Stack.h"




using namespace std;
using json = nlohmann::json;
namespace fs = std::filesystem;


//Variables globales
CircularDoubleList<Airplane> ListaAvionesDisponibles;
CircularDoubleList<Airplane> ListaAvionesMantenimiento;
DoubleLinkedList<Passenger> ListaEquipajeFacturado;
Queue<Passenger> ColaPasajeros;
Stack<Passenger> EquipajePasajeros;





// funcion para mostrar el menu
int Menu();

// funcion para leer el archivo JSON de aviones
void readJsonAvion(const string& filepath);

// funcion para leer el archivo JSON de pasajeros
void readJsonPasajeros(const string& filepath);

// funcion para seleccionar un archivo JSON
string selectJsonFile(const string& directory);

int main() {
    int input; // Variable para almacenar la opcion del menu

    while (true) {
        input = Menu();

        // Correccion de errores
        if (cin.fail() || input < 1 || input > 6) {
            cin.clear(); // Bandera de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number from 1 to 6." << endl;
            continue;
        }

        switch (input) {
            case 1: {
                string directory = "."; // Cambiar a la direccion deseada
                string jsonfilepath = selectJsonFile(directory);
                cout << "Datos cargados exitosamente" << endl;
                cout << "Leyendo el archivo json..." << endl;
                if (!jsonfilepath.empty()) {
                    readJsonAvion(jsonfilepath);
                }
                break;
            }
            case 2: {
                string directory = "."; // Cambiar a la direccion deseada
                string jsonfilepath = selectJsonFile(directory);
                    cout << "Datos cargados exitosamente" << endl;
                    cout << "Leyendo el archivo json..." << endl;
                if (!jsonfilepath.empty()) {
                    readJsonPasajeros(jsonfilepath);

                }
                break;
            }
            case 3:
                cout << "Se seleccionó la Opción 3." << endl;
                break;
            case 4:
                cout << "Se seleccionó la Opción 4." << endl;
                break;
            case 5:
                cout << "Se seleccionó la Opción 5." << endl;
                break;
            case 6:
                cout << "Saliendo del programa..." << endl;
                return 0;
        }
    }

    return 0;
}

void readJsonAvion(const string& filepath) {
    // Open the JSON file
    ifstream file(filepath);
    if (!file.is_open()) {
        cout << "Could not open the file." << endl;
        return;
    }

    try {
        // Parseo del archivo JSON
        json jsonData;
        file >> jsonData;

        // Acceso a los datos
        for (const auto& item : jsonData) {
            cout << "Vuelo: " << item.value("vuelo", "N/A") << endl;
            cout << "Numero de Registro: " << item.value("numero_de_registro", "N/A") << endl;
            cout << "Modelo: " << item.value("modelo", "N/A") << endl;
            cout << "Fabricante: " << item.value("fabricante", "N/A") << endl;
            cout << "Año de Fabricacion: " << item.value("ano_fabricacion", 0) << endl;
            cout << "Capacidad: " << item.value("capacidad", 0) << endl;
            cout << "Peso Max Despegue: " << item.value("peso_max_despegue", 0) << endl;
            cout << "Aerolina: " << item.value("aerolinea", "N/A") << endl;
            cout << "Estado: " << item.value("estado", "N/A") << endl;
            cout << "----------" << endl;
        }

    } catch (const json::exception& e) {
        cout << "Error parsing the JSON file: " << e.what() << endl;
    }

    file.close();  // Se cierra el archivo después de leerlo
}

void readJsonPasajeros(const string& filepath) {
    // Se abre el archivo JSON
    ifstream file(filepath);
    if (!file.is_open()) {
        cout << "Could not open the file." << endl;
        return;
    }

    try {
        // Parseo del archivo JSON
        json jsonData;
        file >> jsonData;

        // Access the data
        for (const auto& item : jsonData) {
            cout << "Nombre: " << item.value("nombre", "N/A") << endl;
            cout << "Nacionalidad: " << item.value("nacionalidad", "N/A") << endl;
            cout << "Numero de Pasaporte: " << item.value("numero_de_pasaporte", "N/A") << endl;
            cout << "Vuelo: " << item.value("vuelo", "N/A") << endl; // Changed from number to string
            cout << "Asiento: " << item.value("asiento", 0) << endl;
            cout << "Destino: " << item.value("destino", "N/A") << endl; // Changed from number to string
            cout << "Origen: " << item.value("origen", "N/A") << endl;
            cout << "Equipaje Facturado: " << item.value("equipaje_facturado", 0) << endl;
            cout << "----------" << endl;
        }

    } catch (const json::exception& e) {
        cout << "Error parsing the JSON file: " << e.what() << endl;
    }

    file.close();  // Cierra el archivo después de leerlo
}









int Menu() {
    cout << "|                                                              |" << endl;
    cout << "|                    Bienvenido al Menu Principal              |" << endl;
    cout << "|                                                              |" << endl;
    cout << "|-------------------------------------------------------------+" << endl;
    cout << "|                                                              |" << endl;
    cout << "|                      1. Carga de Aviones                     |" << endl;
    cout << "|                      2. Carga de Pasajeros                   |" << endl;
    cout << "|                      3. Carga de Movimientos                 |" << endl;
    cout << "|                      4. Consulta de Pasajeros                |" << endl;
    cout << "|                      5. Reportes                             |" << endl;
    cout << "|                      6. Salir                                |" << endl;
    cout << "|                                                              |" << endl;
    cout << "|-------------------------------------------------------------+" << endl;
    cout << "|                                                              |" << endl;
    cout << "| Ingrese una opcion:                                          |" << endl;
    cout << "|                                                              |" << endl;
    cout << "+-------------------------------------------------------------+" << endl;
    
    int choice;
    cin >> choice;
    return choice;
}

string selectJsonFile(const string& directory) {
    vector<string> jsonFiles;
    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.path().extension() == ".json") {
            jsonFiles.push_back(entry.path().string());
        }
    }

    if (jsonFiles.empty()) {
        cout << "No se encontraron archivos JSON en el directorio." << endl;
        return "";
    }

    cout << "Archivos JSON disponibles:" << endl;
    for (size_t i = 0; i < jsonFiles.size(); ++i) {
        cout << i + 1 << ". " << jsonFiles[i] << endl;
    }

    int choice;
    cout << "Seleccione un archivo  (1-" << jsonFiles.size() << "): ";
    cin >> choice;

    // Error handling
    if (cin.fail() || choice < 1 || choice > jsonFiles.size()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Selección invalida. Intentelo de nuevo." << endl;
        return "";
    }

    return jsonFiles[choice - 1];
}
