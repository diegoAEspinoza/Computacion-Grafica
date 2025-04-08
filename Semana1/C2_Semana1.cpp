#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

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




void cuadrado (float c[2], float l, float *RGB, GLenum MODO){
    float x = c[0], y=c[1];
    glColor3fv(RGB);
    glBegin(MODO);
        glVertex2f(x,y);
        glVertex2f(x+l,y);
        glVertex2f(x+l,y+l);
        glVertex2f(x,y+l);
    glEnd();
}

// Función de inicialización de OpenGL
void initialize()
{   
    int a = 10;
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-a, a, -a, a); 
    glClearColor(0, 0, 0, 0);
}


// Función de renderizado
void display (void)
{
    // Color de Pantalla
    glClearColor(0, 0.1, 0.1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    cuadrado((float[2]){-8,6}, 2, amarillo, GL_POINTS);
    cuadrado((float[2]){-5,6}, 2, rojo,     GL_LINES);
    cuadrado((float[2]){-2,6}, 2, verde,    GL_LINE_STRIP);
    cuadrado((float[2]){1,6},  2, azul,     GL_LINE_LOOP);
    cuadrado((float[2]){4,6},  2, cyan,     GL_TRIANGLES);
    cuadrado((float[2]){-8,3}, 2, magenta,  GL_TRIANGLE_STRIP);
    cuadrado((float[2]){-5,3}, 2, blanco,   GL_TRIANGLE_FAN);
    cuadrado((float[2]){-2,3}, 2, gris,     GL_QUADS);
    cuadrado((float[2]){1,3},  2, naranja,  GL_QUAD_STRIP);
    cuadrado((float[2]){4,3},  2, rosa,     GL_POLYGON);

    /*Tamanio de Lineas o Puntos*/
    glPointSize(5);
    glLineWidth(5);


    glutSwapBuffers();
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
