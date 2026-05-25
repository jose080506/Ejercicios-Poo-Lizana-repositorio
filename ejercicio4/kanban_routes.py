"""
kanban_routes.py
Agregar al proyecto FastAPI del VPS (vps-poo-2026).

En main.py del VPS incluir:
    from kanban_routes import router as kanban_router
    app.include_router(kanban_router)

VPS: 173.212.209.61
Usuario API: admin
Clave API:   admin123
"""

from fastapi import APIRouter, HTTPException, Depends, status
from fastapi.security import HTTPBasic, HTTPBasicCredentials
from pydantic import BaseModel
from typing import Optional
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
        host=os.getenv("MYSQL_HOST", "db"),
        user=os.getenv("MYSQL_USER", "root"),
        password=os.getenv("MYSQL_PASSWORD", "password"),
        database=os.getenv("MYSQL_DATABASE", "vps-poo")
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


# ── COLUMNAS ───────────────────────────────────────────────────────────────────

@router.get("/columnas")
def obtener_columnas(username: str = Depends(verificar_credenciales)):
    db = get_db()
    cursor = db.cursor(dictionary=True)
    cursor.execute("SELECT * FROM columnas ORDER BY orden")
    columnas = cursor.fetchall()
    for col in columnas:
        cursor.execute(
            "SELECT * FROM tarjetas WHERE columna_id = %s ORDER BY orden",
            (col["id"],)
        )
        col["tarjetas"] = cursor.fetchall()
    cursor.close()
    db.close()
    return columnas


@router.post("/columnas", status_code=201)
def crear_columna(columna: ColumnaCreate, username: str = Depends(verificar_credenciales)):
    db = get_db()
    cursor = db.cursor()
    cursor.execute("SELECT COALESCE(MAX(orden), 0) + 1 FROM columnas")
    nuevo_orden = cursor.fetchone()[0]
    cursor.execute(
        "INSERT INTO columnas (nombre, orden) VALUES (%s, %s)",
        (columna.nombre, nuevo_orden)
    )
    db.commit()
    new_id = cursor.lastrowid
    cursor.close()
    db.close()
    return {"id": new_id, "nombre": columna.nombre, "orden": nuevo_orden}


@router.delete("/columnas/{columna_id}")
def eliminar_columna(columna_id: int, username: str = Depends(verificar_credenciales)):
    db = get_db()
    cursor = db.cursor()
    cursor.execute("DELETE FROM columnas WHERE id = %s", (columna_id,))
    db.commit()
    cursor.close()
    db.close()
    return {"mensaje": "Columna eliminada"}


# ── TARJETAS ───────────────────────────────────────────────────────────────────

@router.post("/tarjetas", status_code=201)
def crear_tarjeta(tarjeta: TarjetaCreate, username: str = Depends(verificar_credenciales)):
    db = get_db()
    cursor = db.cursor()
    cursor.execute(
        "SELECT COALESCE(MAX(orden), 0) + 1 FROM tarjetas WHERE columna_id = %s",
        (tarjeta.columna_id,)
    )
    nuevo_orden = cursor.fetchone()[0]
    cursor.execute(
        "INSERT INTO tarjetas (titulo, descripcion, columna_id, orden) VALUES (%s, %s, %s, %s)",
        (tarjeta.titulo, tarjeta.descripcion, tarjeta.columna_id, nuevo_orden)
    )
    db.commit()
    new_id = cursor.lastrowid
    cursor.close()
    db.close()
    return {"id": new_id, "titulo": tarjeta.titulo, "columna_id": tarjeta.columna_id}


@router.put("/tarjetas/{tarjeta_id}")
def editar_tarjeta(tarjeta_id: int, tarjeta: TarjetaEdit, username: str = Depends(verificar_credenciales)):
    db = get_db()
    cursor = db.cursor()
    cursor.execute(
        "UPDATE tarjetas SET titulo = %s, descripcion = %s WHERE id = %s",
        (tarjeta.titulo, tarjeta.descripcion, tarjeta_id)
    )
    db.commit()
    cursor.close()
    db.close()
    return {"mensaje": "Tarjeta actualizada"}


@router.delete("/tarjetas/{tarjeta_id}")
def eliminar_tarjeta(tarjeta_id: int, username: str = Depends(verificar_credenciales)):
    db = get_db()
    cursor = db.cursor()
    cursor.execute("DELETE FROM tarjetas WHERE id = %s", (tarjeta_id,))
    db.commit()
    cursor.close()
    db.close()
    return {"mensaje": "Tarjeta eliminada"}


@router.put("/tarjetas/{tarjeta_id}/mover")
def mover_tarjeta(tarjeta_id: int, datos: TarjetaMover, username: str = Depends(verificar_credenciales)):
    db = get_db()
    cursor = db.cursor()
    cursor.execute(
        "SELECT COALESCE(MAX(orden), 0) + 1 FROM tarjetas WHERE columna_id = %s",
        (datos.columna_destino_id,)
    )
    nuevo_orden = cursor.fetchone()[0]
    cursor.execute(
        "UPDATE tarjetas SET columna_id = %s, orden = %s WHERE id = %s",
        (datos.columna_destino_id, nuevo_orden, tarjeta_id)
    )
    db.commit()
    cursor.close()
    db.close()
    return {"mensaje": "Tarjeta movida"}
