///////// LIBRERIAS /////////////

//(el printf esta dentro de la libreria)
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<cmath>
#include <stdlib.h>
#include <stdio.h>//esta libreria sirve para utilizar el printf

/////////////////////////////////////
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glut32.lib")
#pragma comment(lib, "opengl32.lib")
// estas tres librerias sirven para poder hacer el link al momento de compilar

/////////////////////////////////////

#define M_PI 3.141592654 // define la constante M_PI

GLint RH=16;
GLint RV=8;
GLint Tx=100,Ty=110,Tz=50,Mx=0,My=0;
GLint w,h;
GLdouble theta[] = {0,0,0,0,0,0,0,0,0}; // angulo de rotacion de los planetas
GLint SRotacion[]= {1,1,1,1,1,1,1,1,1}; //sentido de Rotacion de los planetas
GLint STraslacion[]={1,1,1,1,1,1,1,1,1}; //sentido de traslacion de los planetas

GLdouble alpha[] = {0,0,0,0,0,0,0,0,0,0}; // angulo de traslacion de los planetas
GLdouble PosX[] = {0, 10,25,35,45,55,65,75,85}; // posicion x de la traslacion de planetas
GLdouble PosY[] = {0, 8,18,28,38,48,58,68,78,88}; // posicion y de la traslacion de planetas

GLdouble Vel[] = {0 , 0.06, 0.07, 0.065, 0.08, 0.075, 0.07, 0.05 , 0.03}; // velocidad de traslacion de los planetas

GLdouble Radio[] = {8.5 , 0.746 , 2.347 , 2.5 , 1.69 , 4.7 , 4.0 , 2.9 , 3.2 }; // radio de los planetas
GLdouble a[] = {10,25,35,45,55,65,75,85,95}; // componente de x de la orbita de los planetas
GLdouble b[] = {8,18,28,38,48,58,68,78,88,98}; // componente de y de la orbita de los planetas

GLint Planeta = 9;// declaramos la constante planeta

///////// variables boolenas ///////////
GLboolean Solido=false;
GLboolean Textura=false;
GLboolean Pausa = false;
//Una variable booleana es aquella que puede ser (V o F)///////////////////

////////// Definimos las constantes de luminosidad ////////////

GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };// Esta luz no proviene de una sola fuente sino de luces que estan larededor.
                                                     //para simular esto usamos constantes de iluminacion ambiental que siempre le dan al objeto algo de color.
GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };//Simula el impacto direccional que tiene un objeto sobre otro objeto (cuanto mas un objeto mire hacia la fuente de luz mas brillante se vuelve)
GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };// Simula el punto brillante de la luz que aparece en el objeto, estos reflejos especulares estan + inclinados al color de la luz que al color del objeto.
GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };//

GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat high_shininess[] = { 100.0f };
////////////////////////////////////////////////////////////////

///// TEXTURA//////////////
GLubyte* data;
GLUquadricObj *obj = gluNewQuadric();
GLUquadricObj *obj_reverse = gluNewQuadric();
GLint Nom[12];

//LoadBMP : carga une imagen de 24bmp
#define EXIT {fclose(fichier);return -1;}
#define CTOI(C) (*(int*)&C)

int LoadBMP(char *File)// carga une imagen en formato bmp
{
unsigned char *Data;
FILE *fichier;
unsigned char Header[0x36];
GLuint DataPos,DataSize;
GLint Components;
GLsizei Width,Height;
GLenum Format,Type;
GLuint Name[1];

fichier = fopen(File,"rb");if (!fichier) return -1;
if (fread(Header,1,0x36,fichier)!=0x36) EXIT;
if (Header[0]!='B' || Header[1]!='M') EXIT;
if (CTOI(Header[0x1E])!=0) EXIT;
if (CTOI(Header[0x1C])!=24) EXIT;

DataPos = CTOI(Header[0x0A]);
DataSize = CTOI(Header[0x22]);

Width = CTOI(Header[0x12]);
Height = CTOI(Header[0x16]);
Type = GL_UNSIGNED_BYTE;
Format = GL_RGB;
Components = 3;

if (DataSize==0) DataSize=Width*Height*Components;
if (DataPos==0) DataPos=0x36;

fseek(fichier,DataPos,0);
Data = new unsigned char[DataSize];
if (!Data) EXIT;

if (fread(Data,1,DataSize,fichier)!=DataSize)
{
delete Data;
fclose(fichier);
return -1;
}

fclose(fichier);

unsigned char t;
for (int x=0;x<Width*Height;x++)
{
t=Data[x*3];
Data[x*3]=Data[x*3+2];
Data[x*3+2]=t;
}

glGenTextures(1, Name);
glBindTexture(GL_TEXTURE_2D, Name[0]);


glTexImage2D(GL_TEXTURE_2D,0,Components,Width,Height,0,GL_RGB,GL_UNSIGNED_BYTE,Data);

return Name[0];
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MovimientoP(){
/* . MODIFICAMOS EL ANGULO DE ROTACION DEPENDIENDO DEL SENTIDO PARA LOS PLANETAS*/

for (int Np=0;Np<Planeta;Np++){
/* si el sentido de rotacion es igual a 1 el angulo de rotacion aumenta en 2 */
    if (SRotacion[Np]==1){
        theta[Np] = theta[Np] + 2;

    if (theta[Np]>360)
        theta[Np] = 0;
}
/* si el sentido de rotacion es diferente de 1 el angulo rotacion disminuye*/
else{
theta[Np] =theta[Np]-2;
if(theta[Np]<0) theta[Np] = 360;
}
/* */
if (Np>0)
    {
if(Pausa==false){// si pausa es verdadero no hay traslacion
/* Si el sentido de traslacion es igual a 1 el angulo de traslacion aumenta en su velocidad*/
/* tambien cuando el angulo es mayor q 360 regresa a ser 0 para asi continuar trasladandose
continuamente evitando el OVERFLOW= sobrecarga de informacion*/
if (STraslacion[Np]==1)
    {
     alpha[Np] = alpha[Np] + Vel[Np];

if (alpha[Np]>360)
    alpha[Np]=0;
/* Si el sentido de traslacion es igual a 1 el angulo de traslacion diminuye en su velocidad*/ }
/* tambien cuando el angulo es menor q 0 regresa a ser 360 para asi continuar trasladandose
continuamente evitando el OVERFLOW*/
else{
alpha[Np] = alpha[Np] - Vel[Np];
if (alpha[Np]<0) alpha[Np]=360;
}
}
}
}


/* actualiza los valores de PosX y PosY lo que coresponde a las coordenadas de las posiones X e Y de los planetas*/

for (int Np=1; Np<Planeta;Np++)
    {
     PosX[Np] = a[Np]*cos(alpha[Np]);
     PosY[Np] = b[Np]*sin(alpha[Np]);
    }


//Sleep(100);// detiene la ejecucion del programa a 100 mili segundos
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Inicializacion(void)
{
glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );/* modo en el q va a dibujarse*/
glutInitWindowSize (800, 600); /* tama�o de ventana*/
glutInitWindowPosition (100, 100);/*posicion de la ventana */
glutCreateWindow ("Sistema Solar ");/* crea la ventana de nombre sistema solar*/
glClearColor (0.0, 0.0, 0.0, 0.0);/* color de la ventana*/

GLfloat position1 [] = { 0, 0.0F, 0.0F, 1.0F };/* declaramos el vector position*/
/* activa efectos de luminosidad y sombreado */
glLightfv(GL_LIGHT0, GL_POSITION, position1);
glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);
glShadeModel (GL_SMOOTH);
/* propiedades de luminosidad y sombreado */
glEnable(GL_DEPTH_TEST);
glEnable(GL_COLOR_MATERIAL);
glEnable(GL_TEXTURE_2D);
glMatrixMode (GL_MODELVIEW);
/* se carga las imagenes que van a ser de textura */

Nom[0] = LoadBMP("Sol.bmp");
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);


Nom[1] = LoadBMP("PMercurio.bmp");
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

Nom[2] = LoadBMP("PVenus.bmp");
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

Nom[3] = LoadBMP("PTierra.bmp");
Nom[0] = LoadBMP("C:/Users/reyna/Desktop/pract 6 -10b/pract 6 -10b/pared.bmp");
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

Nom[4] = LoadBMP("PMarte.bmp");
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

Nom[5] = LoadBMP("PJupiter.bmp");
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

Nom[6] = LoadBMP("PSaturno.bmp");
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

Nom[7] = LoadBMP("PUrano.bmp");
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

Nom[8] = LoadBMP("PNeptuno.bmp");
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

//Nom[9] = LoadBMP("universo.bmp");
//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

glDepthFunc(GL_LESS);
glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* funcion que permite dibujar la escena */
void display(void)
{
glBindTexture(GL_TEXTURE_2D, Nom[9]);

/* limpia los bufferes de color y profundidad*/
// bufferes : espacios de memoria
glClear (GL_COLOR_BUFFER_BIT);
glClear (GL_DEPTH_BUFFER_BIT);

//efecto de luminisencia y configuraciones de iluminacion y sombreado estas
//propiedades se activan con los valores que estan designados o declarados en el inicio
/* luz*/

glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
glLightfv(GL_LIGHT0, GL_POSITION, light_position);

/* material*/

glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);


glLoadIdentity();
glTranslatef(Mx,My,0);// permite deslizar o mover el punto de vista de la escena con los
// numeros 8, 4 ,6,2

MovimientoP();// funcion que actualiza los angulos y posiciones de los planetas

/* dibujamos las orbitas */
for (int Np=1;Np<Planeta;Np++){
glColor3f(1,1,1);
glBegin (GL_LINE_LOOP);// polilinea formada uniendo puntos
for( double w = 0; w<2*M_PI ; w=w+0.05)
glVertex3f(a[Np]*cos(w),b[Np]*sin(w),0);
glEnd ();
}

// dibujamos los planetas
for (int Np=0;Np<Planeta;Np++){


if (Textura == false){// si la textura es verdadera no se le asigna colores alos planetas
switch (Np){// asigna un color diferente a cada planeta
case 0:glColor3f(1,1,0);break;
case 1:glColor3f(1,0,1);break;
case 2:glColor3f(1,1,0.5);break;
case 3:glColor3f(0,1,1);break;
case 4:glColor3f(0.5,0.5,0.5);break;
case 5:glColor3f(0.3,0.9,0.7);break;
case 6:glColor3f(0.5,0.3,0);break;
case 7:glColor3f(0.5,0,0.7);break;
case 8:glColor3f(0.8,0.3,0.7);break;
case 9:glColor3f(0.1,0.6,0.3);break;
}
}

glPushMatrix();
glTranslatef(PosX[Np],PosY[Np],0); //traslada la posicion donde se va a dibujar los planetas
glRotatef(theta[Np],1,1,1); // hace el efecto de rotacion del planeta


if (Textura ==true){
glBindTexture(GL_TEXTURE_2D, Nom[Np]);// hace mallado en la imagen
gluQuadricTexture(obj, GL_TRUE );// hace la cuadratura en el objeto
gluQuadricDrawStyle(obj, GLU_FILL);//dibuja la cuadratura en el objeto
gluSphere(obj,Radio[Np],RH/2,RV/2); //crea la esfera utilizando la cudratura texturizada
}
else{//cuando no hay texturas grafica en solido o en malla
if (Solido==true)
    glutSolidSphere(Radio[Np],RH/2,RV/2);//solido
else
    glutWireSphere(Radio[Np],RH/2,RV/2);//malla
}

glPopMatrix();
}
glutSwapBuffers();//hace el intercambio de bufferes (espacio de memoria )
glutPostRedisplay();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void reshape (int width,int height){//redimenzionaliza la ventana
w=width;//ancho de ventana actual
h=height;//alto de ventana actual
glViewport(0, 0, w, h);//define el area rectangular de la ventana de visualizacion(x,y)
glMatrixMode(GL_PROJECTION);
glLoadIdentity();//limp�a la matriz de proyeccion reseteandola a la matriz identidad
glOrtho(-Tx,Tx,-Ty,Ty,-Tz,Tz);//cambia tama�o del area de vista
glMatrixMode(GL_MODELVIEW);//cargamos matriz identidad en modelview

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// funcion ddel teclado
void keyboard(unsigned char key, int x, int y)
{
switch (key) {
case 'l':case 'L':{//aleja la escena modificando el area de vision
Tx=Tx+8;
Ty=Ty+10;
break;
}
case 'a': case'A':{//acerca la escena modificando el area de vision
Tx=Tx-8;
Ty=Ty - 10;
break;
}

case 'S': case's':{//cambia el sentido de traslacion de los planeas en sentido horario y antihorario
for (int Np=0;Np<Planeta;Np++){
STraslacion[Np]=-STraslacion[Np];
}
break;
}
case 't':case 'T':{//activa la textura
if (Textura==true)
    Textura = false;
else Textura = true;
break;
}
case '8':{// mueve la escena haciendo traslaciones
My=My-1;
break;
}
case '2':{//mueve la escena haciendo traslaciones
My=My+1;
break;
}
case '4':{//mueve la escena haciendo traslaciones
Mx=Mx+1;
break;
}
case '6':{//mueve la escena haciendo traslaciones
Mx=Mx-1;
break;
}
case 'p':case 'P':{// pausa la traslacion de los planetas pero no la rotacion
Pausa=!Pausa;
break;
}
case 'j':case 'J':{// cambia el sentido de rotacion de los planetas antihorario y horario
for (int Np=0;Np<Planeta;Np++)
{SRotacion[Np]=-SRotacion[Np];
}
break;
}
case '+':{// aumenta mallado de los planetas
RH=RH+2;
RV=RH/2;
break;
}
case '-':{// disminuye mallado de los planetas
if(RV>4)
RH=RH-2;
RV=RH/2;
break;
}
case 32:{
if (Solido ==true)// hace el cambio de solido a malla
Solido=false;
else
Solido =true;
break;
}
default:printf ("La tecla (%d) no tiene programada alguna funcion.\n", key); break;
}
glMatrixMode(GL_MODELVIEW);
reshape(w,h);// reactualiza la ventana (traslaciones y acercamientos)
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Mensaje(){

printf(" =================================================================\n");
printf(" == Proyecto Sistema Planetario ==\n");
printf(" =================================================================\n\n ");

printf(" ALUMNA : \n");
printf(" \tPerez Nu�ez Jhelly Reynaluz\n");

printf(" TECLA \t FUNCION\n\n");

printf(" [+]\t Aumento de mallado \n");
printf(" [-]\t Disminucion de mallado \n");

printf(" [s]\t Cambiar sentido horario a antihorario y viceversa para traslacion \n");
printf(" [j]\t cambia de sentido de antihorario y viciversa para rotacion \n");
printf(" [a]\t Acercar la escena \n");
printf(" [l]\t Alejar la escena \n");
printf(" [8]\t Mover la escena hacia arriba \n");
printf(" [4]\t Mover la escena hacia la izquierda \n");
printf(" [2]\t Mover la escena hacia abajo \n");
printf(" [6]\t Mover la escena hacia la derecha \n");
printf(" [p]\t Pausar la traslacion de los planetas \n");
printf(" [t]\t Activar o desactivar Textura \n");

printf(" barra espaciadora\t Cambio de: Solido <--> Malla \n");

printf("\n\n");


}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
glutInit(&argc, argv);
Mensaje();//llama a la funcion mensaje
Inicializacion(); //inicializamos la ecena
glutDisplayFunc(display); // dibuja escena
glutReshapeFunc(reshape); // redimension de la ventana
glutKeyboardFunc(keyboard); // controlar el teclado

glutMainLoop(); // hace un bucle infinito
return 0;
}
