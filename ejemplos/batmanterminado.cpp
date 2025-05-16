#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>
#include <stdlib.h>


// Definiciones de colores 
float
    amarillo[] = {1, 1, 0}, 
    negro[]={0,0,0}; 

// Funciones existentes 
void inicio(){
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1,1,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();          
}

void elipse(float x, float y, float r1, float r2,float a, float b, float *RGB)
{   
    glColor3fv(RGB);
    glBegin(GL_POLYGON);
    for(float i=a;i<b;i=i+0.001)
    {
        glVertex2f(x+r1*cos(i),y+r2*sin(i));
    }
    glEnd();
}

// Parte 4: Corresponde al rango [4*PI/3, 3*PI/2)
void draw_logo_part_4(float i_angle, float A, float B) {
    float s = (69.0 * M_PI_4 / 4.0) - i_angle * (15.0 / 8.0); 
    float P_curve_x = (A / 2.0) * sin(2 * s) * cos(s);
    float P_curve_y = (A / 2.0) * sin(2 * s) * sin(s) - B;

    float s_fixed_end = (69.0 * M_PI_4 / 4.0) - (3.0 * M_PI_2) * (15.0 / 8.0);
    float P_base_x = (A / 2.0) * sin(2 * s_fixed_end) * cos(s_fixed_end);
    float P_base_y = (A / 2.0) * sin(2 * s_fixed_end) * sin(s_fixed_end)-B;
    

    glBegin(GL_TRIANGLE_STRIP);
        glVertex2f(-0.3, -B); 
        glVertex2f(P_curve_x, P_curve_y);
        glVertex2f(P_base_x, P_base_y);
    glEnd();
}

// Parte 5: Corresponde al rango [3*PI/2, 5*PI/3)
void draw_logo_part_5(float i_angle, float A, float B) {
    float s = (53.0 * M_PI_4 / 4.0) - i_angle * (15.0 / 8.0); 
    float P_curve_x = (A / 2.0) * sin(2 * s) * cos(s);
    float P_curve_y = (A / 2.0) * sin(2 * s) * sin(s) - B;

    float s_fixed_end = (53.0 * M_PI_4 / 4.0) - (5.0 * M_PI / 3.0) * (15.0 / 8.0);
    float P_base_x = (A / 2.0) * sin(2 * s_fixed_end) * cos(s_fixed_end);
    float P_base_y = (A / 2.0) * sin(2 * s_fixed_end) * sin(s_fixed_end)-B;

    glBegin(GL_TRIANGLE_STRIP);
        glVertex2f(0.3, -B); 
        glVertex2f(P_curve_x, P_curve_y);
        glVertex2f(P_base_x, P_base_y);
    glEnd();
}

// Parte 6: Corresponde al rango (5*PI/4, 4*PI/3)
void draw_logo_part_6(float i_angle, float A, float B) {
    float s = 37.0 * i_angle / 12.0 - 331.0 * M_PI / 144.0;
    float P_curve_x = -0.3 * sin(2*s) * cos(s) - 0.505;
    float P_curve_y = (A/2.0) * sin(2*s) * sin(s) - B;

    float s_fixed_end = 37.0 * (5.0*M_PI/4.0) / 12.0 - 331.0 * M_PI / 144.0;
    float P_base_x = -0.3 * sin(2*s_fixed_end) * cos(s_fixed_end) - 0.505;
    float P_base_y = (A/2.0) * sin(2*s_fixed_end) * sin(s_fixed_end) - B;
    glBegin(GL_QUAD_STRIP);
        glVertex2f(-0.49, -0.29); 
        glVertex2f(P_curve_x, P_curve_y);
        glVertex2f(P_base_x, P_base_y); 
        glVertex2f(-0.28, -0.37); 
        glVertex2f(-0.36, -0.37); 
        glVertex2f(-0.45, -0.33); 
    glEnd();
}

// Parte 7: Corresponde al rango [5*PI/3, 7*PI/4]
void draw_logo_part_7(float i_angle, float A, float B) {
    float s = 37.0 * i_angle / 12.0 - 713.0 * M_PI / 144.0;
    float P_curve_x = -0.3 * sin(2*s) * cos(s) + 0.505;
    float P_curve_y = (A/2.0) * sin(2*s) * sin(s) - B;

    float s_fixed_end = 37.0 * (7*M_PI/4) / 12.0 - 713.0 * M_PI / 144.0;
    float P_base_x = -0.3 * sin(2*s_fixed_end) * cos(s_fixed_end) + 0.505;
    float P_base_y = (A/2.0) * sin(2*s_fixed_end) * sin(s_fixed_end) - B;
    
    glBegin(GL_QUAD_STRIP);
        glVertex2f(0.28, -0.37); 
        glVertex2f(P_curve_x, P_curve_y);
        glVertex2f(P_base_x, P_base_y);
        glVertex2f(0.5, -0.3); 
        glVertex2f(0.36, -0.37); 
    glEnd();
}

// Parte 8: Corresponde al rango [PI/3, 4*PI/9)
void draw_logo_part_8(float i_angle, float A, float B) {
    float s = 4.0 * M_PI - (27.0 * i_angle / 4.0);
    float cos_s = cos(s);
    float one_minus_cos_s = 1.0 - cos_s;
    float P_curve_x = 0.125 * one_minus_cos_s * cos_s + 0.32;
    float P_curve_y = 0.2 * one_minus_cos_s * sin(s) + B;

    float s_fixed_end = 4.0 * M_PI - (27.0 * (4.0*M_PI/9.0) / 4.0);
    float cos_s_fixed = cos(s_fixed_end);
    float P_base_x = 0.125 * (1.0 - cos_s_fixed) * cos_s_fixed + 0.32;
    float P_base_y = 0.0;

    glBegin(GL_LINES);
        glVertex2f(0.32, B);
        glVertex2f(P_curve_x, P_curve_y);
        glVertex2f(P_base_x, P_base_y);
    glEnd();
}

// Parte 9: Corresponde al rango [5*PI/9, 2*PI/3)
void draw_logo_part_9(float i_angle, float A, float B) {
    float s = 11.0 * M_PI_4 - (27.0 * i_angle / 4.0);
    float cos_s = cos(s);
    float one_minus_cos_s = 1.0 - cos_s;
    float P_curve_x = -0.125 * one_minus_cos_s * cos_s - 0.32;
    float P_curve_y = -0.2 * one_minus_cos_s * sin(s) + B;

    float s_fixed_end = 11.0 * M_PI_4 - (27.0 * (2.0*M_PI/3.0) / 4.0);
    float cos_s_fixed = cos(s_fixed_end);
    float P_base_x = -0.125 * (1.0 - cos_s_fixed) * cos_s_fixed - 0.32;
    float P_base_y = 0.0;

    glBegin(GL_LINES);
        glVertex2f(-0.32, B);
        glVertex2f(P_curve_x, P_curve_y);
        glVertex2f(P_base_x, P_base_y);
    glEnd();
}

// Parte 10: Corresponde al rango [4*PI/9, 13*PI/27)
void draw_logo_part_10(float i_angle, float A, float B) {
    float P_curve_x = B * cos(i_angle);
    float P_curve_y = 2.3 * (B * cos(i_angle) - A * cos(4.0*M_PI/9.0)) + 0.527;
    
    float P_base_x = B * cos(13.0*M_PI/27.0);
    float P_base_y = 2.3 * (P_base_x  - A * cos(4.0*M_PI/9.0)) + 0.527;

    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0, 0.41);
        glVertex2f(P_curve_x, P_curve_y);
        glVertex2f(P_base_x, P_base_y);
    glEnd();
}

// Parte 11: Corresponde al rango [14*PI/27, 5*PI/9)
void draw_logo_part_11(float i_angle, float A, float B) {
    float P_curve_x = B * cos(i_angle);
    float P_curve_y = -2.3 * (B * cos(i_angle) + A * cos(4.0*M_PI/9.0)) + 0.527;
    
    float P_base_x = B * cos(5.0*M_PI/9.0);
    float P_base_y = -2.3 * (P_base_x  + A * cos(4.0*M_PI/9.0)) + 0.527;

    glBegin(GL_LINES);
        glVertex2f(0, 0.4); 
        glVertex2f(P_curve_x, P_curve_y);
        glVertex2f(P_base_x, P_base_y);
    glEnd();
}

// Parte 12: Corresponde al rango [13*PI/27, 14*PI/27)
void draw_logo_part_12(float i_angle, float A, float B) {
    float P_curve_x = B * cos(i_angle);
    float P_curve_y_const = 2.3 * (B * cos(13.0*M_PI/27.0) - A * cos(4.0*M_PI/9.0)) + 0.527; 
    
    float P_base_x = B * cos(5.0*M_PI/9.0); 

    glBegin(GL_LINES);
        glVertex2f(0, 0.4);
        glVertex2f(P_curve_x, P_curve_y_const);
        glVertex2f(P_base_x, P_curve_y_const);
    glEnd();
}


// --- Función LogoBatman Refactorizada ---
void LogoBatman()
{
    float A = 0.7;
    float B = 0.4;
    glPointSize(2);
    glColor3fv(amarillo);

    for (float i_loop = 0; i_loop <= 2 * M_PI; i_loop = i_loop + 0.00001)
    {
        if (i_loop >= 4.0 * M_PI / 3.0 && i_loop <= 3.0 * M_PI_2)
        { 
            draw_logo_part_4(i_loop, A, B);
        }
        else if (i_loop >= 3.0 * M_PI_2 && i_loop <= 5.0 * M_PI / 3.0)
        { 
            draw_logo_part_5(i_loop, A, B);
        }
        else if (i_loop > (5.0 * M_PI_4) && i_loop <= 4.0 * M_PI / 3.0) 
        { 
            draw_logo_part_6(i_loop, A, B);
        }
        else if (i_loop >= 5.0 * M_PI / 3.0 && i_loop <= 7.0 * M_PI_4) 
        { 
            draw_logo_part_7(i_loop, A, B);
        }

        if (i_loop >= M_PI / 3.0 && i_loop < 4.0 * M_PI / 9.0)
        { 
            draw_logo_part_8(i_loop, A, B);
        }
       
        if (i_loop >= 5.0 * M_PI / 9.0 && i_loop < 2.0 * M_PI / 3.0)
        { 
            draw_logo_part_9(i_loop, A, B);
        } 
        if (i_loop >= 4.0 * M_PI / 9.0 && i_loop < 13.0 * M_PI / 27.0)
        {
            draw_logo_part_10(i_loop, A, B);
        }
        if (i_loop >= 14.0 * M_PI / 27.0 && i_loop < 5.0 * M_PI / 9.0)
        {
            draw_logo_part_11(i_loop, A, B);
        }
        if (i_loop >= 13.0 * M_PI / 27.0 && i_loop < 14.0 * M_PI / 27.0)
        { 
            draw_logo_part_12(i_loop, A, B);
        } 
    }
}

// --- Función display y main (sin cambios significativos) ---
void display(void)
{
    glClearColor(1,1,1,0); // Fondo blanco
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    elipse(0,0,0.76,0.46,0,2*M_PI, negro);
    elipse(0,0,0.75,0.45,0,2*M_PI, amarillo);
    elipse(0,0,0.7,0.4,0,2*M_PI,negro);
    LogoBatman();

    glutSwapBuffers();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Logo de Batman");
    inicio();
    glutDisplayFunc(display);
    glutMainLoop();

    return EXIT_SUCCESS;
}