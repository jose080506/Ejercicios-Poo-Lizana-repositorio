-- crear_base.sql
-- Script para crear la base de datos pintura.db
-- Uso:  sqlite3 pintura.db < crear_base.sql
-- O abrir el archivo en SQLiteStudio y ejecutar todo.

CREATE TABLE IF NOT EXISTS usuarios (
    id        INTEGER PRIMARY KEY AUTOINCREMENT,
    usuario   TEXT UNIQUE NOT NULL,
    clave     TEXT NOT NULL,
    nombre    TEXT,
    apellido  TEXT
);

CREATE TABLE IF NOT EXISTS logs (
    id       INTEGER PRIMARY KEY AUTOINCREMENT,
    fecha    TEXT NOT NULL,
    tipo     TEXT NOT NULL,   -- 'acceso_ok' | 'intento_fallido'
    usuario  TEXT
);

CREATE TABLE IF NOT EXISTS trazos (
    id         INTEGER PRIMARY KEY AUTOINCREMENT,
    sesion     INTEGER NOT NULL,
    trazo      INTEGER NOT NULL,
    orden      INTEGER NOT NULL,
    x          INTEGER NOT NULL,
    y          INTEGER NOT NULL,
    color      TEXT NOT NULL,    -- formato '#RRGGBB'
    grosor     INTEGER NOT NULL,
    es_inicio  INTEGER NOT NULL  -- 1 = primer punto del trazo, 0 = continuación
);

-- Usuarios de prueba
INSERT OR IGNORE INTO usuarios (usuario, clave, nombre, apellido)
VALUES ('admin', '1234', 'Admin', 'Sistema');

INSERT OR IGNORE INTO usuarios (usuario, clave, nombre, apellido)
VALUES ('jose', 'qwerty', 'José', 'Pérez');
