#ifndef PASAJERO_H
#define PASAJERO_H

#include <string>
using namespace std;

class Pasajero {
private:
    string nombre;
    string nacionalidad;
    string numero_de_pasaporte;
    string vuelo;
    int asiento;
    string destino;
    string origen;
    int equipaje_facturado;
public:
    Pasajero(string nombre, string nacionalidad, string numero_de_pasaporte, string vuelo, int asiento, string destino, string origen, int equipaje_facturado) : nombre(nombre), nacionalidad(nacionalidad), numero_de_pasaporte(numero_de_pasaporte), vuelo(vuelo), asiento(asiento), destino(destino), origen(origen), equipaje_facturado(equipaje_facturado) {}
};


#endif // PASAJERO_H
