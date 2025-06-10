#include "Pasajero.h"
#include "ConexionBD.h"
#include <sstream>
#include <iostream>

using namespace std;

Pasajero::Pasajero() {}

void Pasajero::crearPasajero() {
    ConexionBD con;
    con.abrir_conexion();
    MYSQL* conectar = con.getConector();

    if (conectar) {
        cout << "Ingrese nombre: ";
        getline(cin, nombre);
        cout << "Ingrese apellido: ";
        getline(cin, apellido);
        cout << "Ingrese pasaporte: ";
        getline(cin, pasaporte);
        cout << "Ingrese fecha de nacimiento (YYYY-MM-DD): ";
        getline(cin, fechaNacimiento);
        cout << "Ingrese genero: ";
        getline(cin, genero);

        stringstream ss;
        ss << "INSERT INTO pasajeros(nombre, apellido, pasaporte, fechaNacimiento, genero) VALUES ('"
            << nombre << "', '" << apellido << "', '" << pasaporte << "', '"
            << fechaNacimiento << "', '" << genero << "')";

        string query = ss.str();
        int estado = mysql_query(conectar, query.c_str());

        if (!estado)
            cout << "Pasajero ingresado exitosamente!" << endl;
        else
            cout << "Error al ingresar pasajero: " << mysql_error(conectar) << endl;

        con.cerrar_conexion();
    }
}

void Pasajero::leerPasajeros() {
    ConexionBD con;
    con.abrir_conexion();
    MYSQL* conectar = con.getConector();

    if (conectar) {
        MYSQL_ROW fila;
        MYSQL_RES* resultado;

        int estado = mysql_query(conectar, "SELECT * FROM pasajeros");

        cout << "\n=== LISTADO DE PASAJEROS ===\n";
        if (!estado) {
            resultado = mysql_store_result(conectar);

            if (mysql_num_rows(resultado) == 0) {
                cout << "No hay pasajeros registrados.\n";
            }
            else {
                while ((fila = mysql_fetch_row(resultado))) {
                    cout << "ID: " << fila[0] << " | Nombre: " << fila[1]
                        << " | Apellido: " << fila[2]
                        << " | Pasaporte: " << fila[3]
                        << " | Fecha Nac.: " << fila[4]
                        << " | Género: " << fila[5] << endl;
                }
            }
        }
        else {
            cout << "Error al leer pasajeros: " << mysql_error(conectar) << endl;
        }

        con.cerrar_conexion();
    }
}

void Pasajero::actualizarPasajero() {
    ConexionBD con;
    con.abrir_conexion();
    MYSQL* conectar = con.getConector();

    if (conectar) {
        int id;
        cout << "Ingrese ID del pasajero a actualizar: ";
        cin >> id;
        cin.ignore();

        cout << "Nuevo nombre: ";
        getline(cin, nombre);
        cout << "Nuevo apellido: ";
        getline(cin, apellido);
        cout << "Nuevo pasaporte: ";
        getline(cin, pasaporte);
        cout << "Nueva fecha nacimiento (YYYY-MM-DD): ";
        getline(cin, fechaNacimiento);
        cout << "Nuevo género: ";
        getline(cin, genero);

        stringstream ss;
        ss << "UPDATE pasajeros SET nombre='" << nombre
            << "', apellido='" << apellido
            << "', pasaporte='" << pasaporte
            << "', fechaNacimiento='" << fechaNacimiento
            << "', genero='" << genero
            << "' WHERE idPasajero=" << id;

        int estado = mysql_query(conectar, ss.str().c_str());

        if (!estado)
            cout << "Pasajero actualizado correctamente!" << endl;
        else
            cout << "Error al actualizar pasajero: " << mysql_error(conectar) << endl;

        con.cerrar_conexion();
    }
}

void Pasajero::eliminarPasajero() {
    ConexionBD con;
    con.abrir_conexion();
    MYSQL* conectar = con.getConector();

    if (conectar) {
        int id;
        cout << "Ingrese ID del pasajero a eliminar: ";
        cin >> id;
        cin.ignore();

        stringstream ss;
        ss << "DELETE FROM pasajeros WHERE idPasajero = " << id;
        int estado = mysql_query(conectar, ss.str().c_str());

        if (!estado)
            cout << "Pasajero eliminado correctamente!" << endl;
        else
            cout << "Error al eliminar pasajero: " << mysql_error(conectar) << endl;

        con.cerrar_conexion();
    }
}
