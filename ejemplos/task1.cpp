#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <math.h>

#define PI 3.141592f

float crema[3]={1, 0.9, 0.8}, negro[3] = {0,0,0};


void cuadrado(float x, float y, float lado, float *RGB){
    float vx = x+ lado/2;
    float vy = y+ lado/2;

    glColor3fv(RGB);
    glBegin(GL_LINE_LOOP);
        glVertex2f(vx, vy);
        glVertex2f(vx, vy-lado);
        glVertex2f(vx-lado, vy-lado);
        glVertex2f(vx-lado, vy);
    glEnd();
}

void rombo(float x, float y, float lado, float *RGB){
    float a = lado/sqrt(2);
    
    glColor3fv(RGB);
    glBegin(GL_LINE_LOOP);
        glVertex2f(x+a, y);
        glVertex2f(x, y+a);
        glVertex2f(x-a, y);
        glVertex2f(x, y-a);
    glEnd();
}




void display(void) {
    glClearColor(0, 0, 0, 0);  
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(2);

    float x=0;
    float y=0;
    float lado=15;
    float num=4;

    for (int i = 0; i < num; i++)
    {
        float newLado = lado - i*(lado/num);
        cuadrado(x,y,newLado,crema);
        rombo(x,y,newLado/sqrt(2),crema);
    }
    
    

        
    glEnd();

    glutSwapBuffers();  
}


void inicio()
{   
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    int a = 10;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-a,a,-a,a);

}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv); 
    glutInitWindowSize(400,400);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);


    glutCreateWindow("");
    inicio();
    glutDisplayFunc(display);
    glutMainLoop();

    return EXIT_SUCCESS; 
}