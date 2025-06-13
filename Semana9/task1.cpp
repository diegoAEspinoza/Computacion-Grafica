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


void ejes(float a){
    glColor3fv(rojo);
    glBegin(GL_POINTS);
    for (int t = 0; t < 100; t++)
    {glVertex2f(-a + 2*a * t * 1/100, 0);}
    glEnd();
    glColor3fv(azul);
    glBegin(GL_POINTS);
    for (int t = 0; t < 100; t++)
    {glVertex2f(0, -a + 2 * a * t * 1/100);}
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
    ejes(4);
    flor(GL_POINTS);

    glutSwapBuffers();  
}

void display2(void){
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ejes(4);
    flor(GL_POINTS);

    glTranslated(2.5,0,0);
    flor(GL_POLYGON);

    glutSwapBuffers();
}


void display3(void)
{
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW); 
    
    glLoadIdentity();
    gluLookAt (0, 0, 8.0, 0.0, 0.0, 0.0, 0.0, 0.25, 0.0);
    ejes(8);

    flor(GL_POINTS);
    glTranslated(0,1,0);
    flor(GL_POLYGON);

    glutSwapBuffers();
}

void display4(void)
{
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW); 

    glLoadIdentity();
    gluLookAt (0, 0, 8.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    ejes(8);

    flor(GL_POINTS);
    glTranslated(0,0,3);
    flor(GL_POLYGON);

    glutSwapBuffers();
}

void display5(void)
{
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW); 

    glLoadIdentity();
    gluLookAt (0, 0, 6.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    ejes(6);

    flor(GL_POINTS);
    glTranslated(4,0,-9);
    flor(GL_POLYGON);
    glTranslated(-7,0,5);
    flor(GL_POLYGON);

    glutSwapBuffers();
}

void display6(void)
{
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt (0, 0, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    ejes(4);
    flor(GL_POINTS);
    glTranslated(2,0,0);
    glRotated(45,0,0,1);
    ejes(6);
    flor(GL_POLYGON);


    glutSwapBuffers();
}

void reshape2D(int w, int h)
{
    if (h == 0) h = 1;
    float aspect_ratio = (float)w / (float)h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluOrtho2D(-4.0 * aspect_ratio, 4.0 * aspect_ratio, -4.0, 4.0);

    glMatrixMode(GL_MODELVIEW);
}

void reshape3D(int w, int h)
{
    if (h == 0) h = 1;
    float aspect_ratio = (float)w / (float)h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glFrustum(-1.5 * aspect_ratio, 1.5 * aspect_ratio, -1.5, 1.5, 1.5, 25.0);
    
    glMatrixMode(GL_MODELVIEW);
}


void inicio()
{   
    int a = 4;
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-a,a,-a,a);
    glClearColor(0,0,0,0);
}
void inicio3D()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); 
    
    gluPerspective(60.0, 1.0, 1.0, 100.0); 
    glClearColor(0,0,0,0);
}

int main(int argc, char *argv[])
{
    WindowConfig windows[] = {
        {1,   1,   "Primer Codigo",                display1, reshape2D},
        {420, 1,   "Segundo Codigo",        display2, reshape2D},
        {840, 1,   "Tercer Codigo",        display3, reshape3D},
        {1,   390, "Cuarto Codigo",        display4, reshape3D},
        {420, 390, "Quinto Codigo",    display5, reshape3D},
        {840, 390, "Sexto Codigo",            display6, reshape3D}
    };

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(300, 300);

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