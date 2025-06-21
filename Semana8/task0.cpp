#ifdef _WIN32
#include <windows.h>
#endif
#ifdef __APPLE__
#include <GLUT/freeglut.h>
#else
#include <GL/freeglut.h>
#endif


#include <stdlib.h>
#include <math.h>
#include <cstdlib>
#include <iostream>
#include <string.h>

// VARIABLES GLOBALES
float rotX = 0, rotY = 0;
bool mousePressed = false;
int lastX, lastY;


GLuint textureID;


unsigned char* loadBMP(const char* filename, int& width, int& height) {
    FILE* file = fopen(filename, "rb");

    if (!file) {
        std::cout << "No existe el archivo: " << filename << std::endl;
        return nullptr;
    }

    // Ir al byte 18 para leer width y height
    fseek(file, 18, SEEK_SET);
    fread(&width, sizeof(int), 1, file);
    fread(&height, sizeof(int), 1, file);

    // Ir al offset 54 para empezar a leer datos de píxeles
    fseek(file, 54, SEEK_SET);

    int imageSize = width * height * 3; // 3 bytes por píxel (RGB)
    unsigned char* data = new unsigned char[imageSize];

    fread(data, 1, imageSize, file);

    for(int i=0; i<imageSize; i+=3){
        std::swap(data[i], data[i+2]);
    }

    fclose(file); // Cerrar el archivo

    return data;
}

void crearTexture(const char* filename){
    int width, height;

    unsigned char* data= loadBMP(filename, width, height);

    if(!data) return;

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0 , GL_RGB, GL_UNSIGNED_BYTE, data);

}

void iluminacion(){
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat PosicionLuz[] = {2.0, 2.0, 2.0, 1.0};

    glLightfv(GL_LIGHT0, GL_POSITION, PosicionLuz);

    glClearColor(0.5,0.5,0.5, 1);

    crearTexture("./img/tierra.bmp");
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
    
    iluminacion();
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,textureID);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glTexGend(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGend(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);


    //glColor3f(0.88,0.25,0.55);
    //glutSolidTeapot(1);
    glutSolidSphere(1,40,40);
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_2D);

    glutSwapBuffers();
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
    glutCreateWindow("Tetera Texturisada");

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