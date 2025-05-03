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
#include <cmath>
#include <cstdlib>
const double PI = 3.141592;
const int segmentos = 150;


float blanco[3]       = {1, 1, 1},
      negro[3]        = {0,0,0};


void Circulo(
    float cx, float cy,
    float radio,
    GLenum modo,const float* colorRelleno,
    float paso = 0.1f, float grosorContorno = 1.0f,
    const float* colorContorno = negro) {
    if (modo != GL_LINE_LOOP && modo != GL_LINE_STRIP) {
        glColor3fv(colorRelleno);
        glBegin(modo);
        for (float theta = 0; theta < 2 * PI; theta += paso) {
            float x = cx + radio * cosf(theta);
            float y = cy + radio * sinf(theta);
            glVertex2f(x, y);
        }
        glEnd();
    }

    // ——— Contorno siempre (GL_LINE_LOOP)
    glLineWidth(grosorContorno);
    glColor3fv(colorContorno);
    glBegin(GL_LINE_LOOP);
    for (float theta = 0; theta < 2 * PI; theta += paso) {
        float x = cx + radio * cosf(theta);
        float y = cy + radio * sinf(theta);
        glVertex2f(x, y);
    }
    glEnd();
    glLineWidth(1.0f);
}

void dibujarHojaPuntiaguda(
    float ox, float oy,
    float largo, float alto, 
    GLenum modo, 
    float grosorContorno, const float* colorContorno, 
    const float* colorRelleno = nullptr) {
    
    const int N = 100;
 
    // — Dibujo del relleno si se especifica —
    if (colorRelleno != nullptr && modo != GL_POINTS && modo != GL_LINES) {
        glColor3fv(colorRelleno);
        glBegin(GL_POLYGON);
        for (int i = 0; i <= N; ++i) {
            float t = i / (float)N;
            float x = ox + largo * (t - 0.5f);
            float y = oy + alto * sinf(t * PI);
            
            glVertex2f(x, y);
        }
        for (int i = N; i >= 0; --i) {
            float t = i / (float)N;
            float x = ox + largo * (t - 0.5f);
            float y = oy - alto * sinf(t * PI);
            glVertex2f(x, y);
        }
        glEnd();
    }
    
    // — Dibujo del contorno o puntos —
    glLineWidth(grosorContorno);
    glPointSize(grosorContorno);
    glColor3fv(colorContorno);
    glBegin(modo);
    for (int i = 0; i <= N; ++i) {
        float t = i / (float)N;
        float x = ox + largo * (t - 0.5f);
        float y = oy + alto * sinf(t * PI);
        glVertex2f(x, y);
    }
    for (int i = N; i >= 0; --i) {
        float t = i / (float)N;
        float x = ox + largo * (t - 0.5f);
        float y = oy - alto * sinf(t * PI);
        glVertex2f(x, y);
    }
    glEnd();
    
    // Regresar el contorno
    glLineWidth(1.0f);
    glPointSize(1.0f);
}

void dibujarFlorDeHojaPuntiaguda(
    float ox, float oy, 
    float r,
    float angleInit, float angleMove,
    float lHoja1, float lHoja2,
    float aHoja1, float aHoja2,
    float grosor1, float grosor2,
    float *relleno1, float *relleno2,
    float *contorno1, float *contorno2,
    GLenum modo1, GLenum modo2
){
for (int i = 0; i < 8; i++) {
        float angle = i * angleInit + angleMove;  
    
        float Cx = ox + r * cosf(angle);
        float Cy = oy + r * sinf(angle);
    
        float rot = atan2(ox-Cy,oy-Cx) * 180.0f / PI;
    
        glPushMatrix();
            glTranslatef(Cx, Cy, 0.0f);  
            glRotatef(rot, 0, 0, 1);     
            dibujarHojaPuntiaguda(
                0.0f, 0.0f,             
                lHoja1, aHoja1,         
                modo1,          
                grosor1,        
                contorno1,      
                relleno1        
            );

            dibujarHojaPuntiaguda(
                0.0f, 0.0f,
                lHoja2, aHoja2,
                modo2,
                grosor1,
                contorno2,
                relleno2);
                
        glPopMatrix();
    } 
}


void dibujarGota(
    float Cx, float Cy,
    float radio, float largo,
    float *colorRelleno,
    float grosorContorno,
    float *colorContorno,
    GLenum modo1, GLenum modo2)
{
    // Relleno
    glColor3fv(colorRelleno);
    glBegin(modo1);
        glVertex2f(Cx, Cy + largo);
        for (int i = 0; i <= segmentos; ++i) {
            float theta = PI*(1 + i / segmentos);
            float x = radio * cos(theta);
            float y = radio * sin(theta);
            glVertex2f(x+Cx, y+Cy);
        }
    glEnd();
    
    // Contorno
    glLineWidth(grosorContorno);
    glColor3fv(colorContorno);
    glBegin(modo2);
        glVertex2f(Cx, Cy + largo);
        for (int i = 0; i <= segmentos; ++i) {
            float theta = PI + PI * i / segmentos;
            float x = Cx + radio * cos(theta);
            float y = Cy + radio * sin(theta);
            glVertex2f(x, y);
        }
    glEnd();
    glLineWidth(1.0f);
}


void dibujarFlorDeGotas(
    float ox, float oy, 
    float r1, float r2,
    float rGota1, float rGota2,
    float lGota1, float lGota2,
    float *relleno1, float *relleno2,
    float *contorno1, float *contorno2,
    float grosor1, float grosor2,
    GLenum modo1, GLenum modo2) {

    for (int i = 0; i < 8; i++) {
        // Gota Grande
        float angle1 = i * PI / 4.0f;
        float Cx1 = ox + r1 * cosf(angle1);
        float Cy1 = oy + r1 * sinf(angle1);
        float rot1 = atan2(oy - Cy1, ox - Cx1) * 180.0f / PI - 90.0f;

        glPushMatrix();
            glTranslatef(Cx1, Cy1, 0.0f);
            glRotatef(rot1, 0, 0, 1);
            dibujarGota(0.0f, 0.0f, rGota1, lGota1, relleno1, grosor1, contorno1,modo1,modo2);
        glPopMatrix();
        
        // Gota Pequeña
        float angle2 = angle1 + (PI / 8.00f);
        float Cx2 = ox + r2 * cosf(angle2);
        float Cy2 = oy + r2 * sinf(angle2);
        float rot2 = atan2(oy - Cy2, ox - Cx2) * 180.0f / PI - 90.0f;

        glPushMatrix();
            glTranslatef(Cx2, Cy2, 0.0f);
            glRotatef(rot2, 0, 0, 1);
            dibujarGota(
                0.0f, 0.0f, rGota2, lGota2, relleno2, grosor2, contorno2, modo1, modo2);
        glPopMatrix();
    
    }
}



void display(void) {
    glClearColor(1, 1, 1, 1);  
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < 8; i++)
    {   
        float r = 4.25;
        float x = r*cos(i*PI/4.0f);
        float y = r*sin(i*PI/4.0f);
        dibujarFlorDeGotas(
            x, y, 
            1.1f, 1.3f,
            0.25,0.25,
            1.35,1.34,
            blanco,blanco,
            negro,negro,4,4,GL_POLYGON,GL_LINE_LOOP);
    } 
    
    for (int i = 0; i < 8; i++) {
        float angle = i * PI / 4.0f;
        float r = 5.75f;
 
        float Cx = r * cosf(angle);
        float Cy = r * sinf(angle);
 
        float rot = atan2(-Cy, -Cx) * 180.0f / PI - 90.0f;
 
        glPushMatrix();
            glTranslatef(Cx, Cy, 0.0f);
            glRotatef(rot, 0, 0, 1);
            dibujarGota(0.0f, 0.0f, 0.30f, 1.75f,blanco, 4.0f,negro,GL_POLYGON,GL_LINE_LOOP); 
        glPopMatrix();
    }   


    dibujarFlorDeHojaPuntiaguda(
        0, 0,
        3.8, 
        PI/4, PI/8,
        4.9, 4.1,
        1.5, 1.0,
        4, 4,
        blanco, negro,
        negro, negro,
        GL_LINE_LOOP,GL_LINE_LOOP);


    for (int i = 0; i < 8; i++) {
        float angle = i * PI / 4.0f+ PI / 8.0f;  // 45° por hoja
        float r = 3.7f;
    
        float Cx = r * cosf(angle);
        float Cy = r * sinf(angle);
    
        // Calcula el ángulo en grados para apuntar al centro (0,0)
        float rot = atan2(-Cy, -Cx) * 180.0f / PI;
    
        glPushMatrix();
            glTranslatef(Cx, Cy, 0.0f);  // Mueve al punto sobre el círculo
            glRotatef(rot, 0, 0, 1);     // Rota para que apunte al centro
            //HOJA GRANDE
            dibujarHojaPuntiaguda(
                0.0f, 0.0f,             // Centro local
                2.6f, 0.3f,            // Largo, alto (forma de ojo)
                GL_LINE_LOOP,           // Contorno cerrado
                3.5f,                   // Grosor de línea
                negro,                  // Contorno negro
                blanco                   // Relleno verde
            );
    
        glPopMatrix();
    } 

    dibujarFlorDeHojaPuntiaguda(
        0, 0,
        2.5, 
        PI/4, 0,
        3.5, 2.5,
        0.9, 0.5,
        4, 4,
        blanco, blanco,
        negro, negro,
        GL_LINE_LOOP,GL_LINE_LOOP);

  

    // Arco Del Circulo
    for (int i = 0; i < 8; i++) {
        float angle = i * PI / 4.0f;
        float r = 2.5f;

        float Cx = r * cosf(angle);
        float Cy = r * sinf(angle);

        float rot = atan2(-Cy, -Cx) * 180.0f / PI - 90.0f;

        glPushMatrix();
            glTranslatef(Cx, Cy, 0.0f);
            glRotatef(rot, 0, 0, 1);
            dibujarGota(0.0f, 0.0f, 0.30f, 1.5f, blanco, 4.0f, negro, GL_POLYGON,GL_LINE_LOOP); 
        glPopMatrix();
    }

    dibujarFlorDeGotas(
        0, 0,
        1.65, 1.45,
        0.4, 0.3,
        0.7, 0.7,
        blanco, blanco,
        blanco, blanco,
        4, 4,
        GL_POLYGON, GL_POLYGON);

    // Circulos pequeños
    for (int i = 0; i < 8; i++) {
        float angle = i * PI / 4;  // ángulo en radianes

        float r  = 2.45f; //radio del circulo sobre el cual van a posicionar
        float Cx = r * cosf(angle);
        float Cy = r * sinf(angle);

        Circulo(Cx, Cy, 0.1f, GL_POLYGON ,blanco ,0.05f, 3.0f, negro);
    }

    // Centro Listo
    dibujarFlorDeGotas(
        0, 0,
        1.6, 1.45,
        0.4, 0.3,
        0.7, 0.7,
        blanco, blanco,
        negro, negro,
        4, 4,
        GL_POLYGON,GL_LINE_LOOP);

    Circulo(0.0f, 0.0f, 1.6f, GL_POLYGON ,blanco ,0.05f, 3.0f, blanco);  
    Circulo(0.0f, 0.0f, 1.3f, GL_POLYGON ,negro ,0.05f, 3.0f, blanco); 
    
    dibujarFlorDeGotas(
        0, 0,
        1.6, 1.3,
        0.25, 0.25,
        1.35, 1.35,
        blanco, blanco,
        negro, negro,
        4, 4,
        GL_POLYGON,GL_LINE_LOOP); 
   
    glutSwapBuffers();  
}


void inicio()
{   
    int a = 8;
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-a,a,-a,a);
    glClearColor(0,0,0,0);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv); 
    glutInitWindowSize(800,800);
    glutInitWindowPosition(500,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);


    glutCreateWindow("ComputaciOn Grafica 1.2");
    inicio();
    glutDisplayFunc(display);
    glutMainLoop();

    return EXIT_SUCCESS; 
}