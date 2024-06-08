#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <vector>
#include <filesystem>
#include "json.hpp"
#include "Avion.cpp"
#include "Pasajero.cpp"
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
void cargarPasajeros(Cola<Pasajero>& colaRegistro);
void cargarMovimientos(Cola<Pasajero>& colaRegistro, ListaDoble<Pasajero>& listaPasajeros, Pila<Pasajero>& pilaEquipajes);
void consultarPasajero(const ListaDoble<Pasajero>& listaPasajeros);
void generarReportes(const ListaCircularDoble<Avion>& disponibles, const ListaCircularDoble<Avion>& mantenimiento, const Cola<Pasajero>& colaRegistro, const Pila<Pasajero>& pilaEquipajes);

void readJsonAviones(const string& filepath, ListaCircularDoble<Avion>& disponibles, ListaCircularDoble<Avion>& mantenimiento);
void readJsonPasajeros(const string& filepath, Cola<Pasajero>& colaRegistro);
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

        switch (opcion) {
            case 1:
                cargarAviones(avionesDisponibles, avionesMantenimiento);
                break;
            case 2:
                cargarPasajeros(colaRegistro);
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
                cout << "Saliendo..." << endl;
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
    } catch (const json::exception& e) {
        cout << "Error al analizar el archivo JSON: " << e.what() << endl;
    }

    file.close();
}

void readJsonPasajeros(const string& filepath, Cola<Pasajero>& colaRegistro) {
    ifstream file(filepath);
    if (!file.is_open()) {
        cout << "No se pudo abrir el archivo" << endl;
        return;
    }

    try {
        json jsonData;
        file >> jsonData;

        for (const auto& item : jsonData) {
            cout << "Nombre: " << item.value("nombre", "N/A") << endl;
            cout << "Nacionalidad: " << item.value("nacionalidad", "N/A") << endl;
            cout << "Número de pasaporte: " << item.value("numero_de_pasaporte", "N/A") << endl;
            cout << "Vuelo: " << item.value("vuelo", "N/A") << endl;
            cout << "Asiento: " << item.value("asiento", 0) << endl;
            cout << "Destino: " << item.value("destino", "N/A") << endl;
            cout << "Origen: " << item.value("origen", "N/A") << endl;
            cout << "Equipaje facturado: " << item.value("equipaje_facturado", 0) << endl;
            cout << "----------" << endl;

            Pasajero p = {
                item.value("nombre", ""),
                item.value("nacionalidad", ""),
                item.value("numero_de_pasaporte", ""),
                item.value("vuelo", ""),
                item.value("asiento", 0),
                item.value("destino", ""),
                item.value("origen", ""),
                item.value("equipaje_facturado", 0)
            };

            colaRegistro.encolar(p);
        }
    } catch (const json::exception& e) {
        cout << "Error al analizar el archivo JSON: " << e.what() << endl;
    }

    file.close();
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

    cout << "Archivos JSON encontrados:" << endl;
    for (size_t i = 0; i < jsonFiles.size(); ++i) {
        cout << i + 1 << ". " << jsonFiles[i] << endl;
    }

    int choice;
    cout << "Seleccione un archivo (1-" << jsonFiles.size() << "): ";
    cin >> choice;

    if (choice < 1 || choice > jsonFiles.size()) {
        cout << "Selección inválida." << endl;
        return "";
    }

    return jsonFiles[choice - 1];
}










void mostrarMenu() {
    cout << "----- Menu -----" << endl;
    cout << "1. Carga de aviones" << endl;
    cout << "2. Carga de pasajeros" << endl;
    cout << "3. Carga de movimientos" << endl;
    cout << "4. Consultar pasajero" << endl;
    cout << "5. Visualizar reportes" << endl;
    cout << "6. Salir" << endl;
    cout << "Seleccione una opción: ";
}

void cargarAviones(ListaCircularDoble<Avion>& disponibles, ListaCircularDoble<Avion>& mantenimiento) {
    string directory = "."; // Puedes cambiar esto a la ruta del directorio que desees
    string jsonfilepath = selectJsonFile(directory);
    if (!jsonfilepath.empty()) {
        readJsonAviones(jsonfilepath, disponibles, mantenimiento);
        cout << "Aviones cargados correctamente." << endl;
    }
}

void cargarPasajeros(Cola<Pasajero>& colaRegistro) {
    string directory = "."; // Puedes cambiar esto a la ruta del directorio que desees
    string jsonfilepath = selectJsonFile(directory);
    if (!jsonfilepath.empty()) {
        readJsonPasajeros(jsonfilepath, colaRegistro);
        cout << "Pasajeros cargados correctamente." << endl;
    }
}

void cargarMovimientos(Cola<Pasajero>& colaRegistro, ListaDoble<Pasajero>& listaPasajeros, Pila<Pasajero>& pilaEquipajes) {
    string archivo;
    cout << "Ingrese el nombre del archivo de movimientos: ";
    cin >> archivo;

    ifstream ifs(archivo);
    string linea;

    while (getline(ifs, linea)) {
        if (linea.find("IngresoEquipajes") != string::npos) {
            if (!colaRegistro.estaVacia()) {
                Pasajero p = colaRegistro.obtenerFrente();
                colaRegistro.desencolar();
                listaPasajeros.insertar(p);
                if (p.equipaje_facturado > 0) {
                    pilaEquipajes.push(p);
                }
            }
        } else if (linea.find("MantenimientoAviones") != string::npos) {
            // Lógica para mover aviones entre listas según su estado
        }
    }

    cout << "Movimientos cargados correctamente." << endl;
}

void consultarPasajero(const ListaDoble<Pasajero>& listaPasajeros) {
    string numero_de_pasaporte;
    cout << "Ingrese el número de pasaporte del pasajero: ";
    cin >> numero_de_pasaporte;

    Nodo<Pasajero>* actual = listaPasajeros.cabeza;
    while (actual != nullptr) {
        if (actual->dato.numero_de_pasaporte == numero_de_pasaporte) {
            cout << "Nombre: " << actual->dato.nombre << endl;
            cout << "Nacionalidad: " << actual->dato.nacionalidad << endl;
            cout << "Número de pasaporte: " << actual->dato.numero_de_pasaporte << endl;
            cout << "Vuelo: " << actual->dato.vuelo << endl;
            cout << "Asiento: " << actual->dato.asiento << endl;
            cout << "Destino: " << actual->dato.destino << endl;
            cout << "Origen: " << actual->dato.origen << endl;
            cout << "Equipaje facturado: " << actual->dato.equipaje_facturado << endl;
            return;
        }
        actual = actual->siguiente;
    }

    cout << "Pasajero no encontrado." << endl;
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
    Nodo<Pasajero>* actualEquipaje = pilaEquipajes.obtenerCima();
    while (actualEquipaje != nullptr) {
        archivo << "\"" << actualEquipaje << "\" [label=\"{" << actualEquipaje->dato.nombre << "|" << actualEquipaje->dato.numero_de_pasaporte << "}\"];" << endl;
        actualEquipaje = actualEquipaje->siguiente;
    }
    archivo << "}" << endl;

    archivo << "}" << endl;

    archivo.close();
    cout << "Reporte generado en reportes.dot" << endl;
}
