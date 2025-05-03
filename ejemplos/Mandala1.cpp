#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>
#include <cstdlib>
 
// Definir constante PI si no está definida
#define PI 3.14159265358979323846
 
const float ROJO[]     = {1.0f, 0.0f, 0.0f};
const float VERDE[]    = {0.0f, 1.0f, 0.0f};
const float AZUL[]     = {0.0f, 0.0f, 1.0f};
const float AMARILLO[] = {1.0f, 1.0f, 0.0f};
const float CIAN[]     = {0.0f, 1.0f, 1.0f};
const float MAGENTA[]  = {1.0f, 0.0f, 1.0f};
const float BLANCO[]   = {1.0f, 1.0f, 1.0f};
const float NEGRO[]    = {0.0f, 0.0f, 0.0f};
 

 
void Circulo(float cx, float cy,float radio,GLenum modo,const float* colorRelleno,float paso = 0.1f,float grosorContorno = 1.0f,const float* colorContorno = NEGRO) {
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
 
void dibujarGotaInvertida(float Cx, float Cy, float radio, float largo, const float colorRelleno[3], float grosorContorno = 1.0f, const float colorContorno[3] = NEGRO) {
    int segmentos = 100;
 
    // ——— 1. Relleno
    glColor3fv(colorRelleno);
    glBegin(GL_POLYGON);
        glVertex2f(Cx, Cy + largo);
        for (int i = 0; i <= segmentos; ++i) {
            float theta = PI + PI * i / segmentos;
            float x = Cx + radio * cos(theta);
            float y = Cy + radio * sin(theta);
            glVertex2f(x, y);
        }
    glEnd();
 
    // ——— 2. Contorno
    glLineWidth(grosorContorno);
    glColor3fv(colorContorno);
    glBegin(GL_LINE_LOOP);
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
 
void dibujarTrianguloIsoceles(float base, float altura, const float colorRelleno[3], float grosorContorno = 1.0f) {
    // — Relleno —
    glColor3fv(colorRelleno);
    glBegin(GL_TRIANGLES);
        glVertex2f(-base / 2.0f, 0.0f);
        glVertex2f( base / 2.0f, 0.0f);
        glVertex2f( 0.0f,       altura);
    glEnd();
 
    // — Contorno negro —
    glLineWidth(grosorContorno);
    glColor3fv(NEGRO);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-base / 2.0f, 0.0f);
        glVertex2f( base / 2.0f, 0.0f);
        glVertex2f( 0.0f,       altura);
    glEnd();
 
    glLineWidth(1.0f); // Restaurar grosor por defecto
}

void dibujarFlorDeGotas(float ox, float oy, float r1, float r2) {
    // — Parte grande
    for (int i = 0; i < 8; i++) {
        float angle = i * PI / 4.0f;
        float Cx = ox + r1 * cosf(angle);
        float Cy = oy + r1 * sinf(angle);
        float rot = atan2(oy - Cy, ox - Cx) * 180.0f / PI - 90.0f;
 
        glPushMatrix();
            glTranslatef(Cx, Cy, 0.0f);
            glRotatef(rot, 0, 0, 1);
            dibujarGotaInvertida(0.0f, 0.0f, 0.25f, 1.35f, BLANCO, 4.0f, NEGRO);
        glPopMatrix();
    }
 
    // — Parte intercalada pequeña
    for (int i = 0; i < 8; i++) {
        float angle = i * PI / 4.0f + PI / 8.0f;
        float Cx = ox + r2 * cosf(angle);
        float Cy = oy + r2 * sinf(angle);
        float rot = atan2(oy - Cy, ox - Cx) * 180.0f / PI - 90.0f;
 
        glPushMatrix();
            glTranslatef(Cx, Cy, 0.0f);
            glRotatef(rot, 0, 0, 1);
            dibujarGotaInvertida(0.0f, 0.0f, 0.25f, 1.34f, BLANCO, 4.0f, NEGRO);
        glPopMatrix();
    }
}
 
void dibujarHojaPuntiaguda(float ox, float oy, float largo, float alto, GLenum modo, float grosorContorno, const float* colorContorno, const float* colorRelleno = nullptr) {
    
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
    glLineWidth(1.0f);
    glPointSize(1.0f);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

      dibujarFlorDeGotas(-2.7f, 2.7f, 1.1f, 1.3f);
    dibujarFlorDeGotas(2.7f, 2.7f, 1.1f, 1.3f);

 dibujarFlorDeGotas(2.7f, -2.7f, 1.1f, 1.3f);
    dibujarFlorDeGotas(-2.7f, -2.7f, 1.1f, 1.3f);

    dibujarFlorDeGotas(-3.8f, 0.0f, 1.1f, 1.3f);
    dibujarFlorDeGotas(3.8f, 0.0f, 1.1f, 1.3f);

    dibujarFlorDeGotas(0.0f, 3.8f, 1.1f, 1.3f);
    dibujarFlorDeGotas(0.0f, -3.8f, 1.1f, 1.3f); 

    ///------------------------------------------------------------------
   /// DETALLE DE PETALO GRANDE EXTREMOS
    for (int i = 0; i < 8; i++) {
        float angle = i * PI / 4.0f;
        float r = 5.3f;
 
        float Cx = r * cosf(angle);
        float Cy = r * sinf(angle);
 
        // Rotación para apuntar hacia el centro (0, 0)
        float rot = atan2(-Cy, -Cx) * 180.0f / PI - 90.0f;
 
        glPushMatrix();
            glTranslatef(Cx, Cy, 0.0f);
            glRotatef(rot, 0, 0, 1);
            dibujarGotaInvertida(0.0f, 0.0f, 0.30f, 1.55f,BLANCO, 4.0f,NEGRO);  // (Cx,Cy) = 0,0 relativo al sistema local
 
        glPopMatrix();
    } 

    ///PETALOS GRANDES ---------------------------------------------
    for (int i = 0; i < 8; i++) {
        float angle = i * PI / 4.0f+ PI / 8.0f;  // 45° por hoja
        float r = 3.0f;
    
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
            5.1f, 1.47f,            // Largo, alto (forma de ojo)
            GL_LINE_LOOP,           // Contorno cerrado
            3.0f,                   // Grosor de línea
            NEGRO,                  // Contorno negro
            BLANCO                   // Relleno verde
        );
    
                    //HOJA GRANDE
            dibujarHojaPuntiaguda(0.0f, 0.0f,4.1f, 1.0f,GL_LINE_LOOP,4.0f,NEGRO,BLANCO);
        glPopMatrix();
    }
 
    ///PETALOS MEDIANOSssss ---------------------------------------------
    
    ///PETALOS GRANDES DETALLES  ---------------------------------------------
    
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
                NEGRO,                  // Contorno negro
                BLANCO                   // Relleno verde
            );
    
        glPopMatrix();
    }
 /* 
///PETALOS MEDIANOS ---------------------------------------------
 
    for (int i = 0; i < 8; i++) {
        float angle = i * PI / 4.0f;  // 45° por hoja
        float r = 2.4f;
    
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
                2.5f, 0.97f,            // Largo, alto (forma de ojo)
                GL_LINE_LOOP,           // Contorno cerrado
                4.0f,                   // Grosor de línea
                NEGRO,                  // Contorno negro
                BLANCO                   // Relleno verde
            );
            // Hoja larga en el eje X, por lo que la rotación la alinea
            dibujarHojaPuntiaguda(
                0.0f, 0.0f,             // Centro local
                1.9f, 0.6f,            // Largo, alto (forma de ojo)
                GL_LINE_LOOP,           // Contorno cerrado
                4.0f,                   // Grosor de línea
                NEGRO,                  // Contorno negro
                BLANCO                   // Relleno verde
            );
    
        glPopMatrix();
    }
 
///------------------------------------------------------------
///PETALOS DESPUES DEL CENTRO
 
    for (int i = 0; i < 8; i++) {
        float angle = i * PI / 4.0f;
        float r = 2.2f;

        float Cx = r * cosf(angle);
        float Cy = r * sinf(angle);

        // Rotación para apuntar hacia el centro (0, 0)
        float rot = atan2(-Cy, -Cx) * 180.0f / PI - 90.0f;

        glPushMatrix();
            glTranslatef(Cx, Cy, 0.0f);
            glRotatef(rot, 0, 0, 1);
            dibujarGotaInvertida(0.0f, 0.0f, 0.35f, 0.9f,BLANCO, 4.0f,NEGRO);  // (Cx,Cy) = 0,0 relativo al sistema local

        glPopMatrix();
    }


    ///CIRCULITOS
    for (int i = 0; i < 8; i++) {
        float angle = i * PI / 4;  // ángulo en radianes

        float r  = 2.28f; //radio del circulo sobre el cual van a posicionar
        float Cx = r * cosf(angle);
        float Cy = r * sinf(angle);

        Circulo(Cx, Cy, 0.13f, GL_POLYGON ,BLANCO ,0.05f, 3.0f, NEGRO);

    }

//==========================================================================
///CONTORNO dEL CENTRO
    for (int i = 0; i < 8; i++) {
        float angle = i * PI / 4.0f;
        float r = 1.6f;
 
        float Cx = r * cosf(angle);
        float Cy = r * sinf(angle);
 
        // Rotación para apuntar hacia el centro (0, 0)
        float rot = atan2(-Cy, -Cx) * 180.0f / PI - 90.0f;
 
        glPushMatrix();
            glTranslatef(Cx, Cy, 0.0f);
            glRotatef(rot, 0, 0, 1);
            dibujarGotaInvertida(0.0f, 0.0f, 0.4f, 0.7f,BLANCO, 3.0f,NEGRO);
 
        glPopMatrix();
    }

    ///CONTORNO DEL CENTRO
    for (int i = 0; i < 8; i++) {
        float angle = i * PI / 4.0f + PI / 8.0f; // ⬅️ ¡aquí rotamos el círculo!
        float r = 1.6f;

        float Cx = r * cosf(angle);
        float Cy = r * sinf(angle);

        float rot = atan2(-Cy, -Cx) * 180.0f / PI - 90.0f;

        glPushMatrix();
            glTranslatef(Cx, Cy, 0.0f);
            glRotatef(rot, 0, 0, 1);
            dibujarGotaInvertida(0.0f, 0.0f, 0.3f, 0.4f, BLANCO, 3.0f,NEGRO);
        glPopMatrix();
    }
 
    Circulo(0.0f, 0.0f, 1.68f, GL_POLYGON ,BLANCO ,0.05f, 3.0f, BLANCO);
 
    //==========================================================================
 
    /// CENTRO PART 1 grande
    for (int i = 0; i < 8; i++) {
        float angle = i * PI / 4.0f;
        float r = 1.5f;
 
        float Cx = r * cosf(angle);
        float Cy = r * sinf(angle);
 
        // Rotación para apuntar hacia el centro (0, 0)
        float rot = atan2(-Cy, -Cx) * 180.0f / PI - 90.0f;
 
        glPushMatrix();
            glTranslatef(Cx, Cy, 0.0f);
            glRotatef(rot, 0, 0, 1);
            dibujarGotaInvertida(0.0f, 0.0f, 0.25f, 1.45f,BLANCO, 4.0f,NEGRO);
 
        glPopMatrix();
    }
 
    /// CENTRO PART 2 PEQUEÑO
    for (int i = 0; i < 8; i++) {
        float angle = i * PI / 4.0f + PI / 8.0f;
        float r = 1.3f;

        float Cx = r * cosf(angle);
        float Cy = r * sinf(angle);

        float rot = atan2(-Cy, -Cx) * 180.0f / PI - 90.0f;

        glPushMatrix();
            glTranslatef(Cx, Cy, 0.0f);
            glRotatef(rot, 0, 0, 1);
            dibujarGotaInvertida(0.0f, 0.0f, 0.25f, 1.34f, BLANCO, 4.0f,NEGRO);
        glPopMatrix();
    } */

    glutSwapBuffers();
}



void inicio()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    int a = 6 ;
    gluOrtho2D(-a, a, -a, a);
    glClearColor(1, 1, 1, 1);
    glShadeModel(GL_SMOOTH);
 
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(50, 50);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("QUISPE GONZALES MARK");
 
    inicio();
    glutDisplayFunc(display);
    glutMainLoop();
 
    return EXIT_SUCCESS;
}
 