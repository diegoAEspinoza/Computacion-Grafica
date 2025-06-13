#ifdef _WIN32
#include <windows.h>
#endif
#ifdef __APPLE__
#include <GLUT/freeglut.h>
#else
#include <GL/freeglut.h>
#endif

#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <cstdlib>

#define PI 3.141592653589793f

struct WindowConfig {
    int x;
    int y;
    const char* title;
    void (*displayFunc)(void);      
    void (*reshapeFunc)(int, int);  
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
    glColor3f(1, 0, 0);
        glVertex3f(-10, 0, 0); glVertex3f(10, 0, 0);
    glColor3f(0, 1, 0);
        glVertex3f(0, -10, 0); glVertex3f(0, 10, 0); 
    glColor3f(0, 0, 1);
        glVertex3f(0, 0, -10); glVertex3f(0, 0, 10); 
    glEnd();
}

void display1(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera();
    drawAxes();

    glPushMatrix();
        glColor3f(0, 1, 1); 
        glutWireCone(0.3f, 0.6f, 20, 20);
    glPopMatrix();    
    glutSwapBuffers();
}
void display2(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera(1,1,0.5);
    drawAxes();

    glPushMatrix();
        glColor3f(0, 1, 1); 
        glutWireCube(0.5f);
    glPopMatrix(); 

    glutSwapBuffers();
}
void display3(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       camera(3,4,5);
        drawAxes();

    glPushMatrix();
            glScalef(2,2,2);

        glColor3f(0, 1, 1); 
        glutWireDodecahedron();
    glPopMatrix(); 
    glutSwapBuffers();
}
void display4(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       camera(1,1,5);
        drawAxes();

    glPushMatrix();
            glScalef(2,2,2);

        glColor3f(0, 1, 1); 
        glutWireIcosahedron();
    glPopMatrix(); 
    glutSwapBuffers();
}

void display5(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       camera(1,1,5);
        drawAxes();

    glPushMatrix();
            glScalef(2,2,2);

        glColor3f(0, 1, 1); 
    glutWireOctahedron();
    glPopMatrix(); 

    glutSwapBuffers();
}

void display6(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       camera(5,7,5);
        drawAxes();

    glPushMatrix();

        glColor3f(0, 1, 1); 
    glutWireSphere(4.5,20,20);
    glPopMatrix(); 
    glutSwapBuffers();
}

void display7(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       camera(0,4,3);
        drawAxes();

    glPushMatrix();

        glColor3f(0, 1, 1); 
    glutWireTeapot(1.8);
    glPopMatrix(); 
    glutSwapBuffers();
}

void display8(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       camera(1,1.5,1);
        drawAxes();

    glPushMatrix();

        glColor3f(0, 1, 1); 
glutWireTetrahedron();
    glPopMatrix(); 
    glutSwapBuffers();
}

void display9(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       camera(1,1,1);
        drawAxes();
    glPushMatrix();
        glColor3f(0, 1, 1); 
        glRotatef(90, 1, 0, 0); 
        glutWireTorus(0.2f, 0.5f, 20, 30); 
    glPopMatrix();
    glutSwapBuffers();
}


void display10(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera(2,2,2);
    drawAxes();
    glPushMatrix();
        glColor3f(0, 1, 1); 
        glTranslatef(0, 0, -1); 
    glutWireCylinder(1.0, 2.0, 20, 20);
    
    glPopMatrix();
    glutSwapBuffers();
}


void display11(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera(1,4,2);
    drawAxes();
    glPushMatrix();
        glColor3f(0, 1, 1); 
            glScalef(2,2,2);

glutWireRhombicDodecahedron();
    
    glPopMatrix();
    
    glutSwapBuffers();
}


void display12(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera(2.5,1,2.5);
    drawAxes();
    glPushMatrix();
        glColor3f(0, 1, 1); 
double x[]={0,0,0}; 
glutWireSierpinskiSponge(1,x,2);
    
    glPopMatrix();
    
    glutSwapBuffers();
}


void display13(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera(-1,2,6);
    drawAxes();
    glPushMatrix();
        glColor3f(0, 1, 1); 
glutWireTeacup(3);

    
    glPopMatrix();
    glutSwapBuffers();
}


void display14(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera(3,2,3);
    drawAxes();
    glPushMatrix();
        glColor3f(0, 1, 1); 
                glTranslatef(0, 0, -3); 

glutWireTeaspoon(8);

    
    glPopMatrix();
    glutSwapBuffers();
}

void display15(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera(2,1,3);
    drawAxes();
    glPushMatrix();
        glColor3f(0, 1, 1); 
double x[]={0,0,0}; 
glutWireSierpinskiSponge(3,x,2);
    
    glPopMatrix();
    
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

int main(int argc, char *argv[])
{
 WindowConfig windows[] = {
        // Fila 1
        {1,   50, "Cono",       display1, reshape},
        {315, 50, "Cubo",       display2, reshape},
        {630, 50, "Dodecaedro", display3, reshape},
        {945, 50, "Icosaedro",  display4, reshape},

        // Fila 2
        {1,   350, "Octaedro",  display5, reshape},
        {315, 350, "Esfera",    display6, reshape},
        {630, 350, "Tetera",    display7, reshape},
        {945, 350, "Tetraedro", display8, reshape},

        // Fila 3
        {1,   650, "Toroide",            display9,  reshape},
        {315, 650, "Cilindro",           display10, reshape},
        {630, 650, "Dodecaedro Rombico", display11, reshape},
        {945, 650, "Tetraedro de Sierpinski", display12, reshape},

        // Fila 4
        {1260,   50, "Taza",  display13, reshape},
        {1260, 350, "Cuchara", display14, reshape},
        {1260, 650, "Tetraedro de Sierpinski", display15, reshape}
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
