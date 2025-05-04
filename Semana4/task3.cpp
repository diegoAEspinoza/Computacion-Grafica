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


float blanco[3]       = {1, 1, 1},
      negro[3]        = {0,0,0};


void drawCircle(double *CO, float radius, float *RGB, float segments, float move, GLenum modo) {
    glLineWidth(3);
    double cx = CO[0], cy= CO[1];
    glColor3fv(RGB);
    glBegin(modo);
    for (int i = 0; i < segments; ++i) {
        float theta = (i * (2*PI) / segments) + move;
        float x1 = cx + radius * cosf(theta);
        float y1 = cy + radius * sinf(theta);
        glVertex2f(x1, y1);
    }
    glEnd();
    }



void tablero(float size, int count) {
    glLineWidth(2);

    float dist = size / 2.0f;
    float step = size / count;
    glColor3fv(negro);
    glBegin(GL_LINES);
        for (int i = 0; i <= count; i++) {
            float point = -dist + i * step;

            glVertex2f(point, -dist); glVertex2f(point, dist);
            glVertex2f(-dist, point); glVertex2f(dist, point);
        }
    glEnd();
    glLineWidth(1);
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
    
    double C[]={0,0};
    drawCircle(C,0.25,negro,150,0,GL_POLYGON);
    drawCircle(C,0.2,blanco,150,0,GL_POLYGON);
    for (int i = 0; i < 8; i++)
    {
        float r = 0.25f;
        float t = PI/4;
        float move = 0;
        double C[] = {r*cosf(i*t + move), r*sinf(i*t+move)};
        drawLine(C,negro);
    }

    for (int i = 0; i < 8; i++)
    {
        float r = 1.0f;
        float t = PI/4;
        float move = 0;
        double C[] = {r*cosf(i*t + move), r*sinf(i*t+move)};
        drawCircle(C,1,negro,150,0,GL_LINE_LOOP);
    }

    tablero(1.98, 3);

    for (int i = 0; i < 8; i++)
    {
        float r = 2.35f;
        float t = PI/4;
        float move = 0;
        double C[] = {r*cosf(i*t + move), r*sinf(i*t+move)};
        drawCircle(C,0.15,negro,150,0,GL_LINE_LOOP);
    }

    for (int i = 0; i < 4; i++)
    {
        float r = 2.35f;
        float t = PI/2;
        float move = 0;
        double C[] = {r*cosf(i*t + move), r*sinf(i*t+move)};
        drawCircle(C,0.35,negro,4,PI/4,GL_LINE_LOOP);
    }

    for (int i = 0; i < 4; i++)
    {
        float r = 2.35f;
        float t = PI/2;
        float move = PI/4;
        double C[] = {r*cosf(i*t + move), r*sinf(i*t+move)};
        drawCircle(C,0.35,negro,4,0,GL_LINE_LOOP);
    }

    drawCircle(C,2.9f,negro,150,0,GL_LINE_LOOP);
    glutSwapBuffers();  
}

void inicio()
{   
    int a = 4;
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