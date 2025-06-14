#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>
#include <iostream>
#include <string.h>

// VARIABLES GLOBALES
float rotX = 0, rotY = 0;
bool mousePressed = false;
int lastX, lastY;


// SIN ILUMINACIÓN
void Sin_Iluminacion() {
    // NO SE HACE CALCULOS DE ILUMINACION
    glDisable(GL_LIGHTING);
    // DEFINIMOS EL COLOR DEL OBJETO
    glColor3f(1.0f, 0.0f, 0.0f);
}

void ILuminacionAmbiental(){
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Luz Ambiental
    GLfloat luzAmbiental[]={0.5, 0.5, 0.5, 1};
    GLfloat luzDifusa[]={0, 0, 0, 1};
    GLfloat luzEspecular[]={0, 0, 0, 1};

    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiental);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);

    // Obejto
    GLfloat materialAmbiental[] = {0.8, 0.2, 0.2, 1};
    glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbiental);
}

void ILuminacionDifusa(){
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Luz Ambiental
    GLfloat posicionLuz[]={2, 2, 2, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, posicionLuz);
    
    GLfloat luzAmbiental[]={0.5, 0.5, 0.5, 1};
    GLfloat luzDifusa[]={0.8, 0.8, 0.8, 1};
    GLfloat luzEspecular[]={0, 0, 0, 1};

    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiental);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);

    // Obejto
    GLfloat materialAmbiental[] = {0.8, 0.2, 0.2, 1};
    GLfloat materialDifuso[] = {0.8, 0.2, 0.2, 1};
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbiental);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDifuso);
}

void ILuminacionEspecular(){
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat posicionLuz[]={2, 2, 2, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, posicionLuz);
    
    GLfloat luzAmbiental[]={0.5, 0.5, 0.5, 1};
    GLfloat luzDifusa[]={0.8, 0.8, 0.8, 1};
    GLfloat luzEspecular[]={1, 1, 1, 1};

    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiental);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);

    // Obejto
    GLfloat materialAmbiental[] = {0.8, 0.2, 0.2, 1};
    GLfloat materialDifuso[]    = {0.8, 0.2, 0.2, 1};
    GLfloat materialEspecular[] = {1, 1, 1, 1};
    GLfloat materialbrillo[]    = {20};

    glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbiental);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDifuso);
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialEspecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, materialbrillo);
}

void Iluminacion_Combinada(){
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    // Luz Principal GL_LIGHT0
    GLfloat posicionLuz_0[]={2, 2, 2, 1};
    GLfloat luzAmbiental_0[]={0.2, 0.2, 0.2, 1};
    GLfloat luzDifusa_0[]={0.8, 0.8, 0.8, 1};
    GLfloat luzEspecular_0[]={1, 1, 1, 1};

    glLightfv(GL_LIGHT0, GL_POSITION, posicionLuz_0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiental_0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa_0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular_0);

    GLfloat materialAmbiental[] = {0.8, 0.2, 0.2, 1};
    GLfloat materialDifuso[]    = {0.8, 0.2, 0.2, 1};
    GLfloat materialEspecular[] = {1, 1, 1, 1};
    GLfloat materialbrillo[]    = {20};

    glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbiental);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDifuso);
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialEspecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, materialbrillo);

    // Luz Secuandaria (GL_LIGHT1)
    GLfloat posicionLuz_1[]={-2, -2, 2, 1};
    GLfloat luzAmbiental_1[]={0.2, 0.2, 0.2, 1};
    GLfloat luzDifusa_1[]={0.8, 0.8, 0.8, 1};
    GLfloat luzEspecular_1[]={1, 1, 1, 1};

    glLightfv(GL_LIGHT0, GL_POSITION, posicionLuz_1);
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiental_1);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa_1);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular_1);

    GLfloat materialAmbiental_1[] = {0.8, 0.2, 0.2, 1};
    GLfloat materialDifuso_1[]    = {0.8, 0.2, 0.2, 1};
    GLfloat materialEspecular_1[] = {1, 1, 1, 1};
    GLfloat materialbrillo_1[]    = {20};

    glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbiental_1);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDifuso_1);
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialEspecular_1);
    glMaterialfv(GL_FRONT, GL_SHININESS, materialbrillo_1);
}

// MOSTRAR EN PANTALLA
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    // CÁMARA
    gluLookAt(
        0, 0, 5,
        0, 0, 0,
        0, 1, 0
    );

    // ROTACIÓN DE LA ESFERA
    glRotatef(rotX, 1, 0, 0);
    glRotatef(rotY, 0, 1, 0);

    // LLAMAMOS LA FUNCIÓN 1 DE ILUMINACIÓN
    // Sin_Iluminacion();
    // ILuminacionAmbiental();
    // ILuminacionDifusa();
    ILuminacionEspecular();

    // DIBUJAMOS UNA ESFERA SÓLIDA
        glColor3f(0.5,0.25,1);
        glutSolidCube(3);

    //glDisable(GL_LIGHTING);

    glutSwapBuffers();
}

// MANEJAR EVENTOS CUANDO SE HACE CLIC
void mouse(int button, int state, int x, int y) {
    if(button == GLUT_LEFT_BUTTON) {
        if(state == GLUT_DOWN) { // CUANDO SE PRESIONA
            mousePressed = true;
            lastX = x; // SE GUARDA LA POSICION X
            lastY = y; // SE GUARDA LA POSICION Y
        } else {
            mousePressed = false;
        }
    }
}

// PERMITEN RORTAR EL OBJETO
void mouseMotion(int x, int y) {
    if(mousePressed) {
        rotY += (x - lastX) * 0.5f;
        rotX += (y - lastY) * 0.5f;
        lastX = x;
        lastY = y;
        glutPostRedisplay();
    }
}

// AJUSTA EL AREA DE DIBUJO AL TAMAÑO DE LA VENTANA
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)w/h, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("ILUMINACION OpenGL - ESFERA 3D");

    // CONFIGURACION INICIAL
    glEnable(GL_DEPTH_TEST); // PRUEBA DE PROFUNDIDAD
    // PERMITE QUE LOS COLORES DEFINIDOS SE USEN COMO PARTE DEL MATERIAL DEL OBJETO
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    // HABILITAR NORMALIZACION AUTOMATICA
    glEnable(GL_NORMALIZE);

    // CALLBACKS
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutReshapeFunc(reshape);


    glutMainLoop();
    return 0;
}