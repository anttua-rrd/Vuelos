#pragma once
#include <iostream>
#include "Reserva.h"
using namespace std;

class Reserva {
protected:
    int idReserva = 0;
    int idVuelo = 0;
    int idPasajero = 0;
    string asiento, fechaReserva;

public:
    Reserva();
    void crearReserva();
    void leerReservas();
    void actualizarReserva();
    void eliminarReserva();
    void generarPaseHTML(int idReserva);


};
