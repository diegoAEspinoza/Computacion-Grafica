#include <GL/glut.h> // Or <GLUT/glut.h> on macOS
#include <cmath>
#include <cstdio> // For sprintf (or sprintf_s on Windows for safety)
#include <cstdlib> // For rand(), srand()
#include <ctime> // For time()
#include <iostream>
#include <vector>

// --- Constants ---
const float SCENARIO_MIN_X = -0.9f;
const float SCENARIO_MAX_X = 0.9f;
const float SCENARIO_MIN_Y = -0.9f;
const float SCENARIO_MAX_Y = 0.9f;
const float APPLE_RADIUS = 0.025f; // Made slightly smaller for better visual
const float SNAKE_RADIUS = 0.025f; // Same as apple
const float MOVE_STEP = 0.05f; // Snake movement step (should be 2 * RADIUS for perfect grid feel)
const int WIN_SCORE = 20;
const int TIMER_DELAY_MS = 150; // Speed of the game

// --- Structs ---
struct Point {
    float x, y;

    // Overload == for easy comparison, useful for self-collision on a grid
    bool operator==(const Point& other) const
    {
        // For floating point, exact comparison can be tricky.
        // If using a strict grid, this is fine. Otherwise, use a small epsilon.
        return std::fabs(x - other.x) < (MOVE_STEP / 2.0f) && std::fabs(y - other.y) < (MOVE_STEP / 2.0f);
    }
};

// --- Global Game State Variables ---
std::vector<Point> snake;
Point applePosition;
Point snakeDirection;
int score = 0;
bool gameOver = false;
bool victoryAchieved = false;
bool gamePaused = false; // Added pause functionality

// --- Utility Functions ---
void drawCircle(float cx, float cy, float r, int num_segments, float colR, float colG, float colB)
{
    glColor3f(colR, colG, colB);
    glBegin(GL_POLYGON);
    for (int ii = 0; ii < num_segments; ii++) {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void drawText(float x, float y, const char* string, float colR, float colG, float colB)
{
    glColor3f(colR, colG, colB);
    glRasterPos2f(x, y);
    for (const char* c = string; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

// --- Game Logic Functions ---
void spawnApple()
{
    // Keep spawning until apple is not on the snake
    bool onSnake;
    do {
        onSnake = false;
        // Spawn within scenario, trying to align to a potential grid based on MOVE_STEP
        int numStepsX = static_cast<int>((SCENARIO_MAX_X - SCENARIO_MIN_X - 2 * APPLE_RADIUS) / MOVE_STEP);
        int numStepsY = static_cast<int>((SCENARIO_MAX_Y - SCENARIO_MIN_Y - 2 * APPLE_RADIUS) / MOVE_STEP);

        if (numStepsX <= 0)
            numStepsX = 1;
        if (numStepsY <= 0)
            numStepsY = 1;

        applePosition.x = SCENARIO_MIN_X + APPLE_RADIUS + (rand() % numStepsX) * MOVE_STEP;
        applePosition.y = SCENARIO_MIN_Y + APPLE_RADIUS + (rand() % numStepsY) * MOVE_STEP;

        // Check if apple spawned on the snake
        for (const auto& segment : snake) {
            float dx = segment.x - applePosition.x;
            float dy = segment.y - applePosition.y;
            if (sqrt(dx * dx + dy * dy) < SNAKE_RADIUS + APPLE_RADIUS) {
                onSnake = true;
                break;
            }
        }
    } while (onSnake);
}

void resetGame()
{
    gameOver = false;
    victoryAchieved = false;
    gamePaused = false;
    score = 0;
    snake.clear();

    // Start snake in the middle, moving right
    snake.push_back({ (SCENARIO_MIN_X + SCENARIO_MAX_X) / 2.0f, (SCENARIO_MIN_Y + SCENARIO_MAX_Y) / 2.0f });
    snakeDirection = { MOVE_STEP, 0.0f };

    spawnApple();
    glutPostRedisplay();
}

bool checkCircleCollision(Point p1, float r1, Point p2, float r2)
{
    float dx = p1.x - p2.x;
    float dy = p1.y - p2.y;
    float distance = std::sqrt(dx * dx + dy * dy);
    return distance < (r1 + r2 - MOVE_STEP * 0.1f); // Subtract small epsilon to avoid "sticky" collisions
}

// --- GLUT Callback Functions ---
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Draw Scenario Border
    glColor3f(0.3f, 0.3f, 0.3f); // Dark Gray for border
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(SCENARIO_MIN_X - SNAKE_RADIUS, SCENARIO_MIN_Y - SNAKE_RADIUS);
    glVertex2f(SCENARIO_MAX_X + SNAKE_RADIUS, SCENARIO_MIN_Y - SNAKE_RADIUS);
    glVertex2f(SCENARIO_MAX_X + SNAKE_RADIUS, SCENARIO_MAX_Y + SNAKE_RADIUS);
    glVertex2f(SCENARIO_MIN_X - SNAKE_RADIUS, SCENARIO_MAX_Y + SNAKE_RADIUS);
    glEnd();
    glLineWidth(1.0f);

    if (gameOver) {
        drawText(-0.35f, 0.1f, "GAME OVER!", 1.0f, 0.2f, 0.2f);
        char finalScoreText[50];
        sprintf(finalScoreText, "Final Score: %d", score);
        drawText(-0.3f, 0.0f, finalScoreText, 1.0f, 1.0f, 1.0f);
        drawText(-0.45f, -0.1f, "Press 'R' to Restart or 'Q' to Quit", 0.8f, 0.8f, 0.8f);
    } else if (victoryAchieved) {
        drawText(-0.35f, 0.1f, "VICTORY!", 0.2f, 1.0f, 0.2f);
        char finalScoreText[50];
        sprintf(finalScoreText, "You reached %d points!", score);
        drawText(-0.4f, 0.0f, finalScoreText, 1.0f, 1.0f, 1.0f);
        drawText(-0.45f, -0.1f, "Press 'R' to Restart or 'Q' to Quit", 0.8f, 0.8f, 0.8f);
    } else if (gamePaused) {
        drawText(-0.25f, 0.0f, "PAUSED", 1.0f, 1.0f, 0.2f);
        drawText(-0.45f, -0.1f, "Press 'P' to Resume or 'Q' to Quit", 0.8f, 0.8f, 0.8f);
    } else { // Game is active
        // Draw Apple
        drawCircle(applePosition.x, applePosition.y, APPLE_RADIUS, 32, 1.0f, 0.0f, 0.0f); // Red

        // Draw Snake
        for (const auto& segment : snake) {
            drawCircle(segment.x, segment.y, SNAKE_RADIUS, 32, 0.0f, 0.5f, 1.0f); // Blue
        }

        // Display Score
        char scoreText[50];
        sprintf(scoreText, "Score: %d", score);
        drawText(SCENARIO_MIN_X + 0.02f, SCENARIO_MAX_Y + 0.03f, scoreText, 1.0f, 1.0f, 1.0f); // White
        drawText(SCENARIO_MIN_X + 0.02f, SCENARIO_MIN_Y - 0.08f, "P: Pause, Q: Quit", 0.7f, 0.7f, 0.7f);
    }

    glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height)
{
    if (height == 0)
        height = 1;
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Maintain a consistent viewing area regardless of window aspect ratio
    // This setup ensures the -1 to 1 range is always visible.
    // The game logic uses coordinates roughly within -0.9 to 0.9.
    if (width >= height) {
        gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
    } else {
        gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
    }
    // Ensure the scenario boundaries are well within the ortho projection
    // For example, gluOrtho2D(SCENARIO_MIN_X - 0.1, SCENARIO_MAX_X + 0.1, SCENARIO_MIN_Y - 0.1, SCENARIO_MAX_Y + 0.1);
    // If using the -1 to 1 range from gluOrtho2D, your scenario coordinates should match this.
    // The current setup is okay as SCENARIO_MIN/MAX are within -1 to 1.

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 'r':
    case 'R':
        if (gameOver || victoryAchieved) {
            resetGame();
        }
        break;
    case 'p':
    case 'P':
        if (!gameOver && !victoryAchieved) {
            gamePaused = !gamePaused;
            glutPostRedisplay(); // Update display to show paused message
        }
        break;
    case 'q':
    case 'Q':
    case 27: // Escape key
        exit(0); // Quit the game
        break;
    }
}

void specialKeys(int key, int x, int y)
{
    if (gameOver || victoryAchieved || gamePaused || snake.empty())
        return;

    Point currentDirection = snakeDirection; // Store current direction to prevent 180-degree turns

    switch (key) {
    case GLUT_KEY_UP:
        if (currentDirection.y == 0) { // Can only go up if not currently moving down (or up)
            snakeDirection = { 0.0f, MOVE_STEP };
        }
        break;
    case GLUT_KEY_DOWN:
        if (currentDirection.y == 0) { // Can only go down if not currently moving up (or down)
            snakeDirection = { 0.0f, -MOVE_STEP };
        }
        break;
    case GLUT_KEY_LEFT:
        if (currentDirection.x == 0) { // Can only go left if not currently moving right (or left)
            snakeDirection = { -MOVE_STEP, 0.0f };
        }
        break;
    case GLUT_KEY_RIGHT:
        if (currentDirection.x == 0) { // Can only go right if not currently moving left (or right)
            snakeDirection = { MOVE_STEP, 0.0f };
        }
        break;
    }
}

void updateGameLogic()
{
    if (gameOver || victoryAchieved || gamePaused || snake.empty()) {
        return; // Don't update game logic if game is over, won, or paused
    }

    // Calculate new head position
    Point newHead = snake.front();
    newHead.x += snakeDirection.x;
    newHead.y += snakeDirection.y;

    // Boundary collision check (head's center against scenario limits)
    if (newHead.x < SCENARIO_MIN_X || newHead.x > SCENARIO_MAX_X || newHead.y < SCENARIO_MIN_Y || newHead.y > SCENARIO_MAX_Y) {
        gameOver = true;
        std::cout << "Game Over: Wall Collision!" << std::endl;
        glutPostRedisplay();
        return;
    }

    // Self-collision check
    // Start checking from the second segment (index 1) because the head will always "collide" with itself (index 0 before moving)
    // For a more robust check, iterate through the snake body (excluding the current head before it's added)
    // The check should be against snake[i] for i > 0 after the new head has been inserted,
    // or against snake[i] for i >=0 before the old tail is popped (if not growing).
    for (size_t i = 0; i < snake.size(); ++i) { // Check against all current segments
        if (snake[i] == newHead) { // Using the overloaded == for Point
            // A more precise floating point check:
            // float dx_self = newHead.x - snake[i].x;
            // float dy_self = newHead.y - snake[i].y;
            // if (std::sqrt(dx_self*dx_self + dy_self*dy_self) < SNAKE_RADIUS * 0.5f) { // Stricter collision for self
            gameOver = true;
            std::cout << "Game Over: Self Collision!" << std::endl;
            glutPostRedisplay();
            return;
        }
    }

    // Add new head
    snake.insert(snake.begin(), newHead);

    // Apple collision check
    if (checkCircleCollision(newHead, SNAKE_RADIUS, applePosition, APPLE_RADIUS)) {
        score++;
        std::cout << "Score: " << score << std::endl;
        if (score >= WIN_SCORE) {
            victoryAchieved = true;
            std::cout << "Victory! You reached " << WIN_SCORE << " points!" << std::endl;
            glutPostRedisplay();
            return;
        }
        spawnApple(); // Spawn new apple
        // Snake grows, so we don't remove the tail segment this frame
    } else {
        // Didn't eat an apple, remove the tail segment
        snake.pop_back();
    }

    glutPostRedisplay(); // Tell GLUT to redraw the screen
}

void timer(int value)
{
    updateGameLogic();
    glutTimerFunc(TIMER_DELAY_MS, timer, 0); // Schedule next update
}

// --- OpenGL and Game Initialization ---
void initGL()
{
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f); // Dark grayish-blue background
}

int main(int argc, char** argv)
{
    srand(static_cast<unsigned int>(time(0))); // Seed random number generator

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 700); // Slightly larger window
    glutInitWindowPosition(100, 100);
    glutCreateWindow("C++ GLUT Snake Game");

    initGL();
    resetGame(); // Initialize game state

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutTimerFunc(TIMER_DELAY_MS, timer, 0); // Start the game loop timer

    std::cout << "Controls:" << std::endl;
    std::cout << "Arrow Keys: Move Snake" << std::endl;
    std::cout << "P: Pause/Resume Game" << std::endl;
    std::cout << "R: Restart Game (after Game Over or Victory)" << std::endl;
    std::cout << "Q or ESC: Quit Game" << std::endl;

    glutMainLoop();
    return 0;
}
