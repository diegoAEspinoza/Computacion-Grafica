// Nombre: Diego A. Espinoza


#ifdef _WIN32
#include <windows.h>
#endif
#ifdef __APPLE__
#include <GLUT/freeglut.h>
#else
#include <GL/freeglut.h>
#endif

#include <cmath>
#include <cctype>
#include <cstdlib>
#include <iostream> 

// Dimensiones de la Pantalla
int windowWidth = 800;
int windowHeight = 600;

// 
int op = 1;
float camX = 2.0f,
      camY = 10.0f,
      camZ = 10.0f;


void keyboard(unsigned char key, int x, int y) {
    switch (tolower(key)) {
        case 'q': 
            camX = 10.0f,
            camY = 0.0f,
            camZ = 0.0f;
            break;
        case 'w': 
            camX = 0.0f,
            camY = 10.0f,
            camZ = 0.3f;
            break;
        case 'e': 
            camX = 2.0f,
            camY = 10.0f,
            camZ = 10.0f;
            break;
        case 'r': 
            camX = 0.0f,
            camY = 0.0f,
            camZ = 10.0f;
            break;
        case 't': 
            camX = 0.0f,
            camY = 0.0f,
            camZ = -10.0f;
            break;
        case 'a': 
            if (op==1)
            {
               op=0;
            }else{
               op=1; 
            }
            
            break;
        case 27: 
            exit(0);
            break;
    }

    glutPostRedisplay(); 
}

void camera(float camX, float camY, float camZ) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 800.0 / 600.0, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        camX, camY, camZ,          
        0, 0.5, 0,     
        0, 1, 0                    
    );
}

void drawCoordinateAxes() {
    glBegin(GL_LINES);
    // Eje X en Rojo
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-10.0f, 0.0f, 0.0f);
    glVertex3f(10.0f, 0.0f, 0.0f);
    // Eje Y en Verde
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -10.0f, 0.0f);
    glVertex3f(0.0f, 10.0f, 0.0f);
    // Eje Z en Azul
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -10.0f);
    glVertex3f(0.0f, 0.0f, 10.0f);
    glEnd();
}

void avion(){
 glPushMatrix();
        glColor3f(0.75, 0.75, 0.75);
        GLdouble eqn2[4] = { 0.0, -1.0, 0.0, 0.0 };
        glEnable (GL_CLIP_PLANE1);
        glClipPlane (GL_CLIP_PLANE1, eqn2);
        glTranslated(0,0,-2);
        
        if(op==1){
            glutSolidCylinder(1,4,100,100);
        }else{
            glutWireCylinder(1,4,50,50);
        }
        glDisable(GL_CLIP_PLANE1);
    glPopMatrix();
    
    glPushMatrix();
        glColor3f(0.65, 0.65, 0.65);
        glTranslated(0,0,-2);
                if(op==1){
        glutSolidCylinder(1,1,100,100);
        }else{
        glutWireCylinder(1,1,15,15);
        }
    glPopMatrix();
    
    glPushMatrix();
        glColor3f(0.65, 0.65, 0.65);
        glTranslated(0,0,2);

                if(op==1){
        glutSolidCylinder(1,1,100,100);
        }else{
        glutWireCylinder(1,1,15,15);
        }

    glPopMatrix();
    
    glPushMatrix();
        glColor3f(0.65, 0.65, 0.65);
        GLdouble eqn3[4] = { 0.0, 0.0, -1.0, 4 };
        glEnable (GL_CLIP_PLANE1);
        glClipPlane (GL_CLIP_PLANE1, eqn3);
        glTranslated(0,0,3);

               if(op==1){
        glutSolidCone(1,2,100,100);
        }else{
        glutWireCone(1,2,50,50);
        }
        glDisable(GL_CLIP_PLANE1);
    glPopMatrix();

    
    glPushMatrix();
        glColor3f(0.55, 0.55, 0.55);
        glTranslated(0,0,4.1);

               if(op==1){
        glutSolidSphere(0.5,100,100);
        }else{
        glutWireSphere(0.5,50,50);
        }

        glDisable(GL_CLIP_PLANE1);
    glPopMatrix();

    glPushMatrix();
        GLdouble eqn4[4] = { 0.0, 0.0, 1.0, 5 };
        glEnable (GL_CLIP_PLANE1);
        glClipPlane (GL_CLIP_PLANE1, eqn4);
        glRotated(180,0,1,0);
        glTranslated(0,0,2);
               if(op==1){
        glutSolidCone(1,4,200,200);
        }else{
        glutWireCone(1,4,50,50);
        }
        glDisable(GL_CLIP_PLANE1);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.55, 0.55, 0.55);
        glTranslated(0,0,-5.5);
        if(op==1){
        glutSolidCylinder(0.35,0.45,100,100);
        }else{
        glutWireCylinder(0.35,0.45,15,15);
        }
    glPopMatrix();

    // Alas Traceras
    glPushMatrix();
        glColor3f(0.95, 0.95, 0.95);
        glTranslated(0,0,-5.25);
        glScalef(4.0f, 0.1f, 0.42f);
                   if(op==1){
        glutSolidSphere(0.5,100,100);
        }else{
        glutWireSphere(0.5,10,10);
        }  
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.95, 0.95, 0.95);
        glTranslated(0,0,-5.28);
        glScalef(0.1f, 4.0f, 0.42f);  
        if(op==1){
            glutSolidSphere(0.5,100,100);}
        else{glutWireSphere(0.5,10,10);}  
    glPopMatrix();
  
    // Ala grande
    glPushMatrix();
        glColor3f(0.75, 0.75, 0.75);
        glTranslated(0,-0.5,0);
        glScalef(10.0f, 0.05f, 2.5f);
    if(op==1){
        glutSolidSphere(0.5,100,100);;}
        else{glutWireSphere(0.5,50,50);;}  
    glPopMatrix();
}

void displayScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    camera(camX,camY,camZ);
    drawCoordinateAxes(); 
    avion();
    glutSwapBuffers();
}

void reshape(int width, int height) {
    if (height == 0) {
        height = 1;
    }
    float ratio = 1.0 * width / height;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Escena en 3D - Avion");

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);

    glutDisplayFunc(displayScene);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

        // Mostrar controles en consola
    std::cout << "Controles:\n";
    std::cout << "    Q: Vista Lateral\n";
    std::cout << "    W: Vista Superior\n";
    std::cout << "    E: Vista Normal\n";
    std::cout << "    R: Vista Frontal\n";
    std::cout << "    T: Vista Tracera\n";
    std::cout << "    A: Cambiar Modo\n";
    std::cout << "    Esc: Para salir de la simulacion\n";

    glutMainLoop();
    return 0;
}