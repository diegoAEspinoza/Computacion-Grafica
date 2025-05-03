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
#define PI 3.141592f
int segments = 100;
double C[]={0,0};
float R=0.3;

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
      aqua[3]         = {0, 1, 0.5f},
      crema[3]        = {1, 0.9, 0.8},
      negro[3]        = {0,0,0};


void drawSector(double *CO, float radius, float *RGB, GLenum modo) {
    double cx = CO[0], cy= CO[1];
    glColor3fv(RGB);
    glBegin(modo);
    for (int i = 0; i < segments; ++i) {
        float theta = i * (2*PI) / segments;
        float x1 = cx + radius * cosf(theta);
        float y1 = cy + radius * sinf(theta);
        glVertex2f(x1, y1);
    }
    glEnd();
    }

void display(void) {
    glClearColor(1, 1, 1, 1);  
    glClear(GL_COLOR_BUFFER_BIT);
    
    drawSector(C, 0.80,  negro, GL_LINE_LOOP);
    drawSector(C, 0.75,  negro, GL_LINE_LOOP);
    drawSector(C, 0.50,  negro, GL_LINE_LOOP);

    for (int i = 0; i < 8; i++) {
        double C1[] = { 0.5*cos(i*PI/4) , 0.5*sin(i*PI/4) };
        drawSector(C1, 0.07, negro, GL_LINE_LOOP);
        drawSector(C1, 0.13, negro, GL_LINE_LOOP);
        drawSector(C1, 0.19, negro, GL_LINE_LOOP);
        }
    
    for (int i = 0; i < 8; i++) {
        double C2[] = { 0.16*cos(i*PI/4) , 0.16*sin(i*PI/4) };
        drawSector(C2, 0.14 , negro, GL_LINE_LOOP);
        }

    for (int i = 0; i < 8; i++) {
        double C3[] = { 0.62*cos((2*i-1)*PI/8) , 0.62*sin((2*i-1)*PI/8) };
        drawSector(C3, 0.02, negro, GL_LINE_LOOP);
        drawSector(C3, 0.05, negro, GL_LINE_LOOP);
        }
    glutSwapBuffers();  
}

void inicio()
{   
    int a = 1;
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-a,a,-a,a);
    glClearColor(0,0,0,0);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv); 
    glutInitWindowSize(400,400);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);


    glutCreateWindow("Mandala");
    inicio();
    glutDisplayFunc(display);
    glutMainLoop();

    return EXIT_SUCCESS; 
}