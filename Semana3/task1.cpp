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
#include <cstddef> 
#include <string>    
#include <sstream>   
#include <ctime>     


#define PI 3.141592f


// Estructura de un Objt 
struct Objt {
    float x;
    float y;
    float radius;
    bool isVisible;
};

// Contenedor Objts
std::vector<Objt> objts;
float objtRadioComun = 0.15;
const int NUM_OBJETOS = 10; 

// Variables Globales 
// Pacman
float ejeX  = 0,           ejeY  = 0;
float radio = 0.5;
float t1 = 0.25*PI, t2 = 1.75*PI; 

// Movimiento y Crecimiento
float crece = 0.05; 
float paso = 0.15; 

// Colores
float   amarillo[3]     = {1, 1, 0},
        rojo[3]       = {1, 0, 0},
        blanco[3]     = {1, 1, 1},
        negro[3]      = {0, 0, 0};

// Limites de Pantalla
const float minB = -5.0f;
const float maxB = 4.5f;

// Game
int score = 0;        
bool gameWon = false; 

// Inicio de Objts
void initializeObjects() {
    float minC = -4.5f;
    float maxC = 4.5f;
    float rango = maxC - minC;

    for (int i = 0; i < NUM_OBJETOS; ++i) {
        // Posición aleatoria
        float randomX = minC + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * rango;
        float randomY = minC + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * rango;

        objts.push_back({ randomX, randomY, objtRadioComun, true });
    }
    score = 0;
    gameWon = false;
}


// Dibujos
void drawSector(float cx, float cy, float radius, float t1, float t2, int n, float *RGB) {
    glColor3fv(RGB);
    float segments = (t2 - t1) / n;
  
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; ++i) {
      float theta = t1 + i * segments ;
      float theta2 = t1 + (i + 1) * segments;
      
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

void drawText(float x, float y, float *RGB, void* font, const std::string &text) {
    glColor3fv(RGB);
    glRasterPos2f(x, y); 

    for (char c : text) { 
        glutBitmapCharacter(font, c);
    }
}


void collision() {
    for (std::vector<Objt>::size_type i = 0; i < objts.size(); ++i) {
        if (objts[i].isVisible) {
            float dx = objts[i].x - ejeX;
            float dy = objts[i].y - ejeY;
            float distanciaCuadrada = dx * dx + dy * dy;

            float sumaRadios = radio + objts[i].radius;
            float sumaRadiosCuadrada = sumaRadios * sumaRadios;

            if (distanciaCuadrada <= sumaRadiosCuadrada) {
                objts[i].isVisible = false; 
                radio += crece;
                
                score++; 
                if (score >= NUM_OBJETOS) {
                    gameWon = true;
                }
            }
        }
    }
}

void move(float dx, float dy, float new_t1, float new_t2) {
    if (gameWon) return;

    // Calcular la nueva posición 
    float potentialX = ejeX + dx;
    float potentialY = ejeY + dy;

    // Calcular los límites reales
    float limitLeft   = minB + radio;
    float limitRight  = maxB - radio;
    float limitBottom = minB + radio;
    float limitTop    = maxB - radio;

    // Validar y limitar (Eje X)
    if (potentialX < limitLeft) {
        ejeX = limitLeft;

    } else if (potentialX > limitRight) {
        ejeX = limitRight;

    } else {
        ejeX = potentialX; 
    }

    // Validar y limitar (Eje Y)
    if (potentialY < limitBottom) {
        ejeY = limitBottom;
    } else if (potentialY > limitTop) {
        ejeY = limitTop;
    } else {
        ejeY = potentialY; 
    }

    t1 = new_t1;
    t2 = new_t2;

    glutPostRedisplay();
}

void ProcessSpecialKeys( int key, int x, int y ) {
    switch (key) {
        case GLUT_KEY_UP:
            move(0, paso, 0.75*PI, 2.25*PI); 
            break;
        case GLUT_KEY_DOWN:
            move(0, -paso, 1.75*PI, 3.25*PI); 
            break;
        case GLUT_KEY_LEFT:
            move(-paso, 0, 1.25*PI, 2.75*PI); 
            break;
        case GLUT_KEY_RIGHT:
            move(paso, 0, 0.25*PI, 1.75*PI); 
            break;
    }
}

void keyboard(unsigned char key, int x, int y){
    switch (toupper(key)) {
        case 'W':
            move(0, paso, 0.75*PI, 2.25*PI);
            break;
        case 'S':
            move(0, -paso, 1.75*PI, 3.25*PI);
            break;
        case 'A':
            move(-paso, 0, 1.25*PI, 2.75*PI);
            break;
        case 'D':
            move(paso, 0, 0.25*PI, 1.75*PI);
            
            break;
    }
}


void display(void) {
    glClearColor(0, 0, 0, 0);  
    glClear(GL_COLOR_BUFFER_BIT);


    // Verificar colisiones
    collision();

    // Objetos Visibles
    for (const auto& objt : objts) { 
        if (objt.isVisible) {
            drawSector(objt.x, objt.y, objt.radius, 0, 2 * PI, 30, rojo); 
        }
    }

    // Pacman
    drawSector(ejeX, ejeY, radio, t1, t2, 50, amarillo);

    // Texto
    if (gameWon) {
        std::string winMsg = "¡GAME OVER!";
        drawText(-0.48, 0, blanco, GLUT_BITMAP_TIMES_ROMAN_24, winMsg);
    } else {
        // Int >> String
        std::ostringstream scoreStream;
        scoreStream << "Puntos: " << score;
        std::string scoreText = scoreStream.str();
        
        drawText(-4.8f, 4.5f, blanco, GLUT_BITMAP_HELVETICA_18, scoreText);
    }

    glutSwapBuffers();  
}




void inicio()
{   
    int a = 5;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluOrtho2D(-a,a,-a,a);
    glClearColor(0,0,0,0);

    initializeObjects();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv); 
    glutInitWindowSize(600,600);
    glutInitWindowPosition(50,50);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE );


    glutCreateWindow("PACMAN");
    inicio();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(ProcessSpecialKeys);
    
    glutMainLoop();

    return EXIT_SUCCESS; 
}