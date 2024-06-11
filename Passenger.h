#ifndef PASSENGER_H
#define PASSENGER_H

#include <string>
using namespace std;

class Passenger {
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
    Passenger(string nombre, string nacionalidad, string numero_de_pasaporte, string vuelo, int asiento, string destino, string origen, int equipaje_facturado) 
    : nombre(nombre), nacionalidad(nacionalidad), numero_de_pasaporte(numero_de_pasaporte), vuelo(vuelo), asiento(asiento), destino(destino), origen(origen), equipaje_facturado(equipaje_facturado) {}
    
    string getNombre() const {
        return nombre;
    }

    string getNacionalidad() const {
        return nacionalidad;
    }

    string getNumeroDePasaporte() const {
        return numero_de_pasaporte;
    }

    string getVuelo() const {
        return vuelo;
    }

    int getAsiento() const {
        return asiento;
    }

    string getDestino() const {
        return destino;
    }

    string getOrigen() const {
        return origen;
    }

    int getEquipajeFacturado() const {
        return equipaje_facturado;
    }

    // Destructor
    ~Passenger() {}

};


#endif // PASAJERO_H
