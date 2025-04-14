#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

/**
 * Dibuja un tablero de líneas sobre un plano 2D.
 *
 * @param size El tamaño total del tablero.
 * @param count La cantidad de divisiones tanto en el eje X como en el eje Y.
 */
void tablero(float size, int count) {
    float dist = size / 2.0f;
    float step = size / count;

    glColor3f(1,1,1);
    glBegin(GL_LINES);
        for (int i = 0; i <= count; i++) {
            float point = -dist + i * step;

            // Líneas verticales
            glVertex2f(point, -dist); glVertex2f(point, dist);

            // Líneas horizontales
            glVertex2f(-dist, point); glVertex2f(dist, point);
        }
    glEnd();
}


void task1(){
    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
    for (int i = 0; i < 9; i++) {
        glColor3f(1, 0, 0);
        glVertex2f(-8 + (2 * i), 8); glVertex2f(-8 + (2 * i), -8);
        glColor3f(0, 1, 0);
        glVertex2f(-8, 8 - (2 * i)); glVertex2f(8, 8 - (2 * i));
    }
    glEnd();
}





/**
 * Dibuja un tablero de líneas sobre un plano 2D.
 *
 * @param x1 Punto en X
 * @param count Punto en Y
 * @param r Distancia entre lineas
 * @param iter Cantidad de subdivisiones
 */
void task2(int x1,int y1,float r=2, int iter=5){
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i <= iter; i++){
        int x = x1 + (r*i);
        int y = y1 - (r*i);
        glVertex2f(x, y1); glVertex2f(x, y1 - (r*iter));
        
        glVertex2f(x1, y); glVertex2f(x1 + (r*iter), y);
        
        glVertex2f(x1, y-(r*iter)); glVertex2f(x1 + (r*iter), y);


    }
    glEnd();
}


void cuadrado(float size, int count){
    float dist = size / 2.0f;
    float step = size / count;

    glColor3f(1,1,1);
    glBegin(GL_LINES);
        for (int i = 0; i <= count/2; i++) {
            float point = -dist + i * step;

            // Líneas verticales
            glVertex2f(point, -dist); glVertex2f(point, dist);

            // Líneas horizontales
            //glVertex2f(-dist, point); glVertex2f(dist, point);
        }
    glEnd();
}

void ejes(){
    glColor3f(1, 0, 1);
    glLineWidth(1);
    task2(-20,20,1,40);
    glBegin(GL_LINES);
    glColor3f(1,0,0);
    glVertex2f(-20,0);glVertex2f(20,0);
    glVertex2f(0,20);glVertex2f(0,-20);
    glEnd();
}

void display(void) {
    glClearColor(0, 0, 0, 0);  
    glClear(GL_COLOR_BUFFER_BIT);

    //tablero(10.0f, 5);
    //ejes();
    glColor3f(1, 1, 0);
    //task2(-9,9,3.2,3);
    cuadrado(5,8);
    
    glutSwapBuffers();  
}


void inicio()
{   
    int a = 10;
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-a,a,-a,a);
    glClearColor(0,0,0,0);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv); 
    glutInitWindowSize(600,600);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);


    glutCreateWindow("ComputaciOn Grafica 1.2");
    inicio();
    glutDisplayFunc(display);
    glutMainLoop();

    return EXIT_SUCCESS; 
}