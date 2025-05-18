// Nombre: Diego A. Espinoza

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
#define PI 3.141592653589793f



float  negro[3]  = {0,0,0};


void drawSector(float cx, float cy, float radius, float rotationAngleRad, const float *RGB, GLenum modo, int segments = 150) {

    glColor3fv(RGB);
    glBegin(modo);
    for (int i = 0; i < segments; ++i) {
        float base_theta = ((float)i / (float)segments) * (2.0f * PI);
        
        float effective_theta = base_theta + rotationAngleRad;
        
        float x1 = cx + radius * cosf(effective_theta);
        float y1 = cy + radius * sinf(effective_theta);
        
        glVertex2f(x1, y1);
    }
    glEnd();
}

void tablero(float size, int count) {
    float dist = size / 2.0f;
    float step = size / count;

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

void display(void) {
    glClearColor(1, 1, 1, 1);  
    glClear(GL_COLOR_BUFFER_BIT);

    // Circulos Grandes
    drawSector(0,0,2.73,0,negro,GL_LINE_LOOP);
    drawSector(0,0,3.5,0,negro,GL_LINE_LOOP);
    // Cuadrado
    tablero(2,1);
    
    //Circulos pequeños
    for (int i = 0; i < 8; i++)
    {
        float r = 3.1;
        float t = PI/4;
        double C[] = {r*cosf(i*t), r*sinf(i*t)};
        drawSector(C[0],C[1],0.3,0,negro,GL_LINE_LOOP);
    }

    // Triangulos
    for (int i = 0; i < 4; i++)
    {
        float r = 1.58;
        float t = PI/2;
                
        double C[] = {r*cosf(i*t), r*sinf(i*t)};

        drawSector(C[0],C[1],1.15,i*PI/2,negro,GL_LINE_LOOP,3);

    }
    
    // X
    for (int i = 0; i < 4; i++)
    {   glColor3b(1,1,1);
        float r = 2.73;
        glBegin(GL_LINES);
            float base_theta = ((float)i / (float)4) * (2.0f * PI);
        
            float effective_theta = base_theta + PI/4;
            
            float x1 = r * cosf(effective_theta);
            float y1 = r * sinf(effective_theta);
            
            glVertex2f(x1, y1);

            glVertex2f(0,0);
        glEnd();
    }

        glBegin(GL_LINES);
            glVertex2f(1,1); glVertex2f(0.67,0); 
            glVertex2f(1,-1); glVertex2f(0.67,0);
            
            glVertex2f(1,-1); glVertex2f(0,-0.67); 
            glVertex2f(-1,-1); glVertex2f(0,-0.67);

            glVertex2f(-1,-1); glVertex2f(-0.67,0); 
            glVertex2f(-1,1); glVertex2f(-0.67,0);

            glVertex2f(-1,1); glVertex2f(0,0.67); 
            glVertex2f(1,1); glVertex2f(0,0.67);

        glEnd();



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


    glutCreateWindow("Mandala Examen");
    inicio();
    glutDisplayFunc(display);
    glutMainLoop();

    return EXIT_SUCCESS; 
}