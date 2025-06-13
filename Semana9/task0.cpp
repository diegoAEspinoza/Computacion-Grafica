#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<cmath>
#include <stdlib.h>

void key(unsigned char key, int x, int y)
{
    switch (key) {
    case 27 : // tecla Esc
    case 'q': {
        exit(EXIT_SUCCESS); // Terminar la aplicación
        break;
        }
    }
    glutPostRedisplay();
}

void Linea(float *X0, float *X1, float *C, float A = 1, int f = 1, int P = 0)
{
    glColor3fv(C);
    glLineWidth(A);
    glEnable(GL_LINE_STIPPLE);
    switch (P){
        case 1: glLineStipple (f, 0x0101); break;
        case 2: glLineStipple (f, 0xAAAA); break;
        case 3: glLineStipple (f, 0x00FF); break;
        case 4: glLineStipple (f, 0x0c0F); break;
        case 5: glLineStipple (f, 0x1C47); break;
        default: glLineStipple (f, 0xFFFF); break;
    }
    glBegin(GL_LINES);
    glVertex3fv(X0);
    glVertex3fv(X1);
    glEnd();
    glDisable(GL_LINE_STIPPLE);
    //glLineWidth(1);
}

void Ejes(int c){
    float P[]={-20.0,0.0,0.0} , P1[]={20.0,0.0,0.0};
    float P2[]={0.0,-20.0,0.0}, P3[]={0.0,20.0,0.0};
    float P4[]={0.0,0.0,-20.0} , P5[]={0.0,0.0,20.0};
    float C1[]={1,0,0}, C2[]={0,0,1}, C3[]={0,1,0};
    switch (c){ // linea punteada
    case 0:{
        Linea(P,P1,C1,2,2,1);
        Linea(P2,P3,C2,2,2,1);
        Linea(P4,P5,C3,2,2,1);
        break;
    }
    default :{ // linea solida de grosor c
        Linea(P,P1,C1,c);
        Linea(P2,P3,C2,c);
        Linea(P4,P5,C3,c);
        }
    }
}
void Circulo(float x,float y, float a, float b,float r,GLenum modo)
{
    glBegin(modo);
    glVertex2f(x,y);
    for (float T=a ; T<b ; T = T + 0.01)
    {
        glVertex2f(x+r*cos(T),y+r*sin(T));
    }
    glEnd();
}

void rosas(float x,float y,float n,float i,float f,float r,GLenum modo)
{
    glBegin(modo);
    //glVertex2f(x,y);
    for(float a=i;a<f;a=a+0.01)
    {
        glVertex2f(r*sin(n*a)*cos(a)+x,r*sin(n*a)*sin(a)+y);
    }
    glEnd();
}

void lemniscata(float x,float y,float i,float f,float r,GLenum modo)
{
    glBegin(modo);
    glVertex2f(x,y);
    for(float a=i;a<f;a=a+0.01)
    {
        glVertex2f(r*sqrt(cos(2*a))*cos(a)+x,r*sqrt(cos(2*a))*sin(a)+y);
    }
    glEnd();
}

void flor(GLenum modo)
{
    glLineWidth(7);
    glColor3f(0,1,0);
    glBegin(GL_LINES);
    glVertex2f(0,3);
    glVertex2f(0,-6);
    glEnd();
    lemniscata(0,-4,0,2*M_PI,4,modo);
    glColor3f(1,0,0);
    rosas(0,3,6,0,2*M_PI,4,modo);
    glColor3f(1,1,0);
    Circulo(0,3,0,2*M_PI,0.5,modo);
}

void display(void)
{
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt (0, 0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    Ejes(1);
    //glTranslated(5,0,0);
    //glRotated(60,0,1,0);
    flor(GL_POINTS);

    glutSwapBuffers();
}

void display1(void)
{
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt (0, 0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    Ejes(1);

    flor(GL_POINTS);

    glTranslated(10,0,0);
    flor(GL_POLYGON);

    glutSwapBuffers();
}

void display2(void)
{
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt (0, 0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    Ejes(1);

    flor(GL_POINTS);
    glTranslated(0,7,0);
    flor(GL_POLYGON);

    glutSwapBuffers();
}

void display3(void)
{
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt (0, 0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    Ejes(1);

    flor(GL_POINTS);
    glTranslated(0,0,7);
    flor(GL_POLYGON);

    glutSwapBuffers();
}

void display4(void)
{
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt (0, 0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    Ejes(1);

    flor(GL_POINTS);
    glTranslated(13,0,-9);
    flor(GL_POLYGON);
    glTranslated(-23,0,5);
    flor(GL_POLYGON);

    glutSwapBuffers();
}

void display5(void)
{
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt (0, 0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    Ejes(0);
    flor(GL_POINTS);
    glTranslated(10,0,0);
    glRotated(45,0,0,1);
    Ejes(1);
    flor(GL_POLYGON);


    glutSwapBuffers();
}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glFrustum (-1.5, 1.5, -1.5, 1.5, 1.5, 25.0);
    glMatrixMode (GL_MODELVIEW);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(300,300);

    glutInitWindowPosition(1,1);
    glutCreateWindow("Primer codigo");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(key);

    glutInitWindowPosition(420,1);
    glutCreateWindow("Segundo codigo");
    glutDisplayFunc(display1);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(key);

    glutInitWindowPosition(840,1);
    glutCreateWindow("Tercer codigo");
    glutDisplayFunc(display2);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(key);

    glutInitWindowPosition(1,390);
    glutCreateWindow("Cuarto codigo");
    glutDisplayFunc(display3);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(key);

    glutInitWindowPosition(420,390);
    glutCreateWindow("Quinto codigo");
    glutDisplayFunc(display4);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(key);

    glutInitWindowPosition(840,390);
    glutCreateWindow("Sexto codigo");
    glutDisplayFunc(display5);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(key);

    glutMainLoop();
    return EXIT_SUCCESS;
}