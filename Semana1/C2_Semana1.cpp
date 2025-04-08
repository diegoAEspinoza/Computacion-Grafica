#include <GL/glut.h>
#include <cmath>

void drawSquare() {
    glColor3f(1.0f, 0.0f, 0.0f); // Rojo
    glBegin(GL_QUADS);
        glVertex2f(-0.8f, 0.2f);
        glVertex2f(-0.4f, 0.2f);
        glVertex2f(-0.4f, 0.6f);
        glVertex2f(-0.8f, 0.6f);
    glEnd();
}

void drawTriangle() {
    glColor3f(0.0f, 1.0f, 0.0f); // Verde
    glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, 0.2f);
        glVertex2f(0.3f, 0.6f);
        glVertex2f(-0.3f, 0.6f);
    glEnd();
}

void drawStar() {
    glColor3f(0.0f, 0.0f, 1.0f); // Azul
    glBegin(GL_LINE_LOOP);
        glVertex2f(0.7f, 0.6f);
        glVertex2f(0.75f, 0.4f);
        glVertex2f(0.9f, 0.4f);
        glVertex2f(0.78f, 0.3f);
        glVertex2f(0.83f, 0.1f);
        glVertex2f(0.7f, 0.2f);
        glVertex2f(0.57f, 0.1f);
        glVertex2f(0.62f, 0.3f);
        glVertex2f(0.5f, 0.4f);
        glVertex2f(0.65f, 0.4f);
    glEnd();
}

void drawFan() {
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0f, 1.0f, 0.0f); // Centro amarillo
        glVertex2f(-0.2f, -0.3f);
        for (int i = 0; i <= 10; i++) {
            float angle = i * 2.0f * 3.14159f / 10;
            float x = -0.2f + 0.2f * cos(angle);
            float y = -0.3f + 0.2f * sin(angle);
            glColor3f((i % 3 == 0), (i % 3 == 1), (i % 3 == 2)); // Colores variados
            glVertex2f(x, y);
        }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawSquare();
    drawTriangle();
    drawStar();
    drawFan();

    glFlush();
}

void init() {
    glClearColor(1, 1, 1, 1);
    glPointSize(5);
    glLineWidth(2);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutCreateWindow("Figuras Coloridas con OpenGL");
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
