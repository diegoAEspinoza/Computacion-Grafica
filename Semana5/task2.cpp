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



void drawSector(float cx, float cy, float radius, float t1, float t2, float *RGB) {
    glColor3fv(RGB);
    int segments = 50;
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < segments; ++i) {
        float theta = t1 + i * (t2 - t1) / segments;
        float theta2 = t1 + (i + 1) * (t2 - t1) / segments;
        float x1 = cx + radius * cosf(theta);
        float y1 = cy + radius * sinf(theta);
        float x2 = cx + radius * cosf(theta2);
        float y2 = cy + radius * sinf(theta2);
        glVertex2f(cx, cy);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    }
    glEnd();
    }

void cuadrado (float x,float y, float *RGB){
    glColor3fv(RGB);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x,-y);
        glVertex2f(x,y);
        glVertex2f(-x,y);
        glVertex2f(-x,-y);
    glEnd();
}

void display(void) {
    glClearColor(0, 0, 0, 0);  
    glClear(GL_COLOR_BUFFER_BIT);

    drawSector(0, 0, 0.8, 0, 2 * PI, blanco);
    drawSector(0, 0, 0.7, 0, 2 * PI, negro);

    cuadrado(-1,-0.03,negro);
    cuadrado(-0.03,-1,negro);

    drawSector(0, -0.1, 0.7, PI / 3, 2 * PI / 3,verde_oscuro);
    drawSector(0, 0.1, 0.7, 4 * PI / 3, 5 * PI / 3, verde_oscuro);

    glutSwapBuffers();  
}


void inicio()
{   
    int a = 1;
    glMatrixMode(GL_PROJECTION);
    glShadeModel(GL_SMOOTH);
    gluOrtho2D(-a,a,-a,a);
    glClearColor(0,0,0,0);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv); 
    glutInitWindowSize(400,400);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);


    glutCreateWindow("Omnitrix");
    inicio();
    glutDisplayFunc(display);
    glutMainLoop();

    return EXIT_SUCCESS; 
}