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
#define PI 3.14159265358979323846

const int segmentos = 100;

float rojo[3]         = {1, 0, 0}, 
      blanco[3]       = {1, 1, 1},
      negro[3]        = {0,0,0};



      
      void drawTangentsToCircle(
        float cx, float cy,
        float radius,
        float x2, float y2
    ) {
        float dx = x2 - cx;
        float dy = y2 - cy;
        float distSq = dx * dx + dy * dy;
        float dist = sqrtf(distSq);
    
        if (dist <= radius) return; // No hay tangentes reales
    
        // Ángulo entre el vector (cx, cy) -> (x2, y2)
        float angleToPoint = atan2f(dy, dx);
    
        // Ángulo de desviación para las tangentes
        float offset = acosf(radius / dist);
    
        // Primer punto de tangencia
        float theta1 = angleToPoint + offset;
        float tx1 = cx + radius * cosf(theta1);
        float ty1 = cy + radius * sinf(theta1);
    
        // Segundo punto de tangencia
        float theta2 = angleToPoint - offset;
        float tx2 = cx + radius * cosf(theta2);
        float ty2 = cy + radius * sinf(theta2);
        
        glColor3fv(blanco); // rojo
        glBegin(GL_POLYGON);
            glVertex2f(x2, y2);
            glVertex2f(tx1, ty1);
            glVertex2f(tx2, ty2);
        glEnd();

        // Dibuja las líneas tangentes
        glColor3fv(negro); // rojo
        glBegin(GL_LINE_LOOP);
            glVertex2f(x2, y2);
            glVertex2f(tx1, ty1);
            glVertex2f(x2, y2);
            glVertex2f(tx2, ty2);
        glEnd();
    }
void drawSector(
        float cx, float cy,
        float tx, float ty,
        float radius,
        float t1, float t2,
        float *RGB) {
        
        glColor3fv(RGB);
        int segments = 100;
        
        glBegin(GL_LINE_LOOP);
        //glVertex2f(cx, cy);
        for (int i = 0; i < segments; ++i) {
            float theta = t1 + i * (t2 - t1) / segments;
            float theta2 = t1 + (i + 1) * (t2 - t1) / segments;
            float x1 = cx + radius * cosf(theta);
            float y1 = cy + radius * sinf(theta);
            float x2 = cx + radius * cosf(theta2);
            float y2 = cy + radius * sinf(theta2);
            glVertex2f(x1, y1);
            glVertex2f(x2, y2);
        }
        glEnd();
        drawTangentsToCircle(cx, cy, radius, tx, ty);
    }























void display(void) {
glClearColor(1, 1, 1, 1);  
glClear(GL_COLOR_BUFFER_BIT);

    //Alas Derecha
    // --Pequeña
    drawSector(
        1.25, -1,
        0.2,0,
        1,
        0, 2*PI,
        negro);
    // --Grande
        drawSector(
            2,1.5,
            0.2,0,
            1.5,
            0, 2*PI,
            negro);
    
    //Alas Izquierda
        // --Pequeña

    drawSector(
            -1.25,-1,
            -0.2,0,
            1,
            0, 2*PI,
            negro);
    
    // --Grande
    drawSector(
        -2,1.5,
        -0.2,0,
        1.5,
        0, 2*PI,
        negro);

glutSwapBuffers();  
}
void inicio()
{   
    int a = 5;
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