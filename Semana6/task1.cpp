/*
Nombre: Diego Alexhander Espinoza Huaman

Mejoras:
    1.
    2.
    3.
    4.

*/

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
#include <ctype.h>
#include <cstdlib>

#define PI 3.141592653589793f

// Propiedades de la Camara
float camAngle = 0.5f, camRadius = 10.0f;  
float camY = 8.0f;
float camZoom = 0.05f;
float lookAtX = 0.0f, lookAtZ = 0.0f;

// Propiedades de la Escena
const float FLOOR_BOUNDARY = 5.0f;
const int FLOOR_DIVISIONS = 10.0f;

void keyboard(unsigned char key, int x, int y) {
    switch (tolower(key)) {
        case 'w': 
            camRadius -= camZoom*10;
            if (camRadius < 2.0f) camRadius = 2.0f;
            break;
        case 's': 
            camRadius += camZoom*10;
            if (camRadius > 50.0f) camRadius = 50.0f;
            break;
        case 'a': 
            camAngle -= camZoom;
            break;
        case 'd': 
            camAngle += camZoom;
            break;
        case 'q': 
            camY -= camZoom*10;
            if (camY < 3.0f) camY = 3.0f;
            break;
        case 'e': 
            camY += camZoom*10;
            if (camY > 20.0f) camY = 20.0f;

            break;
            
    }

    glutPostRedisplay(); 
}

void scene() {
    float cellSize = (2.0f * FLOOR_BOUNDARY) / FLOOR_DIVISIONS;

    for (int i = 0; i < FLOOR_DIVISIONS; ++i) {
        for (int j = 0; j < FLOOR_DIVISIONS; ++j) {
            if ((i + j) % 2 == 0)
                glColor3f(0.9f, 0.9f, 0.9f);  // Blanco
            else
                glColor3f(0.2f, 0.2f, 0.2f);  // Gris oscuro

            float x = -FLOOR_BOUNDARY + j * cellSize;
            float z = -FLOOR_BOUNDARY + i * cellSize;

            glBegin(GL_QUADS);
                glVertex3f(x, 0, z);
                glVertex3f(x + cellSize, 0, z);
                glVertex3f(x + cellSize, 0, z + cellSize);
                glVertex3f(x, 0, z + cellSize);
            glEnd();
        }
    }
    
    glColor3f(0.4, 0.4, 0.4);
    glBegin(GL_QUADS);
        glVertex3f(-FLOOR_BOUNDARY, 0, -FLOOR_BOUNDARY); glVertex3f(FLOOR_BOUNDARY, 0, -FLOOR_BOUNDARY);
        glVertex3f(FLOOR_BOUNDARY, 4, -FLOOR_BOUNDARY);  glVertex3f(-FLOOR_BOUNDARY, 4, -FLOOR_BOUNDARY);

    glEnd();
    glBegin(GL_QUADS);
        glVertex3f(-FLOOR_BOUNDARY, 0, -FLOOR_BOUNDARY); glVertex3f(-FLOOR_BOUNDARY, 0, FLOOR_BOUNDARY);
        glVertex3f(-FLOOR_BOUNDARY, 4, FLOOR_BOUNDARY); glVertex3f(-FLOOR_BOUNDARY, 4, -FLOOR_BOUNDARY);
    glEnd();
}

void dibujarArmario(float posX, float posY, float posZ, float anguloRotacionY) {
    glPushMatrix(); 
    glTranslatef(posX, posY, posZ);
    glRotatef(anguloRotacionY, 0.0f, 1.0f, 0.0f); 

    glColor3f(0.5f, 0.35f, 0.2f);
    glPushMatrix();
        glTranslatef(-4.9f, 1.5f, -3.85f);
        glScalef(0.15f, 3.0f, 2.0f);
        glutSolidCube(1.0f);
    glPopMatrix();

    // Pared derecha 
    glPushMatrix();
        glColor3f(0.6f, 0.3f, 0.0f);
        glTranslatef(-4.68f, 1.5f, -4.8f);
        glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
        glScalef(0.15f, 3.0f, 0.6f);
        glutSolidCube(1.0f);
    glPopMatrix();

    // Pared Izquierda 
    glPushMatrix();
        glColor3f(0.6f, 0.3f, 0.0f); 
        glTranslatef(-4.68f, 1.5f, -2.9f);
        glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
        glScalef(0.15f, 3.0f, 0.6f);
        glutSolidCube(1.0f);
    glPopMatrix();

    // Techo 
    glPushMatrix();
        glColor3f(0.6f, 0.3f, 0.0f);
        glTranslatef(-4.68f, 3.0f, -3.85f);
        glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
        glScalef(0.15f, 0.6f, 2.0f);
        glutSolidCube(1.0f);
    glPopMatrix();

    // Subsecciones 
    for (int i = 0; i < 3; i++) {
        glColor3f(0.6f, 0.3f, 0.25f);
        glPushMatrix();
            glTranslatef(-4.68f, (float)i + 0.2f, -3.85f);
            glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
            glScalef(0.15f, 0.6f, 1.8f); 
            glutSolidCube(1.0f);
        glPopMatrix();
    }

    glPopMatrix(); 
}


void mesa(float anchoMesa, float altoMesa, float profundidadMesa, float alturaPata, float anchoPata) {

    // Dibuja la Mesa
    glPushMatrix();
        glColor3f(0.6f, 0.3f, 0.0f);  
        glTranslatef(0.0f, alturaPata + (altoMesa / 2.0f), 0.0f); 
        glScalef(anchoMesa, altoMesa, profundidadMesa);    
        glutSolidCube(1.0f);
    glPopMatrix();

    // Posición de las patas
    float offsetX = (anchoMesa / 2.0f) - (anchoPata / 2.0f);
    float offsetZ = (profundidadMesa / 2.0f) - (anchoPata / 2.0f);

    // Coordenadas de las patas
    int signos[4][2] = {
        {-1, -1},
        { 1, -1},
        {-1,  1},
        { 1,  1}
    };

    for (int i = 0; i < 4; ++i) {
        float x = signos[i][0] * offsetX;
        float z = signos[i][1] * offsetZ;

        glPushMatrix();
            glTranslatef(x, alturaPata / 2.0f, z);
            glScalef(anchoPata, alturaPata, anchoPata);
            glutSolidCube(1.0f);
        glPopMatrix();
    }
}

void camera() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 800.0 / 600.0, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float camX = camRadius * sin(camAngle);
    float camZ = camRadius * cos(camAngle);

    gluLookAt(
        camX, camY, camZ,          
        lookAtX, 0.5, lookAtZ,     
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


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera();

    drawAxes();
    scene();
    glLineWidth(1.5);

    // Mesa
    mesa(3.0f, 0.1f, 3.0f, 1.0f, 0.1f);
    for (int i = 0; i < 3; i++)
    {
        dibujarArmario(i*-3, 0, 0,-90);
        dibujarArmario(0, 0, i*3,0);
    }
     



    float yMesa = 1.40f;
    // Cubo
    glPushMatrix();
        glTranslatef(-1.15f, yMesa, 0.0f); 
        glColor3f(1, 0, 0);
        glutWireCube(0.5f);
    glPopMatrix();

    // Esfera
    glPushMatrix();
        glTranslatef(0.0f, yMesa, 1.0f); 
        glColor3f(0, 1, 0); 
        glutWireSphere(0.35f, 20, 20);
    glPopMatrix();

    // Cono
    glPushMatrix();
        glTranslatef(1.0f, yMesa-0.25, 0.0f); 
        glRotatef(-90, 1, 0, 0); 
        glColor3f(0, 0, 1); 
        glutWireCone(0.3f, 0.6f, 20, 20);
    glPopMatrix();

    // Toroide
    glPushMatrix();
        glTranslatef(0.0f, yMesa + 0.1f, -1.0f); 
        glColor3f(1, 1, 0); 
        glRotatef(30, 0, 1, 0); 
        glutWireTorus(0.2f, 0.3f, 20, 30); 
    glPopMatrix();

    // Tetera
    glPushMatrix();
        glTranslatef(0.0f, yMesa, 0.0f); 
        glRotatef(-45, 0, 1, 0); 
        glColor3f(1, 0.5, 0);            
        glutWireTeapot(0.5);             
    glPopMatrix();

    
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Semana 10");

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
