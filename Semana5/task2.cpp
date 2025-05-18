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
#include <iostream>



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
    float dx = 0;
    float dy = -1;
};

// Contenedores
std::vector<Objt> foods; // Comida
std::vector<SnakeSegment> snake; // Serpiente

// Radios y Tamaños
float foodRadio = 0.15f;
float snakeSegmentRadio = 0.25f;
const int MAX_FOOD_ON_SCREEN = 1;

float paso = 0.1f;



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







void spawnNewFood(size_t foodIndex) {
    if (foodIndex >= foods.size()) return;

    float minC = -4.5f; 
    float maxC = 4.5f;
    float rango = maxC - minC;
    bool positionOK;
    float randomX, randomY;

    do {
        positionOK = true;
        randomX = minC + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * rango;
        randomY = minC + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * rango;

        for (const auto& segment : snake) {
            float dx = segment.x - randomX;
            float dy = segment.y - randomY;
            float distSq = dx * dx + dy * dy;
            if (distSq < (snakeSegmentRadio + foodRadio + 0.1f) * (snakeSegmentRadio + foodRadio + 0.1f) ) {
                positionOK = false;
                break;
            }
        }
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


// Inicio de la Comida
void initializeFood() {
    foods.clear();
    for (int i = 0; i < MAX_FOOD_ON_SCREEN; ++i) {
        foods.push_back({ 0, 0, foodRadio, false });
        spawnNewFood(i);
    }
}

// Reinicio
void resetGame() {
    snake.clear();
    snake.push_back({0, 0}); 
    initializeFood();

    score = 0;
    gameOver = false;
    playerWon = false; 
    glutPostRedisplay();
}



// Dibuja un sector circular (usado para serpiente y comida)
void drawSector(float cx, float cy, float radius,float *RGB,int segments=100) {
    glColor3fv(RGB);
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; ++i) {
        float theta = i * (2*PI) / segments;
        float x1 = cx + radius * cosf(theta);
        float y1 = cy + radius * sinf(theta);
        glVertex2f(x1, y1);
    }
    glEnd();
    }


// Dibuja un texto en pantalla en una posicion especifica

void drawText(float x, float y, float *RGB, void* font, const std::string &text) {
    glColor3fv(RGB);
    glRasterPos2f(x, y); 

    for (char c : text) { 
        glutBitmapCharacter(font, c);
    }
}


void collision() {
    if (gameOver || snake.empty()) return; 

    SnakeSegment& head = snake[0];
    for (size_t i = 0; i < foods.size(); ++i) {
        if (foods[i].isVisible) {
            float dx = foods[i].x - head.x;
            float dy = foods[i].y - head.y;
            float distanciaCuadrada = dx * dx + dy * dy;

            float sumaRadios = snakeSegmentRadio + foods[i].radius;
            float sumaRadiosCuadrada = sumaRadios * sumaRadios;

            if (distanciaCuadrada <= sumaRadiosCuadrada) {
                SnakeSegment last = snake.back();
                float dx = last.dx;
                float dy = last.dy;

                if (dx == 0 && dy == 0) {dx = 0;dy = -1;}

                SnakeSegment newSegment;
                float segmentDiameter = 2 * snakeSegmentRadio;
                newSegment.x = last.x + dx * segmentDiameter;
                newSegment.y = last.y + dy * segmentDiameter;
                newSegment.dx = dx;
                newSegment.dy = dy;

                snake.push_back(newSegment);

                score++;

                if (score >= WINNING_SCORE) {
                    gameOver = true;
                    playerWon = true;
                   
                    foods[i].isVisible = false; 
                                            
                    return;
                } else {
                    spawnNewFood(i);
                }
            }
        }
    }


}

// Movimiento de la serpiente
void moveSnake(float dx_step, float dy_step) {
    if (gameOver || snake.empty()) return;

    float potentialX = snake[0].x + dx_step;
    float potentialY = snake[0].y + dy_step;

    float limitLeft   = minB + snakeSegmentRadio;
    float limitRight  = maxB - snakeSegmentRadio;
    float limitBottom = minB + snakeSegmentRadio;
    float limitTop    = maxB - snakeSegmentRadio;

    float newHeadX = snake[0].x; 
    float newHeadY = snake[0].y;


    
    if (dx_step != 0) { 
        if (potentialX < limitLeft)   newHeadX = limitLeft;
        else if (potentialX > limitRight)  newHeadX = limitRight;
        else newHeadX = potentialX;
    } else {
        newHeadX = snake[0].x; 
    }

    
    if (dy_step != 0) { 
         if (potentialY < limitBottom) newHeadY = limitBottom;
         else if (potentialY > limitTop)    newHeadY = limitTop;
         else newHeadY = potentialY;
    } else {
        newHeadY = snake[0].y; 
    }


    bool headMoved = (newHeadX != snake[0].x || newHeadY != snake[0].y);

    if (headMoved) {
        for (size_t i = snake.size() - 1; i > 0; --i) {
            snake[i].x = snake[i - 1].x;
            snake[i].y = snake[i - 1].y;
            snake[i].dx = snake[i - 1].dx;
            snake[i].dy = snake[i - 1].dy;
        }
        snake[0].x = newHeadX;
        snake[0].y = newHeadY;
        snake[0].dx = dx_step;
        snake[0].dy = dy_step;
    }

    glutPostRedisplay();
}

// Definicion de teclas especiales
void ProcessSpecialKeys( int key, int x, int y ) {
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
        return; 
    }

    switch (toupper(key)) {
        case 'W': moveSnake(0, paso); break;
        case 'S': moveSnake(0, -paso); break;
        case 'A': moveSnake(-paso, 0); break;
        case 'D': moveSnake(paso, 0); break;
        case 'Q': exit(0); break;
    }

}


void display(void) {
    glClearColor(0, 0, 0, 0);  
    glClear(GL_COLOR_BUFFER_BIT);

    // Cuadro
    glColor3f(1,1,1);
    glBegin(GL_LINE_LOOP);
        glVertex2f(maxB,maxB);
        glVertex2f(-maxB,maxB);
        glVertex2f(-maxB,-maxB);
        glVertex2f(maxB,-maxB);
    glEnd();


    // Verificar colisiones
    collision();

    // Objetos Visibles
    for (const auto& objt : foods) { 
        if (objt.isVisible) {
            drawSector(objt.x, objt.y, objt.radius,rojo);
        }
    }

    if (!snake.empty()) {
        float head_x = snake[0].x;
        float head_y = snake[0].y;
        float dir_x = snake[0].dx;
        float dir_y = snake[0].dy; 

      
        float line_length = snakeSegmentRadio * 1.5f; 

        float norm_dx = 0.0f;
        float norm_dy = 0.0f;

        float current_direction_length = sqrt(dir_x * dir_x + dir_y * dir_y);

        if (current_direction_length > 0.0001f) {
            norm_dx = dir_x / current_direction_length;
            norm_dy = dir_y / current_direction_length;
        } else {
            norm_dx = 0.0f;
            norm_dy = -1.0f; 
        }

        float line_end_x = head_x + norm_dx * line_length;
        float line_end_y = head_y + norm_dy * line_length;
        
        glColor3f(1.0f, 0.0f, 0.0f); 
        glBegin(GL_LINES);
            glVertex2f(head_x, head_y);         
            glVertex2f(line_end_x, line_end_y); 
        glEnd();

        for (const auto& segment : snake) {
            drawSector(segment.x, segment.y, snakeSegmentRadio, verde_oscuro);
        }
        

    }




    // Texto del Juego
    if (gameOver) {
        if (playerWon) {
            std::string msg = "¡HAS GANADO!";
            drawText(-0.9f, 0.3f, verde_oscuro, GLUT_BITMAP_TIMES_ROMAN_24, msg);
            snake.clear();

        } else {
            std::string msg = "¡GAME OVER!";
            drawText(-0.9f, 0.3f, rojo, GLUT_BITMAP_TIMES_ROMAN_24, msg);
            snake.clear();

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

    initializeFood();
    resetGame(); 

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
    
    std::cout << "Controles:" << std::endl;
    std::cout << "WASD or Flechas: Mover la Serpiente" << std::endl;
    std::cout << "P: Pausar/Reanudar el juego" << std::endl;
    std::cout << "R: Reiniciar el juego (después de perder)" << std::endl;
    std::cout << "Q: Salir del juego" << std::endl;

    glutMainLoop();

    return EXIT_SUCCESS; 
}