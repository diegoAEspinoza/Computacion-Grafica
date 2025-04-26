#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <math.h>

#define PI 3.141592f


void display(void) {
    glClearColor(0, 0, 0, 0);  
    glClear(GL_COLOR_BUFFER_BIT);

    // Cardioide
    glBegin(GL_LINE_STRIP);
    for(float theta = 0.0f;theta <=2*PI;theta+=0.01f){
        float r= 0.25f*(1.0f-sin(theta));
        float x= r*cos(theta);
        float y= r*sin(theta);
        glVertex2f(1+x,1+y);
    }
    glEnd();
    
    // Caracol con rizo
    glBegin(GL_LINE_STRIP);
    for(float theta = 0.0f;theta <=2*PI;theta+=0.01f){
        float r= 0.25f- 0.6f*sin(theta);
        float x= r*cos(theta);
        float y= r*sin(theta);
        glVertex2f(-1+x,-1+y);
    }
    glEnd();
    

    // Rosa 4
    glBegin(GL_LINE_STRIP);
    for (float theta = 0.0f; theta <= 2 * PI; theta += 0.01f) {
        float r = 0.4f *sin(theta*2);
        float vx = r * cos(theta);
        float vy = r * sin(theta);
        glVertex2f(-1+ vx, 1 + vy );
    }
    glEnd();


    // Rosa 3
    glBegin(GL_LINE_STRIP);
    for (float theta = 0.0f; theta <= 2 * PI; theta += 0.01f) {
        float r = 0.5f *sin(theta*3);
        float vx = r * cos(theta);
        float vy = r * sin(theta);
        glVertex2f(1 + vx, -1 + vy );
    }
    glEnd();

    glutSwapBuffers();  
}


void inicio()
{   
    int a = 2;
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