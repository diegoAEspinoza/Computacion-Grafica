#ifdef _APPLE_
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



void polygon(float c[2], float r, float n,float *RGB, GLenum MODO){
    float x = c[0], y=c[1];

    glColor3fv(RGB);
    glPolygonMode(GL_FRONT_AND_BACK, MODO);
    glBegin(GL_POLYGON);
        float angulo = 2 * M_PI / n;
        for (int i = 0; i < n; i++) {
            float vx = x + r * cos(i * angulo);
            float vy = y + r * sin(i * angulo);
            glVertex2f(vx, vy);
        }
    glEnd();
}


// Función de renderizado
void display(void)
{
    glClearColor(0,0.5,0.5,0);// color de fondo de ventana
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(5);

    polygon((float[2]){0,0}, 3, 8,amarillo, GL_LINE);
    //polygon((float[2]){-3,1}, 3, 4,rojo,     GL_LINE);
    //polygon((float[2]){2,1},  3, 5,verde,    GL_FILL);


    glutSwapBuffers();
    // glFlush();
}

// Función de inicialización de OpenGL
void initialize()
{   
    int a = 10;
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-a, a, -a, a); 
    glClearColor(0, 0, 0, 0);
}


// Función principal
int main(int argc, char *argv[])
{   
    int size = 400;
    
    glutInit(&argc, argv);
    glutInitWindowSize(size, size);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Primera Clase");

    initialize();

    glutDisplayFunc(display);

    glutMainLoop();

    return EXIT_SUCCESS; 
}
