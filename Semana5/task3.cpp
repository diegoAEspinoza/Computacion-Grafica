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
#include <cstddef> // For size_t
#include <string>
#include <sstream>
#include <ctime>


#define PI 3.141592f

// Estructura de un Objt (Comida)
struct Objt {
    float x;
    float y;
    float radius;
    bool isVisible;
};

// Estructura de un Segmento de la Serpiente
struct SnakeSegment {
    float x;
    float y;
};

// Contenedores
std::vector<Objt> foods; // Comida
std::vector<SnakeSegment> snake; // Serpiente

// Radios y Tamaños
float foodRadio = 0.15f;
float snakeSegmentRadio = 0.25f;
const int MAX_FOOD_ON_SCREEN = 1;

float paso = 0.15f;



// Colores
float   blanco[3] = {1, 1, 1}, rojo[3]       = {1, 0, 0},     verde_oscuro[3] = {0, 0.5f, 0};


// Limites de Pantalla
const float minB = -4.35f;
const float maxB = 4.35f;

// Estado del Juego
int score = 0;
bool gameOver = false;
bool playerWon = false; // NUEVO: Para rastrear si el jugador ganó
const int WINNING_SCORE = 20; // NUEVO: Puntuación para ganar

// Prototipos de funciones
void spawnNewFood(size_t foodIndex);
void resetGame();

// Inicio de la Comida
void initializeFood() {
    foods.clear();
    // srand(static_cast<unsigned int>(time(0))); // Semilla para números aleatorios - MOVIDO a resetGame o main para evitar re-seed frecuente si se llama varias veces
    // Es mejor sembrar una vez al inicio del programa o en resetGame.

    for (int i = 0; i < MAX_FOOD_ON_SCREEN; ++i) {
        foods.push_back({ 0, 0, foodRadio, false });
        spawnNewFood(i);
    }
}

// Coloca una comida en una nueva posición aleatoria (evitando la serpiente)
void spawnNewFood(size_t foodIndex) {
    if (foodIndex >= foods.size()) return;

    float minC = -4.5f; // Ligeramente dentro de los bordes para evitar que la comida se dibuje parcialmente fuera
    float maxC = 4.5f;
    float rango = maxC - minC;
    bool positionOK;
    float randomX, randomY;

    do {
        positionOK = true;
        randomX = minC + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * rango;
        randomY = minC + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * rango;

        // Verificar que no aparezca encima de la serpiente
        for (const auto& segment : snake) {
            float dx = segment.x - randomX;
            float dy = segment.y - randomY;
            float distSq = dx * dx + dy * dy;
            // Distancia mínima entre centros de comida y segmento de serpiente
            // Aumentar ligeramente el umbral para más espacio
            if (distSq < (snakeSegmentRadio + foodRadio + 0.1f) * (snakeSegmentRadio + foodRadio + 0.1f) ) {
                positionOK = false;
                break;
            }
        }
        // Adicional: Asegurar que la comida no esté demasiado cerca de los bordes si es grande
        if (randomX - foodRadio < minB || randomX + foodRadio > maxB ||
            randomY - foodRadio < minB || randomY + foodRadio > maxB) {
            positionOK = false;
        }


    } while (!positionOK);

    foods[foodIndex].x = randomX;
    foods[foodIndex].y = randomY;
    foods[foodIndex].radius = foodRadio;
    foods[foodIndex].isVisible = true;
}

// Reinicia el estado del juego
void resetGame() {
    snake.clear();
    snake.push_back({0, 0}); // Serpiente inicial

    // La semilla para números aleatorios es mejor aquí o en main una sola vez.
    // Si initializeFood se llama múltiples veces sin resetear el tiempo, rand() puede dar secuencias similares.
    // srand(static_cast<unsigned int>(time(0))); // Ya está en initializeFood globalmente, o mejor en main

    initializeFood();

    score = 0;
    gameOver = false;
    playerWon = false; // MODIFICADO: Resetear estado de victoria
    glutPostRedisplay();
}


// Dibuja un círculo completo
void drawCircle(float cx, float cy, float radius, float *RGB, int segments = 100) {
    glColor3fv(RGB);
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; ++i) {
        float theta = i * (2.0f * PI) / segments;
        float x1 = cx + radius * cosf(theta);
        float y1 = cy + radius * sinf(theta);
        glVertex2f(x1, y1);
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

// Detección de colisiones
void handleCollisions() {
    if (gameOver || snake.empty()) return; // Si el juego ya terminó (por victoria o derrota), no hacer nada más

    SnakeSegment& head = snake[0];

    // 1. Colisión Cabeza con Comida
    for (size_t i = 0; i < foods.size(); ++i) {
        if (foods[i].isVisible) {
            float dx = foods[i].x - head.x;
            float dy = foods[i].y - head.y;
            float distanciaCuadrada = dx * dx + dy * dy;

            float sumaRadios = snakeSegmentRadio + foods[i].radius;
            float sumaRadiosCuadrada = sumaRadios * sumaRadios;

            if (distanciaCuadrada <= sumaRadiosCuadrada) {
                SnakeSegment newSegment = snake.back();
                snake.push_back(newSegment);
                score++;

                // MODIFICADO: Comprobar condición de victoria
                if (score >= WINNING_SCORE) {
                    gameOver = true;
                    playerWon = true;
                    // No es necesario llamar a spawnNewFood si el juego ha terminado con victoria
                    // pero lo dejamos para que la comida desaparezca visualmente
                    foods[i].isVisible = false; // Ocultar la comida comida
                                                // Opcionalmente, podrías simplemente retornar aquí:
                    return; // El juego termina, no hay necesidad de buscar más colisiones este cuadro
                } else {
                    spawnNewFood(i); // Mueve la comida a una nueva posición si el juego continúa
                }
            }
        }
    }

    // Si playerWon se hizo true arriba y retornamos, esta parte no se ejecuta.
    // Si el juego no ha sido ganado, entonces comprobar auto-colisión.

    // 2. Colisión Cabeza con Cuerpo (Auto-colisión)
 /*    for (size_t i = 1; i < snake.size(); ++i) { // Empezar desde 1 (el segmento después de la cabeza)
        float dx_self = snake[i].x - head.x;
        float dy_self = snake[i].y - head.y;
        float distSq_self = dx_self * dx_self + dy_self * dy_self;

        // Umbral para colisión: si la distancia entre centros es menor que un radio
        // O un poco menos para que sea más visual la colisión.
        // Un umbral más pequeño como (snakeSegmentRadio * 0.5f)^2 puede ser más permisivo.
        // El original (snakeSegmentRadio * snakeSegmentRadio * 0.25f) es (radio/2)^2, bastante estricto.
        // Usemos una distancia basada en los radios para ser más claro, ej. si se tocan.
        // Si la distancia es menor que (radio_cabeza + radio_segmento)/2 o algo así.
        // O simplemente si los centros están muy cerca.
        // El umbral original es (0.5 * snakeSegmentRadio)^2. Lo que significa que la cabeza
        // debe superponerse significativamente.
        // Si la distancia es menor que el diámetro (o radio) de un segmento.
        if (distSq_self < (snakeSegmentRadio * snakeSegmentRadio * 0.9f)) { // Ajustado ligeramente, antes 0.25f
                                                                          // Una colisión más robusta sería distSq_self < (snakeSegmentRadio * snakeSegmentRadio)
                                                                          // o incluso distSq_self < (2*snakeSegmentRadio)^2 si no deben ni tocarse los bordes.
                                                                          // Pero para snake, es común que la cabeza se superponga un poco antes de morir.
                                                                          // La condición original de 0.25f * radio^2 es muy pequeña, la cabeza casi debe estar encima del centro de un segmento.
                                                                          // Usemos un valor más grande para la detección, por ejemplo, si la distancia es menor que un radio.
                                                                          // if (distSq_self < snakeSegmentRadio * snakeSegmentRadio) { // centros a menos de 1 radio de distancia
            gameOver = true;
            playerWon = false; // MODIFICADO: Asegurar que no es una victoria
            return; // El juego termina por auto-colisión.
        }
    } */
}

// Mueve la serpiente
void moveSnake(float dx_step, float dy_step) {
    if (gameOver || snake.empty()) return;

    float potentialX = snake[0].x + dx_step;
    float potentialY = snake[0].y + dy_step;

    // Límites reales para el centro de la cabeza
    float limitLeft   = minB + snakeSegmentRadio;
    float limitRight  = maxB - snakeSegmentRadio;
    float limitBottom = minB + snakeSegmentRadio;
    float limitTop    = maxB - snakeSegmentRadio;

    float newHeadX = snake[0].x; // Por defecto, no se mueve si está en el borde y intenta cruzar
    float newHeadY = snake[0].y;


    // Validar y limitar (Eje X)
    if (dx_step != 0) { // Solo actualiza si hay movimiento en X
        if (potentialX < limitLeft)   newHeadX = limitLeft;
        else if (potentialX > limitRight)  newHeadX = limitRight;
        else newHeadX = potentialX;
    } else {
        newHeadX = snake[0].x; // Mantener X si no hay movimiento horizontal
    }

    // Validar y limitar (Eje Y)
    if (dy_step != 0) { // Solo actualiza si hay movimiento en Y
         if (potentialY < limitBottom) newHeadY = limitBottom;
         else if (potentialY > limitTop)    newHeadY = limitTop;
         else newHeadY = potentialY;
    } else {
        newHeadY = snake[0].y; // Mantener Y si no hay movimiento vertical
    }


    // Verificar si la cabeza realmente se movió. Si golpeó un borde y no pudo moverse,
    // no actualizar el cuerpo para evitar que el cuerpo "alcance" a la cabeza detenida.
    bool headMoved = (newHeadX != snake[0].x || newHeadY != snake[0].y);

    if (headMoved) {
        for (size_t i = snake.size() - 1; i > 0; --i) {
            snake[i] = snake[i - 1];
        }
        snake[0].x = newHeadX;
        snake[0].y = newHeadY;
    }

    glutPostRedisplay();
}

void ProcessSpecialKeys( int key, int x, int y ) {
    if (gameOver) return;
    switch (key) {
        case GLUT_KEY_UP:    moveSnake(0, paso); break;
        case GLUT_KEY_DOWN:  moveSnake(0, -paso); break;
        case GLUT_KEY_LEFT:  moveSnake(-paso, 0); break;
        case GLUT_KEY_RIGHT: moveSnake(paso, 0); break;
    }
}

void keyboard(unsigned char key, int x, int y){
    if (gameOver) {
        if (toupper(key) == 'R') {
            resetGame();
        }
        return; // Importante: retornar aquí para no procesar otras teclas si el juego terminó
    }

    switch (toupper(key)) {
        case 'W': moveSnake(0, paso); break;
        case 'S': moveSnake(0, -paso); break;
        case 'A': moveSnake(-paso, 0); break;
        case 'D': moveSnake(paso, 0); break;
    }
}


void display(void) {
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    // Dibujar borde
    glColor3fv(blanco);
    glBegin(GL_LINE_LOOP);
        glVertex2f(maxB,maxB); // Usar maxB para consistencia con límites de serpiente
        glVertex2f(minB,maxB); // Usar minB
        glVertex2f(minB,minB);
        glVertex2f(maxB,minB);
    glEnd();

    // Las colisiones deben manejarse ANTES de dibujar, idealmente después de mover.
    // Dado que moveSnake llama a glutPostRedisplay, y display llama a handleCollisions,
    // el orden es: input -> moveSnake -> (collision check in next display) -> display.
    // Esto es común.
    handleCollisions(); // Comprobar colisiones en cada cuadro

    // Dibujar Comida(s)
    for (const auto& foodItem : foods) {
        if (foodItem.isVisible) {
            drawCircle(foodItem.x, foodItem.y, foodItem.radius, rojo);
        }
    }

    // Dibujar Serpiente
    if (!snake.empty()) {
        // Dibujar cabeza de un color diferente (opcional)
        // drawCircle(snake[0].x, snake[0].y, snakeSegmentRadio, algun_color_cabeza);
        // for (size_t i = 0; i < snake.size(); ++i) { // Empezar desde 0 si la cabeza es del mismo color
        for (const auto& segment : snake) {
             drawCircle(segment.x, segment.y, snakeSegmentRadio, verde_oscuro);
        }
    }

    // Texto del Juego
    if (gameOver) {
        if (playerWon) {
            std::string msg = "¡HAS GANADO!";
            drawText(-0.9f, 0.3f, verde_oscuro, GLUT_BITMAP_TIMES_ROMAN_24, msg);
        } else {
            std::string msg = "¡GAME OVER!";
            drawText(-0.9f, 0.3f, rojo, GLUT_BITMAP_TIMES_ROMAN_24, msg); 
        }

        std::string restartMsg = "Presiona 'R' para reiniciar";
        drawText(-1.6f, -0.3f, blanco, GLUT_BITMAP_HELVETICA_18, restartMsg);

        std::ostringstream finalScoreStream;
        finalScoreStream << "Puntos finales: " << score;
        drawText(-1.2f, -0.7f, blanco, GLUT_BITMAP_HELVETICA_18, finalScoreStream.str());

    } else {
        std::ostringstream scoreStream;
        scoreStream << "Puntos: " << score << " / " << WINNING_SCORE; 
        std::string scoreText = scoreStream.str();
        drawText(minB + 0.2f, maxB - 0.3f, blanco, GLUT_BITMAP_HELVETICA_18, scoreText);
    }

    glutSwapBuffers();
}


void initGL() {
    int a = 5;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-a, a, -a, a);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0,0,0,0);
    
    resetGame();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(50,50);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE );
    glutCreateWindow("Snake Game");
    initGL();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(ProcessSpecialKeys);
    


    glutMainLoop();

    return EXIT_SUCCESS;
}