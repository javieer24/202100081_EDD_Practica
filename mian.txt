#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <vector>
#include <filesystem>
#include "json.hpp"
#include "Avion.cpp"
#include "Pasajero.h"
#include "Nodo.h"
#include "Pila.h"
#include "Cola.h"
#include "ListaDoble.h"
#include "ListaCircular.h"
#include "ListaCircularDoble.h"

using namespace std;
using json = nlohmann::json;
namespace fs = std::filesystem;

void mostrarMenu();
void cargarAviones(ListaCircularDoble<Avion>& disponibles, ListaCircularDoble<Avion>& mantenimiento);
void cargarPasajeros(ListaDoble<Pasajero>& listaPasajeros);
void cargarMovimientos(Cola<Pasajero>& colaRegistro, ListaDoble<Pasajero>& listaPasajeros, Pila<Pasajero>& pilaEquipajes);
void consultarPasajero(const ListaDoble<Pasajero>& listaPasajeros);
void generarReportes(const ListaCircularDoble<Avion>& disponibles, const ListaCircularDoble<Avion>& mantenimiento, const Cola<Pasajero>& colaRegistro, const Pila<Pasajero>& pilaEquipajes);

void readJsonAviones(const string& filepath, ListaCircularDoble<Avion>& disponibles, ListaCircularDoble<Avion>& mantenimiento);
void readJsonPasajeros(const string& filepath, ListaDoble<Pasajero>& listaPasajeros);
string selectJsonFile(const string& directory);

int main() {
    ListaCircularDoble<Avion> avionesDisponibles;
    ListaCircularDoble<Avion> avionesMantenimiento;
    Cola<Pasajero> colaRegistro;
    ListaDoble<Pasajero> listaPasajeros;
    Pila<Pasajero> pilaEquipajes;

    int opcion;
    do {
        mostrarMenu();
        cin >> opcion;

        if (cin.fail() || opcion < 1 || opcion > 6) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada inválida. Por favor, ingrese un número del 1 al 6." << endl;
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer de entrada

        switch (opcion) {
            case 1:
                cout << "Se seleccionó la Opción 1" << endl;
                cargarAviones(avionesDisponibles, avionesMantenimiento);
                break;
            case 2:
                cout << "Se seleccionó la Opción 2" << endl;
                cargarPasajeros(listaPasajeros);
                break;
            case 3:
                cargarMovimientos(colaRegistro, listaPasajeros, pilaEquipajes);
                break;
            case 4:
                consultarPasajero(listaPasajeros);
                break;
            case 5:
                generarReportes(avionesDisponibles, avionesMantenimiento, colaRegistro, pilaEquipajes);
                break;
            case 6:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción no válida, intente de nuevo." << endl;
        }
    } while (opcion != 6);

    return 0;
}

void readJsonAviones(const string& filepath, ListaCircularDoble<Avion>& disponibles, ListaCircularDoble<Avion>& mantenimiento) {
    ifstream file(filepath);
    if (!file.is_open()) {
        cout << "No se pudo abrir el archivo" << endl;
        return;
    }

    try {
        json jsonData;
        file >> jsonData;

        for (const auto& item : jsonData) {
            Avion a = {
                item.value("vuelo", ""),
                item.value("numero_de_registro", ""),
                item.value("modelo", ""),
                item.value("fabricante", ""),
                item.value("ano_fabricacion", 0),
                item.value("capacidad", 0),
                item.value("peso_max_despegue", 0),
                item.value("aerolinea", ""),
                item.value("estado", "")
            };

            if (a.estado == "disponible") {
                disponibles.insertar(a);
            } else if (a.estado == "mantenimiento") {
                mantenimiento.insertar(a);
            }
        }
        cout << "Datos cargados exitosamente" << endl;
    } catch (const json::exception& e) {
        cout << "Error al analizar el archivo JSON: " << e.what() << endl;
    }

    file.close();
}

void readJsonPasajeros(const string& filepath, ListaDoble<Pasajero>& listaPasajeros) {
    ifstream file(filepath);
    if (!file.is_open()) {
        cout << "No se pudo abrir el archivo" << endl;
        return;
    }

    try {
        json jsonData;
        file >> jsonData;

        for (const auto& item : jsonData) {
            Pasajero p(item.value("nombre", ""),
                item.value("nacionalidad", ""),
                item.value("numero_de_pasaporte", ""),
                item.value("vuelo", ""),
                item.value("asiento", 0),
                item.value("destino", ""),
                item.value("origen", ""),
                item.value("equipaje_facturado", 0)
            );

            listaPasajeros.agregar(p);
        }
        cout << "Datos cargados exitosamente" << endl;
    } catch (const json::exception& e) {
        cout << "Error al analizar el archivo JSON: " << e.what() << endl;
    }

    file.close();
}

https://github.com/javieer24/202100081_EDD_Practica/blob/95f0ba20e0887adb2d94de1cc09bfc8cd83a6a4e/main.cpp#L183


void mostrarMenu() {
    cout << "------------------Bienvenido------------------" << endl;
    cout << "Menu Principal" << endl;
    cout << "1. Carga de Aviones" << endl;
    cout << "2. Carga de Pasajeros" << endl;
    cout << "3. Carga de Movimientos" << endl;
    cout << "4. Consulta de Pasajeros" << endl;
    cout << "5. Reportes" << endl;
    cout << "6. Salir" << endl;
    cout << "Ingrese una opción: ";
}
string selectJsonFile(const string& directory) {
    vector<string> jsonFiles;
    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.path().extension() == ".json") {
            jsonFiles.push_back(entry.path().string());
        }
    }

    if (jsonFiles.empty()) {
        cout << "No se encontraron archivos JSON en el directorio especificado." << endl;
        return "";
    }

    int choice = -1;
    while (choice < 1 || choice > jsonFiles.size()) {
        cout << "Archivos JSON disponibles:" << endl;
        for (size_t i = 0; i < jsonFiles.size(); ++i) {
            cout << i + 1 << ". " << jsonFiles[i] << endl;
        }

        cout << "Seleccione un archivo (1-" << jsonFiles.size() << "): ";
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > jsonFiles.size()) {
            cin.clear();  // Limpia el estado de error de cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Descarta la entrada inválida
            cout << "Selección inválida. Intente de nuevo." << endl;
        }
    }

    return jsonFiles[choice - 1];
}


void cargarAviones(ListaCircularDoble<Avion>& disponibles, ListaCircularDoble<Avion>& mantenimiento) {
    string directory = "."; // Puedes cambiar este directorio si es necesario
    string jsonfilepath = selectJsonFile(directory);
    if (!jsonfilepath.empty()) {
        readJsonAviones(jsonfilepath, disponibles, mantenimiento);
    }
}

void cargarPasajeros(ListaDoble<Pasajero>& listaPasajeros) {
    string directory = "."; // Puedes cambiar este directorio si es necesario
    string jsonfilepath = selectJsonFile(directory);
    if (!jsonfilepath.empty()) {
        cout << "Archivo seleccionado: " << jsonfilepath << endl;  // Mensaje de depuración
        readJsonPasajeros(jsonfilepath, listaPasajeros);
    } else {
        cout << "No se seleccionó ningún archivo." << endl;  // Mensaje de depuración
    }
}


void cargarMovimientos(Cola<Pasajero>& colaRegistro, ListaDoble<Pasajero>& listaPasajeros, Pila<Pasajero>& pilaEquipajes) {
    // Implementa esta función según tus necesidades
}

void consultarPasajero(const ListaDoble<Pasajero>& listaPasajeros) {
    string numeroPasaporte;
    cout << "Ingrese el número de pasaporte del pasajero a consultar: ";
    getline(cin, numeroPasaporte);

    Pasajero* pasajero = listaPasajeros.buscar(numeroPasaporte);
    if (pasajero) {
        cout << "Información del pasajero:" << endl;
        cout << "Nombre: " << pasajero->nombre << endl;
        cout << "Nacionalidad: " << pasajero->nacionalidad << endl;
        cout << "Número de pasaporte: " << pasajero->numero_de_pasaporte << endl;
        cout << "Vuelo: " << pasajero->vuelo << endl;
        cout << "Asiento: " << pasajero->asiento << endl;
        cout << "Destino: " << pasajero->destino << endl;
        cout << "Origen: " << pasajero->origen << endl;
        cout << "Equipaje facturado: " << pasajero->equipaje_facturado << endl;
    } else {
        cout << "Pasajero no encontrado." << endl;
    }
}

void generarReportes(const ListaCircularDoble<Avion>& disponibles, const ListaCircularDoble<Avion>& mantenimiento, const Cola<Pasajero>& colaRegistro, const Pila<Pasajero>& pilaEquipajes) {
    ofstream archivo("reportes.dot");

    archivo << "digraph G {" << endl;
    archivo << "node [shape=record];" << endl;

    archivo << "subgraph cluster_0 {" << endl;
    archivo << "label=\"Aviones Disponibles\";" << endl;
    Nodo<Avion>* actual = disponibles.cabeza;
    if (actual != nullptr) {
        do {
            archivo << "\"" << actual << "\" [label=\"{" << actual->dato.modelo << "|" << actual->dato.numero_registro << "}\"];" << endl;
            actual = actual->siguiente;
        } while (actual != disponibles.cabeza);
    }
    archivo << "}" << endl;

    archivo << "subgraph cluster_1 {" << endl;
    archivo << "label=\"Aviones en Mantenimiento\";" << endl;
    actual = mantenimiento.cabeza;
    if (actual != nullptr) {
        do {
            archivo << "\"" << actual << "\" [label=\"{" << actual->dato.modelo << "|" << actual->dato.numero_registro << "}\"];" << endl;
            actual = actual->siguiente;
        } while (actual != mantenimiento.cabeza);
    }
    archivo << "}" << endl;

    archivo << "subgraph cluster_2 {" << endl;
    archivo << "label=\"Pasajeros en Cola\";" << endl;
    Nodo<Pasajero>* actualPasajero = colaRegistro.frente;
    while (actualPasajero != nullptr) {
        archivo << "\"" << actualPasajero << "\" [label=\"{" << actualPasajero->dato.nombre << "|" << actualPasajero->dato.numero_de_pasaporte << "}\"];" << endl;
        actualPasajero = actualPasajero->siguiente;
    }
    archivo << "}" << endl;

    archivo << "subgraph cluster_3 {" << endl;
    archivo << "label=\"Equipajes en Pila\";" << endl;
    while (actualEquipaje != nullptr) {
        archivo << "\"" << actualEquipaje << "\" [label=\"{" << actualEquipaje->dato.nombre << "|" << actualEquipaje->dato.numero_de_pasaporte << "}\"];" << endl;
        actualEquipaje = actualEquipaje->siguiente;
    }
    archivo << "}" << endl;

    archivo << "}" << endl;

    archivo.close();
    cout << "Reporte generado en reportes.dot" << endl;
}
