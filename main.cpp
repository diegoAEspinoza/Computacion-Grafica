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



// Función de renderizado
void display(void)
{
    glClearColor(0,0,0,0);// color de fondo de ventana
    glClear(GL_COLOR_BUFFER_BIT);





    glutSwapBuffers();
    // glFlush();
}

// Función de inicialización de OpenGL
void initialize()
{   
    int a = 8;
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
