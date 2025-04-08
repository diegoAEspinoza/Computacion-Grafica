# Computación Gráfica

## Profesor
    Nombre: Jhelly Perez

Este repositorio contiene ejemplos y ejercicios realizados en el curso de **Computación Gráfica**.

## Descripción

En este proyecto se exploran diferentes conceptos de computación gráfica usando OpenGL y la librería GLUT. Los ejercicios están organizados por semanas, donde cada semana se profundiza en distintos aspectos del manejo de gráficos 2D y 3D.

- **Semana 1**: Introducción a la visualización básica utilizando primitivas 2D y 3D (puntos, líneas, polígonos, etc.).
- **Semana 2**: 

## Estructura del Repositorio

La estructura del repositorio es la siguiente:

    Directory structure:
        ├── main.cpp
        ├── Makefile
        ├── READEM.md
        └── Semana1/
            ├── C1_Semana1.cpp
            ├── C1_Semana1
            └── C2_Semana1.cpp


## Requisitos

Para compilar y ejecutar este proyecto, necesitas tener instalados los siguientes programas:

- **GLUT**: Librería que permite crear ventanas y manejar eventos para OpenGL.
- **OpenGL**: Biblioteca gráfica estándar para la renderización de gráficos 2D y 3D.
- **GLEW**: Librería que facilita el acceso a las extensiones de OpenGL.

En sistemas basados en Unix, puedes instalar las dependencias con:

```bash
sudo apt-get install freeglut3 freeglut3-dev glew-utils libglew-dev

```

## Cómo compilar y ejecutar

Para compilar el proyecto, simplemente ejecuta el siguiente comando en la terminal:

```bash
make
```

Esto generará los ejecutables correspondientes. Para ejecutar uno de los programas, solo necesitas ejecutar el archivo generado, por ejemplo:

```bash
./C1_Semana1
```