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

float black[] = {0,0,0}, white[]={1,1,1}, blue[] = {0,0,1}, marron[] = {0.5,0.35,0.05};
float rojo[] = {1,0,0}, verde[]={0,1,0}, amarillo[]={1,1,0};
float cyan[]={0,1,1}, pink[]={1,0.5,0.5}, orange[]={1,0.5,0};

void Linea(float *X0, float *X1, float *C, float A = 1, int f = 1, int P =0)
{ glColor3fv(C);
  glLineWidth(A);
  glEnable(GL_LINE_STIPPLE);
   switch (P)
    {case 1: glLineStipple (f, 0x0101); break;
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


void Ejes(int c)
{
float P[]={-20.0,0.0,0.0} , P1[]={20.0,0.0,0.0};
float P2[]={0.0,-20.0,0.0}, P3[]={0.0,20.0,0.0};
float P4[]={0.0,0.0,-20.0} , P5[]={0.0,0.0,20.0};
float C1[]={1,0,0}, C2[]={0,0,1}, C3[]={0,1,0};
      switch (c)
      { // linea punteada
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
void circulo(float x, float y, float a, float b, float r, GLenum modo)
{
    glBegin(modo);
    glVertex2f(x,y);
    for( float T=a;T<b;T=T+0.01)
    {
     glVertex2f(r*cos(T)+x,r*sin(T)+y);
    }
    glEnd();

}

void Petalos(float x, float y, float N, float i, float f, int R,GLenum modo)
{
     glBegin(modo);
        for (float T=i ; T<f ; T = T + 0.01)
            {
                glVertex2f(x+R*sin(N*T)*cos(T),y+R*sin(N*T)*sin(T));
            }
    glEnd();
}

void hoja(float x,float y,int i, float t,float r, GLenum modo)
 {
    glBegin(modo);
    glVertex2f(x,y);
    for (float T=i; T<t;T=T+0.01)
    {
        glVertex2f(r*sqrt(cos(2*T))*cos(T)+x,r*sqrt(cos(2*T))*sin(T)+y);
    }
    glEnd();
 }

void tallo(GLenum modo){
    glBegin(modo);
    for(int i=0; i<1; i+=0.05){
        
    }
    glEnd();
}


void flor(GLenum modo)
{
    glLineWidth(7);
    glColor3f(0,1,0);
    if(modo == GL_POINTS){tallo(GL_LINES);}
    else{tallo(GL_POLYGON);}

    hoja(0,-4,0,2*M_PI,4,modo);
    glColor3f(1,0,0);
    Petalos(0,3,6,0,2*M_PI,4, modo);
    glColor3f(1,1,0);
    circulo(0,3, 0,2*M_PI,0.5, modo);

}


void display1(void)
{
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    //gluLookAt(0,0,15,0,0,0,0,1,0);
    Ejes(0);
    flor(GL_POINTS);
    glutSwapBuffers();
}


void display2(void)
{
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    //gluLookAt(0,0,15,0,0,0,0,1,0);
    Ejes(0);
    flor(GL_POINTS);

    glTranslated(8,0,0);
    flor(GL_POLYGON);

    glutSwapBuffers();
}





static void key(unsigned char key, int x, int y)
{ switch (key)
    {case 27 : // tecla Esc
     case 'q':
         {
         exit(EXIT_SUCCESS); // Terminar la aplicación
         break;
         }
    }
glutPostRedisplay(); // llama a la función encargada de renderizar la escena para dicha ventana.
}

void reshape (int w,int h)
{
    glViewport(0,0,(GLsizei) w,(GLsizei) h);
    glMatrixMode(GL_PROJECTION); // activa la matriz de proyeccion
    glLoadIdentity(); // limpia la ventana
    glOrtho(-20,20,-20*h/w,20*h/w,-20,20);// activa la matriz de modelado que se quiere ver.
   // glFrustum(-1,1,-1,1,1.5,20);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv); //Inicializa la ventana
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(400,400); //Tamaño de la ventana

    glutInitWindowPosition(1,1); //Posición de la ventana
    glutCreateWindow("Flor: Figura base");
    glutDisplayFunc(display1); //Evento renderizado
    glutReshapeFunc(reshape);
    glutKeyboardFunc(key);//control del teclado

    glutInitWindowPosition(420,1); //Posición de la ventana
    glutCreateWindow("Flor: Traslacion en X");
    glutDisplayFunc(display2); //Evento renderizado
    glutReshapeFunc(reshape);
    glutKeyboardFunc(key);//control del teclado


    glutMainLoop();
    return EXIT_SUCCESS;
}