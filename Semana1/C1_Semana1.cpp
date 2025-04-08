#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

void inicio()
{
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1,1,-1,1);
    glClearColor(0,0,0,0);
}

void display(void) {
    glClearColor(0, 0, 0, 0);  // Fondo negro
    glClear(GL_COLOR_BUFFER_BIT);

    int grid_size = 8;  // Tamaño del tablero de ajedrez (8x8)
    float board_size = 1.0f;  // Tamaño total del tablero

    // Dibujar las líneas horizontales
    glColor3f(1.0f, 1.0f, 1.0f);  // Color blanco para las líneas

    for (int i = 0; i <= grid_size; i++) {
        float y = -0.5f + (i * (board_size / grid_size));  // Posición Y de la línea horizontal
        glBegin(GL_LINES);
            glVertex2f(-0.5f, y);  // Esquina izquierda
            glVertex2f(0.5f, y);   // Esquina derecha
        glEnd();
    }

    // Dibujar las líneas verticales
    for (int i = 0; i <= grid_size; i++) {
        float x = -0.5f + (i * (board_size / grid_size));  // Posición X de la línea vertical
        glBegin(GL_LINES);
            glVertex2f(x, -0.5f);  // Esquina inferior
            glVertex2f(x, 0.5f);   // Esquina superior
        glEnd();
    }

    glutSwapBuffers();  // Intercambiar los buffers para mostrar el resultado
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv); // Inicializa la ventana de Opengl
    glutInitWindowSize(400,400);// tamaño de la ventana
    glutInitWindowPosition(10,10);// posicion de la ventana
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);// Especifica el tipo de modo de visualizacion al creae una ventana (activar el buffer de color RGB)


    glutCreateWindow("ComputaciOn Grafica 1.2");//Nombre que se le da ala pantalla
    inicio();
    glutDisplayFunc(display);// nombre de la funcion
    glutMainLoop();// hace que aparezca la ventana

    return EXIT_SUCCESS; // puede colocarse tambien return 0
}