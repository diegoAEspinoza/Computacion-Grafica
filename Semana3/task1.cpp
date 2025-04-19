#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <math.h>

void polygon(float c[2], float r, float n, float *RGB, GLenum MODO){
    float x = c[0], y=c[1];

    glColor3fv(RGB);
    glBegin(MODO);
        float angulo = 2 * M_PI / n;
        
        for (int i = 0; i < n-1; i++) {
            float vx = x + r * cos(i * angulo);
            float vy = y + r * sin(i * angulo);
            glVertex2f(vx, vy);
        }
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

    semicircle(-4, 3, 0.5,-0.5*M_PI, 0.5*M_PI, GL_LINE_LOOP);
    semicircle(-2, 3, 0.5, 0.5*M_PI,   2*M_PI, GL_LINE_LOOP);
    semicircle( 0, 3, 0.5,     M_PI, 1.5*M_PI, GL_LINE_LOOP);
    semicircle(-4, 1, 0.5,-0.5*M_PI, 0.5*M_PI, GL_POLYGON);
    semicircle(-2, 1, 0.5, 0.5*M_PI,   2*M_PI, GL_POLYGON);
    semicircle( 0, 1, 0.5,     M_PI, 1.5*M_PI, GL_POLYGON);



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
    glutInitWindowSize(400,400);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);


    glutCreateWindow("ComputaciOn Grafica 1.2");
    inicio();
    glutDisplayFunc(display);
    glutMainLoop();

    return EXIT_SUCCESS; 
}