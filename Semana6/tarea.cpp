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

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

struct WindowConfig {
int width = 800;
int height = 600;
const char* title = "3D Scene";
};

struct CameraConfig {
float angle = -0.5f;
float directionX = 0.0f;
float directionZ = -1.0f;
const float rotationSpeed = 0.05f;
const float distanceToPlayer = 5.0f;
const float y = 5.0f;
const float lookAtPlayerY = 0.5f;
};

struct PlayerConfig {
float x = 0.0f;
float z = 0.0f;
const float speed = 0.1f;
const float size = 1.0f;
const float collisionOffset = 0.01f;
const float halfSize = size / 2.0f;

const float boundaryCheckHalfSize = halfSize + collisionOffset;
};

struct SceneConfig {
const float floorBoundary = 5.0f;
const int floorDivisions = 20;
const float axisLength = 10.0f;
};

WindowConfig windowSettings;
CameraConfig cameraSettings;
PlayerConfig playerSettings;
SceneConfig sceneSettings;

void drawCoordinateAxes() {
glBegin(GL_LINES);

glColor3f(1.0f, 0.0f, 0.0f);
glVertex3f(-sceneSettings.axisLength, 0.0f, 0.0f);
glVertex3f(sceneSettings.axisLength, 0.0f, 0.0f);

glColor3f(0.0f, 1.0f, 0.0f);
glVertex3f(0.0f, -sceneSettings.axisLength, 0.0f);
glVertex3f(0.0f, sceneSettings.axisLength, 0.0f);

glColor3f(0.0f, 0.0f, 1.0f);
glVertex3f(0.0f, 0.0f, -sceneSettings.axisLength);
glVertex3f(0.0f, 0.0f, sceneSettings.axisLength);
glEnd();
}

void drawFloor() {
float cellSize = (2.0f * sceneSettings.floorBoundary) / sceneSettings.floorDivisions;

for (int i = 0; i < sceneSettings.floorDivisions; ++i) {
for (int j = 0; j < sceneSettings.floorDivisions; ++j) {
if ((i + j) % 2 == 0)
glColor3f(0.9f, 0.9f, 0.9f);
else
glColor3f(0.2f, 0.2f, 0.2f);

float x = -sceneSettings.floorBoundary + j * cellSize;
float z = -sceneSettings.floorBoundary + i * cellSize;

glBegin(GL_QUADS);
glVertex3f(x, 0.0f, z);
glVertex3f(x + cellSize, 0.0f, z);
glVertex3f(x + cellSize, 0.0f, z + cellSize);
glVertex3f(x, 0.0f, z + cellSize);
glEnd();
}
}
}

void drawPlayer() {
glPushMatrix();
glLineWidth(2.0f);
glColor3f(1.0f, 0.0f, 1.0f);

glTranslatef(playerSettings.x, playerSettings.halfSize, playerSettings.z);
glutWireCube(playerSettings.size);
glLineWidth(1.0f);
glPopMatrix();
}

void movePlayer(float deltaX, float deltaZ) {
float newPlayerX = playerSettings.x + deltaX;
float newPlayerZ = playerSettings.z + deltaZ;

if (newPlayerX >= -sceneSettings.floorBoundary + playerSettings.boundaryCheckHalfSize &&
newPlayerX <= sceneSettings.floorBoundary - playerSettings.boundaryCheckHalfSize) {
playerSettings.x = newPlayerX;
}

if (newPlayerZ >= -sceneSettings.floorBoundary + playerSettings.boundaryCheckHalfSize &&
newPlayerZ <= sceneSettings.floorBoundary - playerSettings.boundaryCheckHalfSize) {
playerSettings.z = newPlayerZ;
}
}

void setupCameraView() {

glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(60.0, (float)windowSettings.width / (float)windowSettings.height, 0.1, 100.0);

glMatrixMode(GL_MODELVIEW);
glLoadIdentity();

cameraSettings.directionX = sin(cameraSettings.angle * M_PI);
cameraSettings.directionZ = cos(cameraSettings.angle * M_PI);

float camX = playerSettings.x - cameraSettings.directionX * cameraSettings.distanceToPlayer;
float camZ = playerSettings.z - cameraSettings.directionZ * cameraSettings.distanceToPlayer;

gluLookAt(
camX, cameraSettings.y, camZ,
playerSettings.x, cameraSettings.lookAtPlayerY, playerSettings.z,
0.0f, 1.0f, 0.0f
);
}

void displayScene() {
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

setupCameraView();

drawFloor();
drawPlayer();
drawCoordinateAxes();

glutSwapBuffers();
}

void reshape(int width, int height) {
if (height == 0) height = 1;

windowSettings.width = width;
windowSettings.height = height;

glViewport(0, 0, (GLsizei)width, (GLsizei)height);

glutPostRedisplay();
}

void keyboardHandler(unsigned char key, int x, int y) {
float moveX = 0.0f;
float moveZ = 0.0f;

switch (toupper(key)) {

case 'W':
moveX = cameraSettings.directionX * playerSettings.speed;
moveZ = cameraSettings.directionZ * playerSettings.speed;
break;
case 'S':
moveX = -cameraSettings.directionX * playerSettings.speed;
moveZ = -cameraSettings.directionZ * playerSettings.speed;
break;
case 'A':

moveX = -cameraSettings.directionZ * playerSettings.speed;
moveZ = cameraSettings.directionX * playerSettings.speed;
break;
case 'D':

moveX = cameraSettings.directionZ * playerSettings.speed;
moveZ = -cameraSettings.directionX * playerSettings.speed;
break;

case 'Q':
cameraSettings.angle -= cameraSettings.rotationSpeed;
break;
case 'E':
cameraSettings.angle += cameraSettings.rotationSpeed;
break;

case 27:
exit(0);
break;
}

if (moveX != 0.0f || moveZ != 0.0f) {
movePlayer(moveX, moveZ);
}

glutPostRedisplay();
}

int main(int argc, char** argv) {
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
glutInitWindowSize(windowSettings.width, windowSettings.height);
glutCreateWindow(windowSettings.title);

glEnable(GL_DEPTH_TEST);
glClearColor(0.1f, 0.1f, 0.15f, 1.0f);

glutDisplayFunc(displayScene);
glutReshapeFunc(reshape);
glutKeyboardFunc(keyboardHandler);

glutMainLoop();
return 0;
}