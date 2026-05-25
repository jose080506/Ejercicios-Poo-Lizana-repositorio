-- Ejecutar en phpMyAdmin: http://173.212.209.61:8080
-- (o desde MySQL CLI en el VPS)

CREATE TABLE IF NOT EXISTS columnas (
    id       INT AUTO_INCREMENT PRIMARY KEY,
    nombre   VARCHAR(100) NOT NULL,
    orden    INT DEFAULT 0
);

CREATE TABLE IF NOT EXISTS tarjetas (
    id          INT AUTO_INCREMENT PRIMARY KEY,
    titulo      VARCHAR(200) NOT NULL,
    descripcion TEXT DEFAULT '',
    columna_id  INT,
    orden       INT DEFAULT 0,
    FOREIGN KEY (columna_id) REFERENCES columnas(id) ON DELETE CASCADE
);

-- Columnas iniciales
INSERT INTO columnas (nombre, orden) VALUES
    ('Por hacer',   1),
    ('En progreso', 2),
    ('Hecho',       3);
