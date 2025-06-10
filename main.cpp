#include <iostream>
#include "Reserva.h"
#include "Pasajero.h"
#include "Vuelo.h"
using namespace std;


void menuReservas() {
    Reserva r;
    int opcion;

    do {
        cout << "\n===== MENU DE RESERVAS =====" << endl;
        cout << "1. Crear nueva reserva" << endl;
        cout << "2. Mostrar reservas" << endl;
        cout << "3. Actualizar reserva" << endl;
        cout << "4. Eliminar reserva" << endl;
        cout << "5. Generar pase de abordar" << endl;  // NUEVO
        cout << "0. Volver al menu principal" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case 1: r.crearReserva(); break;
        case 2: r.leerReservas(); break;
        case 3:
            r.leerReservas();
            r.actualizarReserva();
            break;
        case 4:
            r.leerReservas();
            r.eliminarReserva();
            break;
        case 5: { // NUEVO CASO
            r.leerReservas();
            int id;
            cout << "Ingrese ID de la reserva para generar pase: ";
            cin >> id;
            cin.ignore();
            r.generarPaseHTML(id);
            break;
        }
        case 0: break;
        default: cout << "Opcion invalida.\n"; break;
        }
    } while (opcion != 0);
}




void menuPasajeros() {
    Pasajero p;
    int opcion;

    do {
        cout << "\n===== MENU DE PASAJEROS =====" << endl;
        cout << "1. Agregar pasajero" << endl;
        cout << "2. Mostrar pasajeros" << endl;
        cout << "3. Actualizar pasajero" << endl;
        cout << "4. Eliminar pasajero" << endl;
        cout << "0. Volver al menu principal" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case 1: p.crearPasajero(); break;
        case 2: p.leerPasajeros(); break;
        case 3:
            p.leerPasajeros();
            p.actualizarPasajero();
            break;
        case 4:
            p.leerPasajeros();
            p.eliminarPasajero();
            break;
        case 0: break;
        default: cout << "Opción inválida.\n"; break;
        }
    } while (opcion != 0);
}



void menuVuelos() {
    Vuelo v;
    int opcion;

    do {
        cout << "\n===== MENU DE VUELOS =====" << endl;
        cout << "1. Agregar vuelo" << endl;
        cout << "2. Mostrar vuelos" << endl;
        cout << "3. Actualizar vuelo" << endl;
        cout << "4. Eliminar vuelo" << endl;
        cout << "0. Volver al menu principal" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case 1: v.crearVuelo(); break;
        case 2: v.leerVuelos(); break;
        case 3:
            v.leerVuelos();
            v.actualizarVuelo();
            break;
        case 4:
            v.leerVuelos();
            v.eliminarVuelo();
            break;
        case 0: break;
        default: cout << "Opcion invalida.\n"; break;
        }
    } while (opcion != 0);
}




int main() {
    int opcion;

    do {
        cout << "\n===== MENU PRINCIPAL =====" << endl;
        cout << "1. Modulo Reservas" << endl;
        cout << "2. Modulo Pasajeros" << endl;
        cout << "3. Modulo Vuelos" << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case 1: menuReservas(); break;
        case 2: menuPasajeros(); break;
        case 3: menuVuelos(); break;
        case 0: cout << "Saliendo...\n"; break;
        default: cout << "Opción invalida.\n"; break;
        }
    } while (opcion != 0);

    return 0;
}
