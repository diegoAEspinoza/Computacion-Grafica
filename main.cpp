
#ifdef _WIN32
#include <windows.h>
#endif
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <cstdlib>
#include <vector>
#include <iostream>


struct Asteroide {
    float radioX, radioZ;    
    float velocidadOrbita;   
    float anguloInicial;     
    float escala;            
    float ejeRotacion[3];    
    float velocidadRotacion; 
};

struct Orbita {
    std::vector<float> vertices;
    float radioX;
    float radioZ;
};

// Propiedades de la Camara
float camAngle = 0.5f, camRadius = 10.0f;  
float camY = 40.0f;
float camZoom = 0.05f;
float lookAtX = 0.0f, lookAtZ = 0.0f;

float camY_min = 10.0f;
float camY_max = 60.0f;

// VARIABLES GLOBALES
Orbita orbitas[8];
GLuint textureIDs[12]; 
std::vector<Asteroide> cinturonAsteroides;


float tiempo = 0.0f;

// CARGAR TEXTURAS
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

void cargarTexturas() {
    const char* filenames[] = {
        "./img/Sol.bmp", "./img/0PMercurio.bmp", "./img/1PVenus.bmp",
        "./img/2PTierra.bmp", "./img/3PMarte.bmp", "./img/4PJupiter.bmp",
        "./img/5PSaturno.bmp", "./img/6PUrano.bmp", "./img/7PNeptuno.bmp",
        "./img/rings.bmp","./img/estrellas.bmp","./img/asteroide.bmp" 
    };
    glGenTextures(12, textureIDs); 
    for (int i = 0; i < 12; ++i) { 
        crearTexture(filenames[i], textureIDs[i]);
    }
}




// CAMARA
void keyboard(unsigned char key, int x, int y) {
    switch (tolower(key)) {
        case 'w': 
            camRadius -= camZoom*10;
            if (camRadius < 2.0f) camRadius = 2.0f;
            break;
        case 's': 
            camRadius += camZoom*10;
            if (camRadius > 50.0f) camRadius = 50.0f;
            break;
        case 'a': 
            camAngle -= camZoom;
            break;
        case 'd': 
            camAngle += camZoom;
            break;
        case 'q': 
            camY -= camZoom*10;
            if (camY < camY_min) camY = camY_min; 
            break;
        case 'e': 
            camY += camZoom*10;
            if (camY > camY_max) camY = camY_max; 
            break;
        case 27: 
            exit(0);
            break;
    }

    glutPostRedisplay(); 
}

void camera() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 800.0 / 600.0, 0.1, 200.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float camX = camRadius * sin(camAngle);
    float camZ = camRadius * cos(camAngle);

    gluLookAt(
        camX, camY, camZ,          
        lookAtX, 0.5, lookAtZ,     
        0, 1, 0                    
    );
}

// Dibujo de Orbitas
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

void inicializarOrbitas() {
    float radiosX[] = {2.5, 4.0, 6.0, 8.0, 12.0, 15.0, 18.0, 21.0};
    float radiosZ[] = {2.0, 3.5, 5.5, 7.5, 11.0, 14.0, 17.0, 20.0};
    for (int i = 0; i < 8; i++) {
        calcularOrbita(radiosX[i], radiosZ[i], 100, orbitas[i]);
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

// Dibujo de Cinturon de Asteroides

float rand_float(float min, float max) {
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

void inicializarCinturon() {
    srand(time(NULL)); 
    int numAsteroides = 500; // Puedes aumentar o disminuir este número

    for (int i = 0; i < numAsteroides; i++) {
        Asteroide ast;

        ast.radioX = rand_float(8.5f, 10.5f);
        ast.radioZ = rand_float(8.0f, 10.0f);
        
        ast.velocidadOrbita = rand_float(0.1f, 0.5f);
        ast.anguloInicial = rand_float(0.0f, 360.0f);
        ast.escala = rand_float(0.06f, 0.09f);

        ast.ejeRotacion[0] = rand_float(-1.0f, 1.0f);
        ast.ejeRotacion[1] = rand_float(-1.0f, 1.0f);
        ast.ejeRotacion[2] = rand_float(-1.0f, 1.0f);
        ast.velocidadRotacion = rand_float(10.0f, 80.0f);

        cinturonAsteroides.push_back(ast);
    }
}

void dibujarCinturon() {
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    
    glBindTexture(GL_TEXTURE_2D, textureIDs[11]); 

    for (const auto& ast : cinturonAsteroides) {
        glPushMatrix();

        float angulo = tiempo * ast.velocidadOrbita + ast.anguloInicial;
        float x = cos(angulo) * ast.radioX;
        float z = sin(angulo) * ast.radioZ;

        glTranslatef(x, 0.0f, z);
        glRotatef(tiempo * ast.velocidadRotacion, ast.ejeRotacion[0], ast.ejeRotacion[1], ast.ejeRotacion[2]);
        

        GLUquadric* quad = gluNewQuadric();
        gluQuadricTexture(quad, GL_TRUE); 
        
        gluSphere(quad, ast.escala, 10, 10); 
        
        gluDeleteQuadric(quad);

        glPopMatrix();
    }
}



// Imagen de Fondo
void dibujarFondoEstrellado(GLuint textureID) {
    glPushMatrix();
    
    glDisable(GL_LIGHTING);
    glDepthMask(GL_FALSE); 

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    GLUquadric* quad = gluNewQuadric();
    gluQuadricTexture(quad, GL_TRUE);

    gluQuadricOrientation(quad, GLU_INSIDE);
    
    gluSphere(quad, 90.0, 100, 100); 
    
    gluDeleteQuadric(quad);
    
    glDepthMask(GL_TRUE);
    glEnable(GL_LIGHTING);
    
    glPopMatrix();
}

// Dibujo de Planetas
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
    float radioEsfera, float velocidadOrbita, const Orbita& orbita,
    GLuint planetaTextureID, 
    GLuint anilloTextureID = 0,  
    float inclinacionAnillo = 25.0f 
) {
    glPushMatrix(); 
        
        
        float angulo = tiempo * velocidadOrbita;
        float x = cos(angulo) * orbita.radioX;
        float z = sin(angulo) * orbita.radioZ;
        glTranslatef(x, 0.0f, z);

        glPushMatrix(); 
            glEnable(GL_LIGHTING);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, planetaTextureID);
            glRotatef(tiempo * 50.0f, 0.0f, 1.0f, 0.0f);
            
            GLUquadric* quad = gluNewQuadric();
            gluQuadricTexture(quad, GL_TRUE);
            gluSphere(quad, radioEsfera, 40, 40);
            gluDeleteQuadric(quad);
        glPopMatrix(); 

        
        if (anilloTextureID != 0) {
            glRotatef(inclinacionAnillo, 1.0f, 0.0f, 0.1f); 
            dibujarAnillo(radioEsfera + 0.15f, radioEsfera + 0.55f, 100, anilloTextureID);
        }

    glPopMatrix(); // Restaura el estado del universo
}

// Dibujado
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    camera();
    dibujarFondoEstrellado(textureIDs[10]); 
    
    dibujarCinturon();

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
    dibujarPlaneta(0.70, 0.9, orbitas[5], textureIDs[6], textureIDs[9]);
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
    inicializarCinturon();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Sistema Solar Animado");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(25, update, 0);

// Mostrar controles en consola
    std::cout << "Controles:\n";
    std::cout << "    Q: Para bajar la altura de la camara\n";
    std::cout << "    E: Para aumentar la altura de la camara\n";
    std::cout << "    D: Para girar en sentido antihorario de la camara\n";
    std::cout << "    A: Para girar en sentido horario de la camara\n";
    std::cout << "    W: Para disminuir la distancia de la camara al Eje Y\n";
    std::cout << "    S: Para aumentar la distancia de la camara al Eje Y\n";
    std::cout << "    Esc: Para salir de la simulacion\n";

    glutMainLoop();
    return 0;
}