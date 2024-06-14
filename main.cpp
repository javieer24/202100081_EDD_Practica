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

int Menu();
void readJsonAvion(const string& filepath);
void readJsonPasajeros(const string& filepath);
string selectJsonFile(const string& directory);
string selectTxtFile(const string& directory);
void readmovimientos();
void consultar_pasajero();


// Funciones Graphviz
void graphAvionesDisponibles();
void graphAvionesMantenimiento();






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
                cout << "Se selecciono la Opcion 1." << endl;
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
                cout << "Se selecciono la Opcion 2." << endl;
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
                cout << "Se selecciono la Opcion 3." << endl;
                readmovimientos();

                break;
            case 4:
                cout << "Se selecciono la Opcion 4." << endl;
                consultar_pasajero();   
                break;
            case 5:
                cout << "Se selecciono la Opcion 5." << endl;
                graphAvionesDisponibles();
                graphAvionesMantenimiento();
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
            Airplane *avion = new Airplane(item.value("vuelo", "N/A"), 
                                            item.value("numero_de_registro", "N/A"), 
                                            item.value("modelo", "N/A"), 
                                            item.value("fabricante", "N/A"),
                                            item.value("ano_fabricacion", 0), 
                                            item.value("capacidad", 0),
                                            item.value("peso_max_despegue", 0), 
                                            item.value("aerolinea", "N/A"),
                                            item.value("estado", "N/A"));
            ListaAvionesDisponibles.insert(*avion);
            ListaAvionesMantenimiento.insert(*avion);
        }

    } catch (const json::exception& e) {
        cout << "Error parsing the JSON file: " << e.what() << endl;
    }

    file.close();  // Se cierra el archivo después de leerlo
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
            Passenger *pasajero = new Passenger(item.value("nombre", "N/A"), 
                                            item.value("nacionalidad", "N/A"), 
                                            item.value("numero_de_pasaporte", "N/A"), 
                                            item.value("vuelo", "N/A"),
                                            item.value("asiento", 0), 
                                            item.value("destino", "N/A"),
                                            item.value("origen", "N/A"), 
                                            item.value("equipaje_facturado", 0));
            ColaPasajeros.enqueue(*pasajero);
        }

    } catch (const json::exception& e) {
        cout << "Error parsing the JSON file: " << e.what() << endl;
    }

    file.close();  // Cierra el archivo después de leerlo
}



string selectTxtFile(const string& directory) {
    vector<string> txtFiles;
    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.path().extension() == ".txt") {
            txtFiles.push_back(entry.path().string());
        }
    }

    if (txtFiles.empty()) {
        cout << "No se encontraron archivos TXT en el directorio." << endl;
        return "";
    }

    cout << "Archivos TXT disponibles:" << endl;
    for (size_t i = 0; i < txtFiles.size(); ++i) {
        cout << i + 1 << ". " << txtFiles[i] << endl;
    }

    int choice;
    cout << "Seleccione un archivo (1-" << txtFiles.size() << "): ";
    cin >> choice;

    // Manejo de errores
    if (cin.fail() || choice < 1 || choice > txtFiles.size()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Selección inválida. Inténtelo de nuevo." << endl;
        return "";
    }

    return txtFiles[choice - 1];
}
void readmovimientos(){
    ifstream file("movimientos.txt");
    string line;


    if (file.is_open()) {
        cout << "\nMovimientos realizados:" << endl;
        while (getline(file, line)) {
            if (line == "IngresoEquipajes;") {
                cout << "\tSe detecto Ingreso de Equipajes" << endl;
                // El primer pasajero de la cola agregarlo a la pila y la listaEquipaje y equipajePasajeros
                Passenger pasajero = ColaPasajeros.dequeue();
                // verificar si el pasajero contiene el atributo equipaje_facturado
                if (pasajero.getEquipajeFacturado() > 0) {
                    EquipajePasajeros.push(pasajero);
                    ListaEquipajeFacturado.insertAtBeginning(pasajero);
                    
                    
                    cout << "El pasajero " << pasajero.getNombre() << " con numero de pasaporte " << pasajero.getNumeroDePasaporte() << " tiene equipaje." << endl;
                } else if (pasajero.getEquipajeFacturado() == 0){
                    ListaEquipajeFacturado.insertAtBeginning(pasajero);
                    
                    cout << "El pasajero " << pasajero.getNombre() << " con numero de pasaporte " << pasajero.getNumeroDePasaporte() << " no tiene equipaje." << endl;
                }
            } else if (line.find("MantenimientoAviones,Ingreso,") == 0) {
                cout << "\tSe detecto Ingreso de aviones" << endl;
                string cambioEstado = "Mantenimiento";
                // Extraer el texto después de la coma y antes del punto y coma
                string texto = line.substr(29, line.find(";") - 29);
                // Buscar el avión en la listaAvionesDisponible a travez del metodo buscarPorNumeroDeRegistro
                Airplane* avion = ListaAvionesDisponibles.searchByRegistrationNumber(texto);
                // Verificar si se encontró el avión
                if (avion != nullptr) {
                    // Cambiar el estado del avión a "Mantenimiento"
                    Airplane avionMantenimiento(avion->getVuelo(), avion->getNumeroDeRegistro(), avion->getModelo(),
                    avion->getFabricante(), avion->getAnoFabricacion(), avion->getCapacidad(),
                    avion->getPesoMaxDespegue(), avion->getAerolinea(), cambioEstado);
                    // Agregarlo a la listaAvionesMantenimiento
                    ListaAvionesMantenimiento.insert(avionMantenimiento);
                    // Eliminarlo de la listaAvionesDisponible
                    ListaAvionesDisponibles.removeByRegistrationNumber(texto);
                    cout << "El avion con número de registro " << texto << " ha ingresado a mantenimiento." << endl;
                } else {
                    std::cout << "No se encontro el avión con número de registro: " << texto << std::endl;
                }
            } else if (line.find("MantenimientoAviones,Salida,") == 0) {
                cout << "\tSe detecto Salida de aviones" << endl;
                string cambioEstado = "Disponible";
                // Extraer el texto después de la coma y antes del punto y coma
                string texto = line.substr(28, line.find(";") - 28);
                // Buscar el avión en la listaAvionesDisponible a travez del metodo buscarPorNumeroDeRegistro
                Airplane* avion = ListaAvionesMantenimiento.searchByRegistrationNumber(texto);
                // Verificar si se encontró el avión
                if (avion != nullptr) {
                    // Cambiar el estado del avión a "Mantenimiento"
                    Airplane avionMantenimiento(avion->getVuelo(), avion->getNumeroDeRegistro(), avion->getModelo(),
                    avion->getFabricante(), avion->getAnoFabricacion(), avion->getCapacidad(),
                    avion->getPesoMaxDespegue(), avion->getAerolinea(), cambioEstado);
                    // Agregarlo a la listaAvionesMantenimiento
                    ListaAvionesDisponibles.insert(avionMantenimiento);
                    // Eliminarlo de la listaAvionesDisponible
                    ListaAvionesMantenimiento.removeByRegistrationNumber(texto);
                    cout << "El avión con número de registro " << texto << " ha salido de mantenimiento." << endl;
                } else {
                    std::cout << "No se encontro el avión con número de registro: " << texto << std::endl;
                }
            } else {
                cout << "La linea no cumple con ninguna de las condiciones" << endl;
            }
        }
        cout << endl;
        file.close();
    } 
    // Verificar si el pasajero tiene el mismo numero de vuelo y si es asi ordenar por asiento
}

void consultar_pasajero() {
    cout << "Ingrese el numero de pasaporte del pasajero: ";
    string numeroPasaporte;
    cin >> numeroPasaporte;

    try {
        Node<Passenger> *pasajero = ListaEquipajeFacturado.search(numeroPasaporte);
        cout << "\nInformacion del pasajero: " << endl;
        if(pasajero)
        pasajero->data.print();
        else 
            cout << "Pasajero es un apuntador nulo"; 
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Error desconocido." << std::endl;
    }

}


void graphAvionesDisponibles(){
    ofstream file("aviones_disponibles.dot");
    file << "digraph AvionesDisponibles {" << endl;
    // Recorre la lista de aviones disponibles y los imprime en el archivo .dot utiliza un for para recorrer la lista, agrega todos los atributos
    for (int i = 0; i < ListaAvionesDisponibles.getSize(); i++) {
        Airplane avion = ListaAvionesDisponibles.getElement(i);
        file << "    " << avion.getNumeroDeRegistro() << " [label=\"" << avion. getNumeroDeRegistro() << "\\n" << avion.getModelo() << "\\n" << avion.getFabricante() << "\\n" << avion.getAnoFabricacion() << "\\n" << avion.getCapacidad() << "\\n" << avion.getPesoMaxDespegue() << "\\n" << avion.getAerolinea() << "\"];" << endl;
    }
    file << "}" << endl;
    file.close();

    // Genera la imagen utilizando Graphviz
    if (system("dot -Tpng aviones_disponibles.dot -o aviones_disponibles.png") != 0) {
        cerr << "Error al ejecutar el comando Graphviz" << endl;
        std::exit(EXIT_FAILURE); // Termina el programa si el comando falla
    }
}

void graphAvionesMantenimiento(){
    ofstream file("aviones_mantenimiento.dot");
    file << "digraph AvionesMantenimiento {" << endl;
    // Recorre la lista de aviones en mantenimiento y los imprime en el archivo .dot utiliza un for para recorrer la lista, agrega todos los atributos
    for (int i = 0; i < ListaAvionesMantenimiento.getSize(); i++) {
        Airplane avion = ListaAvionesMantenimiento.getElement(i);
        file << "    " << avion.getNumeroDeRegistro() << " [label=\"" << avion.getNumeroDeRegistro() << "\\n" << avion.getModelo() << "\\n" << avion.getFabricante() << "\\n" << avion.getAnoFabricacion() << "\\n" << avion.getCapacidad() << "\\n" << avion.getPesoMaxDespegue() << "\\n" << avion.getAerolinea() << "\"];" << endl;
    }
    file << "}" << endl;
    file.close();

    // Genera la imagen utilizando Graphviz
    system("dot -Tpng aviones_mantenimiento.dot -o aviones_mantenimiento.png");
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



