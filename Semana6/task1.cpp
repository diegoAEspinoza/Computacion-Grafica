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


void circle(float x, float y, float r, float w=3.0f){
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


void display(void) {
    glClearColor(1, 1, 1, 1);  
    glClear(GL_COLOR_BUFFER_BIT);
    
    circle(0,0, 19);
    circle(0,0, 18,5);
    circle(0,0, 16.55);
    circle(0,0, 11.8,5);
    circle(0,0, 9);
    
    for (int i = 0; i < 3; i++)
    {
        float ang = i*2*PI/3 + PI/6;
        float r = 0.8;
        float x = r*cosf(ang), y = r*sinf(ang);
        circle(x,y,1.2);
    }

    for (int i = 0; i < 12; i++)
    {
        float ang = i*PI/6;
        float r = 4;
        float x = r*cosf(ang), y = r*sinf(ang);
        
        circle(x,y,2);
    }
    
    for (int i = 0; i < 12; i++)
    {
        float ang = i*PI/6;
        float r = 12;
        float x = r*cosf(ang);
        float y = r*sinf(ang);
        
        circle(x,y,6);
    }

    for (int i = 0; i < 12; i++)
    {
        float ang = i*PI/6 + PI/12;
        float r = 3.5;
        float x = r*cosf(ang);
        float y = r*sinf(ang);
        
        circle(x,y,0.8);
    }

    for (int i = 0; i < 12; i++)
    {
        float ang = i*PI/6;
        float r = 7;
        float x = r*cosf(ang);
        float y = r*sinf(ang);
        
        circle(x,y,0.9);
    }

    for (int i = 0; i < 12; i++)
    {
        float ang = i*PI/6 + PI/12;
        float r = 7.9;
        float x = r*cosf(ang);
        float y = r*sinf(ang);
        
        circle(x,y,1.1);
        circle(x,y,0.35);
    }

    for (int i = 0; i < 12; i++)
    {
        float ang = i*PI/6 + PI/12;
        float r = 10.5;
        float x = r*cosf(ang);
        float y = r*sinf(ang);
        
        circle(x,y,1.33);
        circle(x,y,0.55);
    }

    for (int i = 0; i < 12; i++)
    {
        float ang = i*PI/6 + PI/12;
        float r = 14.85;
        float x = r*cosf(ang);
        float y = r*sinf(ang);
        
        circle(x,y,1.35);
        
    }
    
    for (int i = 0; i < 12; i++)
    {
        float ang = i*PI/6 + PI/12;
        float r = 15.25;
        float x = r*cosf(ang);
        float y = r*sinf(ang);
        
        circle(x,y,0.9);
    }
    
    for (int i = 0; i < 12; i++)
    {
        float ang = i*PI/6 + PI/12;
        float r = 12.7;
        float x = r*cosf(ang);
        float y = r*sinf(ang);
        
        circle(x,y,0.75);
    }

    for (int i = 0; i < 12; i++)
    {
        float ang = i*PI/6;
        float r = 15.2;
        float x = r*cosf(ang);
        float y = r*sinf(ang);
        
        circle(x,y,1.35);
        
    }
    
    for (int i = 0; i < 12; i++)
    {
        float ang = i*PI/6;
        float r = 15.5;
        float x = r*cosf(ang);
        float y = r*sinf(ang);
        
        circle(x,y,0.9);
    }
    
    for (int i = 0; i < 12; i++)
    {
        float ang = i*PI/6;
        float r = 13.25;
        float x = r*cosf(ang);
        float y = r*sinf(ang);
        
        circle(x,y,0.65);
    }

    glutSwapBuffers();  
}


void inicio()
{   
    int a = 22;
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


    glutCreateWindow("Mandala 1");
    inicio();
    glutDisplayFunc(display);
    glutMainLoop();

    return EXIT_SUCCESS; 
}