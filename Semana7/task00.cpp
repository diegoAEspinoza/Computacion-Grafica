/*
Nombre: Diego Alexhander Espinoza Huaman

Resumen:
    - Se creo una funcion que meneje la funcion de la camara, tambien se optimizo la iniciacion de
      varias pantallas mediante una estructura.
    
    - En los diferentes 'displays', se grafico con el mismo color y vemos que en las diferentes pantallas
      se logra observar la iluminacion y mas en la ultima que tiene un cambio de color. 
*/

#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>
#include <iostream>
#include <string.h>

struct WindowConfig {
    int x;
    int y;
    const char* title;
    void (*displayFunc)(void);      
    void (*reshapeFunc)(int, int);  
};

// VARIABLES GLOBALES
float rotX = 0, rotY = 0;
bool mousePressed = false;
int lastX, lastY;

void luzAmbiental(){
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat posicionLuz[]={1, 1, 1, 1};
    GLfloat luzAmbiental[]={0.1, 0.35, 0.1, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, posicionLuz);
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiental);

    GLfloat materialAmbiental[] = {0.1, 0.2, 0.2, 1};
    glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbiental);
}

void luzDifusa(){
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat posicionLuz[]={3, 3, 0, 1};
    GLfloat luzAmbiental[]={0.1, 0.35, 0.1, 1};
    GLfloat luzDifusa[]={0.5, 0.7, 0.9, 1};
    
    glLightfv(GL_LIGHT0, GL_POSITION, posicionLuz);
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiental);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);

    GLfloat materialAmbiental[] = {0.3, 0.7, 0.5, 1};
    GLfloat materialDifuso[] = {0.5, 0.3, 0.7, 1};
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbiental);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDifuso);
}

void luzEspecular(){
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat posicionLuz[]={3, 3, 3, 1};
    GLfloat luzAmbiental[]={0.1, 0.35, 0.1, 1};
    GLfloat luzDifusa[]={0.5, 0.7, 0.9, 1};
    GLfloat luzEspecular[]={1, 1, 1, 1};

    glLightfv(GL_LIGHT0, GL_POSITION, posicionLuz);
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiental);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);

    // Obejto
    GLfloat materialAmbiental[] = {0.3, 0.7, 0.5, 1};
    GLfloat materialDifuso[] = {0.5, 0.3, 0.7, 1};
    GLfloat materialEspecular[] = {1, 1, 1, 1};
    GLfloat materialbrillo[]    = {50};

    glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbiental);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDifuso);
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialEspecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, materialbrillo);
}

void luzCombinada(){
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2); 

    // Luz Principal
    GLfloat PosicionLuz0[] = {2.0, 2.0, 4.0, 1.0};  
    GLfloat Luz0Ambiental[] = {0.1, 0.1, 0.1, 1.0};
    GLfloat Luz0Difusa[] = {1.0, 1.0, 1.0, 1.0};    
    GLfloat Luz0Especular[] = {0.8, 1.0, 0.8, 1.0};

    glLightfv(GL_LIGHT0, GL_POSITION, PosicionLuz0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, Luz0Ambiental);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, Luz0Difusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, Luz0Especular);

    // Luz 1
    GLfloat PosicionLuz1[] = {0.0, -1.0, -1.0, 0.0}; 
    GLfloat Luz1Ambiental[] = {0.0, 0.0, 0.0, 1.0};  
    GLfloat Luz1Difusa[] = {0.2, 0.9, 0.7, 1.0};     
    GLfloat Luz1Especular[] = {0.4, 0.4, 0.7, 1.0};  

    glLightfv(GL_LIGHT1, GL_POSITION, PosicionLuz1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, Luz1Ambiental);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, Luz1Difusa);
    glLightfv(GL_LIGHT1, GL_SPECULAR, Luz1Especular);
    
    // Luz 2
    GLfloat PosicionLuz2[] = {3.0, 0.0, 3.0, 1.0};    
    GLfloat Luz2Difusa[] = {0.8, 0.8, 0.8, 1.0};      
    GLfloat Luz2Especular[] = {0.5, 0.5, 0.5, 1.0};    

    glLightfv(GL_LIGHT2, GL_POSITION, PosicionLuz2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, Luz2Difusa);
    glLightfv(GL_LIGHT2, GL_SPECULAR, Luz2Especular);


    GLfloat MaterialAmbiental[] = {0.8, 0.2, 0.2, 1.0};
    GLfloat MaterialDifuso[] = {0.8, 0.2, 0.2, 1.0};
    GLfloat MaterialEspecular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat MaterialBrillo[] = {50.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT, MaterialAmbiental);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, MaterialDifuso);
    glMaterialfv(GL_FRONT, GL_SPECULAR, MaterialEspecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, MaterialBrillo);
}

void camera() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 800.0 / 600.0, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        2, 3, 2,          
        0, 0.5, 0,     
        0, 1, 0                    
    );
}

void mouse(int button, int state, int x, int y) {
    if(button == GLUT_LEFT_BUTTON) {
        if(state == GLUT_DOWN) { 
            mousePressed = true;
            lastX = x; 
            lastY = y; 
        } else {
            mousePressed = false;
        }
    }
}

void mouseMotion(int x, int y) {
    if(mousePressed) {
        rotY += (x - lastX) * 0.5f;
        rotX += (y - lastY) * 0.5f;
        lastX = x;
        lastY = y;
        glutPostRedisplay();
    }
}

void display1() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera();
    glRotatef(rotX, 1, 0, 0);
    glRotatef(rotY, 0, 1, 0);

    luzAmbiental();
    
    glColor3f(1,0,1);
    glutSolidCone(1,2,30,30);
    glutSwapBuffers();
}

void display2() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera();
    glRotatef(rotX, 1, 0, 0);
    glRotatef(rotY, 0, 1, 0);

    luzDifusa();

    glColor3f(1,0,1);
    glutSolidTeapot(1); 
    glutSwapBuffers();
}

void display3() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera();
    glRotatef(rotX, 1, 0, 0);
    glRotatef(rotY, 0, 1, 0);

    luzEspecular();

    glColor3f(1,0,1);
    glutSolidTorus(0.5, 1, 20, 30); 
    glutSwapBuffers();
}

void display4() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    camera();

    glRotatef(rotX, 1, 0, 0);
    glRotatef(rotY, 0, 1, 0);

    luzCombinada();
    glColor3f(1,0,1);
    glutSolidDodecahedron();
    glutSwapBuffers();
}


void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)w/h, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char *argv[]){
 WindowConfig windows[] = {
        {1,   50, "Ambiental",       display1, reshape},
        {315, 50, "Ambiental y Difusa",       display2, reshape},
        {630, 50, "Ambiental ,Difusa y ESpecular", display3, reshape},
        {945, 50, "3 tipos de Luces",  display4, reshape},
    };

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(300, 300);

    int num_windows = sizeof(windows) / sizeof(WindowConfig);
    for (int i = 0; i < num_windows; i++) {
        glEnable(GL_DEPTH_TEST); 
        glEnable(GL_COLOR_MATERIAL);
        glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        glutInitWindowPosition(windows[i].x, windows[i].y);
        glutCreateWindow(windows[i].title);
        glutDisplayFunc(windows[i].displayFunc);
        glutReshapeFunc(windows[i].reshapeFunc);
        glutMouseFunc(mouse);
        glutMotionFunc(mouseMotion);
    }
    glutMainLoop();
    return EXIT_SUCCESS;
}