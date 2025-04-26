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
    morado[3] = {0.5f, 0.0f, 0.5f};


void cardioide(float x, float y, float a, float b, float angulo, float n, float m, GLenum Modo, float *RGB){
    glColor3fv(RGB);
    glBegin(Modo);
    if ( Modo == GL_POLYGON)
    {
        glVertex2f(x, y);
    }
    float theta = angulo / n;
    for (float i = 0; i <= n; i++) {
        
        float r = a - b*sin(i*theta*m);
        
        float vx = r * cos(i*theta);
        float vy = r * sin(i*theta);
        
        glVertex2f(x+vx, y+vy);
    }
    glEnd();
}

void lemniscatas(float x, float y, float a, float b, float angulo, float n, float m, GLenum Modo, float *RGB){
    glColor3fv(RGB);
    glBegin(Modo);
    if ( Modo == GL_POLYGON || Modo == GL_LINES  )
    {
        glVertex2f(x, y);
    }
    float theta = angulo / n;
    for (float i = 0; i <= n; i++) {
        float r = sqrt(a + b*cos(i*theta*m));
        float vx = r * cos(i*theta);
        float vy = r * sin(i*theta);
        
        glVertex2f(x+vx, y+vy);
    }
    glEnd();
}


void display(void) {
    glClearColor(0, 0, 0, 0);  
    glClear(GL_COLOR_BUFFER_BIT);
    
    glBegin(GL_POLYGON);
    glColor3fv(verde);
        glVertex2f(-0.05,1);glVertex2f(0.05,1);
        glVertex2f(0.05,-2);glVertex2f(-0.05,-2);
    glEnd();

    cardioide(0,1,0,-1,2*PI,500,6,GL_POLYGON,morado);
    cardioide(0,1,0.1,0,2*PI,100,1,GL_POLYGON,amarillo);

    lemniscatas(0,-1,0,0.81, 2*PI,5000,2, GL_POLYGON,verde);
    

    glutSwapBuffers();  
}


void inicio()
{   
    int a = 3;
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


    glutCreateWindow("Flor Morada");
    inicio();
    glutDisplayFunc(display);
    glutMainLoop();

    return EXIT_SUCCESS; 
}