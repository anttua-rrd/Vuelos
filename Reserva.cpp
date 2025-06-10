#include "Reserva.h"
#include "ConexionBD.h"
#include <sstream>   // Para construir el query
#include <iostream>  // Para cout
#include <fstream>

using namespace std;

Reserva::Reserva() {
    // Constructor vacío
}

void Reserva::crearReserva() {
    ConexionBD con;
    con.abrir_conexion();
    MYSQL* conectar = con.getConector();

    if (conectar) {
        MYSQL_ROW row;
        MYSQL_RES* res;

        // Mostrar vuelos
        cout << "\n=== VUELOS DISPONIBLES ===\n";
        mysql_query(conectar, "SELECT idVuelo, numeroVuelo FROM vuelos");
        res = mysql_store_result(conectar);
        while ((row = mysql_fetch_row(res))) {
            cout << "ID: " << row[0] << " | Vuelo: " << row[1] << endl;
        }
        mysql_free_result(res);

        // Mostrar pasajeros
        cout << "\n=== PASAJEROS REGISTRADOS ===\n";
        mysql_query(conectar, "SELECT idPasajero, nombre, apellido FROM pasajeros");
        res = mysql_store_result(conectar);
        while ((row = mysql_fetch_row(res))) {
            cout << "ID: " << row[0] << " | " << row[1] << " " << row[2] << endl;
        }
        mysql_free_result(res);

        // Captura de datos
        int idVuelo, idPasajero;
        string asiento, fecha;
        cout << "\nIngrese ID del vuelo: ";
        cin >> idVuelo;
        cout << "Ingrese ID del pasajero: ";
        cin >> idPasajero;
        cin.ignore();

        cout << "Ingrese asiento: ";
        getline(cin, asiento);
        cout << "Ingrese fecha (YYYY-MM-DD): ";
        getline(cin, fecha);

        stringstream ss;
        ss << "INSERT INTO reservas(idVuelo, idPasajero, asiento, fechaReserva) VALUES ("
            << idVuelo << ", " << idPasajero << ", '" << asiento << "', '" << fecha << "')";

        int estado = mysql_query(conectar, ss.str().c_str());

        if (!estado)
            cout << "✅ Reserva ingresada exitosamente!\n";
        else
            cout << "❌ Error al ingresar reserva: " << mysql_error(conectar) << endl;

        con.cerrar_conexion();
    }
}



void Reserva::leerReservas() {
    ConexionBD con;
    con.abrir_conexion();
    MYSQL* conectar = con.getConector();

    if (conectar) {
        MYSQL_ROW fila;
        MYSQL_RES* resultado;

        string consulta = "SELECT * FROM reservas";
        const char* c = consulta.c_str();

        int estado = mysql_query(conectar, c);

        if (!estado) {
            resultado = mysql_store_result(conectar);

            cout << "\n=== LISTADO DE RESERVAS ===\n";

            if (mysql_num_rows(resultado) == 0) {
                cout << "No hay reservas registradas.\n";
            }
            else {
                while ((fila = mysql_fetch_row(resultado))) {
                    cout << "ID Reserva: " << fila[0]
                        << " | ID Vuelo: " << fila[1]
                        << " | ID Pasajero: " << fila[2]
                        << " | Asiento: " << fila[3]
                        << " | Fecha: " << fila[4] << endl;
                }
            }
        }
        else {
            cout << "Error al consultar reservas: " << mysql_error(conectar) << endl;
        }

        con.cerrar_conexion();
    }
    else {
        cout << "Error: no se pudo conectar a la base de datos." << endl;
    }
}


void Reserva::eliminarReserva() {
    ConexionBD con;
    con.abrir_conexion();
    MYSQL* conectar = con.getConector();

    if (conectar) {
        int idEliminar;
        cout << "Ingrese el ID de la reserva que desea eliminar: ";
        cin >> idEliminar;

        stringstream ss;
        ss << "DELETE FROM reservas WHERE idReserva = " << idEliminar;
        string query = ss.str();
        const char* q = query.c_str();

        int estado = mysql_query(conectar, q);

        if (!estado) {
            cout << "Reserva eliminada correctamente!" << endl;
        }
        else {
            cout << "Error al eliminar la reserva: " << mysql_error(conectar) << endl;
        }

        con.cerrar_conexion();
    }
    else {
        cout << "Error: no se pudo conectar a la base de datos." << endl;
    }
}


void Reserva::actualizarReserva() {
    ConexionBD con;
    con.abrir_conexion();
    MYSQL* conectar = con.getConector();

    if (conectar) {
        int idActualizar;
        cout << "Ingrese el ID de la reserva que desea actualizar: ";
        cin >> idActualizar;
        cin.ignore(); // para evitar que el getline falle

        cout << "Nuevo asiento: ";
        getline(cin, asiento);

        cout << "Nueva fecha (YYYY-MM-DD): ";
        getline(cin, fechaReserva);

        stringstream ss;
        ss << "UPDATE reservas SET asiento = '" << asiento
            << "', fechaReserva = '" << fechaReserva
            << "' WHERE idReserva = " << idActualizar;

        string query = ss.str();
        const char* q = query.c_str();

        int estado = mysql_query(conectar, q);

        if (!estado) {
            cout << "Reserva actualizada correctamente!" << endl;
        }
        else {
            cout << "Error al actualizar la reserva: " << mysql_error(conectar) << endl;
        }

        con.cerrar_conexion();
    }
    else {
        cout << "Error: no se pudo conectar a la base de datos." << endl;
    }
}



void Reserva::generarPaseHTML(int idReserva) {
    ConexionBD con;
    con.abrir_conexion();
    MYSQL* conectar = con.getConector();

    if (conectar) {
        stringstream ss;
        ss << "SELECT r.idReserva, p.nombre, p.apellido, v.numeroVuelo, v.destino, v.fecha, r.asiento "
            << "FROM reservas r "
            << "INNER JOIN pasajeros p ON r.idPasajero = p.idPasajero "
            << "INNER JOIN vuelos v ON r.idVuelo = v.idVuelo "
            << "WHERE r.idReserva = " << idReserva;

        if (mysql_query(conectar, ss.str().c_str()) == 0) {
            MYSQL_RES* res = mysql_store_result(conectar);
            MYSQL_ROW row = mysql_fetch_row(res);

            if (row) {
                ofstream html("pase_abordar.html");
                html << "<!DOCTYPE html><html><head><meta charset='UTF-8'>";
                html << "<style>";
                html << "body { font-family: Arial; background: #f8f9fa; padding: 20px; }";
                html << ".pase { background: white; padding: 20px; border-radius: 10px; width: 600px; box-shadow: 0 0 10px rgba(0,0,0,0.1); }";
                html << "h2 { color: #0074D9; margin-top: 0; }";
                html << "table { width: 100%; border-collapse: collapse; margin-top: 15px; }";
                html << "td { padding: 8px; vertical-align: top; }";
                html << ".footer { font-size: 12px; color: #333; margin-top: 20px; }";
                html << "</style>";
                html << "</head><body>";

                html << "<div class='pase'>";
                html << "<h2>PASE DE ABORDAR / BOARDING PASS</h2>";

                html << "<table>";
                html << "<tr><td><strong>Pasajero:</strong></td><td>" << row[1] << " " << row[2] << "</td></tr>";
                html << "<tr><td><strong>Vuelo:</strong></td><td>" << row[3] << "</td></tr>";
                html << "<tr><td><strong>Destino:</strong></td><td>" << row[4] << "</td></tr>";
                html << "<tr><td><strong>Fecha:</strong></td><td>" << row[5] << "</td></tr>";
                html << "<tr><td><strong>Asiento:</strong></td><td style='color:red; font-weight:bold;'>" << row[6] << "</td></tr>";
                html << "</table>";

                html << "<div class='footer'><hr>Preséntese 2 horas antes. La puerta cierra 15 minutos antes de la salida.</div>";
                html << "</div></body></html>";
                html.close();

                cout << "Pase generado: pase_abordar.html" << endl;
                system("explorer pase_abordar.html"); // Abrir archivo en navegador
            }
            else {
                cout << "No se encontró la reserva." << endl;
            }

            mysql_free_result(res);
        }
        else {
            cout << "Error en consulta: " << mysql_error(conectar) << endl;
        }

        con.cerrar_conexion();
    }
}
