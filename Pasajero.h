#pragma once
#include <iostream>
using namespace std;

class Pasajero {
protected:
    int idPasajero = 0;
    string nombre, apellido, pasaporte, fechaNacimiento, genero;

public:
    Pasajero();
    void crearPasajero();
    void leerPasajeros();
    void actualizarPasajero();
    void eliminarPasajero();
};
