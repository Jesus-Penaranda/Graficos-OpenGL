# Graficos OpenGL - UPC FIB Solutions

![C++](https://img.shields.io/badge/C%2B%2B-17-blue?logo=c%2B%2B&logoColor=white)
![Qt](https://img.shields.io/badge/Qt-qmake-41CD52?logo=qt&logoColor=white)
![OpenGL](https://img.shields.io/badge/OpenGL-GLSL-5586A4)
![FIB](https://img.shields.io/badge/FIB-UPC-orange)

Bienvenido a mi repositorio de soluciones de prácticas de la asignatura de gráficos de la **Facultad de Informática de Barcelona (FIB - UPC)**.

Aquí se recopilan ejercicios de shaders y plugins en C++/Qt para un viewer 3D, con técnicas que van desde lo básico de GLSL hasta bloques más avanzados de renderizado.

---

## Estructura del repositorio

Los contenidos estan organizados en dos bloques principales:

### plugins
- Plugins del viewer en C++/Qt
- Navegacion y render base
- Iluminacion, sombras y reflexiones
- Efectos visuales e interaccion con objetos

### Shaders
- Coleccion de shaders GLSL por sesiones y practicas
- Ejercicios de texturas, deformaciones y animaciones
- Geometry shaders y tecnicas de render avanzado

---

## Bloques destacados

### Fundamentos
- `Parte1`
- `Lab2_Texturas`

### Geometry shaders
- `S7-GS`

### Plugins y efectos
- `S8-Plugins`
- `S9-Effect-Action`
- `S10-Render-PLugins`
- `S11-Render-plugins-2`

---

## Puntos clave

- Trabajo con C++ y Qt (`.cpp`, `.h`, `.pro`)
- Uso de shaders GLSL (`.vert`, `.frag`, `.geom`, `.glsl`)
- Ejemplos de seleccion de objetos, sombras, reflexiones y postprocesado
- Repositorio limpio centrado en codigo fuente y recursos utiles para estudio

---

## Compilacion rapida

```bash
cd plugins
qmake
make
```

> [!CAUTION]
> Este repositorio se comparte con fines docentes y de referencia. Úsalo para aprender y comparar enfoques, no para copiar entregas tal cual.

