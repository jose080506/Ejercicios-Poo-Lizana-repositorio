-- Ejecutar en phpMyAdmin: http://173.212.209.61:8080
-- o desde MySQL CLI en el VPS

-- Tabla de columnas
CREATE TABLE IF NOT EXISTS columns (
    id     INT AUTO_INCREMENT PRIMARY KEY,
    nombre VARCHAR(100) NOT NULL,
    orden  INT DEFAULT 0
);

-- Tabla de tarjetas
CREATE TABLE IF NOT EXISTS cards (
    id          INT AUTO_INCREMENT PRIMARY KEY,
    titulo      VARCHAR(200) NOT NULL,
    descripcion TEXT,
    columna_id  INT,
    FOREIGN KEY (columna_id) REFERENCES columns(id) ON DELETE CASCADE
);

-- Tabla de orden de tarjetas dentro de cada columna
CREATE TABLE IF NOT EXISTS card_order (
    columna_id INT NOT NULL,
    card_id    INT NOT NULL,
    posicion   INT NOT NULL DEFAULT 0,
    PRIMARY KEY (columna_id, card_id),
    FOREIGN KEY (columna_id) REFERENCES columns(id) ON DELETE CASCADE,
    FOREIGN KEY (card_id)    REFERENCES cards(id)   ON DELETE CASCADE
);

-- Columnas iniciales
INSERT INTO columns (nombre, orden) VALUES
    ('Por hacer',   1),
    ('En progreso', 2),
    ('Hecho',       3);
