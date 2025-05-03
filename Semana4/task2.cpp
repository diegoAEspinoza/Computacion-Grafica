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


void drawCircle(double *CO, float radius, float *RGB) {
    double cx = CO[0], cy= CO[1];
    glColor3fv(RGB);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; ++i) {
        float theta = i * (2*PI) / segments ;
        float x1 = cx + radius * cosf(theta);
        float y1 = cy + radius * sinf(theta);
        glVertex2f(x1, y1);
    }
    glEnd();
    }

void drawLine(double *CO, float *RGB){
    double cx = CO[0], cy= CO[1];
    glColor3fv(RGB);
    glBegin(GL_LINE_LOOP);
    glBegin(GL_LINES);
        glVertex2f(0,0);
        glVertex2f(cx,cy);
    glEnd();
    }

void display(void) {
    glClearColor(1, 1, 1, 1);  
    glClear(GL_COLOR_BUFFER_BIT);
    
    for (int i = 0; i < 6; i++)
    {
        float r = 2.3f;
        float t = PI/3;
        float move = PI/6;
        double C[] = {r*cosf(i*t + move), r*sinf(i*t+move)};
        drawCircle(C,2,negro);
    }

    for (int i = 0; i < 6; i++)
    {
        float r = 3.8f;
        float t = PI/3;
        float move = PI/6;
        double C[] = {r*cosf(i*t + move), r*sinf(i*t+move)};
        drawCircle(C,0.5f,negro);
    }

    for (int i = 0; i < 6; i++)
    {
        float r = 4.3f;
        float t = PI/3;
        float move = PI/6;
        double C[] = {r*cosf(i*t + move), r*sinf(i*t+move)};
        drawLine(C,negro);
    }

    glLineWidth(2);
    double C[] ={0,0};
    drawCircle(C,4.3f,negro);


    glutSwapBuffers();  
}

void inicio()
{   
    int a = 5;
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-a,a,-a,a);
    glClearColor(0,0,0,0);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv); 
    glutInitWindowSize(800,800);
    glutInitWindowPosition(500,100);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);


    glutCreateWindow("Mandala");
    inicio();
    glutDisplayFunc(display);
    glutMainLoop();

    return EXIT_SUCCESS; 
}