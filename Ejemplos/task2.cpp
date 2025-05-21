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
#include <cstdlib>
#define PI 3.14159265358979323846f


float amarillo[3]     = {1, 1, 0},
      blanco[3]       = {1, 1, 1},
      negro[3]        = {0,0,0};

void drawElipse(
    float x, float y,                       
    float radiusX, float radiusY,                                   
    const float *RGB, 
    int segments = 300,
    float pivotX = 0, float pivotY = 0,               
    float orbitAngleRad = 0) {

    glColor3fv(RGB);
    glBegin(GL_POLYGON);

    float cosOrbit = cosf(orbitAngleRad);
    float sinOrbit = sinf(orbitAngleRad);

    for (int i = 0; i < segments; ++i) {
        float base_theta = ((float)i / (float)segments) * (2.0f * PI);
        
        float cx = radiusX * cosf(base_theta);
        float cy = radiusY * sinf(base_theta);
        
        float relativePivotX = (x + cx) - pivotX;
        float relativePivotY = (y + cy) - pivotY;
        
        float x_rotated = relativePivotX * cosOrbit - relativePivotY * sinOrbit;
        float y_rotated = relativePivotX * sinOrbit + relativePivotY * cosOrbit;
        
        
        glVertex2f(x_rotated + pivotX, y_rotated + pivotY);
    }
    glEnd();
}


void drawRingSector(
    float cx, float cy, 
    float radius_inner, float radius_outer,
    float t1, float t2,
    float *RGB1,
    int segments = 300) 
{
    glColor3fv(RGB1);
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= segments; i++) {
        float theta = t1 + i * (t2 - t1) / segments;
        
        float x_outer = cx + radius_outer * cosf(theta);
        float y_outer = cy + radius_outer * sinf(theta);
        
        float x_inner = cx + radius_inner * cosf(theta);
        float y_inner = cy + radius_inner * sinf(theta);
        
        glVertex2f(x_outer, y_outer);
        glVertex2f(x_inner, y_inner);
    }
    glEnd();
}

void drawRectangulo(
    float cx, float cy,
    float width, float height,
    const float *RGB,
    float pivotX=0, float pivotY=0,
    float rotationAngleRad=0) {

    glColor3fv(RGB);

    float cosAngle = cosf(rotationAngleRad);
    float sinAngle = sinf(rotationAngleRad);

    // Esquina inferior izquierda
    float p1x = cx;              float p1y = cy;
    
    // Esquina inferior derecha
    float p2x = cx + width;       
    float p2y = cy;

    // Esquina superior derecha
    float p3x = cx + width;       
    float p3y = cy + height;

    // Esquina superior izquierda
    float p4x = cx;               
    float p4y = cy + height;


    // Vértice 1 
    float tx1 = p1x - pivotX; 
    float ty1 = p1y - pivotY;
    float p1x_rotated = (tx1 * cosAngle - ty1 * sinAngle) + pivotX;
    float p1y_rotated = (tx1 * sinAngle + ty1 * cosAngle) + pivotY;

    // Vértice 2
    float tx2 = p2x - pivotX;
    float ty2 = p2y - pivotY;
    float p2x_rotated = (tx2 * cosAngle - ty2 * sinAngle) + pivotX;
    float p2y_rotated = (tx2 * sinAngle + ty2 * cosAngle) + pivotY;

    // Vértice 3 
    float tx3 = p3x - pivotX;
    float ty3 = p3y - pivotY;
    float p3x_rotated = (tx3 * cosAngle - ty3 * sinAngle) + pivotX;
    float p3y_rotated = (tx3 * sinAngle + ty3 * cosAngle) + pivotY;

    // Vértice 4 
    float tx4 = p4x - pivotX;
    float ty4 = p4y - pivotY;
    float p4x_rotated = (tx4 * cosAngle - ty4 * sinAngle) + pivotX;
    float p4y_rotated = (tx4 * sinAngle + ty4 * cosAngle) + pivotY;

    
    glBegin(GL_POLYGON);
    glVertex2f(p1x_rotated, p1y_rotated);
    glVertex2f(p2x_rotated, p2y_rotated);
    glVertex2f(p3x_rotated, p3y_rotated);
    glVertex2f(p4x_rotated, p4y_rotated);
    glEnd();
}



// Función de renderizado
void display(void)
{
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);

    // Triangulos
    drawElipse(0,0,5.65,5.65,negro,3,0,0,PI/2);
    for(int i=0; i<3; i++){

        float r= 5.4;
        float t = PI/2;
        float t1 = 2*PI/3;

        float x1 = r*cosf(i*t1 +t),y1 = r*sinf(i*t1+t);
        float x2 = (r-0.1)*cosf(i*t1+t),y2 = (r-0.1)*sinf(i*t1+t);
        float x3 = (r-0.45)*cosf(i*t1+t),y3 = (r-0.45)*sinf(i*t1+t);
        
        // Limpieza
        drawElipse(x1,y1,0.25,0.25,blanco);
        drawElipse(x2,y2,0.25,0.25,blanco);

        // Dibujo Real
        drawElipse(x3,y3,0.35,0.35,negro);
    }

    drawElipse(0,0,4.8,4.8,amarillo,3,0,0,PI/2);
    
   // Elipse
    drawElipse(0,1,1.37,1.48,negro);
    drawElipse(0,1,1.37,1.48,negro,100,0,0,2*PI/3);
    drawElipse(0,1,1.37,1.48,negro,100,0,0,4*PI/3);

    // Circunferencias
    for(int i=0; i<3; i++){

        float r= 1.52;
        float t = PI/2;
        float t1 = 2*PI/3;

        float x = r*cosf(i*t1 +t),y = r*sinf(i*t1+t);
        drawElipse(x,y,0.97,0.97,amarillo);
    }
  
    // Circulo Pequeño
    drawElipse(0,0,0.25,0.25,amarillo);

    // Coronas
    drawRingSector(0,0,0.9,1.35,PI/3,2*PI/3,negro);
    drawRingSector(0,0,0.9,1.35,PI,4*PI/3,negro);
    drawRingSector(0,0,0.9,1.35,-PI/3,0,negro);

    // Rectangulos
    drawRectangulo(-0.05,0.2,0.1,0.6,amarillo);
    drawRectangulo(-0.05,0.2,0.1,0.6,amarillo,0,0,2*PI/3);
    drawRectangulo(-0.05,0.2,0.1,0.6,amarillo,0,0,4*PI/3);


    glutSwapBuffers();
    glFlush();
}

// Función de inicialización de OpenGL
void initialize()
{   
    int a = 6;
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-a,a,-3,a); 
    glClearColor(0, 0, 0, 0);
}


// Función principal
int main(int argc, char *argv[])
{   
    int size = 450;
    int with = 400;

    glutInit(&argc, argv);
    glutInitWindowSize(size, with);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Logo: Riesgo Biologico");

    initialize();

    glutDisplayFunc(display);

    glutMainLoop();

    return EXIT_SUCCESS; 
}
