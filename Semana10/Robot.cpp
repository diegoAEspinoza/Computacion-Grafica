// Nombre: Diego A. Espinoza


#ifdef _WIN32
#include <windows.h>
#endif
#ifdef __APPLE__
#include <GLUT/freeglut.h>
#else
#include <GL/freeglut.h>
#endif

#include <cmath>
#include <cctype>
#include <cstdlib>

// Dimensiones de la Pantalla
int windowWidth = 800;
int windowHeight = 600;

// Propiedades de la Escena
const float Piso = 7.0f;
const int divionesPiso = 20; 

float camX = 8.0f,
      camZ = 8.0f;

void keyboard(unsigned char key, int x, int y) {
    switch (tolower(key)) {
        case 'q': 
            camX = 8.0f,
            camZ = 8.0f;
            break;
        case 'w': 
            camX = -8.0f,
            camZ = 8.0f;
            break;
        case 'e': 
            camX = -8.0f,
            camZ = -8.0f;
            break;
        case 'r': 
            camX = 8.0f,
            camZ = -8.0f;
            break;
            
            break;
        case 27: 
            exit(0);
            break;
    }

    glutPostRedisplay(); 
}

void camera(float camX, float camY, float camZ) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 800.0 / 600.0, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        camX, camY, camZ,          
        0, 0.5, 0,     
        0, 1, 0                    
    );
}

void drawCoordinateAxes() {
    glBegin(GL_LINES);
    // Eje X en Rojo
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-10.0f, 0.0f, 0.0f);
    glVertex3f(10.0f, 0.0f, 0.0f);
    // Eje Y en Verde
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -10.0f, 0.0f);
    glVertex3f(0.0f, 10.0f, 0.0f);
    // Eje Z en Azul
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -10.0f);
    glVertex3f(0.0f, 0.0f, 10.0f);
    glEnd();
}

void drawFloor() {
    float cellSize = (2.0f * Piso) / divionesPiso;
    glColor3f(0.6f, 1.0f, 0.6f); 

    for (int i = 0; i < divionesPiso; ++i) {
        for (int j = 0; j < divionesPiso; ++j) {

            float x = -Piso + j * cellSize;
            float z = -Piso + i * cellSize;

            glBegin(GL_LINE_LOOP);
                glVertex3f(x, 0.0f, z);
                glVertex3f(x + cellSize, 0.0f, z);
                glVertex3f(x + cellSize, 0.0f, z + cellSize);
                glVertex3f(x, 0.0f, z + cellSize);
            glEnd();
        }
    }
}

void dibujarHexagono3D(float radio, float altura) {
    glBegin(GL_QUADS);
    for (int i = 0; i < 6; i++) {
        float ang1 = i * M_PI / 3;
        float ang2 = (i + 1) * M_PI / 3;

        float x1 = radio * cos(ang1);
        float y1 = radio * sin(ang1);
        float x2 = radio * cos(ang2);
        float y2 = radio * sin(ang2);

        // Cara lateral
        glVertex3f(x1, y1, 0.0f);
        glVertex3f(x2, y2, 0.0f);
        glVertex3f(x2, y2, altura);
        glVertex3f(x1, y1, altura);
    }
    glEnd();

    glBegin(GL_POLYGON);  
    for (int i = 0; i < 6; i++) {
        float ang = i * M_PI / 3;
        glVertex3f(radio * cos(ang), radio * sin(ang), 0.0f);
    }
    glEnd();

    glBegin(GL_POLYGON);  
    for (int i = 0; i < 6; i++) {
        float ang = i * M_PI / 3;
        glVertex3f(radio * cos(ang), radio * sin(ang), altura);
    }
    glEnd();
}

void brazo(){
    glPushMatrix();
        glTranslatef(-2.0f, 1.0f, 0.0f); 
glColor3f(0.75f, 0.75f, 0.75f);
        glRotatef(30.0f, 0.0f, 0.0f, 1.0f); 
        glScalef(4.0f, 0.5f, 0.5f); 
        glutSolidCube(1.0f);

    glPopMatrix();

    // Rectángulo derecho
    glPushMatrix();
        glTranslatef(2.0f, 1.0f, 0.0f); 
glColor3f(0.75f, 0.75f, 0.75f);
        glRotatef(-30.0f, 0.0f, 0.0f, 1.0f);
        glScalef(4.0f, 0.5f, 0.5f);  
        glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f, 2.0f, 0.0f); 
        glColor3f(1.0f, 0.0f, 0.0f); 
        glutSolidSphere(0.5f, 20, 20); 
    glPopMatrix();
}
void robot(){
    glPushMatrix();
        glColor3f(1, 0, 0);
        glRotated(-90,1,0,0);
        glRotated(60,0,0,1);
        dibujarHexagono3D(1.5,0.5);
    glPopMatrix();

    glPushMatrix();
        glColor3f(1, 0, 0);
        glRotated(-90,1,0,0);
        glRotated(60,0,0,1);
        dibujarHexagono3D(0.5,5);
    glPopMatrix();

    glPushMatrix();
        glColor3f(1, 1, 0);
        glRotated(-90,1,0,0);
        glutSolidCylinder(1,4.8,10,10);
    glPopMatrix();



glPushMatrix();
    glRotated(45,0,1,0);
    glTranslatef(-2.5f, 2.5f, 0.0f); 
     
    brazo();
glPopMatrix();

}


void displayScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    camera(camX,10,camZ);

   
    drawCoordinateAxes(); 
    drawFloor();

    robot();

    // Taza
    glPushMatrix();
        glColor3f(0, 1, 0);
        glTranslated(4,1,-4);
        glutWireTeacup(2);
    glPopMatrix();
    // Cuchara
    glPushMatrix();
        glColor3f(1.0f, 0.0f, 1.0f);
        glTranslatef(4, 1, 4); 
        glRotated(-125,0,1,0); 
        glutWireTeaspoon(2);   
    glPopMatrix();
    // Tetera
    glPushMatrix();
    glColor3f(0.545f, 0.27f, 0.07f);
        glTranslatef(-3, 1, 5); 
        glRotated(-130,0,1,0); 
        glutWireTeapot(1);   
    glPopMatrix();

    glutSwapBuffers();
}

void reshape(int width, int height) {
    if (height == 0) {
        height = 1;
    }
    float ratio = 1.0 * width / height;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Escena en 3D - Robot");

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);

    glutDisplayFunc(displayScene);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);


    
    glutMainLoop();
    return 0;
}