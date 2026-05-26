"""
kanban_routes.py  —  Ejercicio 04 completo
Cumple todos los requisitos del enunciado:
  - CRUD columnas y tarjetas
  - Mover tarjeta entre columnas
  - Reordenar tarjetas dentro de una columna (usa tabla card_order)
  - Autenticación básica

En app/main.py agregar:
    from routers import kanban
    app.include_router(kanban.router)
"""

from fastapi import APIRouter, HTTPException, Depends, status
from fastapi.security import HTTPBasic, HTTPBasicCredentials
from pydantic import BaseModel
from typing import Optional, List
import mysql.connector
import os
import secrets

router = APIRouter(prefix="/kanban", tags=["kanban"])
security = HTTPBasic()


# ── Autenticación ──────────────────────────────────────────────────────────────
def verificar_credenciales(credentials: HTTPBasicCredentials = Depends(security)):
    usuario_ok = secrets.compare_digest(
        credentials.username.encode("utf8"),
        os.getenv("API_USER", "admin").encode("utf8")
    )
    clave_ok = secrets.compare_digest(
        credentials.password.encode("utf8"),
        os.getenv("API_PASS", "admin123").encode("utf8")
    )
    if not (usuario_ok and clave_ok):
        raise HTTPException(
            status_code=status.HTTP_401_UNAUTHORIZED,
            detail="Credenciales incorrectas",
            headers={"WWW-Authenticate": "Basic"},
        )
    return credentials.username


# ── Conexión MySQL ─────────────────────────────────────────────────────────────
def get_db():
    return mysql.connector.connect(
        host=os.getenv("MYSQL_HOST", "poo_mysql"),
        user=os.getenv("MYSQL_USER", "poo_user"),
        password=os.getenv("MYSQL_PASSWORD", "poo1234"),
        database=os.getenv("MYSQL_DATABASE", "poo_db")
    )


# ── Modelos Pydantic ───────────────────────────────────────────────────────────
class ColumnaCreate(BaseModel):
    nombre: str

class TarjetaCreate(BaseModel):
    titulo: str
    descripcion: Optional[str] = ""
    columna_id: int

class TarjetaEdit(BaseModel):
    titulo: str
    descripcion: Optional[str] = ""

class TarjetaMover(BaseModel):
    columna_destino_id: int

class ReordenarTarjetas(BaseModel):
    orden: List[int]   # lista de card_id en el nuevo orden


# ── TABLERO COMPLETO ───────────────────────────────────────────────────────────

@router.get("/columnas")
def obtener_tablero(username: str = Depends(verificar_credenciales)):
    """Devuelve todas las columnas con sus tarjetas ordenadas por card_order."""
    db = get_db()
    cursor = db.cursor(dictionary=True)

    cursor.execute("SELECT * FROM columns ORDER BY orden")
    columnas = cursor.fetchall()

    for col in columnas:
        # Traer tarjetas ordenadas por card_order.posicion
        cursor.execute("""
            SELECT c.id, c.titulo, c.descripcion, co.posicion
            FROM cards c
            JOIN card_order co ON co.card_id = c.id
            WHERE c.columna_id = %s
            ORDER BY co.posicion
        """, (col["id"],))
        col["tarjetas"] = cursor.fetchall()

    cursor.close()
    db.close()
    return columnas


# ── COLUMNAS ───────────────────────────────────────────────────────────────────

@router.post("/columnas", status_code=201)
def crear_columna(columna: ColumnaCreate,
                  username: str = Depends(verificar_credenciales)):
    db = get_db()
    cursor = db.cursor()
    cursor.execute("SELECT COALESCE(MAX(orden), 0) + 1 FROM columns")
    nuevo_orden = cursor.fetchone()[0]
    cursor.execute(
        "INSERT INTO columns (nombre, orden) VALUES (%s, %s)",
        (columna.nombre, nuevo_orden)
    )
    db.commit()
    new_id = cursor.lastrowid
    cursor.close()
    db.close()
    return {"id": new_id, "nombre": columna.nombre, "orden": nuevo_orden}


@router.delete("/columnas/{columna_id}")
def eliminar_columna(columna_id: int,
                     username: str = Depends(verificar_credenciales)):
    db = get_db()
    cursor = db.cursor()
    cursor.execute("DELETE FROM columns WHERE id = %s", (columna_id,))
    db.commit()
    cursor.close()
    db.close()
    return {"mensaje": "Columna eliminada"}


# ── TARJETAS ───────────────────────────────────────────────────────────────────

@router.post("/tarjetas", status_code=201)
def crear_tarjeta(tarjeta: TarjetaCreate,
                  username: str = Depends(verificar_credenciales)):
    db = get_db()
    cursor = db.cursor()

    # Insertar la tarjeta
    cursor.execute(
        "INSERT INTO cards (titulo, descripcion, columna_id) VALUES (%s, %s, %s)",
        (tarjeta.titulo, tarjeta.descripcion, tarjeta.columna_id)
    )
    db.commit()
    new_id = cursor.lastrowid

    # Agregar al final del card_order de esa columna
    cursor.execute(
        "SELECT COALESCE(MAX(posicion), 0) + 1 FROM card_order WHERE columna_id = %s",
        (tarjeta.columna_id,)
    )
    nueva_pos = cursor.fetchone()[0]
    cursor.execute(
        "INSERT INTO card_order (columna_id, card_id, posicion) VALUES (%s, %s, %s)",
        (tarjeta.columna_id, new_id, nueva_pos)
    )
    db.commit()
    cursor.close()
    db.close()
    return {"id": new_id, "titulo": tarjeta.titulo, "columna_id": tarjeta.columna_id}


@router.put("/tarjetas/{tarjeta_id}")
def editar_tarjeta(tarjeta_id: int, tarjeta: TarjetaEdit,
                   username: str = Depends(verificar_credenciales)):
    db = get_db()
    cursor = db.cursor()
    cursor.execute(
        "UPDATE cards SET titulo = %s, descripcion = %s WHERE id = %s",
        (tarjeta.titulo, tarjeta.descripcion, tarjeta_id)
    )
    db.commit()
    cursor.close()
    db.close()
    return {"mensaje": "Tarjeta actualizada"}


@router.delete("/tarjetas/{tarjeta_id}")
def eliminar_tarjeta(tarjeta_id: int,
                     username: str = Depends(verificar_credenciales)):
    db = get_db()
    cursor = db.cursor()
    # card_order se elimina por CASCADE
    cursor.execute("DELETE FROM cards WHERE id = %s", (tarjeta_id,))
    db.commit()
    cursor.close()
    db.close()
    return {"mensaje": "Tarjeta eliminada"}


@router.put("/tarjetas/{tarjeta_id}/mover")
def mover_tarjeta(tarjeta_id: int, datos: TarjetaMover,
                  username: str = Depends(verificar_credenciales)):
    """Mueve una tarjeta a otra columna, al final de esa columna."""
    db = get_db()
    cursor = db.cursor()

    # Obtener columna actual
    cursor.execute("SELECT columna_id FROM cards WHERE id = %s", (tarjeta_id,))
    row = cursor.fetchone()
    if not row:
        raise HTTPException(status_code=404, detail="Tarjeta no encontrada")
    columna_actual = row[0]

    # Actualizar columna en cards
    cursor.execute(
        "UPDATE cards SET columna_id = %s WHERE id = %s",
        (datos.columna_destino_id, tarjeta_id)
    )

    # Eliminar de card_order de la columna actual
    cursor.execute(
        "DELETE FROM card_order WHERE card_id = %s AND columna_id = %s",
        (tarjeta_id, columna_actual)
    )

    # Agregar al final de la columna destino
    cursor.execute(
        "SELECT COALESCE(MAX(posicion), 0) + 1 FROM card_order WHERE columna_id = %s",
        (datos.columna_destino_id,)
    )
    nueva_pos = cursor.fetchone()[0]
    cursor.execute(
        "INSERT INTO card_order (columna_id, card_id, posicion) VALUES (%s, %s, %s)",
        (datos.columna_destino_id, tarjeta_id, nueva_pos)
    )

    db.commit()
    cursor.close()
    db.close()
    return {"mensaje": "Tarjeta movida"}


@router.put("/columnas/{columna_id}/reordenar")
def reordenar_tarjetas(columna_id: int, datos: ReordenarTarjetas,
                       username: str = Depends(verificar_credenciales)):
    """
    Reordena las tarjetas dentro de una columna.
    Se recibe la lista de card_id en el nuevo orden deseado.
    """
    db = get_db()
    cursor = db.cursor()

    for posicion, card_id in enumerate(datos.orden):
        cursor.execute(
            """INSERT INTO card_order (columna_id, card_id, posicion)
               VALUES (%s, %s, %s)
               ON DUPLICATE KEY UPDATE posicion = %s""",
            (columna_id, card_id, posicion, posicion)
        )

    db.commit()
    cursor.close()
    db.close()
    return {"mensaje": "Orden actualizado"}
