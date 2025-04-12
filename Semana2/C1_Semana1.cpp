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


void Recta(float c[2], float l, float *RGB, float width = 1, int styles = 0) {
    GLushort patrones[] = {0xFFFF, 0x0101, 0xAAAA, 0x00FF, 0x0C0F, 0x1C47};
    int index = (styles >= 0 && styles <= 5) ? styles : 0;

    glColor3fv(RGB);
    glLineWidth(width);

    glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, patrones[index]);
        glBegin(GL_LINES);
            glVertex2f(c[0], c[1]);
            glVertex2f(c[0] + l, c[1]);
        glEnd();
    glDisable(GL_LINE_STIPPLE);
}



// Función de renderizado
void display(void)
{
    glClearColor(0,0,0,0);// color de fondo de ventana
    glClear(GL_COLOR_BUFFER_BIT);

    Recta((float[2]){-1,3},  2, amarillo, 4, 0);
    Recta((float[2]){-1,2},  2, rojo,     4, 1);
    Recta((float[2]){-1,1},  2, verde,    4, 2);
    Recta((float[2]){-1,0},  2, azul,     4, 3);
    Recta((float[2]){-1,-1}, 2, magenta,  4, 4);
    Recta((float[2]){-1,-2}, 2, aqua,     4, 5);
    Recta((float[2]){-1,-3}, 2, gris,     4, 6);

   
    glutSwapBuffers();
    //glFlush();
}


// Función de inicialización de OpenGL
void initialize()
{   
    int a = 4;
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
    glutDisplayFunc(display);
    initialize();


    



    glutMainLoop();

    return EXIT_SUCCESS; 
}
