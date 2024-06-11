#ifndef AIRPLANE_H
#define AIRPLANE_H

#include <string>
using namespace std;

class Airplane
{
public:
    Airplane(const string &vuelo, const string &numero_de_registro, const string &modelo, const string &fabricante, int ano_fabricacion, int capacidad, int peso_max_despegue, const string &aerolinea, const string &estado)
    : vuelo(vuelo), numero_de_registro(numero_de_registro), modelo(modelo), fabricante(fabricante), ano_fabricacion(ano_fabricacion), capacidad(capacidad), peso_max_despegue(peso_max_despegue), aerolinea(aerolinea), estado(estado) {}

    string getVuelo() const {
        return vuelo;
    }

    string getNumeroDeRegistro() const {
        return numero_de_registro;
    }

    string getModelo() const {
        return modelo;
    }

    string getFabricante() const {
        return fabricante;
    }

    int getAnoFabricacion() const {
        return ano_fabricacion;
    }

    int getCapacidad() const {
        return capacidad;
    }

    int getPesoMaxDespegue() const {
        return peso_max_despegue;
    }

    string getAerolinea() const {
        return aerolinea;
    }

    string getEstado() const {
        return estado;
    }

    // Destructor
    ~Airplane() {}


private:
    string vuelo;
    string numero_de_registro;
    string modelo;
    string fabricante;
    int ano_fabricacion;
    int capacidad;
    int peso_max_despegue;
    string aerolinea;
    string estado;
};

#endif // AIRPLANE_H
