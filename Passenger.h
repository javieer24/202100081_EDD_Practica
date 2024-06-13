#ifndef PASSENGER_H
#define PASSENGER_H

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
    Passenger(string nombre, 
                string nacionalidad, 
                string numero_de_pasaporte, 
                string vuelo, 
                int asiento, 
                string destino, 
                string origen, 
                int equipaje_facturado) 
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

    void print();

    // Destructor
    ~Passenger() {}

};

void Passenger::print(){
    cout << "Nombre123123: " << nombre << endl;
    cout << "Nacionalidad: " << nacionalidad << endl;
    cout << "Numero de Pasaporte: " << numero_de_pasaporte << endl;
    cout << "Vuelo: " << vuelo << endl;
    cout << "Asiento: " << asiento << endl;
    cout << "Destino: " << destino << endl;
    cout << "Origen: " << origen << endl;
    cout << "Equipaje: " << equipaje_facturado << endl;
}


#endif // PASAJERO_H
