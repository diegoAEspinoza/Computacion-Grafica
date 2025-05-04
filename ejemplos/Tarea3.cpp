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

float blanco[3]       = {1, 1, 1},
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
        glColor3fv(negro); 
        glBegin(GL_LINE_LOOP);
            glVertex2f(x2, y2);
            glVertex2f(tx1, ty1);
            glVertex2f(x2, y2);
            glVertex2f(tx2, ty2);
        glEnd();
    }
void drawCircle(float cx, float cy, float radius, float *RGB) {
    int segments = 100; 

    glColor3fv(blanco);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < segments; ++i) {
        float theta = (i * (2*PI) / segments) ;
        float x1 = cx + radius * cosf(theta);
        float y1 = cy + radius * sinf(theta);
        glVertex2f(x1, y1);
    }
    glEnd();


    glColor3fv(RGB);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; ++i) {
        float theta = (i * (2*PI) / segments) ;
        float x1 = cx + radius * cosf(theta);
        float y1 = cy + radius * sinf(theta);
        glVertex2f(x1, y1);
    }
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

void dibujarContornoElipse(
        float cx, float cy,
        float rx, float ry,
        float *RGB)
    {
        int segments = 100; 

        glColor3fv(blanco);   
    
        glBegin(GL_TRIANGLE_FAN);
        for (int i = 0; i < segments; i++) {
            float theta = 2.0f * PI * float(i) / float(segments);
    
            float x = rx * cosf(theta);
            float y = ry * sinf(theta); 
    
            glVertex2f(x + cx, y + cy);
        }
        glEnd(); 

        glColor3fv(RGB);   
    
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < segments; i++) {
            float theta = 2.0f * PI * float(i) / float(segments);
    
            float x = rx * cosf(theta);
            float y = ry * sinf(theta); 
    
            glVertex2f(x + cx, y + cy);
        }
        glEnd(); 
    }

    void drawLine(float cx, float cy, float *RGB){
        glColor3fv(RGB);
        glBegin(GL_LINE_LOOP);
        glBegin(GL_LINES);
            glVertex2f(0,0);
            glVertex2f(cx,cy);
        glEnd();
        }

void parabola(float xInit, float xEnd, float paso, float h, float k, float m, float *RGB){
    glColor3fv(RGB);
    glBegin(GL_LINE_STRIP);
    for (float x = xInit; x <= xEnd; x += paso) {
        float y = k- m * std::pow((x - h), 2);
        glVertex2f(x, y);
    }
    glEnd();
}

void drawHeart(float cx, float cy, float scaleX, float scaleY, float rotationDegrees = 0.0f, float step = 0.01f) {
    float angleRad = rotationDegrees * (PI / 180.0f); // convertir a radianes

    glBegin(GL_LINE_LOOP);

    for (float t = 0.0f; t <= 2 * PI; t += step) {
        // Coordenadas originales del corazón
        float x = 16 * pow(sin(t), 3);
        float y = 13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t);

        // Aplicar escala
        x *= scaleX / 20.0f;
        y *= scaleY / 20.0f;

        // Aplicar rotación alrededor del origen
        float rotatedX = x * cos(angleRad) - y * sin(angleRad);
        float rotatedY = x * sin(angleRad) + y * cos(angleRad);

        // Trasladar al centro (cx, cy)
        glVertex2f(cx + rotatedX, cy + rotatedY);
    }

    glEnd();
}

void display(void) {
glClearColor(1, 1, 1, 1);  
glClear(GL_COLOR_BUFFER_BIT);




    //Alas Derecha
    // --Pequeña
    drawSector(
    1.25, -1,
    0.2,0,
    1.1,
    0, 2*PI,
    negro);


    // --Grande
    drawSector(
    2,1.5,
    0.2,0,
    1.5,
    0, 2*PI,
    negro);

        
    drawLine(1.75,0,blanco);
    drawSector(
        1.25, -1,
        0.35,0.1,
        1,
        0, 2*PI,
        negro);
        drawSector(
            1.25, -1,
            0.43,0,
            .5,
            0, 2*PI,
            negro);
        drawSector(
            1.25, -1,
            0.56,-0.15,
            .25,
            0, 2*PI,
            negro);

    drawSector(
        2,1.5,
        0.35,0.15,
        1.35,
        0, 2*PI,
        negro);
    //Alas Izquierda
    // --Pequeña

    drawSector(
    -1.25,-1,
    -0.2,0,
    1.1,
    0, 2*PI,
    negro);

    // --Grande
    drawSector(
    -2,1.5,
    -0.2,0,
    1.5,
    0, 2*PI,
    negro);

    drawLine(-1.75,0,blanco);

    drawSector(
        -1.25, -1,
        -0.35,0.1,
        1,
        0, 2*PI,
        negro);
        
        drawSector(
            -1.25, -1,
            -0.4,0,
            .5,
            0, 2*PI,
            negro);
        drawSector(
            -1.25, -1,
            -0.5,-0.15,
            .25,
            0, 2*PI,
            negro);
    
    drawSector(
            -2,1.5,
            -0.35,0.15,
            1.35,
            0, 2*PI,
            negro);
//
drawCircle(1.,0.35,0.15,negro);
drawCircle(1.,0.35,0.1,negro);

drawCircle(1.5,0.35,0.15,negro);
drawCircle(1.5,0.35,0.1,negro);

drawCircle(2.,0.35,0.15,negro);
drawCircle(2.,0.35,0.1,negro);

drawCircle(-1,0.35,0.15,negro);
drawCircle(-1,0.35,0.1,negro);

drawCircle(-1.5,0.35,0.15,negro);
drawCircle(-1.5,0.35,0.1,negro);

drawCircle(-2,0.35,0.15,negro);
drawCircle(-2,0.35,0.1,negro);

drawCircle(-0.68,1,0.09,negro);
drawCircle(-0.77,1.5,0.09,negro);
//

drawCircle(1.38,-0.25,0.1,negro);

drawCircle(1.79,-0.48,0.15,negro);

drawCircle(1.99,-1.05,0.15,negro);
drawCircle(1.99,-1.05,0.1,negro);

drawCircle(1.66,-1.6,0.15,negro);
drawCircle(1.66,-1.6,0.1,negro);

drawCircle(1.,-1.7,0.15,negro);
drawCircle(1.,-1.7,0.1,negro);

drawCircle(0.6,-1.4,0.15,negro);

drawCircle(0.5,-0.87,0.1,negro);

drawCircle(0.68,1,0.09,negro);
drawCircle(0.77,1.5,0.09,negro);

// --
drawCircle(-1.38,-0.25,0.1,negro);

drawCircle(-1.79,-0.48,0.15,negro);

drawCircle(-1.99,-1.05,0.15,negro);
drawCircle(-1.99,-1.05,0.1,negro);

drawCircle(-1.66,-1.6,0.15,negro);
drawCircle(-1.66,-1.6,0.1,negro);

drawCircle(-1.,-1.7,0.15,negro);
drawCircle(-1.,-1.7,0.1,negro);

drawCircle(-0.6,-1.4,0.15,negro);

drawCircle(-0.5,-0.87,0.1,negro);
//
    drawCircle(0.68,3,0.2,negro);
    drawCircle(0.49,2.95,0.18,blanco);
    parabola(0,0.63,0.01,0.6,2.8,8,negro);
    parabola(0,0.63,0.01,0.6,3.2,9,negro);
    
    drawCircle(0.68,3,0.1,negro);
    drawCircle(0.67,2.99,0.09,blanco);
    parabola(0.35, 0.7, 0.01, 0.7, 2.9, 3, negro);
    parabola(0.35, 0.67, 0.01, 0.67, 3.1, 6, negro);
//

    drawCircle(-0.68,3,0.2,negro);
    drawCircle(-0.49,2.95,0.18,blanco);
    parabola(-0.63,0,0.01,-0.6,2.8,8,negro);
    parabola(-0.63,0,0.01,-0.6,3.2,9,negro);

    drawCircle(-0.68,3,0.1,negro);
    drawCircle(-0.67,2.99,0.09,blanco);
    parabola(-0.7,-0.35,  0.01, -0.7, 2.9, 3, negro);
    parabola(-0.67,-0.35,  0.01, -0.67, 3.1, 6, negro);

//
    drawHeart(-1.6, 1.35, 1.1f, 1.5, 50.0f);
    drawHeart(-1.45, 1.2, 0.65f, 0.9, 50.0f);

    drawHeart(1.6, 1.35, 1.1f, 1.5, -48.0f);
    drawHeart(1.45, 1.2, 0.65f, 0.9, -48.0f);

    // Cuerpo
    dibujarContornoElipse(0, -0.5, 0.2, 1.5, negro);

glutSwapBuffers();  
}
void inicio()
{   
    int a = 4;
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-a,a,-a,a);
    glClearColor(0,0,0,0);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv); 
    glutInitWindowSize(800,800);
    glutInitWindowPosition(500,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);


    glutCreateWindow("ComputaciOn Grafica 1.2");
    inicio();
    glutDisplayFunc(display);
    glutMainLoop();

    return EXIT_SUCCESS; 
}