#include <GL/glut.h>
#include <iostream>

GLenum currentMode = GL_POINTS;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.2f, 0.2f, 1.0f);
    glBegin(currentMode);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.5f, -0.5f);
        glVertex2f(0.5f, 0.5f);
        glVertex2f(-0.5f, 0.5f);
    glEnd();

    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case '1': currentMode = GL_POINTS; break;
        case '2': currentMode = GL_LINES; break;
        case '3': currentMode = GL_LINE_STRIP; break;
        case '4': currentMode = GL_LINE_LOOP; break;
        case '5': currentMode = GL_TRIANGLES; break;
        case '6': currentMode = GL_TRIANGLE_STRIP; break;
        case '7': currentMode = GL_TRIANGLE_FAN; break;
        case '8': currentMode = GL_QUADS; break;
        case '9': currentMode = GL_POLYGON; break;
    }
    glutPostRedisplay();
}

void init() {
    glClearColor(1, 1, 1, 1);
    glPointSize(5);
    glLineWidth(2);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutCreateWindow("Modo Interactivo OpenGL");
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(200, 200);
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
