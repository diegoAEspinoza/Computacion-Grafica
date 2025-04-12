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


void Recta(float c[2], float l, float a, float *RGB, float width = 1, int styles = 0) {
    GLushort patrones[] = {0xFFFF, 0x0101, 0xAAAA, 0x00FF, 0x0C0F, 0x1C47};
    int index = (styles >= 0 && styles <= 5) ? styles : 0;

    // Definición de segmentos para cada letra (U, N, M, S)
    struct Letter {
        int segments;
        float data[7][4]; // Máximo 7 segmentos (M y S usan más)
    };

    Letter LETRAS[] = {
        // U: 3 segmentos
        {3, {{0,0,0,-1}, {0,-1,1,-1}, {1,-1,1,0}}},
        
        // N: 3 segmentos
        {3, {{0,-1,0,0}, {0,0,1,-1}, {1,-1,1,0}}},
        
        // M: 4 segmentos
        {4, {{0,-1,0,0}, {0,0,0.5,-0.5}, {0.5,-0.5,1,0}, {1,0,1,-1}}},

        // S: 5 segmentos
        {5, {{0,0,1,0}, {0,0,0,-0.5}, {0,-0.5,1,-0.5}, {1,-0.5,1,-1}, {0,-1,1,-1}}}
    };

    float x = c[0], y = c[1];
    float space = 1; // Espacio entre letras

    glColor3fv(RGB);
    glLineWidth(width);

    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, patrones[index]);
    
    glBegin(GL_LINES);
        // Dibuja "UNSM M" (5 letras)
        int orden[] = {0,1,2,3,2};
        
        for (int i = 0; i < 5; ++i) {
            Letter &letra = LETRAS[orden[i]];

            for (int j = 0; j < letra.segments; ++j) {
                float *s = letra.data[j];
                glVertex2f(x + s[0]*a, y + s[1]*l);
                glVertex2f(x + s[2]*a, y + s[3]*l);
            }

            x += a + (i < 4 ? space : 0); // Actualiza posición X
        }
    glEnd();
    glDisable(GL_LINE_STIPPLE);
}



// Función de renderizado
void display(void)
{
    glClearColor(0,0,0,0);// color de fondo de ventana
    glClear(GL_COLOR_BUFFER_BIT);

    Recta((float[2]){-9,9.6} ,  2, 1,amarillo, 4, 0);
    Recta((float[2]){-9,6.6} ,  2, 1,rojo, 4, 1);
    Recta((float[2]){-9,3.6} ,  2, 1,verde, 4, 2);
    Recta((float[2]){-9,0.6} ,  2, 1,azul, 4, 3);
    Recta((float[2]){-9,-2.6},  2, 1,cyan, 4, 4);
    Recta((float[2]){-9,-5.6},  2, 1,magenta, 4, 5);
    
   
    glutSwapBuffers();
    //glFlush();
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
