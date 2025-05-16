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
#define PI 3.141592f




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
      aqua[3]         = {0, 1, 0.5f},
      crema[3]        = {1, 0.9, 0.8},
      negro[3]        = {0,0,0};

void circle(float x, float y, float r, float w=1.0f){
    glColor3fv(negro);
    glLineWidth(w);
    glBegin(GL_LINE_LOOP);
        float angulo = 2 * M_PI / 150;
        for (int i = 0; i < 150; i++) {
            float vx = x + r * cos(i * angulo);
            float vy = y + r * sin(i * angulo);
            glVertex2f(vx, vy);
        }
    glEnd();
}

void cruz(float r, float large, float angleSet,float angleCircle, float w=1.0f){
    glLineWidth(w);

    for (int i = 0; i < 50; i++) {
        float angle = i * 2 * PI / 26 + PI/26;

        float x = r * cosf(angle);
        float y = r * sinf(angle);

        float tx = -sinf(angle), ty =  cosf(angle);  

        float xI = x + tx * angleCircle, yI = y + ty * angleCircle;

        float xD = x - tx * angleCircle, yD = y - ty * angleCircle;

        float x1 = xI + cosf(angle - angleSet) * large, y1 = yI + sinf(angle - angleSet) * large;

        float x2 = xD + cosf(angle + angleSet) * large, y2 = yD + sinf(angle + angleSet) * large;

        // Dibujar los bracitos desde los lados
        glColor3fv(negro);
        glBegin(GL_LINES);
            glVertex2f(xI, yI); glVertex2f(x1, y1); // izquierdo
            glVertex2f(xD, yD); glVertex2f(x2, y2); // derecho
        glEnd();
    }
}

void display(void) {
    glClearColor(1, 1, 1, 1);  
    glClear(GL_COLOR_BUFFER_BIT);

     for (int i = 0; i < 26; i++)
    {
        float ang = i*2*PI/26;
        float r = 1.5;
        float x = r*cosf(ang), y = r*sinf(ang);
        circle(x,y,1.6);
    }
    
    circle(0,0,3.1,4);

    for (int i = 0; i < 26; i++)
    {
        float ang = i*2*PI/26;
        float r = 6;
        float x = r*cosf(ang), y = r*sinf(ang);
        circle(x,y,3);
    }

    for (int i = 0; i < 26; i++)
    {
        float ang = i*2*PI/26;
        float r = 7.7;
        float x = r*cosf(ang), y = r*sinf(ang);
        circle(x,y,0.35);
    }
    for (int i = 0; i < 26; i++)
    {
        float ang = i*2*PI/26 + PI/26;
        float r = 8.35;
        float x = r*cosf(ang), y = r*sinf(ang);
        circle(x,y,0.35);
    }

     for (int i = 0; i < 26; i++)
    {
        float ang = i*2*PI/26 + PI/26;
        float r = 4.5;
        float x = r*cosf(ang), y = r*sinf(ang);
        circle(x,y,0.4);
        
    }
    for (int i = 0; i < 26; i++)
    {
        float ang = i*2*PI/26 + PI/26;
        float r = 6.5;
        float x = r*cosf(ang), y = r*sinf(ang);
        circle(x,y,0.4);
    }

    circle(0,0,9,3);
    cruz(4.75, 1.8, PI/8, 0.3);


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
    glutInitWindowSize(800,800);
    glutInitWindowPosition(500,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);


    glutCreateWindow("Mandala 2");
    inicio();
    glutDisplayFunc(display);
    glutMainLoop();

    return EXIT_SUCCESS; 
}