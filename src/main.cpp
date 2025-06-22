#include <stdlib.h>
#include <math.h>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <vector>
#include <GL/glut.h>
#include "img.h"

struct Elipse {
    std::vector<float> vertices;  // Almacenará las coordenadas de la elipse
    int num_segmentos;
};

Elipse elipses[7];

// VARIABLES GLOBALES
float rotX = 0, rotY = 0;
bool mousePressed = false;
int lastX, lastY;

GLuint textureIDSol, textureIDMercurio, textureIDVenus, textureIDTierra;

// Función para calcular las elipses
void calcularElipse(float cx, float cz, float rx, float rz, int num_segmentos, Elipse &elipse) {
    elipse.vertices.clear();
    
    for (int i = 0; i <= num_segmentos; i++) {
        float angulo = 2.0f * M_PI * float(i) / float(num_segmentos);
        float x = cx + (cos(angulo) * rx);
        float z = cz + (sin(angulo) * rz);
        elipse.vertices.push_back(x);
        elipse.vertices.push_back(0.0f);  // Y siempre será 0 en este caso
        elipse.vertices.push_back(z);
    }
}

// Función para dibujar las elipses
void dibujarElipse(const Elipse &elipse) {
    glBegin(GL_LINE_LOOP);
    for (size_t i = 0; i < elipse.vertices.size(); i += 3) {
        glVertex3f(elipse.vertices[i], elipse.vertices[i+1], elipse.vertices[i+2]);
    }
    glEnd();
}

// Inicialización de las elipses
void inicializarElipses() {
    for (int i = 0; i < 7; i++) {
        float rx = 2 * (i + 1);
        float rz = 2.5 * (i + 1);
        calcularElipse(0, 0, rx, rz, 100, elipses[i]);
    }
}

// Cargar texturas y asignarlas a las variables
void cargarTexturas() {
    crearTexture("./img/Sol.bmp", textureIDSol);
    crearTexture("./img/0PMercurio.bmp", textureIDMercurio);
    crearTexture("./img/1PVenus.bmp", textureIDVenus);
}

// Función de iluminación, ahora asigna correctamente las texturas
void iluminacion(const char* imagen, GLuint textureID) {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat PosicionLuz[] = {2.0, 2.0, 2.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, PosicionLuz);

    glClearColor(0.5, 0.5, 0.5, 1);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glTexGend(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGend(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(25, 20, 25, 0, 0.1, 0, 0, 1, 0);

    for (int i = 0; i < 7; i++) {
        dibujarElipse(elipses[i]);
    }

    // Dibuja el Sol
    glPushMatrix();
        iluminacion("./img/Sol.bmp", textureIDSol);
        glutSolidSphere(1, 40, 40);
    glPopMatrix();

    // Dibuja Mercurio
    glPushMatrix();
        iluminacion("./img/0PMercurio.bmp", textureIDMercurio);
        glTranslatef(2.0f, 0.0f, 0.0f);
        glutSolidSphere(0.25, 40, 40);
    glPopMatrix();

    // Dibuja Venus
    glPushMatrix();
        iluminacion("./img/1PVenus.bmp", textureIDMercurio);
        glTranslatef(4.0f, 0.0f, 0.0f);
        glutSolidSphere(0.45, 40, 40);
    glPopMatrix();
    
    // Dibuja Tierra
    glPushMatrix();
        iluminacion("./img/2PTierra.bmp", textureIDMercurio);
        glTranslatef(6.0f, 0.0f, 0.0f);
        glutSolidSphere(0.55, 40, 40);
    glPopMatrix();
    
    // Dibuja Marte
    glPushMatrix();
        iluminacion("./img/3PMarte.bmp", textureIDMercurio);
        glTranslatef(8.0f, 0.0f, 0.0f);
        glutSolidSphere(0.5, 40, 40);
    glPopMatrix();
    
    // Dibuja Jupiter
    glPushMatrix();
        iluminacion("./img/4PJupiter.bmp", textureIDMercurio);
        glTranslatef(10.0f, 0.0f, 0.0f);
        glutSolidSphere(0.85, 40, 40);
    glPopMatrix();

    // Dibuja Saturno
    glPushMatrix();
        iluminacion("./img/5PSaturno.bmp", textureIDMercurio);
        glTranslatef(12.0f, 0.0f, 0.0f);
        glutSolidSphere(0.75, 40, 40);
    glPopMatrix();

    // Dibuja Urano
    glPushMatrix();
        iluminacion("./img/6PUrano.bmp", textureIDMercurio);
        glTranslatef(14.0f, 0.0f, 0.0f);
        glutSolidSphere(0.7, 40, 40);
    glPopMatrix();

    // Dibuja Neptuno
    glPushMatrix();
        iluminacion("./img/7PNeptuno.bmp", textureIDMercurio);
        glTranslatef(2.0f, 0.0f, 0.0f);
        glutSolidSphere(0.6, 40, 40);
    glPopMatrix();

    glutSwapBuffers();
}

// Reshape para ajustar el tamaño de la ventana
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)w/h, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Tetera Texturisada");

    cargarTexturas();
    inicializarElipses();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_NORMALIZE);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}
