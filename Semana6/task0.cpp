#ifdef _WIN32
#include <windows.h>
#endif
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <cstdlib>
#include <vector> 
#include <cstddef> 
#include <string>    
#include <sstream>   
#include <ctime>  
#define PI 3.141592653589793f


float camaraHor =-0.5;
float esferaX = 0;
float esferaZ = 0;
float paso = 0.1f;
float limite = 5.0f;
float dirZ = -1.0f;
float dirX = 0.0f;

void actDirCamera(){
    dirX = sin(camaraHor * PI);
    dirZ = cos(camaraHor * PI);
}


void move(float x, float z) {
    float nuevoX = esferaX + x;
    float nuevoZ = esferaZ + z;

    if (nuevoX >= -limite + 0.5f && nuevoX <= limite - 0.5f)
        esferaX = nuevoX;

    if (nuevoZ >= -limite + 0.5f && nuevoZ <= limite - 0.5f)
        esferaZ = nuevoZ;
}

void keyboard(unsigned char key, int x, int y){
    switch (toupper(key)) {
        case 'W':
            move(dirX * paso, dirZ * paso);
            break;
        case 'S':
            move(-dirX * paso, -dirZ * paso);    
            break;
        case 'A':
            move(-dirZ * paso, dirX * paso); // Perpendicular izquierda
            break;
        case 'D':
            move(dirZ * paso, -dirX * paso); // Perpendicular derecha
            break;
        case 'Q':
            camaraHor -= 0.05f;
            actDirCamera();
            break;
        case 'E':
            camaraHor += 0.05f;
            actDirCamera();
            break;
    }
    glutPostRedisplay();
}



void drawAxes() {
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
        glVertex3f(-10, 0, 0); glVertex3f(10, 0, 0); // Eje X
    glColor3f(0, 1, 0);
        glVertex3f(0, -10, 0); glVertex3f(0, 10, 0); // Eje Y
    glColor3f(0, 0, 1);
        glVertex3f(0, 0, -10); glVertex3f(0, 0, 10); // Eje Z
    glEnd();
}

void piso(){
    glColor3f(0.4, 0.4, 0.4);
    glBegin(GL_QUADS);
        glVertex3f(-5, 0, -5);
        glVertex3f(-5, 0, 5);
        glVertex3f(5, 0, 5);
        glVertex3f(5, 0, -5);
    glEnd();
}

void camera(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 800.0 / 600.0, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float distancia = 5;
    float camX = esferaX - dirX * distancia;
    float camZ = esferaZ - dirZ * distancia;

    gluLookAt(
        camX, 5, camZ,              // Posición de la cámara
        esferaX, 0.5, esferaZ,      // Mira hacia la esfera (jugador)
        0, 1, 0                     // Vector "arriba"
    );
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera();

 

    glPushMatrix();
        glColor3f(1,1,1);
        glTranslated(esferaX, 0.5, esferaZ);
        glutWireCube(1);
    glPopMatrix();
    piso();
    drawAxes();

    glutSwapBuffers();
}

void reshape (int w, int h) {
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Semana 10");

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
