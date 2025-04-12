// Crear ventana con punteros a funciones
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <stdlib.h>
#include <math.h>  // Necesario para cos() y sin()

// Colores
float amarillo[3]     = {1, 1, 0},
      rojo[3]         = {1, 0, 0}, 
      verde[3]        = {0, 1, 0}, 
      azul[3]         = {0, 0, 1},
      cyan[3]         = {0, 1, 1},
      magenta[3]      = {1, 0, 1},
      blanco[3]       = {1, 1, 1},
      gris[3]         = {0.5f, 0.5f, 0.5f},
      naranja[3]      = {1, 0.647f, 0},
      rosa[3]         = {1, 0.75f, 0.8f},
      marron[3]       = {0.6f, 0.3f, 0},
      verde_oscuro[3] = {0, 0.5f, 0},
      azul_oscuro[3]  = {0, 0, 0.5f},
      aqua[3]         = {0, 1, 0.5f}; 
void inicio ()
{
    glMatrixMode(GL_PROJECTION);
    int a=10;
    gluOrtho2D(-a,a,-a,a);
}


GLubyte mosca[] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x03, 0x80, 0x01, 0xC0, 0x06, 0xC0, 0x03, 0x60,
0x04, 0x60, 0x06, 0x20, 0x04, 0x30, 0x0C, 0x20,
0x04, 0x18, 0x18, 0x20, 0x04, 0x0C, 0x30, 0x20,
0x04, 0x06, 0x60, 0x20, 0x44, 0x03, 0xC0, 0x22,
0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,
0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,
0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,
0x66, 0x01, 0x80, 0x66, 0x33, 0x01, 0x80, 0xCC,
0x19, 0x81, 0x81, 0x98, 0x0C, 0xC1, 0x83, 0x30,
0x07, 0xe1, 0x87, 0xe0, 0x03, 0x3f, 0xfc, 0xc0,
0x03, 0x31, 0x8c, 0xc0, 0x03, 0x33, 0xcc, 0xc0,
0x06, 0x64, 0x26, 0x60, 0x0c, 0xcc, 0x33, 0x30,
0x18, 0xcc, 0x33, 0x18, 0x10, 0xc4, 0x23, 0x08,
0x10, 0x63, 0xC6, 0x08, 0x10, 0x30, 0x0c, 0x08,
0x10, 0x18, 0x18, 0x08, 0x10, 0x00, 0x00, 0x08 } ;

void polygon(float c[2], float r, float n,float *RGB){
    float x = c[0], y=c[1];

    glEnable(GL_POLYGON_STIPPLE);
    glPolygonStipple(mosca);

    glColor3fv(RGB);
    glBegin(GL_POLYGON);
        float angulo = 2 * M_PI / n;
        for (int i = 0; i < n; i++) {
            float vx = x + r * cos(i * angulo);
            float vy = y + r * sin(i * angulo);
            glVertex2f(vx, vy);
        }
    glEnd();
    glDisable(GL_POLYGON_STIPPLE);
}


void display(void)
{
    glClearColor(0,0,0,0);  // Color de fondo negro
    glClear(GL_COLOR_BUFFER_BIT);

    polygon((float[2]){-1,1}, 2, 4, amarillo);


    glutSwapBuffers();
}


void display2(void)
{
    glClearColor(0,0,0,0);  // Color de fondo negro
    glClear(GL_COLOR_BUFFER_BIT);

    polygon((float[2]){-1,1}, 2, 4, verde);
    glutSwapBuffers();
}


void createWindow(const char* name, int a, int l, void (*func)()) {
    glutInitWindowPosition(a,l);
    glutCreateWindow(name);
    glutDisplayFunc(func);
    inicio();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(600,600);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);

    createWindow("Mosca 1", 0,0, display);
    createWindow("Mosca 2", 700,0, display2);

    glutMainLoop();
    return EXIT_SUCCESS;
}