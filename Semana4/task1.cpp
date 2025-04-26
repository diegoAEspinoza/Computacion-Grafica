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
    aqua[3]         = {0, 1, 0.5f};

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
        
        float r = sqrt(a - b*sin(i*theta*m));
        
        float vx = r * cos(i*theta);
        float vy = r * sin(i*theta);
        
        glVertex2f(x+vx, y+vy);
    }
    glEnd();
}


void display(void) {
    glClearColor(0, 0, 0, 0);  
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3fv(amarillo);

    // Cardioide
    cardioide(-5, 5, 0.5, 0.5, 2*PI, 50, 1, GL_POINTS,amarillo);
    cardioide(-3, 5, 0.5, 0.5, 2*PI, 50, 1, GL_LINES,rojo);
    cardioide(-1, 5, 0.5, 0.5, 2*PI, 50, 1, GL_POLYGON,verde);
    cardioide(1, 5, 0.5, 0.5, 2*PI, 50, 1, GL_LINE_LOOP,azul);


    // Caracol con riso
    cardioide(-5, 3.5, 0.5, 1, 2*PI, 100, 1,GL_POINTS,amarillo);
    cardioide(-3, 3.5, 0.5, 1, 2*PI, 100, 1,GL_LINES,rojo);
    cardioide(-1, 3.5, 0.5, 1, 2*PI, 100, 1,GL_POLYGON,verde);
    cardioide(1, 3.5, 0.5, 1, 4*PI, 100, 1,GL_LINE_LOOP,azul);

    
    // Rosas 4
    cardioide(-5, 1, 0, -1, 2*PI, 100, 2,GL_POINTS,amarillo);
    cardioide(-3, 1, 0, -1, 2*PI, 100, 2,GL_LINES,rojo);
    cardioide(-1, 1, 0, -1, 2*PI, 100, 2,GL_POLYGON,verde);
    cardioide(1, 1, 0, -1, 2*PI, 100, 2,GL_LINE_LOOP,azul);

    // Rosas 3
    cardioide(-5, -1, 0, -1, 2*PI, 100, 3,GL_POINTS,amarillo);
    cardioide(-3, -1, 0, -1, 2*PI, 100, 3,GL_LINES,rojo);
    cardioide(-1, -1, 0, -1, 2*PI, 100, 3,GL_POLYGON,verde);
    cardioide(1, -1, 0, -1, 2*PI, 100, 3,GL_LINE_LOOP,azul);

    // lemniscatas
    lemniscatas(-5,-3,0,0.81, 2*PI,5000,2, GL_POINTS,amarillo);
    lemniscatas(-3,-3,0,0.81, 2*PI,5000,2, GL_LINES,rojo);
    lemniscatas(-1,-3,0,0.81, 2*PI,5000,2, GL_POLYGON,verde);
    lemniscatas(1,-3,0,0.81, 2*PI,5000,2, GL_LINE_LOOP,azul);


    glutSwapBuffers();  
}


void inicio()
{   
    int a = 6;
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


    glutCreateWindow("Cardioide");
    inicio();
    glutDisplayFunc(display);
    glutMainLoop();

    return EXIT_SUCCESS; 
}