#include <stdlib.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <GL/glut.h>

struct Orbita {
    std::vector<float> vertices;
    float radioX;
    float radioZ;
};

// VARIABLES GLOBALES
Orbita orbitas[8];
GLuint textureIDs[10]; // <-- MODIFICADO: Aumentado a 10 para la textura del anillo

float tiempo = 0.0f;

void calcularOrbita(float rx, float rz, int num_segmentos, Orbita &orbita) {
    orbita.vertices.clear();
    orbita.radioX = rx;
    orbita.radioZ = rz;

    for (int i = 0; i <= num_segmentos; i++) {
        float angulo = 2.0f * M_PI * float(i) / float(num_segmentos);
        float x = cos(angulo) * rx;
        float z = sin(angulo) * rz;
        orbita.vertices.push_back(x);
        orbita.vertices.push_back(0.0f);
        orbita.vertices.push_back(z);
    }
}

void dibujarOrbita(const Orbita &orbita) {
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    glColor3f(0.6f, 0.6f, 0.6f);
    glBegin(GL_LINE_LOOP);
    for (size_t i = 0; i < orbita.vertices.size(); i += 3) {
        glVertex3f(orbita.vertices[i], orbita.vertices[i+1], orbita.vertices[i+2]);
    }
    glEnd();
}

unsigned char* loadBMP(const char* filename, int& width, int& height) {
    FILE* file = fopen(filename, "rb");

    if (!file) {
        std::cout << "No existe el archivo: " << filename << std::endl;
        return nullptr;
    }
    fseek(file, 18, SEEK_SET);
    fread(&width, sizeof(int), 1, file);
    fread(&height, sizeof(int), 1, file);

    fseek(file, 54, SEEK_SET);

    int imageSize = width * height * 3;
    unsigned char* data = new unsigned char[imageSize];

    fread(data, 1, imageSize, file);

    for(int i = 0; i < imageSize; i += 3) {
        std::swap(data[i], data[i + 2]);
    }

    fclose(file);

    return data;
}

void crearTexture(const char* filename, GLuint& textureID) {
    int width, height;

    unsigned char* data = loadBMP(filename, width, height);

    if (!data) return;

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    delete[] data;
}

void inicializarOrbitas() {
    float radiosX[] = {2.5, 4.0, 6.0, 8.0, 11.0, 14.0, 17.0, 20.0};
    float radiosZ[] = {2.0, 3.5, 5.5, 7.5, 10.0, 13.0, 16.0, 19.0};
    for (int i = 0; i < 8; i++) {
        calcularOrbita(radiosX[i], radiosZ[i], 100, orbitas[i]);
    }
}

void cargarTexturas() {
    const char* filenames[] = {
        "./img/Sol.bmp", "./img/0PMercurio.bmp", "./img/1PVenus.bmp",
        "./img/2PTierra.bmp", "./img/3PMarte.bmp", "./img/4PJupiter.bmp",
        "./img/5PSaturno.bmp", "./img/6PUrano.bmp", "./img/7PNeptuno.bmp",
        "./img/rings.bmp"
    };
    glGenTextures(10, textureIDs); // <-- MODIFICADO: a 10 texturas
    for (int i = 0; i < 10; ++i) { // <-- MODIFICADO: el bucle ahora va hasta 10
        crearTexture(filenames[i], textureIDs[i]);
    }
}

void dibujarAnillo(float radioInterior, float radioExterior, int num_segmentos, GLuint textureID) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glDisable(GL_LIGHTING);    

    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= num_segmentos; i++) {
        float angulo = 2.0f * M_PI * float(i) / float(num_segmentos);
        float x = cos(angulo);
        float z = sin(angulo);

        // Vértice exterior
        glTexCoord2f(float(i) / float(num_segmentos), 1.0f);
        glVertex3f(x * radioExterior, 0.0f, z * radioExterior);

        // Vértice interior
        glTexCoord2f(float(i) / float(num_segmentos), 0.0f);
        glVertex3f(x * radioInterior, 0.0f, z * radioInterior);
    }
    glEnd();
    
    glEnable(GL_LIGHTING);
}


void dibujarPlaneta(
    float radioEsfera, float velocidadOrbita,
    const Orbita& orbita, GLuint textureID) {

    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glPushMatrix();
        float angulo = tiempo * velocidadOrbita;
        float x = cos(angulo) * orbita.radioX;
        float z = sin(angulo) * orbita.radioZ;
        glTranslatef(x, 0.0f, z);

        glRotatef(tiempo * 50.0f, 0.0f, 1.0f, 0.0f);

        GLUquadric* quad = gluNewQuadric();
        gluQuadricTexture(quad, GL_TRUE);
        gluSphere(quad, radioEsfera, 40, 40);
        gluDeleteQuadric(quad);
    glPopMatrix();
}

// <-- NUEVO: Función especializada para dibujar a Saturno con su anillo
void dibujarPlanetaConAnillo(
    float radioEsfera, float velocidadOrbita, const Orbita& orbita,
    GLuint planetaTextureID, GLuint anilloTextureID) {
    
    glPushMatrix(); // Guarda la matriz de vista del universo
        // Calcula la posición en la órbita (igual que en dibujarPlaneta)
        float angulo = tiempo * velocidadOrbita;
        float x = cos(angulo) * orbita.radioX;
        float z = sin(angulo) * orbita.radioZ;
        glTranslatef(x, 0.0f, z);

        // --- Dibujar el Planeta (Saturno) ---
        glPushMatrix(); // Guarda la matriz de la posición de Saturno
            glEnable(GL_LIGHTING);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, planetaTextureID);
            glRotatef(tiempo * 50.0f, 0.0f, 1.0f, 0.0f); // Rotación del planeta sobre su eje
            GLUquadric* quad = gluNewQuadric();
            gluQuadricTexture(quad, GL_TRUE);
            gluSphere(quad, radioEsfera, 40, 40);
            gluDeleteQuadric(quad);
        glPopMatrix(); // Restaura la matriz a la posición de Saturno

        // --- Dibujar el Anillo ---
        // El anillo no debe rotar sobre el eje Y como el planeta, pero sí debe inclinarse.
        glRotatef(25.0f, 1.0f, 0.0f, 0.1f); // Inclinación del anillo (25 grados sobre el eje X)
        dibujarAnillo(0.85f, 1.25f, 100, anilloTextureID);

    glPopMatrix(); // Restaura la matriz de vista del universo
}

// Dibujado
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, 45, 30, 0, 0, 0, 0, 1, 0);

    for (int i = 0; i < 8; i++) {
        dibujarOrbita(orbitas[i]);
    }

    // El Sol
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureIDs[0]);
        GLUquadric* quad = gluNewQuadric();
        gluQuadricTexture(quad, GL_TRUE);
        gluSphere(quad, 1.5, 40, 40);
        gluDeleteQuadric(quad);

    // Mercurio
    dibujarPlaneta(0.20, 4.7, orbitas[0], textureIDs[1]);
    // Venus
    dibujarPlaneta(0.35, 3.5, orbitas[1], textureIDs[2]);
    // Tierra
    dibujarPlaneta(0.40, 2.9, orbitas[2], textureIDs[3]);
     // Marte
    dibujarPlaneta(0.30, 2.4, orbitas[3], textureIDs[4]);
     // Júpiter
    dibujarPlaneta(0.80, 1.3, orbitas[4], textureIDs[5]);
    // Saturno
    dibujarPlanetaConAnillo(0.70, 0.9, orbitas[5], textureIDs[6], textureIDs[9]);
    // Urano
    dibujarPlaneta(0.60, 0.6, orbitas[6], textureIDs[7]);
    // Neptuno
    dibujarPlaneta(0.55, 0.5, orbitas[7], textureIDs[8]);

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (h == 0) h = 1;
    gluPerspective(45.0, (float)w/h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void update(int value) {
    tiempo += 0.005f;
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void init() {
    glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat lightPos[] = { 0.0, 0.0, 0.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    GLfloat ambient[] = { 0.3, 0.3, 0.3, 1.0 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    cargarTexturas();
    inicializarOrbitas();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Sistema Solar Animado");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(25, update, 0);

    glutMainLoop();
    return 0;
}