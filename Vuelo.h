#pragma once
#include <iostream>
using namespace std;

class Vuelo {
protected:
    int idVuelo = 0;
    string numeroVuelo, destino, fecha, aerolinea;

public:
    Vuelo();
    void crearVuelo();
    void leerVuelos();
    void actualizarVuelo();
    void eliminarVuelo();
};
