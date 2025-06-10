#include "Vuelo.h"
#include "ConexionBD.h"
#include <sstream>
#include <iostream>

using namespace std;

Vuelo::Vuelo() {}

void Vuelo::crearVuelo() {
    ConexionBD con;
    con.abrir_conexion();
    MYSQL* conectar = con.getConector();

    if (conectar) {
        cout << "Ingrese número de vuelo: ";
        getline(cin, numeroVuelo);
        cout << "Ingrese destino: ";
        getline(cin, destino);
        cout << "Ingrese fecha (YYYY-MM-DD): ";
        getline(cin, fecha);
        cout << "Ingrese aerolínea: ";
        getline(cin, aerolinea);

        stringstream ss;
        ss << "INSERT INTO vuelos(numeroVuelo, destino, fecha, aerolinea) VALUES ('"
            << numeroVuelo << "', '" << destino << "', '" << fecha << "', '" << aerolinea << "')";

        int estado = mysql_query(conectar, ss.str().c_str());

        if (!estado)
            cout << "Vuelo ingresado exitosamente!" << endl;
        else
            cout << "Error al ingresar vuelo: " << mysql_error(conectar) << endl;

        con.cerrar_conexion();
    }
}

void Vuelo::leerVuelos() {
    ConexionBD con;
    con.abrir_conexion();
    MYSQL* conectar = con.getConector();

    if (conectar) {
        MYSQL_ROW fila;
        MYSQL_RES* resultado;

        cout << "\n=== LISTADO DE VUELOS ===\n";

        int estado = mysql_query(conectar, "SELECT * FROM vuelos");

        if (!estado) {
            resultado = mysql_store_result(conectar);

            if (mysql_num_rows(resultado) == 0) {
                cout << "No hay vuelos registrados.\n";
            }
            else {
                while ((fila = mysql_fetch_row(resultado))) {
                    cout << "ID: " << fila[0]
                        << " | Número: " << fila[1]
                        << " | Destino: " << fila[2]
                        << " | Fecha: " << fila[3]
                        << " | Aerolínea: " << fila[4] << endl;
                }
            }
        }
        else {
            cout << "Error al consultar vuelos: " << mysql_error(conectar) << endl;
        }

        con.cerrar_conexion();
    }
}

void Vuelo::actualizarVuelo() {
    ConexionBD con;
    con.abrir_conexion();
    MYSQL* conectar = con.getConector();

    if (conectar) {
        int id;
        cout << "Ingrese ID del vuelo a actualizar: ";
        cin >> id;
        cin.ignore();

        cout << "Nuevo número de vuelo: ";
        getline(cin, numeroVuelo);
        cout << "Nuevo destino: ";
        getline(cin, destino);
        cout << "Nueva fecha (YYYY-MM-DD): ";
        getline(cin, fecha);
        cout << "Nueva aerolínea: ";
        getline(cin, aerolinea);

        stringstream ss;
        ss << "UPDATE vuelos SET numeroVuelo='" << numeroVuelo
            << "', destino='" << destino
            << "', fecha='" << fecha
            << "', aerolinea='" << aerolinea
            << "' WHERE idVuelo=" << id;

        int estado = mysql_query(conectar, ss.str().c_str());

        if (!estado)
            cout << "Vuelo actualizado correctamente!" << endl;
        else
            cout << "Error al actualizar vuelo: " << mysql_error(conectar) << endl;

        con.cerrar_conexion();
    }
}

void Vuelo::eliminarVuelo() {
    ConexionBD con;
    con.abrir_conexion();
    MYSQL* conectar = con.getConector();

    if (conectar) {
        int id;
        cout << "Ingrese ID del vuelo a eliminar: ";
        cin >> id;
        cin.ignore();

        stringstream ss;
        ss << "DELETE FROM vuelos WHERE idVuelo = " << id;
        int estado = mysql_query(conectar, ss.str().c_str());

        if (!estado)
            cout << "Vuelo eliminado correctamente!" << endl;
        else
            cout << "Error al eliminar vuelo: " << mysql_error(conectar) << endl;

        con.cerrar_conexion();
    }
}
