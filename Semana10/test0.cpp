// Nombre: Diego A. Espinoza
// Codigo Corregido

#ifdef __APPLE__
#include <GLUT/glut.h>

#else
#include <GL/glut.h>
#endif

#define M_PI 3.14159
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <cstdlib>
#include <iostream> 

// Propiedades de la Camara
float camX = 0.0f,
      camY = 40.0f,
      camZ = 0.3f;



void keyboard(unsigned char key, int x, int y) {
    switch (tolower(key)) {
        case 'a': 
            camX = 0.0f,
            camY = 40.0f,
            camZ = 0.3f;
            break;
        case 's': 
            camX = 0.0f,
            camY = 0.0f,
            camZ = 40.0f;
            break;
        case 'd': 
            camX = 40.0f,
            camY = 0.0f,
            camZ = 0.0f;
            break;
        case 27: 
            exit(0);
            break;
    }

    glutPostRedisplay(); 
}

void inicio()
{

    float a=40;
    glMatrixMode(GL_PROJECTION);

    gluOrtho2D(-a,a,-80,80);
    glClearColor(1,1,1,1);
    glEnable(GL_DEPTH_TEST);
}


//


void Linea(float *X0, float *X1, float *C, float A = 1, int f = 1, int P = 0){

    glColor3fv(C);
    glLineWidth(A);
    glEnable(GL_LINE_STIPPLE); switch (P){
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
    glLineWidth(1); }



void Ejes(int c){
    float P[]={-100.0,0.0,0.0} , P1[]={100.0,0.0,0.0}; float P2[]={0.0,-100.0,0.0}, P3[]={0.0,50.0,0.0}; float P4[]={0.0,0.0,-100.0} , P5[]={0.0,0.0,100.0}; float C1[]={1,0,0}, C2[]={0,0,1}, C3[]={0,1,0}; switch (c){ // linea punteada
        case 0:{ Linea(P,P1,C1,2,2,0); Linea(P2,P3,C2,2,2,0); Linea(P4,P5,C3,2,2,0); break;
        }
        default :{ // linea solida de grosor c
            Linea(P,P1,C1,c); Linea(P2,P3,C2,c); Linea(P4,P5,C3,c);
        } }
}


//FUNCIONES DE RUEDA

void glutSolidCylinder(float r,float h,int n,int m)
{
    glPushMatrix();
    glRotatef(90,1.0F,0.0F,0.0F);
    glTranslatef(0.0F,0.0F,-h/2);
    GLUquadricObj *qobj = gluNewQuadric();//gluNewQuadric: la funcion es devolver un puntero a un objeto quadric que luego se usa en funcione de control
    // GLUquadricObj es un tipo de objeto para manejar geometrias cuadricas (esferas, cilindros..)
    gluQuadricDrawStyle(qobj,GLU_FILL);// tambien puede ser gluQuadricTexture/ gluQuadricNormals
    gluCylinder(qobj,r,r,h,n,m);
    gluDeleteQuadric(qobj);
    glPopMatrix();
}

void circunferencia(double *XY, float R,float *C, int M=1, int G=3, float inicio=0, float fin=2*M_PI)
{
    glColor3fv(C);
    switch(M)
    {
        case 2: {
            glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
            glPointSize(G);
            break;
        }
        case 3: {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glLineWidth(G);
            break;
        }
        default: glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    glBegin(GL_POLYGON);
    for (float i=inicio; i<=fin;i=i+0.01)
    {
        glVertex2f(R*cos(i)+XY[0],R*sin(i)+XY[1]);
    }

    glEnd();


}
void marcasderueda(float *C,float radio,float radio2)
{
    glColor3fv(C);
    for (float i=0; i<=2.0*M_PI;i=i+72*M_PI/180.0)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glBegin(GL_POLYGON);
        glVertex2f((radio+(radio2-radio)/2)*cos(i+65*M_PI/360.0),(radio+(radio2-radio)/2)*sin(i+65*M_PI/360.0));
        for (float j=i; j<=i+65*M_PI/180.0;j=j+0.01)
        {
            glVertex2f(radio*cos(j),radio*sin(j));
        }
        for (float k=i+65*M_PI/180.0; k>=i;k=k-0.01)
        {
            glVertex2f((radio2)*cos(k),(radio2)*sin(k));
        }
        glVertex2f(radio*cos(i),radio*sin(i));
        glEnd();
    }
}

void Rueda(float radio)
{
    double A[]={0,0};
    float Color1[]={0.6,0.6,0.6};
    float Color2[]={0.102,0.102,0.102};
    float Color3[]={0.31,0.31,0.31};
    //CILINDRO TRASERA
    circunferencia(A, radio, Color2);

    //CILINDRO CENTRAL
    glColor3fv(Color3);
    glPushMatrix();
    glTranslated(0, 0, 2);
    glRotated(90,1,0,0);
    glutSolidCylinder(radio,4,60,10);
    glPopMatrix();

    //CIRCUNFERENCIA MAYOR DELANTERA
    glPushMatrix();
    glTranslated(0, 0, 4);
    circunferencia(A, radio, Color2);
    glPopMatrix();

    //CIRCUNFERENCIA GRIS MEDIANA
    glPushMatrix();
    glTranslated(0, 0, 4.01);
    circunferencia(A, radio-radio*2.0/6.0, Color1);
    glPopMatrix();

    //CIRCUNFERENCIA NEGRA PEQUEÑA
    glPushMatrix();
    glTranslated(0, 0, 4.02);
    circunferencia(A, radio-radio*0.75, Color2);
    glPopMatrix();


    //CIRCUNFERENCIA GRIS PEQUEÑA
    glPushMatrix();
    glTranslated(0, 0, 4.03);
    circunferencia(A, radio-radio*0.75-0.1, Color1);
    glPopMatrix();

    //MARCAS GRISES OSCURO DE LAS RUEDAS
    glPushMatrix();
    glTranslated(0, 0, 4.04);
    marcasderueda(Color3,radio-radio*0.75+0.4,radio-radio*2.0/6.0-0.4);
    glPopMatrix();

}
//FUNCIONES PERNO
void pentagono(double *XY, float R,float *C, int M=1, int G=3, float inicio=0, float fin=2*M_PI)
{
    glColor3fv(C);
    switch(M)
    {
        case 2: {
            glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
            glPointSize(G);
            break;
        }
        case 3: {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glLineWidth(G);
            break;
        }
        default: glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    glBegin(GL_POLYGON);
    for (float i=inicio; i<=fin;i=i+72.0*M_PI/180.0)
    {
        glVertex2f(R*cos(i)+XY[0],R*sin(i)+XY[1]);
    }

    glEnd();


}
void Perno(float radio)
{
    double A[]={0,0};
    float Color1[]={0.412,0.412,0.412};
    float Color2[]={0.102,0.102,0.102};
    float Color3[]={0.31,0.31,0.31};
    float Color4[]={0.85,0.85,0.85};
    //CILINDRO DETRAS
    glColor3fv(Color1);
    glPushMatrix();
    glTranslated(0,0, -3*radio);
    glRotated(90,1,0,0);
    glutSolidCylinder(3*radio/4,6*radio,50,10);
    glPopMatrix();

    //CILINDRO INTERMEDIO
    glColor3fv(Color4);
    glPushMatrix();
    glTranslated(0, 0, (3*radio/8)/2);
    glRotated(90,1,0,0);
    glutSolidCylinder(7*radio/4,3*radio/8,50,10);
    glPopMatrix();

    //CIRCUNFERENCIA GRANDE
    glPushMatrix();
    glTranslated(0, 0, 3*radio/8);
    circunferencia(A, 7*radio/4, Color3);
    glPopMatrix();

    //PENTAGONO CILINDRO
    glColor3fv(Color1);
    glPushMatrix();
    glTranslated(0, 0, 7*radio/8);
    glRotated(90,1,0,0);
    glutSolidCylinder(3*radio/2,radio,5,10);
    glPopMatrix();

    //PENTAGONO
    glPushMatrix();
    glTranslated(0,0, 11*radio/8);
    glRotated(36, 0, 0, 1);
    pentagono(A,3*radio/2,Color3,1,3,18*M_PI/180);
    glPopMatrix();

    //CIRCUNFERENCIA PEQUENHA
    glPushMatrix();
    glTranslated(0, 0, 11*radio/8+0.01);
    circunferencia(A, radio, Color2);
    glPopMatrix();
}

void Rueda_y_Pernos()
{
    Rueda(10);
    for (int i=0 ; i<360 ; i=i+72)
    {
        glPushMatrix();
        glRotatef(i,0,0,1);
        glTranslatef(1.4,0,4);
        Perno(0.4);
        glPopMatrix();

    }
}

void rectangulosolido(float *C1, float *C2, float *XYZ,float ancho, float largo,float grosor)
{
    for(int i=1;i<3;i=i+1)
    {
    glBegin(GL_POLYGON);
    glColor3fv(C1);
        glVertex3f(XYZ[0]+grosor/2,XYZ[1]+largo/2,XYZ[2]+pow(-1,i)*ancho/2);
        glVertex3f(XYZ[0]+grosor/2,XYZ[1]-largo/2,XYZ[2]+pow(-1,i)*ancho/2);
        glVertex3f(XYZ[0]-grosor/2,XYZ[1]-largo/2,XYZ[2]+pow(-1,i)*ancho/2);
        glVertex3f(XYZ[0]-grosor/2,XYZ[1]+largo/2,XYZ[2]+pow(-1,i)*ancho/2);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex3f(XYZ[0]+grosor/2,XYZ[1]+pow(-1,i)*largo/2,XYZ[2]+ancho/2);
        glVertex3f(XYZ[0]+grosor/2,XYZ[1]+pow(-1,i)*largo/2,XYZ[2]-ancho/2);
        glVertex3f(XYZ[0]-grosor/2,XYZ[1]+pow(-1,i)*largo/2,XYZ[2]-ancho/2);
        glVertex3f(XYZ[0]-grosor/2,XYZ[1]+pow(-1,i)*largo/2,XYZ[2]+ancho/2);
    glEnd();
    }
    glBegin(GL_POLYGON);
    glColor3fv(C2);
        glVertex3f(XYZ[0]+grosor/2,XYZ[1]+largo/2,XYZ[2]+ancho/2);
        glVertex3f(XYZ[0]+grosor/2,XYZ[1]-largo/2,XYZ[2]+ancho/2);
        glVertex3f(XYZ[0]+grosor/2,XYZ[1]-largo/2,XYZ[2]-ancho/2);
        glVertex3f(XYZ[0]+grosor/2,XYZ[1]+largo/2,XYZ[2]-ancho/2);
    glEnd();

}

void Cuerpo_Carro(float largo)
{
    float Color4[]={0.85,0.85,0.85};
    float marronoscuro[]={0.325,0.255,0.063};
    float marronclaro[]={0.647,0.518,0.129};
    float verdeamarillo[]={0.525,0.525,0.263};
    float amarilloclaro[]={1,1,0.518};
    float A[]={0,0,0};
    float B[]={largo/16+largo/6,0,0};
    double C[]={0,0};

    //RECTANGULO INFERIOR
    glPushMatrix();
        glRotated(90,0,0,1);
        glRotated(90,1,0,0);
        rectangulosolido(marronoscuro, marronclaro,A,largo/4,largo,largo/8);
    glPopMatrix();

    //BARRAS
    glColor3f(0.318,0.318,0.318);
    for(int j=1;j<3;j=j+1)
    {
        for(int i=1;i<3;i=i+1)
            {
            //BARA DELANTERA IZQUIERDA
            glPushMatrix();
            glTranslated(pow(-1,j)*largo/13,largo/16+largo/12, pow(-1,i)*largo/5);
            glutSolidCylinder(0.18*largo/12,largo/6,50,10);
            glPopMatrix();
            }
    }
    
    //RECTANGULO SUPERIOR
    glPushMatrix();
    glRotated(90,0,0,1);
    glRotated(90,1,0,0);
    rectangulosolido(verdeamarillo, amarilloclaro,B,largo/4,largo/2,0.03*largo);
    glPopMatrix();


    glColor3f(0.8,0.8,0.8);
    for(int i=1;i<3;i=i+1)
    {   //CILINDROS DE RUEDAS
        glPushMatrix();
        glTranslated(0,0, pow(-1,i)*(1.5*largo/5));
        glRotated(90, 0, 0, 1);
        glutSolidCylinder(0.2*largo/12,largo/2.6,50,10);
        glPopMatrix();

        for(int j=1;j<3;j=j+1)
        {
            //CILINDROS DE RUEDAS
            glPushMatrix();
            glTranslated(pow(-1,j)*largo/5.2,0, pow(-1,i)*(1.5*largo/5));
            glRotated(90, 0, 1, 0);
            circunferencia(C, 0.2*largo/12, Color4);
            glPopMatrix();
        }
    }

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



void reshape (int w, int h) {
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 100.0);
    glMatrixMode (GL_MODELVIEW);
}

void display(void) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f (1.0, 1.0, 1.0);
    camera(camX, camY, camZ);

    Ejes(3);

    Cuerpo_Carro(35);

    //RUEDAS DERECHAS
    glPushMatrix();
        glRotatef(90,0,1,0);
        glTranslatef(10,0,6);
        glScalef(0.4,0.4,0.3);
        Rueda_y_Pernos();
    glPopMatrix();
    
    glPushMatrix();
        glRotatef(90,0,1,0);
        glTranslatef(-10,0,6);
        glScalef(0.4,0.4,0.3);
        Rueda_y_Pernos();
    glPopMatrix();

    //RUEDAS IZQUIERDAS
    glPushMatrix();
        glRotatef(270,0,1,0);
        glTranslatef(10,0,6);
        glScalef(0.4,0.4,0.3);
        Rueda_y_Pernos();
    glPopMatrix();

    glPushMatrix();
        glRotatef(270,0,1,0);
        glTranslatef(-10,0,6);
        glScalef(0.4,0.4,0.3);
        Rueda_y_Pernos();
    glPopMatrix(); 

    glutSwapBuffers();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(800,600);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Carro");
    inicio();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    
    // Mostrar controles en consola
    std::cout << "Controles:\n";
    std::cout << "    A: Vista Superior\n";
    std::cout << "    S: Vista Frontal\n";
    std::cout << "    D: Vista Lateral\n";
    std::cout << "    Esc: Para salir de la simulacion\n";

    glutMainLoop();

    return EXIT_SUCCESS;
}