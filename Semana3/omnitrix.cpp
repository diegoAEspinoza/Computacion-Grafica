#include <GL/glut.h>
#include <math.h>

#define PI 3.141592

void drawSector(float cx, float cy, float radius, float t1, float t2) {
  const int segments = 50;

  glBegin(GL_POLYGON);
  for (int i = 0; i < segments; ++i) {
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
}



void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  // Circulo grande
  glColor3f(1, 1, 1);
  drawSector(0, 0, 0.8, 0, 2 * PI);
  glColor3f(0, 0, 0);
  drawSector(0, 0, 0.7, 0, 2 * PI);

  float y = 0.03;
  glColor3f(0, 0, 0);
  glBegin(GL_POLYGON);
    glVertex2f(-1, -y);
    glVertex2f(-1, y);
    glVertex2f(1, y);
    glVertex2f(1, -y);
  glEnd();
  glBegin(GL_POLYGON);
    glVertex2f(-y, -1);
    glVertex2f(y, -1);
    glVertex2f(y, 1);
    glVertex2f(-y, 1);
  glEnd();

  glColor3f(0, 1, 0);
  drawSector(0, -0.1, 0.7, PI / 3, 2 * PI / 3);
  glColor3f(0, 1, 0);
  drawSector(0, 0.1, 0.7, 4 * PI / 3, 5 * PI / 3);

  glutSwapBuffers();
}
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
  }
  
int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(600, 600);
  glutCreateWindow("Omnitrix");

  init();
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}