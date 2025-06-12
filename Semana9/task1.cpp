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

void tallo(float *RGB,GLenum Modo,float n=100){
    glColor3fv(RGB);
    glBegin(Modo);
    if ( Modo == GL_POLYGON)
    {
        glVertex2f(0, 0);
    }
    
    float ap = 1/n;
    for (int t = 0; t < n; t++)
    {
        glVertex2f(-0.05f + 0.10f * t*ap, 1);
        
        glVertex2f(0.05f, 1.0f - 3.0f * t*ap);
       
        glVertex2f(0.05f - 0.10f * t*ap, -2);
        
        glVertex2f(-0.05f, -2.0f + 3.0f*t*ap );
    }
    glEnd();
}

void flor(GLenum modo){
    tallo(verde, modo);

    cardioide(0,1,0,-1,2*PI,500,6,modo,morado);
    cardioide(0,1,0.1,0,2*PI,50,1,modo,amarillo);

    lemniscatas(0,-1,0,0.81, 2*PI,500,2, modo,verde);
}


void display1(void) {
    glClearColor(0, 0, 0, 0);  
    glClear(GL_COLOR_BUFFER_BIT);
    
    flor(GL_POINTS);

    glutSwapBuffers();  
}

void display2(void){
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    flor(GL_POINTS);

    glTranslated(3,0,0);
    flor(GL_POLYGON);

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
    glutInit(&argc, argv); //Inicializa la ventana
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(400,400); //Tamaño de la ventana

    glutInitWindowPosition(1,1); //Posición de la ventana
    glutCreateWindow("Flor: Figura base");
    glutDisplayFunc(display1); //Evento renderizado
    inicio();

    glutInitWindowPosition(420,1); //Posición de la ventana
    glutCreateWindow("Flor: Traslacion en X");
    glutDisplayFunc(display2); //Evento renderizado
    inicio();

    glutMainLoop();
    return EXIT_SUCCESS;
}