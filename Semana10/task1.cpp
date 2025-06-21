#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <cstdlib>
#include <iostream> 


struct WindowConfig {
    int x;
    int y;
    const char* title;
    void (*displayFunc)(void);      
    void (*reshapeFunc)(int, int);  
};


void Linea(float *X0, float *X1, float *C, float A = 1, int f = 1, int P = 0)
{
    glColor3fv(C);
    glLineWidth(A);
    glEnable(GL_LINE_STIPPLE);
    switch (P){
        case 1: glLineStipple (f, 0x0101); break;
        case 2: glLineStipple (f, 0xAAAA); break;
        case 3: glLineStipple (f, 0x00FF); break;
        case 4: glLineStipple (f, 0x0c0F); break;
        case 5: glLineStipple (f, 0x1C47); break;
        default: glLineStipple (f, 0xFFFF); break;
    }
    glBegin(GL_LINES);
    glVertex3fv(X0);
    glVertex3fv(X1);
    glEnd();
    glDisable(GL_LINE_STIPPLE);
    glLineWidth(1);
}

void Ejes(int c){
    float P[]={-20.0,0.0,0.0} , P1[]={20.0,0.0,0.0};
    float P2[]={0.0,-20.0,0.0}, P3[]={0.0,20.0,0.0};
    float P4[]={0.0,0.0,-20.0} , P5[]={0.0,0.0,20.0};
    float C1[]={1,0,0}, C2[]={0,0,1}, C3[]={0,1,0};
    switch (c){ // linea punteada
    case 0:{
        Linea(P,P1,C1,2,2,1);
        Linea(P2,P3,C2,2,2,1);
        Linea(P4,P5,C3,2,2,1);
        break;
    }
    default :{ // linea solida de grosor c
        Linea(P,P1,C1,c);
        Linea(P2,P3,C2,c);
        Linea(P4,P5,C3,c);
        }
    }
}



void display1(void) {

    glClearColor (0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity ();

    gluLookAt (2,15,8, 0, 0.1, 0, 0.0, 1.0, 0.0);
    
    Ejes(2);

    GLdouble eqn1[4] = { 0.0, 1.0, 0.0, 0.0 };
    glEnable (GL_CLIP_PLANE0);
    glClipPlane (GL_CLIP_PLANE0, eqn1);
    glColor3f(0.3,0.4,0.2);
    glutWireTeapot(2.0);    
    glDisable(GL_CLIP_PLANE0);

  glClear(GL_DEPTH_BUFFER_BIT);

glutSwapBuffers();
}

void display2(){
glClearColor (0.0, 0.0, 0.0, 0.0);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glLoadIdentity ();
     gluLookAt (0,0,17, 0, 0.1, 0, 0.0, 1.0, 0.0);
    
    Ejes(2);

    GLdouble eqn1[4] = { 0.0, 1.0, 0.0, 0.0 };
    glEnable (GL_CLIP_PLANE0);
    glClipPlane (GL_CLIP_PLANE0, eqn1);
    glColor3f(0.3,0.4,0.2);
    glutWireTeapot(2.0);    
    glDisable(GL_CLIP_PLANE0);

  glClear(GL_DEPTH_BUFFER_BIT);

glutSwapBuffers();
}
void display3(){
glClearColor (0.0, 0.0, 0.0, 0.0);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glLoadIdentity ();

    gluLookAt (2,8,11, 0, 0.1, 0, 0.0, 1.0, 0.0);

    Ejes(2);

   GLdouble eqn2[4] = { 0.0, -1.0, 0.0, 0.0 };
    glEnable (GL_CLIP_PLANE1);
    glClipPlane (GL_CLIP_PLANE1, eqn2);
    glColor3f(1,0.1,0.2);
    glutWireTeapot(2.0);
    glDisable(GL_CLIP_PLANE1);

glutSwapBuffers();

}
void display4(){
glClearColor (0.0, 0.0, 0.0, 0.0);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glLoadIdentity ();

     gluLookAt (0,0,17, 0, 0.1, 0, 0.0, 1.0, 0.0);

    Ejes(2);

   GLdouble eqn2[4] = { 0.0, -1.0, 0.0, 0.0 };
    glEnable (GL_CLIP_PLANE1);
    glClipPlane (GL_CLIP_PLANE1, eqn2);
    glColor3f(1,0.1,0.2);
    glutWireTeapot(2.0);
    glDisable(GL_CLIP_PLANE1);

glutSwapBuffers();

}
void display5(){
glClearColor (0.0, 0.0, 0.0, 0.0);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glLoadIdentity ();


    gluLookAt (0,0,17, 0, 0.1, 0, 0.0, 1.0, 0.0);

    Ejes(2);

    GLdouble eqn1[4] = { 0.0, 1.0, 0.0, 0.0 };
    glEnable (GL_CLIP_PLANE0);
    glClipPlane (GL_CLIP_PLANE0, eqn1);
    glColor3f(0.3,0.4,0.2);
    glutWireTeapot(2.0);    
    glDisable(GL_CLIP_PLANE0);

    glColor3f(1,0,0);
    glutWireSphere(0.5,20,20);

    glDisable(GL_CLIP_PLANE1);


glutSwapBuffers();

}

void display8(){
glClearColor (0.0, 0.0, 0.0, 0.0);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glLoadIdentity ();


    gluLookAt (2,8,11, 0, 0.1, 0, 0.0, 1.0, 0.0);

    Ejes(2);

    GLdouble eqn1[4] = { 0.0, 1.0, 0.0, 0.0 };
    glEnable (GL_CLIP_PLANE0);
    glClipPlane (GL_CLIP_PLANE0, eqn1);
    glColor3f(0.3,0.4,0.2);
    glutWireTeapot(2.0);    
    glDisable(GL_CLIP_PLANE0);

    glColor3f(1,0,0);
    glutWireSphere(0.5,20,20);

    glDisable(GL_CLIP_PLANE1);


glutSwapBuffers();

}

void display6(){
glClearColor (0.0, 0.0, 0.0, 0.0);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glLoadIdentity ();
    gluLookAt (2,8,11, 0, 0.1, 0, 0.0, 1.0, 0.0);

Ejes(2);

    GLdouble eqn1[4] = { 0.0, 1.0, 0.0, 0.0 };
    glEnable (GL_CLIP_PLANE0);
    glClipPlane (GL_CLIP_PLANE0, eqn1);
    glColor3f(0.3,0.4,0.2);

    glutWireTeapot(2.0);
    glDisable(GL_CLIP_PLANE0);



  glClear(GL_DEPTH_BUFFER_BIT); 

    GLdouble eqn2[4] = { 0.0, -1.0, 0.0, 0.0 };
    glEnable (GL_CLIP_PLANE1);
    glClipPlane (GL_CLIP_PLANE1, eqn2);
    glColor3f(1,0.1,0.2);

    glutWireTeapot(2.0);
    glDisable(GL_CLIP_PLANE1);

glutSwapBuffers();

}

void display7(){
glClearColor (0.0, 0.0, 0.0, 0.0);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glLoadIdentity ();
    gluLookAt (0,0,17, 0, 0.1, 0, 0.0, 1.0, 0.0);

Ejes(2);

    GLdouble eqn1[4] = { 0.0, 1.0, 0.0, 0.0 };
    glEnable (GL_CLIP_PLANE0);
    glClipPlane (GL_CLIP_PLANE0, eqn1);
    glColor3f(0.3,0.4,0.2);

    glutWireTeapot(2.0);
    glDisable(GL_CLIP_PLANE0);



  glClear(GL_DEPTH_BUFFER_BIT); 

    GLdouble eqn2[4] = { 0.0, -1.0, 0.0, 0.0 };
    glEnable (GL_CLIP_PLANE1);
    glClipPlane (GL_CLIP_PLANE1, eqn2);
    glColor3f(1,0.1,0.2);

    glutWireTeapot(2.0);
    glDisable(GL_CLIP_PLANE1);
glutSwapBuffers();

}


void reshape (int w, int h) {
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(25.0, (GLfloat)w/(GLfloat)h, 1.0, 100.0);
    glMatrixMode (GL_MODELVIEW);
}

int main(int argc, char *argv[])
{
 WindowConfig windows[] = {
        // Fila 1
        {1,   50, "1",       display1, reshape},
        {315, 50, "2",       display2, reshape},
        {630, 50, "3", display3, reshape},
        {945, 50, "4",  display4, reshape},

        // Fila 2
        {1,   350, "5",  display5, reshape},
        {315, 350, "6",    display8, reshape},
        {630, 350, "7",    display7, reshape},
        {945, 350, "8",    display6, reshape},

    };

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(300, 300);

    int num_windows = sizeof(windows) / sizeof(WindowConfig);
    for (int i = 0; i < num_windows; i++) {
        glutInitWindowPosition(windows[i].x, windows[i].y);
        glutCreateWindow(windows[i].title);
        glutDisplayFunc(windows[i].displayFunc);
        glutReshapeFunc(windows[i].reshapeFunc);
        
    }
    glutMainLoop();

    return EXIT_SUCCESS;
}
