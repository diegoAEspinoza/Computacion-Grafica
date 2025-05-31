// Nombre: Diego A. Espinoza
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
#include <cstdlib>
#define PI 3.141592653589793f

int ventana1, ventana2, ventana3;

float amarillo[3]     = {1, 1, 0},
      rojo[3]         = {1, 0, 0}, 
      verde[3]        = {0, 1, 0}, 
      azul[3]         = {0, 0, 1},
      cyan[3]         = {0, 1, 1},
      magenta[3]      = {1, 0, 1},
      gris[3]         = {0.5f, 0.5f, 0.5f},
      naranja[3]      = {1, 0.647f, 0},
      rosa[3]         = {1, 0.75f, 0.8f},
      marron[3]       = {0.6f, 0.3f, 0},
      verde_oscuro[3] = {0, 0.5f, 0},
      azul_oscuro[3]  = {0, 0, 0.5f},
      aqua[3]         = {0, 1, 0.5f},
      crema[3]        = {1, 0.9, 0.8},
      blanco[3]       = {1, 1, 1},
      negro[3]        = {0,0,0};


void mariposa_lineal(
    float Init,float End,
    float *RGB2,
    float w=1,
    float paso = 0.01){
    
    glLineWidth(w);
    glColor3fv(RGB2);
    glBegin(GL_LINE_STRIP);
        for (double theta = Init; theta <= End; theta += paso) {
            float r = exp(sin(theta)) - 2*cos(4*theta) + pow(sin((2*theta-PI)/24),5);
            float x = r*cos(theta);
            float y = r*sin(theta);
            glVertex2f(x,y);
        }
    glEnd();
}


void mariposa_color(
    float Init,float End,
    float *RGB, 
    float paso = 0.01,
    bool op=false, 
    float *RGB2=blanco,
    float w=1){
    
    glColor3fv(RGB);

    glBegin(GL_POLYGON);
        glVertex2f(0,0);
        for (double theta = Init; theta <= End; theta += paso) {
            float r = exp(sin(theta)) - 2*cos(4*theta) + pow(sin((2*theta-PI)/24),5);
            float x = r*cos(theta);
            float y = r*sin(theta);
            glVertex2f(x,y);
        }
    glEnd();
    
    if (op){mariposa_lineal(Init, End, RGB2,w,paso);}
    
}

void display1() {
    glClearColor(0, 0, 0, 0); 
    glClear(GL_COLOR_BUFFER_BIT);

    mariposa_color(10*PI,20*PI,magenta);
    mariposa_color(19.5*PI,40*PI,verde);
    mariposa_color(6*PI,8*PI,azul);
    mariposa_color(4*PI,6*PI,rojo);
    mariposa_color(2*PI,4*PI,cyan);
    mariposa_color(0,2*PI,amarillo);

    glutSwapBuffers();
}

void display2() {
    glClearColor(0, 0, 0, 0); 
    glClear(GL_COLOR_BUFFER_BIT);

    mariposa_lineal(10*PI,20*PI,magenta);
    mariposa_lineal(19.5*PI,40*PI,verde);
    mariposa_lineal(6*PI,8*PI,azul);
    mariposa_lineal(4*PI,6*PI,rojo);
    mariposa_lineal(2*PI,4*PI,cyan);
    mariposa_lineal(0,2*PI,amarillo);

    glutSwapBuffers();
}

void display3() {
    glClearColor(0, 0, 0, 0); 
    glClear(GL_COLOR_BUFFER_BIT);

    mariposa_color(10*PI,20*PI,magenta,0.01,true,verde,1.5);
    mariposa_color(19.5*PI,40*PI,verde,0.01,true,azul,1.5);
    mariposa_color(6*PI,8*PI,azul,0.01,true,rojo,1.5);
    mariposa_color(4*PI,6*PI,rojo,0.01,true,cyan,1.5);
    mariposa_color(2*PI,4*PI,cyan,0.01,true,amarillo,1.5);
    mariposa_color(0,2*PI,amarillo,0.01,true,magenta,1.5);

    glutSwapBuffers();
}


void inicio()
{   
    int a = 4;
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-a,a,-a,a);
    glClearColor(0,0,0,0);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    ventana1 = glutCreateWindow("Mariposa Coloreada");
    inicio();
    glutDisplayFunc(display1);

    glutInitWindowSize(400, 400);
    glutInitWindowPosition(550, 100);
    ventana2 = glutCreateWindow("Mariposa con Lineas");
    inicio();
    glutDisplayFunc(display2);

    glutInitWindowSize(400, 400);
    glutInitWindowPosition(1000, 100);
    ventana3 = glutCreateWindow("Mariposa con Lineas y Color");
    inicio();
    glutDisplayFunc(display3);

    glutMainLoop();
    return EXIT_SUCCESS;
}