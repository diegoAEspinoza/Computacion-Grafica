#include <GL/glut.h>
#include <math.h>

#define PI 3.141592

//
// General
//
typedef struct {
  float x;
  float y;
} CartesianCoordinate;

typedef struct {
  float r;
  float theta;
} PolarCoordinate;

typedef CartesianCoordinate (*Parametric)(float);

CartesianCoordinate polarToCartesian(PolarCoordinate p) {
  CartesianCoordinate c;
  c.x = p.r * cosf(p.theta);
  c.y = p.r * sinf(p.theta);
  return c;
}

CartesianCoordinate translation(CartesianCoordinate c, float cx, float cy) {
  CartesianCoordinate c1;
  c1.x = cx + c.x;
  c1.y = cy + c.y;
  return c1;
}

void drawParametricLines(Parametric f, float t1, float t2, float cx, float cy) {
  const int segments = 10000;
  glBegin(GL_LINE_STRIP);
  for (int i = 0; i <= segments; ++i) {
    float p = t1 + i * (t2 - t1) / segments;
    CartesianCoordinate c = f(p);
    c = translation(c, cx, cy);
    glVertex2f(c.x, c.y);
  }
  glEnd();
}

void drawParametricSolid(Parametric f, float t1, float t2, float cx, float cy) {
  const int segments = 10000;
  glBegin(GL_POLYGON);
  glVertex2f(cx, cy);
  for (int i = 0; i <= segments; ++i) {
    float p = t1 + i * (t2 - t1) / segments;
    CartesianCoordinate c = f(p);
    c = translation(c, cx, cy);
    glVertex2f(c.x, c.y);
  }
  glEnd();
}

void drawParametricPoints(Parametric f, float t1, float t2, float cx,
                          float cy) {
  const int segments = 100;
  glBegin(GL_POINTS);
  for (int i = 0; i <= segments; ++i) {
    float p = t1 + i * (t2 - t1) / segments;
    CartesianCoordinate c = f(p);
    c = translation(c, cx, cy);
    glVertex2f(c.x, c.y);
  }
  glEnd();
}

//
// Especifico
//

CartesianCoordinate rose(float t) {
  PolarCoordinate p;
  p.r = 0.5 * sinf(6 * t);
  p.theta = t;
  CartesianCoordinate c = polarToCartesian(p);
  return c;
}

CartesianCoordinate circle(float t) {
  PolarCoordinate p;
  p.r = 0.07;
  p.theta = t;
  CartesianCoordinate c = polarToCartesian(p);
  return c;
}

CartesianCoordinate cardioid(float t) {
  PolarCoordinate p;
  p.r = 0.5 - 0.5 * sinf(t);
  p.theta = t;
  CartesianCoordinate c = polarToCartesian(p);
  return c;
}

CartesianCoordinate lemniscata(float t) {
  PolarCoordinate p;
  p.r = 0.5 * sqrt(cosf(2 * t));
  p.theta = t;
  CartesianCoordinate c = polarToCartesian(p);
  return c;
}

//
// Programa
//
void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  // Ramo
  glColor3f(0, 1, 0);
  float e = 0.03;
  glBegin(GL_POLYGON);
  glVertex2f(e, -0.75);
  glVertex2f(-e, -0.75);
  glVertex2f(-e, 0.5);
  glVertex2f(e, 0.5);
  glEnd();
  drawParametricSolid(lemniscata, 0, 2 * PI, 0, -0.3);

  // Petalos
  glColor3f(1, 0, 0);
  drawParametricSolid(rose, 0, 2 * PI, 0, 0.5);

  // Centro
  glColor3f(1, 1, 0);
  drawParametricSolid(circle, 0, 2 * PI, 0, 0.5);

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
  glutCreateWindow("Rosa");

  init();
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}