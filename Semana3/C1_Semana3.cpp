// NOmbre: Diego Alexhander Espinoza Huaman

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

/*
 * Dibujar nodos en relacion con coordenadas polares
 *
 * @param c[2]: Coordenadas de inicio (X,Y)
 * @param r: Radio de la circunferencia
 * @param n: Cantidad de Nodos
 * @param RGB: Color establecido
 * @param Modo: GL_POINT  or GL_LINE  or GL_FILL
 */
    void polygon(float c[2], float r, float n, float *RGB, GLenum MODO){
        float x = c[0], y=c[1];
    
        glColor3fv(RGB);
        //glPolygonMode(GL_FRONT_AND_BACK, MODO);
        glBegin(MODO);
            float angulo = 2 * M_PI / n;
            
            for (int i = 0; i < n-1; i++) {
                float vx = x + r * cos(i * angulo);
                float vy = y + r * sin(i * angulo);
                glVertex2f(vx, vy);
            }
            glVertex2f(x, y);
            glVertex2f(x + r * cos(0), y + r * sin(0));
        glEnd();
    }



// Función de renderizado
void display(void)
{   
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glPointSize(2);
    polygon((float[2]){-6,6},  1.5, 10, amarillo, GL_POINTS);
    polygon((float[2]){-2,6},  1.5, 10, rojo,     GL_LINES);
    polygon((float[2]){2,6},   1.5, 10, verde,    GL_LINE_STRIP);
    polygon((float[2]){6,6},   1.5, 10, azul,     GL_LINE_LOOP);
    polygon((float[2]){-6,2},  1.5, 10, cyan,     GL_POLYGON);
    polygon((float[2]){-2,2},  1.5, 10, magenta,  GL_LINE_LOOP);
    polygon((float[2]){2,2},   1.5, 10, blanco,   GL_TRIANGLES);
    polygon((float[2]){6,2},   1.5, 10, gris,     GL_TRIANGLE_STRIP);
    polygon((float[2]){-6,-2}, 1.5, 10, naranja,  GL_TRIANGLE_FAN);
    polygon((float[2]){-2,-2}, 1.5, 10, rosa,     GL_QUADS);
    polygon((float[2]){2,-2},  1.5, 10, marron,   GL_QUAD_STRIP);



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
    glutCreateWindow("AEA");

    initialize();

    glutDisplayFunc(display);

    glutMainLoop();

    return EXIT_SUCCESS; 
}
