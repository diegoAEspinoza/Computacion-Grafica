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

void drawSector(
        float cx, float cy,
        float tx, float ty,
        float radius,
        float t1, float t2,
        float *RGB, bool op) {
        
        glColor3fv(RGB);
        int segments = 100;
        
        glBegin(GL_LINE_STRIP);
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
        if (op)
        {
            drawTangentsToCircle(cx, cy, radius, tx, ty);
        }
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

void parabola(float Init, float End, float paso, float h, float k, float m, float *RGB, int op){
    switch (op)
    {
    case 1:
        glBegin(GL_LINE_STRIP);
        for (float x = Init; x <= End; x += paso) {
            float y = k - m * std::pow((x - h), 2);
            glVertex2f(x, y);
        }
        glEnd();
        break;
    case 2:
        glBegin(GL_LINE_STRIP);
        for (float y = Init; y <= End; y += paso) {
            float x = k - m * std::pow((y - h), 2);
            glVertex2f(x, y);
        }
        glEnd();
        break;
    }
    

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
glLineWidth(2);



//Alas Derecha
// --Pequeña
drawSector(1.25, -1,0.2,0,1.1,0, 2*PI,negro, true);
// --Grande
drawSector(2,1.5,0.2,0,1.5,0, 2*PI,negro, true);
// Detalles
drawLine(1.75,0,blanco);
drawSector(1.25, -1,0.35,0.1,1,0, 2*PI,negro, true);
drawSector(1.25, -1,0.43,0,.5,0, 2*PI,negro, true);
drawSector(1.25, -1,0.56,-0.15,.25,0, 2*PI,negro, true);

drawSector(2,1.5,0.35,0.15,1.35,0, 2*PI,negro, true);

//Alas Izquierda
// --Pequeña
drawSector(-1.25,-1,-0.2,0,1.1,0, 2*PI,negro, true);

// --Grande
drawSector(-2,1.5,-0.2,0,1.5,0, 2*PI,negro, true);
// Detalles
drawLine(-1.75,0,blanco);
drawSector(-1.25, -1, -0.35,0.1,1,0, 2*PI,negro, true);
drawSector(-1.25, -1,-0.4,0,.5,0, 2*PI,negro, true);
drawSector(-1.25, -1,-0.5,-0.15,.25,0, 2*PI,negro, true);
drawSector(-2,1.5,-0.35,0.15,1.35,0, 2*PI,negro, true);

// Circulos en Alas Grandes
drawSector(1.,0.35,0,0,0.15,0,2*PI,negro,false);
drawSector(1.,0.35,0,0,0.1,0,2*PI,negro,false);

drawSector(1.5,0.35,0,0,0.15,0,2*PI,negro,false);
drawSector(1.5,0.35,0,0,0.1,0,2*PI,negro,false);

drawSector(2,0.35,0,0,0.15,0,2*PI,negro,false);
drawSector(2,0.35,0,0,0.1,0,2*PI,negro,false);

drawSector(-1,0.35,0,0,0.15,0,2*PI,negro,false);
drawSector(-1,0.35,0,0,0.1,0,2*PI,negro,false);

drawSector(-1.5,0.35,0,0,0.15,0,2*PI,negro,false);
drawSector(-1.5,0.35,0,0,0.1,0,2*PI,negro,false);

drawSector(-2,0.35,0,0,0.15,0,2*PI,negro,false);
drawSector(-2,0.35,0,0,0.1,0,2*PI,negro,false);

drawSector(-0.68,1,0,0,0.09,0,2*PI,negro,false);
drawSector(-0.77,1.5,0,0,0.09,0,2*PI,negro,false);

drawSector(0.68,1,0,0,0.09,0,2*PI,negro,false);
drawSector(0.77,1.5,0,0,0.09,0,2*PI,negro,false);

drawSector(2.5,0.6,0,0,0.1,0,2*PI,negro,false);
drawSector(-2.5,0.6,0,0,0.1,0,2*PI,negro,false);

drawSector(-1.5,2.5,0,0,0.1,0,2*PI,negro,false);
drawSector(1.5,2.5,0,0,0.1,0,2*PI,negro,false);

drawSector(-2.4,2.5,0,0,0.1,0,2*PI,negro,false);
drawSector(2.4,2.5,0,0,0.1,0,2*PI,negro,false);

drawSector(-2.9,1.9,0,0,0.1,0,2*PI,negro,false);
drawSector(2.9,1.9,0,0,0.1,0,2*PI,negro,false);

drawSector(-2.9,1,0,0,0.1,0,2*PI,negro,false);
drawSector(2.9,1,0,0,0.1,0,2*PI,negro,false);

// Circulos en Alas Pequeñas
drawSector(1.38,-0.25,0,0,0.1,0,2*PI,negro,false);

drawSector(1.79,-0.48,0,0,0.15,0,2*PI,negro,false);

drawSector(1.99,-1.05,0,0,0.15,0,2*PI,negro,false);
drawSector(1.99,-1.05,0,0,0.1,0,2*PI,negro,false);

drawSector(1.66,-1.6,0,0,0.15,0,2*PI,negro,false);
drawSector(1.66,-1.6,0,0,0.1,0,2*PI,negro,false);

drawSector(1,-1.7,0,0,0.15,0,2*PI,negro,false);
drawSector(1,-1.7,0,0,0.1,0,2*PI,negro,false);

drawSector(0.6,-1.4,0,0,0.15,0,2*PI,negro,false);
drawSector(0.5,-0.87,0,0,0.1,0,2*PI,negro,false);

drawSector(-1.38,-0.25,0,0,0.1,0,2*PI,negro,false);

drawSector(-1.79,-0.48,0,0,0.15,0,2*PI,negro,false);

drawSector(-1.99,-1.05,0,0,0.15,0,2*PI,negro,false);
drawSector(-1.99,-1.05,0,0,0.1,0,2*PI,negro,false);

drawSector(-1.66,-1.6,0,0,0.15,0,2*PI,negro,false);
drawSector(-1.66,-1.6,0,0,0.1,0,2*PI,negro,false);

drawSector(-1,-1.7,0,0,0.15,0,2*PI,negro,false);
drawSector(-1,-1.7,0,0,0.1,0,2*PI,negro,false);

drawSector(-0.6,-1.4,0,0,0.15,0,2*PI,negro,false);
drawSector(-0.5,-0.87,0,0,0.1,0,2*PI,negro,false);


//
drawSector(-2.9,1.5,0,0,0.15,0.5*PI,1.5*PI,negro,false);
parabola(1.5,1.81,0.01,1.5,-3.05,-6,negro,2);
parabola(-2.9,-2.49,0.01,-2.9,1.35,-2.75,negro,1);

drawSector(-2.75,2.25,0,0,0.15,0.5*PI,1.5*PI,negro,false);
parabola(-2.75,-2.2,0.01,-2.75,2.4,2,negro,1);
parabola(-2.75,-2.2,0.01,-2.75,2.1,1,negro,1);

drawSector(-1.95,2.6,0,0,0.15,-0.5*PI,PI,negro,false);
parabola(-2.23,-1.95,0.01,-1.95, 2.45, 6,negro,1);
parabola(-2.23,-2.1,0.01,-1.93, 2.9, 10,negro,1);


drawSector(2.9,1.5,0,0,0.15,-0.5*PI,0.5*PI,negro,false);
parabola(1.5,1.81,0.01,1.5,3.05,6,negro,2);
parabola(2.49,2.9,0.01,2.9,1.35,-2.75,negro,1);

drawSector(2.75,2.25,0,0,0.15,-0.5*PI,0.5*PI,negro,false);
parabola(2.2,2.75,0.01,2.75,2.4,2,negro,1);
parabola(2.2,2.75,0.01,2.75,2.1,1,negro,1);

drawSector(1.95,2.6,0,0,0.15,0,1.5*PI,negro,false);
parabola(1.95,2.23,0.01,1.95, 2.45, 6,negro,1);
parabola(2.1,2.23,0.01,1.93, 2.9, 10,negro,1);





drawSector(0.68,3,0,0,0.2,-0.65*PI,0.65*PI,negro,false);
parabola(0,0.63,0.01,0.6,2.8,8,negro,1);
parabola(0,0.63,0.01,0.6,3.2,9,negro,1);

drawSector(0.68,3,0,0,0.1,-0.5*PI,0.5*PI,negro,false);
parabola(0.35, 0.7, 0.01, 0.7, 2.9, 3, negro,1);
parabola(0.35, 0.67, 0.01, 0.67, 3.1, 6, negro,1);

drawSector(-0.68,3,0,0,0.2,0.35*PI,1.65*PI,negro,false);
parabola(-0.63,0,0.01,-0.6,2.8,8,negro,1);
parabola(-0.63,0,0.01,-0.6,3.2,9,negro,1);

drawSector(-0.68,3,0,0,0.1,0.5*PI,1.5*PI,negro,false);
parabola(-0.7,-0.35,  0.01, -0.7, 2.9, 3, negro,1);
parabola(-0.67,-0.35,  0.01, -0.67, 3.1, 6, negro,1);


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


    glutCreateWindow("Mandala de Mariposa");
    inicio();
    glutDisplayFunc(display);
    glutMainLoop();

    return EXIT_SUCCESS; 
}