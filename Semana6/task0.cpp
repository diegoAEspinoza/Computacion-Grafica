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

#include <cmath>     
#include <cctype>    
#include <cstdlib>   

// Dimensiones de la Pantalla
int windowWidth = 800;
int windowHeight = 600;

// Propiedades de la Camara
float camHorAngle = -0.5f; 
float camDirectionX = 0.0f;
float camDirectionZ = -1.0f;     
const float cameraRotationSpeed = 0.05f;
const float cameraToPlayer = 5.0f;
const float camY = 5.0f; 
const float cameraToPlayerY = 0.5f; 

// Propiedades del Jugador
float playerX = 0.0f;
float playerZ = 0.0f;
const float playerSpeed = 0.1f;
const float playerSize = 1.0f;
const float playerHalfSize = playerSize / 2.0f+0.01f;

// Propiedades de la Escena
const float FLOOR_BOUNDARY = 5.0f;
const int FLOOR_DIVISIONS = 20.0f;


// Dibujo de la Escena

void drawCoordinateAxes() {
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-10.0f, 0.0f, 0.0f); glVertex3f(10.0f, 0.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, -10.0f, 0.0f); glVertex3f(0.0f, 10.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 0.0f, -10.0f); glVertex3f(0.0f, 0.0f, 10.0f);
    glEnd();
}

void drawFloor() {
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
}


// Funciones del Jugador
void movePlayer(float deltaX, float deltaZ) {
    float newPlayerX = playerX + deltaX;
    float newPlayerZ = playerZ + deltaZ;

    if (newPlayerX >= -FLOOR_BOUNDARY + playerHalfSize && newPlayerX <= FLOOR_BOUNDARY - playerHalfSize) {
        playerX = newPlayerX;
    }

    if (newPlayerZ >= -FLOOR_BOUNDARY + playerHalfSize && newPlayerZ <= FLOOR_BOUNDARY - playerHalfSize) {
        playerZ = newPlayerZ;
    }
}

void player(){
    glPushMatrix();
        glLineWidth(2);
        glColor3f(1.0f, 0.0f, 1.0f); 
        glTranslatef(playerX, playerHalfSize, playerZ);
        glutWireCube(playerSize);
        glLineWidth(1);
    glPopMatrix();
}
    
// Camara
void setupCameraView() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)windowWidth / (float)windowHeight,0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    camDirectionX = sin(camHorAngle * M_PI);
    camDirectionZ = cos(camHorAngle * M_PI);

    float camX = playerX - camDirectionX * cameraToPlayer;
    float camZ = playerZ - camDirectionZ * cameraToPlayer;

    gluLookAt(
        camX, camY, camZ,                     
        playerX, cameraToPlayerY, playerZ, 
        0.0f, 1.0f, 0.0f                                     
    );
}


// Teclado
void Keyboard(unsigned char key, int x, int y) {
    switch (toupper(key)) {
        case 'W': 
            movePlayer(camDirectionX * playerSpeed, camDirectionZ * playerSpeed);
            break;
        case 'S': 
            movePlayer(-camDirectionX * playerSpeed, -camDirectionZ * playerSpeed);
            break;
        case 'A': 
            movePlayer(-camDirectionZ * playerSpeed, camDirectionX * playerSpeed);
            break;
        case 'D': 
            movePlayer(camDirectionZ * playerSpeed, -camDirectionX * playerSpeed);
            break;

        case 'Q': 
            camHorAngle -= cameraRotationSpeed;
            break;
        case 'E': 
            camHorAngle += cameraRotationSpeed;
            break;
        case 27: 
            exit(0);
            break;
    }
    glutPostRedisplay(); 
}


void displayScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    setupCameraView(); 
    player();
    drawFloor(); 
    drawCoordinateAxes(); 

    glutSwapBuffers(); 
}


void reshape(int width, int height) {
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Ecena en 3D");

    glEnable(GL_DEPTH_TEST); 
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f); 

    glutDisplayFunc(displayScene);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(Keyboard);

    glutMainLoop(); 
    return 0;
}