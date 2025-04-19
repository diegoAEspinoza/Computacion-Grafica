#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <math.h>

#define PI 3.141592f

float crema[3]={1, 0.9, 0.8}, negro[3] = {0,0,0};

/*
* @param x      : Punto de incio en eje X
* @param y      : Punto de incio en eje Y
* @param r      : Radio Mayor
* @param n      : Numero de Circulos
* @param angle1 : Angulo de Inicio
* @param angle2 : Angulo de Final
* @param MODO   : Modo de Dibujo
*/
void circle(float x, float y, float r, float n, float angle1, float angle2, GLenum MODO, float *RGB){
    glColor3fv(RGB);
    glBegin(MODO);
        for (int i = 0; i < n; i++)
        {
            float startAngle = angle1 + i*(angle2-angle1)/n;
            float x1 = x + r*cosf(startAngle);
            float y1 = y + r*sinf(startAngle);
           
            float endAngle = angle1 + (i+1)*(angle2-angle1)/n;
            float x2 = x + r*cosf(endAngle);
            float y2 = y + r*sinf(endAngle);
            
            glVertex2f(x1,y1);
            glVertex2f(x2,y2);
        }
        
    glEnd(); 
}

void Sectorcircle(float x, float y, float r, float n, float angle1, float angle2, float *RGB){
    glColor3fv(RGB);
    glBegin(GL_POLYGON);
        glVertex2f(x,y);
        for (int i = 0; i < n; i++)
        {
            float startAngle = angle1 + i*(angle2-angle1)/n;
            float x1 = x + r*cosf(startAngle);
            float y1 = y + r*sinf(startAngle);
           
            float endAngle = angle1 + (i+1)*(angle2-angle1)/n;
            float x2 = x + r*cosf(endAngle);
            float y2 = y + r*sinf(endAngle);
            
            glVertex2f(x1,y1);
            glVertex2f(x2,y2);
        }
        
    glEnd(); 
}

void cuadrado(float x, float y, float radio, float numCircle, float l, float *RGB){
    glColor3fv(RGB);
    glBegin(GL_POLYGON);
        glVertex2f(x, y-(radio/numCircle));
        glVertex2f(x, y-radio);
        glVertex2f(x+l, y-radio);
        glVertex2f(x+l, y-(radio/numCircle));
    glEnd();
}

void lines(float x, float y, float radio, float numCircle, float l, float *RGB){
    glColor3fv(RGB);
    glBegin(GL_LINES);
        for (int i = 1; i < numCircle+1; i++)
        {   
            glVertex2f(x, y - i*(radio/numCircle));
            glVertex2f(x+l, y - i*(radio/numCircle));
        }
}

void graf1(float x, float y, float radio, float numCircle, float l){
    for (int i = 0; i < numCircle; i++)
    {   
        float newRadio = radio - i*(radio/numCircle);
        circle(x, y, newRadio, 50, 0*PI, 2*PI, GL_LINES,crema);
        circle(x+l, y-radio-(radio/numCircle), newRadio, 50, 0*PI, 2*PI, GL_LINES,crema);
    }
    
    cuadrado(x,y,radio,numCircle,l,negro);
    lines(x,y,radio,numCircle,l,crema);

    glEnd();
}

void graf2(float x, float y, float radio, float numCircle, float l){
  

    circle(x, y, radio, 50, 0*PI, 2*PI, GL_POLYGON, crema);
    circle(x+l, y-radio-(radio/numCircle), radio, 50, 0*PI, 2*PI, GL_POLYGON,crema);
    circle(x, y, (radio/numCircle), 50, 0*PI, 2*PI, GL_POLYGON, negro);
    circle(x+l, y-radio-(radio/numCircle), (radio/numCircle), 50, 0*PI, 2*PI, GL_POLYGON,negro);

    for (int i = 0; i < numCircle; i++)
    {   
        float newR1 = radio - i*(radio/numCircle);
        circle(x, y, newR1, 50, 0*PI, 2*PI, GL_LINES, negro);
        circle(x+l, y-radio-(radio/numCircle), newR1, 50, 0*PI, 2*PI, GL_LINES,negro);
    }
    
    cuadrado(x,y,radio,numCircle,l,crema);
    lines(x,y,radio,numCircle,l,negro);
}

void graf3(float x, float y, float radio, float numCircle){

    float x1 = x+radio+radio/numCircle, x2 = x+2*(radio+radio/numCircle);


    for (int i = 0; i < numCircle; i++)
    {   
        float newRadio = radio - i*(radio/numCircle);
        circle(x, y, newRadio, 50, 0*PI, 2*PI, GL_LINES,crema);
        circle(x1, y, newRadio, 50, 0*PI, 2*PI, GL_LINES,crema);
        circle(x2, y, newRadio, 50, 0*PI, 2*PI, GL_LINES,crema);
    }
   
    for (int i = 0; i < numCircle; i++)
    {   
        float newRadio = radio - i*(radio/numCircle);
        circle(x, y, newRadio, 50, -0.6*PI, 0.3*PI, GL_POLYGON,negro);
        circle(x1, y, newRadio, 50, 0*PI, 0.9*PI, GL_POLYGON,negro);
        circle(x2, y, newRadio, 50, 0.65*PI, 1.4*PI, GL_POLYGON,negro);
    }

    for (int i = 0; i < numCircle; i++)
    {   
        float newRadio = radio - i*(radio/numCircle);
        circle(x, y, newRadio, 50, -0.6*PI, 0*PI, GL_LINES,crema);
        circle(x1, y, newRadio, 50, 0*PI, 1*PI, GL_LINES,crema);
        circle(x2, y, newRadio, 50, 1*PI, 1.5*PI, GL_LINES,crema);
    }

    circle(x, y, radio/numCircle, 50, 0*PI, 2*PI, GL_LINES,crema);
    circle(x1, y, radio/numCircle, 50, 0*PI, 2*PI, GL_LINES,crema);
    circle(x2, y, radio/numCircle, 50, 0*PI, 2*PI, GL_LINES,crema);
}

void graf4(float x, float y, float radio, float numCircle){
    float x1 = x+radio+radio/numCircle, x2 = x+2*(radio+radio/numCircle);

    circle(x, y, radio, 50, 0*PI, 2*PI, GL_POLYGON,crema);
    circle(x1, y, radio, 50, 0*PI, 2*PI, GL_POLYGON,crema);
    circle(x2, y, radio, 50, 0*PI, 2*PI, GL_POLYGON,crema);
    for (int i = 0; i < numCircle; i++)
    {   
        float newRadio = radio - i*(radio/numCircle);
        circle(x, y, newRadio, 50, 0*PI, 2*PI, GL_LINES,negro);
        circle(x1, y, newRadio, 50, 0*PI, 2*PI, GL_LINES,negro);
        circle(x2, y, newRadio, 50, 0*PI, 2*PI, GL_LINES,negro);
    }
    
    Sectorcircle(x, y, radio, 50, -0.6*PI, 0.3*PI,crema);
    Sectorcircle(x1, y, radio, 50, 0*PI, 0.9*PI,crema);
    Sectorcircle(x2, y, radio, 50, 0.7*PI, 1.4*PI,crema);
   
    for (int i = 0; i < numCircle; i++)
    {   
        float newRadio = radio - i*(radio/numCircle);
        circle(x, y, newRadio, 50, -0.6*PI, 0*PI, GL_LINES,negro);
        circle(x1, y, newRadio, 50, 0*PI, 1*PI, GL_LINES,negro);
        circle(x2, y, newRadio, 50, 1*PI, 1.5*PI, GL_LINES,negro);
    }

    circle(x, y, radio/numCircle, 50, 0*PI, 2*PI, GL_LINES,negro);
    circle(x2, y, radio/numCircle, 50, 0*PI, 2*PI, GL_LINES,negro);
}


void display(void) {
    glClearColor(0, 0, 0, 0);  
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(2);


    graf1(-15,10,4,6,8);
    graf2(-15,1,4, 6, 8);
    graf3(2,10,4,5);

    graf4(2,1,4,5);
    
        
    glEnd();

    glutSwapBuffers();  
}


void inicio()
{   
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    int a = 20;
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