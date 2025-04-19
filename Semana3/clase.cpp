#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <math.h>


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


void lines(float x, float y){
    glBegin(GL_LINES);
        glVertex2f(x,y);
        glVertex2f(x+5,y);
    glEnd();
}
void semicircle(float x, float y,float r ,float theta1, float theta2, GLenum MODO){
    glBegin(MODO);
    glVertex2d(x,y);
    for (float theta=theta1 ; theta<theta2 ; theta = theta+0.01)
      {
          glVertex2d(x + r*cos(theta), y + r*sin(theta));
       }
    glEnd();
}


void display(void) {
    glClearColor(0, 0, 0, 0);  
    glClear(GL_COLOR_BUFFER_BIT);

    semicircle(-5, 0, 2,0, 1.5*M_PI, GL_LINE_STRIP);
    lines(-5+2*cos(1.5*M_PI),0+2*sin(1.5*M_PI));

    semicircle(-5, 0, 1.5,0, 1.5*M_PI, GL_LINE_STRIP);
    lines(-5+1.5*cos(1.5*M_PI),0+1.5*sin(1.5*M_PI));

    semicircle(-5, 0, 1,0, 1.5*M_PI, GL_LINE_STRIP);
    lines(-5+1*cos(1.5*M_PI),0+1*sin(1.5*M_PI));

    semicircle(-5, 0, 0.5,0, 1.5*M_PI, GL_LINE_STRIP);
    lines(-5+0.5*cos(1.5*M_PI),0+0.5*sin(1.5*M_PI));

    lines(-5,0);
    semicircle(-5, 0, 0.1, 0, 2 * M_PI, GL_LINE_STRIP);



    semicircle(0, -2, 2,M_PI, 2.5*M_PI, GL_LINE_STRIP);
    semicircle(0, -2, 1.5,M_PI, 2.5*M_PI, GL_LINE_STRIP);
    semicircle(0, -2, 1,M_PI, 2.5*M_PI, GL_LINE_STRIP);
    semicircle(0, -2, 0.5,M_PI, 2.5*M_PI, GL_LINE_STRIP);
    semicircle(0, -2.1, 0.1,0, 2*M_PI, GL_LINE_STRIP);



    glutSwapBuffers();  
}







void inicio()
{   
    int a = 10;
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


    glutCreateWindow("ComputaciOn Grafica 1.2");
    inicio();
    glutDisplayFunc(display);
    glutMainLoop();

    return EXIT_SUCCESS; 
}