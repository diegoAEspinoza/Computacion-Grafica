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
        crema[3]        = {1, 0.9, 0.8},
        negro[3]        = {0,0,0};

float black[]={1,1,1};
double C[]={0,0};

void Circunferencia(double *XY, float R, float *rgb, int M, float T){
    glColor3fv(rgb);
    switch (M) {
        case 2: {
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            glPointSize(T); break;
        }
        case 3: {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glLineWidth(T); break;
        }
        default: {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
    }
    glBegin(GL_POLYGON);
    float angulo = 2 * PI / 50;

        for (float i = 0; i <= 100 ; i++)
        glVertex2f(R*cos(i*angulo) + XY[0], R*sin(i*angulo) + XY[1]);
    glEnd();
}
        

    
    void display(void) {
        glClearColor(0, 0, 0, 0);  
        glClear(GL_COLOR_BUFFER_BIT);
        
        Circunferencia(C, 0.80, black, 3, 1);
        Circunferencia(C, 0.75, black, 3, 1);
        Circunferencia(C, 0.50, black, 3, 1);

        for (int i = 0; i < 8; i++) {
            double C1[] = { 0.5*cos(i*PI/4) , 0.5*sin(i*PI/4) };
            Circunferencia(C1, 0.07, black, 3, 1);
            Circunferencia(C1, 0.13, black, 3, 1);
            Circunferencia(C1, 0.19, black, 3, 1);
            }
        
        for (int i = 0; i < 8; i++) {
            double C2[] = { 0.16*cos(i*PI/4) , 0.16*sin(i*PI/4) };
            Circunferencia(C2, 0.14 , black, 3, 1);
            }

        for (int i = 0; i < 8; i++) {
            double C3[] = { 0.62*cos((2*i-1)*PI/8) , 0.62*sin((2*i-1)*PI/8) };
            Circunferencia(C3, 0.02, black, 3, 1);
            Circunferencia(C3, 0.05, black, 3, 1);
            }
        glutSwapBuffers();  
    }
    
    
    void inicio()
    {   
        int a = 1;
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