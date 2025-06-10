CREATE DATABASE vuelos;

USE vuelos;

CREATE TABLE Vuelos (
    id INT AUTO_INCREMENT PRIMARY KEY,
    destino VARCHAR(50),
    fecha DATE
);

CREATE TABLE Pasajeros (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nombre VARCHAR(50),
    apellido VARCHAR(50),
    vuelo_id INT,
    FOREIGN KEY (vuelo_id) REFERENCES Vuelos(id)
);

SELECT * FROM vuelos