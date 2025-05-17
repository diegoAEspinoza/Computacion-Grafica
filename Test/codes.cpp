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


void drawSector(
    float cx, float cy, 
    float radius,
    float t1, float t2,
    float *RGB1, float *RGB2,
    float w = 1.0f,
    int segments=100) {
  
    glColor3fv(RGB1);   

    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < segments; i++) {
        float theta = t1 + i * (t2 - t1) / segments;
        float theta2 = t1 + (i + 1) * (t2 - t1) / segments;
        float x1 = cx + radius * cosf(theta);
        float y1 = cy + radius * sinf(theta);
        float x2 = cx + radius * cosf(theta2);
        float y2 = cy + radius * sinf(theta2);
        glVertex2f(cx, cy);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    }
    glEnd(); 

    glColor3fv(RGB2);   
    glLineWidth(w);

    glBegin(GL_LINE_LOOP);
    glVertex2f(cx, cy);

    for (int i = 0; i < segments; i++) {
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
}

void polygon(float c[2], float r, float n,float *RGB, GLenum MODO){
    float x = c[0], y=c[1];

    glColor3fv(RGB);
    glPolygonMode(GL_FRONT_AND_BACK, MODO);
    // MODO: GL_LINE AND GL_FILL
    glBegin(GL_POLYGON);
        float angulo = 2 * M_PI / n;
        for (int i = 0; i < n; i++) {
            float vx = x + r * cos(i * angulo);
            float vy = y + r * sin(i * angulo);
            glVertex2f(vx, vy);
        }
    glEnd();
}

void elipse(
        float cx, float cy,
        float rx, float ry,
        float *RGB1, float *RGB2,
        float w=1.0f)
    {
        int segments = 100; 

        glColor3fv(RGB1);   
    
        glBegin(GL_TRIANGLE_FAN);
        for (int i = 0; i < segments; i++) {
            float theta = 2.0f * PI * float(i) / float(segments);
    
            float x = rx * cosf(theta);
            float y = ry * sinf(theta); 
    
            glVertex2f(x + cx, y + cy);
        }
        glEnd(); 

        glColor3fv(RGB2);   
            glLineWidth(w);

        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < segments; i++) {
            float theta = 2.0f * PI * float(i) / float(segments);
    
            float x = rx * cosf(theta);
            float y = ry * sinf(theta); 
    
            glVertex2f(x + cx, y + cy);
        }
        glEnd(); 
    }

void cardioide(float x, float y, float a, float b, float angulo, float n, float m, GLenum Modo, float *RGB){
    glColor3fv(RGB);
    glBegin(Modo);
    if ( Modo == GL_POLYGON)
    {
        glVertex2f(x, y);
    }
    float theta = angulo / n;
    for (float i = 0; i <= n; i++) {
        
        float r = a - b*sin(i*theta*m);
        
        float vx = r * cos(i*theta);
        float vy = r * sin(i*theta);
        
        glVertex2f(x+vx, y+vy);
    }
    glEnd();
}

void lemniscatas(float x, float y, float a, float b, float angulo, float n, float m, GLenum Modo, float *RGB){
    glColor3fv(RGB);
    glBegin(Modo);
    if ( Modo == GL_POLYGON || Modo == GL_LINES  )
    {
        glVertex2f(x, y);
    }
    float theta = angulo / n;
    for (float i = 0; i <= n; i++) {
        
        float r = sqrt(a - b*sin(i*theta*m));
        
        float vx = r * cos(i*theta);
        float vy = r * sin(i*theta);
        
        glVertex2f(x+vx, y+vy);
    }
    glEnd();
}
