#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "json.hpp"
#include <filesystem>

using namespace std;
using json = nlohmann::json;
namespace fs = std::filesystem;

// Function for the main menu
int Menu();

// Function to read JSON file
void readJson(const string& filepath);

// Function to display available JSON files and let the user select one
string selectJsonFile(const string& directory);

int main() {
    int input; // Variable to store the user's choice

    while (true) {
        Menu();
        cin >> input;

        // Error handling
        if (cin.fail() || input < 1 || input > 6) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida. Por favor, ingrese un número del 1 al 6." << endl;
            continue;
        }

        switch (input) {
            case 1: {
                string directory = "."; // You can change this to the desired directory path
                string jsonfilepath = selectJsonFile(directory);
                if (!jsonfilepath.empty()) {
                    readJson(jsonfilepath);
                    cout << "Datos cargados exitosamente" << endl;
                    cout << "Leyendo el archivo json..." << endl;
                }
                break;
            }
            case 2: {
                string directory = "."; // You can change this to the desired directory path
                string jsonfilepath = selectJsonFile(directory);
                if (!jsonfilepath.empty()) {
                    readJson(jsonfilepath);
                    cout << "Datos cargados exitosamente" << endl;
                    cout << "Leyendo el archivo json..." << endl;
                }
                break;
            }
            case 3:
                cout << "Se seleccionó la Opción 3" << endl;
                break;
            case 4:
                cout << "Se seleccionó la Opción 4" << endl;
                break;
            case 5:
                cout << "Se seleccionó la Opción 5" << endl;
                break;
            case 6:
                cout << "Saliendo del programa..." << endl;
                return 0;
        }
    }

    return 0; // This line was missing in the original code
}

void readJson(const string& filepath) {
    // Open the JSON file
    ifstream file(filepath);
    if (!file.is_open()) {
        cout << "No se pudo abrir el archivo" << endl;
        return;
    }

    try {
        // Parse the JSON file
        json jsonData;
        file >> jsonData;

        // Access the data
        for (const auto& item : jsonData) {
            cout << "Vuelo: " << item.value("vuelo", "N/A") << endl;
            cout << "Numero de Registro: " << item.value("numero_de_registro", "N/A") << endl;
            cout << "Modelo: " << item.value("modelo", "N/A") << endl;
            cout << "Fabricante: " << item.value("fabricante", "N/A") << endl;
            cout << "Ano Fabricacion: " << item.value("ano_fabricacion", 0) << endl;
            cout << "Capacidad: " << item.value("capacidad", 0) << endl;
            cout << "Peso Max Despegue: " << item.value("peso_max_despegue", 0) << endl;
            cout << "Aerolinea: " << item.value("aerolinea", "N/A") << endl;
            cout << "Estado: " << item.value("estado", "N/A") << endl;
            cout << "----------" << endl;
        }

    } catch (const json::exception& e) {
        cout << "Error al analizar el archivo JSON: " << e.what() << endl;
    }

    file.close();  // Close the file after reading
}

int Menu(){
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
    return 0;
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
    cout << "Seleccione un archivo (1-" << jsonFiles.size() << "): ";
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