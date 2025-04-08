#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
// Función de inicialización de OpenGL
void initialize()
{   
    int a = 8;
    
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
    
    /*Tamanio de Lineas o Puntos*/
    glPointSize(5);
    glLineWidth(5);

    /* glBegin(MODO):
        GL_POINTS
        1) GL_LINES
        2) GL_LINE_STRIP
        3) GL_LINE_LOOP
        4) GL_TRIANGLES
        ) GL_TRIANGLE_STRIP
        ) GL_TRIANGLE_FAN
        ) GL_QUADS
        ) GL_QUAD_STRIP
        ) GL_POLYGON 
    */
   /*
   
    // Uno
    glColor3f(0,0,1);
    glBegin(GL_LINES);
        glVertex2f(-4,3);
        glVertex2f(-4,4);
    glEnd();

    glColor3f(0,1,0);
    glBegin(GL_POINTS);
        glVertex2f(-4,3);
        glVertex2f(-4,4);
    glEnd();

    // Dos
    glColor3f(1,0,0);
    glBegin(GL_LINE_STRIP);
        glVertex2f(-3,3);
        glVertex2f(-3,4);
        glVertex2f(-2.5,3.5);
    glEnd();
    glColor3f(0,1,0);
    glBegin(GL_POINTS);
        glVertex2f(-3,3);
        glVertex2f(-3,4);
        glVertex2f(-2.5,3.5);
    glEnd();
    
    // tres
    glColor3f(1,0,0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-2,3);
        glVertex2f(-2,4);
        glVertex2f(-1,3.5);
    glEnd();
    glColor3f(0,1,0);
    glBegin(GL_POINTS);
        glVertex2f(-2,3);
        glVertex2f(-2,4);
        glVertex2f(-1,3.5);
    glEnd();
    
   // cuatro
   glColor3f(1,0,0);
   glBegin(GL_TRIANGLES);
       glVertex2f(-4,2);
       glVertex2f(-4,1);
       glVertex2f(-3.5,1.5);
   glEnd();
   glColor3f(0,1,0);
   glBegin(GL_POINTS);
        glVertex2f(-4,2);
        glVertex2f(-4,1);
        glVertex2f(-3.5,1.5);
   glEnd();

   // cinco
   glColor3f(1,0,0);
   glBegin(GL_TRIANGLE_STRIP);
       glVertex2f(-1,-1);
       glVertex2f(-1,-2);
       glVertex2f(-.5,-3);
       glVertex2f(0,-4);
   glEnd();

   glColor3f(0,1,0);
   glBegin(GL_POINTS);
        glVertex2f(-1,-1);
        glVertex2f(-1,-2);
        glVertex2f(-.5,-3);
        glVertex2f(0,-4);
   glEnd();
   */

    glColor3f(0,0,1);
    glBegin(GL_POLYGON);
        glVertex2f(-7,7);
        glVertex2f(-4,7);
        glVertex2f(-4,4);
        glVertex2f(-7,4);
    glEnd();

    glColor3f(0,1,0);
    glBegin(GL_POLYGON);
        glVertex2f(-2,7);
        glVertex2f(1,7);
        glVertex2f(1,4);
        glVertex2f(-2,4);
    glEnd();

    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
        glVertex2f(3,7);
        glVertex2f(6,7);
        glVertex2f(6,4);
        glVertex2f(3,4);
    glEnd();

    ///
    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
        glVertex2f(-7,1);
        glVertex2f(-4,1);
        glVertex2f(-4,-2);
        glVertex2f(-7,-2);
    glEnd();

    glColor3f(0,0,1);
    glBegin(GL_POLYGON);
        glVertex2f(-2,1);
        glVertex2f(1,1);
        glVertex2f(1,-2);
        glVertex2f(-2,-2);
    glEnd();

    glColor3f(0,1,0);
    glBegin(GL_POLYGON);
        glVertex2f(3,1);
        glVertex2f(6,1);
        glVertex2f(6,-2);
        glVertex2f(3,-2);
    glEnd();

    glutSwapBuffers();
}

// Función principal
int main(int argc, char *argv[])
{   
    int size = 400;
    // Inicializa GLUT y procesa los argumentos de la línea de comandos
    glutInit(&argc, argv);

    glutInitWindowSize(size, size);

    // Define la posición inicial de la ventana en la pantalla (coordenadas X=10, Y=10)
    glutInitWindowPosition(10, 10);

    // Establece el modo de visualización:
    // - `GLUT_RGB`: Usa el modelo de color RGB
    // - `GLUT_DOUBLE`: Activa el doble buffer para evitar parpadeos
    // - `GLUT_DEPTH`: Activa el buffer de profundidad (aunque no se usa en este código)
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    // Crea una ventana con el título "primer codigo"
    glutCreateWindow("Primera Clase");

    // Llama a la función de inicialización
    initialize();

    // Asigna la función `display()` como la encargada de dibujar la escena
    glutDisplayFunc(display);

    // Inicia el bucle principal de GLUT (permanece en ejecución hasta que se cierre la ventana)
    glutMainLoop();

    // Finaliza el programa correctamente
    return EXIT_SUCCESS; // También se podría usar `return 0;`
}
