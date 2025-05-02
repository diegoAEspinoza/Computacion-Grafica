#ifdef _WIN32
#include <windows.h>
#endif
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>
#include <stdlib.h>
#define M_PI 3.141592 /* Definir la variable m_pi*/

float black[]={0,0,0}; float blanco[]={1,1,1}; float cy[]={0,1,1}; float mag[]={1,0,1}; float yell[]={1,1,0.4};
float rosa[]={1,0.2,0.5}; float verde[]={0,1,0.5}; float amarillo[]={0.86,0.83,0.38}; float naranja[]={1, 0.5, 0}; float green[]={0.4,0.5,0.1};
float azul[]={0,0,1}; float azul2[]={0,0.4,0.9}; float red[]={1,0,0};

void inicio(){

glMatrixMode(GL_PROJECTION);
gluOrtho2D(-20,20,-20,20);
glClearColor(0,0,0,0);
}

void lines(int x, int y,int x1, int y1,int x2, int y2, int x3, int y3,int x4, int y4,int x5, int y5,float *rgb)
{
     glColor3fv(rgb);
     glBegin(GL_LINE_LOOP);
     glVertex2d(x,y);
     glVertex2d(x1,y1);
     glVertex2d(x2,y2);
     glVertex2d(x3,y3);
     glVertex2d(x4,y4);
     glVertex2d(x5,y5);
     glEnd();
}

void tri(int x, int y,int x1, int y1,int x2, int y2, float *rgb)
{
     glColor3fv(rgb);
     glBegin(GL_LINE_LOOP);
     glVertex2d(x,y);
     glVertex2d(x1,y1);
     glVertex2d(x2,y2);
     glEnd();
}

void circulo(float x1, float y1,float a, float b, float radio, float *rgb, int patron, int fun, int n)
{
    glColor3fv(rgb);
    GLint i=0;

    switch(patron)
    {
        case 1: glPolygonMode(GL_FRONT_AND_BACK,GL_POINT); break;
        case 2: glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); break;
        case 3: glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); break;
    }

    switch(fun){
        case 1:
            for(i=0; i<n; i++){
                glBegin(GL_POLYGON);
                 for(float Theta = a; Theta < b ; Theta = Theta+0.01)
                    {
                    glVertex2f(x1+radio*cos(Theta),y1+radio*sin(Theta));
                 }
                 glEnd();
                 y1 = y1-4;
            }
        break;

        case 2:
            for(i=0; i<n; i++){
                glBegin(GL_POLYGON);
                 for(float Theta = a; Theta < b ; Theta = Theta+0.01)
                    {
                    glVertex2f(x1+radio*cos(Theta),y1+radio*sin(Theta));
                 }
                 glEnd();
                 x1 = x1+4;
            }
        break;

    }
}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


   glLineWidth(4);
   circulo(0,12,0,2*M_PI,4,cy,3,1,7);
   circulo(3.5,10,0,2*M_PI,4,cy,3,1,6);
   circulo(-3.5,10,0,2*M_PI,4,cy,3,1,6);
   circulo(7,8,0,2*M_PI,4,cy,3,1,5);
   circulo(-7,8,0,2*M_PI,4,cy,3,1,5);
   circulo(10.5,6,0,2*M_PI,4,cy,3,1,4);
   circulo(-10.5,6,0,2*M_PI,4,cy,3,1,4);

   lines(0,16,-14,8,-14,-8,0,-16,14,-8,14,8,blanco);
   tri(0,16,-14,-8,14,-8,blanco);tri(0,-16,-14,8,14,8,blanco);
   lines(0,8,-7,4,-7,-4,0,-8,7,-4,7,4,blanco);
   tri(0,8,-7,-4,7,-4,blanco); tri(0,-8,-7,4,7,4,blanco);
   tri(-7,4,-7,-4,7,4,blanco); tri(7,-4,-7,4,7,-4,blanco);
   lines(-14,-8,14,8,14,-8,-14,8,14,-8,7,-4,blanco);
   lines(-14,-8,14,-8,-7,-4,0,16,7,-4,7,-4,blanco);
   tri(0,-16,-7,4,7,4,blanco);

   glBegin(GL_LINES);
   glVertex2d(0,16);
   glVertex2d(0,-16);
   glEnd();

   glutSwapBuffers();

}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv); //Inicializa la ventana
    glutInitWindowSize(800,900); //Tamaño de la ventana
    glutInitWindowPosition(10,10); //Posición de la ventana
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Geometría Sagrada");
    inicio();
    glutDisplayFunc(display); //Evento renderizado
    glutMainLoop();

    return EXIT_SUCCESS;
}