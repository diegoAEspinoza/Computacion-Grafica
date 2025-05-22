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




float blanco[3]       = {1, 1, 1},
      negro[3]        = {0,0,0};




void polygon(float x,float y, float r, float n, float *RGB, GLenum modo,float move=0, int op=0){
    glColor3fv(RGB);
    glBegin(modo);

        float angulo = 2 * M_PI / n + move;
        for (int i = 0; i < n; i++) {
            float vx = x + r * cos(i * angulo);
            float vy = y + r * sin(i * angulo);
            glVertex2f(vx, vy);
            if(op!=0){
             glVertex2f(x, y);
            }
        }
    glEnd();
}



void display(void) {
    glClearColor(1, 1, 1, 1);  
    glClear(GL_COLOR_BUFFER_BIT);

    polygon(0,0,4,4,negro,GL_LINE_LOOP,PI/4);


    for (int i = 0; i < 5; i++)
    {
        float r = 4;
        float sep = 0.5;
        polygon(0,0,r-i*sep,4,negro,GL_LINE_LOOP);

    }
    


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
    glutInitWindowPosition(500,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);


    glutCreateWindow("ComputaciOn Grafica 1.2");
    inicio();
    glutDisplayFunc(display);
    glutMainLoop();

    return EXIT_SUCCESS; 
}