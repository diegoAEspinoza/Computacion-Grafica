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
    morado[3] = {0.5f, 0.0f, 0.5f};

struct WindowConfig {
    int x;
    int y;
    const char* title;
    void (*displayFunc)(void);      // Puntero a la función de display
    void (*reshapeFunc)(int, int);  // Puntero a la función de reshape
};


void camera(float x=1,float y=1,float z=1) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 800.0 / 600.0, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        x, y, z,          
        0, 0, 0,     
        0, 1, 0                    
    );
}


void drawAxes() {
    glBegin(GL_LINES);
    glColor3f(0, 1, 0);
        glVertex3f(-10, 0, 0); glVertex3f(10, 0, 0);
    glColor3f(0, 0, 1);
        glVertex3f(0, -10, 0); glVertex3f(0, 10, 0); 
    glColor3f(1, 0, 0);
        glVertex3f(0, 0, -10); glVertex3f(0, 0, 10); 
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
        float r = sqrt(a + b*cos(i*theta*m));
        float vx = r * cos(i*theta);
        float vy = r * sin(i*theta);
        
        glVertex2f(x+vx, y+vy);
    }
    glEnd();
}

void tallo(float *RGB,GLenum Modo,float n=100){
    glColor3fv(RGB);
    glBegin(Modo);
    if ( Modo == GL_POLYGON)
    {
        glVertex2f(0, 0);
    }
    
    float ap = 1/n;
    for (int t = 0; t < n; t++)
    {
        glVertex2f(-0.05f + 0.10f * t*ap, 1);
        
        glVertex2f(0.05f, 1.0f - 3.0f * t*ap);
       
        glVertex2f(0.05f - 0.10f * t*ap, -2);
        
        glVertex2f(-0.05f, -2.0f + 3.0f*t*ap );
    }
    glEnd();
}

void flor(GLenum modo){
    tallo(verde, modo);

    cardioide(0,1,0,-1,2*PI,500,6,modo,morado);
    cardioide(0,1,0.1,0,2*PI,50,1,modo,amarillo);

    lemniscatas(0,-1,0,0.81, 2*PI,500,2, modo,verde);
}


void display1(void) {
    glClearColor(0, 0, 0, 0);  
    glClear(GL_COLOR_BUFFER_BIT);
    
    camera(3,3,3);
    drawAxes();
    
    glPushMatrix();
        glColor3f(0, 1, 1);
        flor(GL_POLYGON);
    glPopMatrix();
    
    glutSwapBuffers();  
}

void display2(void){
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera(3,3,3);
    drawAxes();
    glPushMatrix();
        glColor3f(0, 1, 1); 
        glRotated(90,0,1,0);
        flor(GL_POLYGON);
    
    glPopMatrix();
    glutSwapBuffers();
}


void display3(void)
{
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);

    camera(3,3,3);
    drawAxes();
    glPushMatrix();
        glColor3f(0, 1, 1);
        glRotated(90,0,1,0); 
        flor(GL_POLYGON);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0, 1, 1);
        glTranslated(0,0,2);
        glRotated(90,0,1,0);
        flor(GL_POLYGON);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0, 1, 1);
        glTranslated(0,0,-2);
        glRotated(90,0,1,0);
        flor(GL_POLYGON);
    glPopMatrix();

    glutSwapBuffers();
}
void display4(void)
{
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);

    camera(3,3,3);
    drawAxes();
    glPushMatrix();
        glColor3f(0, 1, 1);
        glRotated(90,0,1,0); 
        flor(GL_POLYGON);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0, 1, 1);
        glTranslated(2,0,0);
        glRotated(90,0,1,0);
        flor(GL_POLYGON);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0, 1, 1);
        glTranslated(-2,0,0);
        glRotated(90,0,1,0);
        flor(GL_POLYGON);
    glPopMatrix();

    glutSwapBuffers();
}


void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

int main(int argc, char *argv[])
{
    WindowConfig windows[] = {
        {1,   1,   "Imagen Original",         display1, reshape},
        {420, 1,   "Rotacion",        display2, reshape},
        {840, 1,   "Rotacion y Translacion en X",        display3, reshape},
        {1, 510,   "Rotacion y Translacion en Z",        display4, reshape}

    };

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(400, 400);

    int num_windows = sizeof(windows) / sizeof(WindowConfig);
    for (int i = 0; i < num_windows; i++) {
        glutInitWindowPosition(windows[i].x, windows[i].y);
        glutCreateWindow(windows[i].title);
        glutDisplayFunc(windows[i].displayFunc);
        glutReshapeFunc(windows[i].reshapeFunc);
    }

    glutMainLoop();

    return EXIT_SUCCESS;
}