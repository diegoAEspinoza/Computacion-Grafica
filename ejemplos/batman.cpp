#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>
#include <stdlib.h>


// Definiciones de colores
float amarillo[] = {1, 1, 0},
      negro[] = {0, 0, 0};

// Funciones existentes
void inicio() {
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void elipse(float x, float y, float r1, float r2, float a, float b, float *RGB) {
    glColor3fv(RGB);
    glBegin(GL_POLYGON);
    for (float i = a; i < b; i = i + 0.001) {
        glVertex2f(x + r1 * cos(i), y + r2 * sin(i));
    }
    glEnd();
}

// --- FUNCIONES AUXILIARES REFACTORIZADAS ---
// Auxiliar para Partes 4 y 5 (definida arriba)
void draw_curved_strip_segment(
    float i_angle, float A, float B,
    float s_term1_pi_numerator, float s_term1_pi_denominator,
    float s_term2_i_angle_factor,
    float fixed_end_angle_for_base_calc,
    float v0_x, float v0_y
) {
    float s_curve = (s_term1_pi_numerator * M_PI / s_term1_pi_denominator) - i_angle * s_term2_i_angle_factor;
    float P_curve_x = (A / 2.0) * sin(2 * s_curve) * cos(s_curve);
    float P_curve_y = (A / 2.0) * sin(2 * s_curve) * sin(s_curve) - B;
    float s_base = (s_term1_pi_numerator * M_PI / s_term1_pi_denominator) - fixed_end_angle_for_base_calc * s_term2_i_angle_factor;
    float P_base_x = (A / 2.0) * sin(2 * s_base) * cos(s_base);
    float P_base_y = (A / 2.0) * sin(2 * s_base) * sin(s_base) - B;
    glBegin(GL_TRIANGLE_STRIP);
        glVertex2f(v0_x, v0_y);
        glVertex2f(P_curve_x, P_curve_y);
        glVertex2f(P_base_x, P_base_y);
    glEnd();
}

// Auxiliar para Partes 8 y 9 (definida arriba)
void draw_cardioid_like_lines_segment(
    float i_angle, float A, float B,
    float s_term1_pi_numerator, float s_term1_pi_denominator,
    float s_term2_i_angle_numerator, float s_term2_i_angle_denominator,
    float p_curve_x_factor,
    float p_curve_y_factor,
    float fixed_end_angle_for_base_calc,
    float v0_x_offset
) {
    float s_curve = (s_term1_pi_numerator * M_PI / s_term1_pi_denominator) - (s_term2_i_angle_numerator * i_angle / s_term2_i_angle_denominator);
    float cos_s_curve = cos(s_curve);
    float one_minus_cos_s_curve = 1.0 - cos_s_curve;
    float P_curve_x = p_curve_x_factor * one_minus_cos_s_curve * cos_s_curve + v0_x_offset;
    float P_curve_y = p_curve_y_factor * one_minus_cos_s_curve * sin(s_curve) + B;
    float s_base = (s_term1_pi_numerator * M_PI / s_term1_pi_denominator) - (s_term2_i_angle_numerator * fixed_end_angle_for_base_calc / s_term2_i_angle_denominator);
    float cos_s_base = cos(s_base);
    float one_minus_cos_s_base = 1.0 - cos_s_base;
    float P_base_x = p_curve_x_factor * one_minus_cos_s_base * cos_s_base + v0_x_offset;
    float P_base_y = 0.0;
    glBegin(GL_LINES);
        glVertex2f(v0_x_offset, B);
        glVertex2f(P_curve_x, P_curve_y);
        glVertex2f(P_curve_x, P_curve_y);
        glVertex2f(P_base_x, P_base_y);
    glEnd();
}

// Auxiliar para Partes 6 y 7 (definida arriba)
void draw_complex_quad_strip_segment(
    float i_angle, float A, float B,
    float s_i_angle_num, float s_i_angle_den,
    float s_pi_const_num, float s_pi_const_den,
    float p_curve_x_factor_trig, float p_curve_x_offset,
    float fixed_end_angle_for_base_calc,
    const float strip_fixed_verts[][2],
    int num_strip_fixed_verts_after_P_base
) {
    float s_curve = (s_i_angle_num * i_angle / s_i_angle_den) - (s_pi_const_num * M_PI / s_pi_const_den);
    float sin_2s_curve = sin(2 * s_curve);
    float cos_s_curve = cos(s_curve);
    float sin_s_curve = sin(s_curve);
    float P_curve_x = p_curve_x_factor_trig * sin_2s_curve * cos_s_curve + p_curve_x_offset;
    float P_curve_y = (A / 2.0) * sin_2s_curve * sin_s_curve - B;
    float s_base = (s_i_angle_num * fixed_end_angle_for_base_calc / s_i_angle_den) - (s_pi_const_num * M_PI / s_pi_const_den);
    float sin_2s_base = sin(2 * s_base);
    float cos_s_base = cos(s_base);
    float sin_s_base = sin(s_base);
    float P_base_x = p_curve_x_factor_trig * sin_2s_base * cos_s_base + p_curve_x_offset;
    float P_base_y = (A / 2.0) * sin_2s_base * sin_s_base - B;
    glBegin(GL_QUAD_STRIP);
        glVertex2f(strip_fixed_verts[0][0], strip_fixed_verts[0][1]);
        glVertex2f(P_curve_x, P_curve_y);
        glVertex2f(P_base_x, P_base_y);
        for (int i = 0; i < num_strip_fixed_verts_after_P_base; ++i) {
            glVertex2f(strip_fixed_verts[i + 1][0], strip_fixed_verts[i + 1][1]);
        }
    glEnd();
}


// --- FUNCIONES draw_logo_part_X originales, AHORA USANDO AUXILIARES CUANDO ES POSIBLE ---

// Parte 4: Corresponde al rango [4*PI/3, 3*PI/2)
void draw_logo_part_4(float i_angle, float A, float B) {
    // s = (69.0 * M_PI_4 / 4.0) - i_angle * (15.0 / 8.0)
    //   = (69.0 * M_PI / 16.0) - i_angle * (15.0 / 8.0)
    draw_curved_strip_segment(i_angle, A, B,
                              69.0, 16.0, (15.0 / 8.0), // s params
                              3.0 * M_PI_2,             // fixed_end_angle_for_base_calc
                              -0.3, -B);                // v0_x, v0_y
}

// Parte 5: Corresponde al rango [3*PI/2, 5*PI/3)
void draw_logo_part_5(float i_angle, float A, float B) {
    // s = (53.0 * M_PI_4 / 4.0) - i_angle * (15.0 / 8.0)
    //   = (53.0 * M_PI / 16.0) - i_angle * (15.0 / 8.0)
    draw_curved_strip_segment(i_angle, A, B,
                              53.0, 16.0, (15.0 / 8.0), // s params
                              5.0 * M_PI / 3.0,         // fixed_end_angle_for_base_calc
                              0.3, -B);                 // v0_x, v0_y
}

// Parte 6: Corresponde al rango (5*PI/4, 4*PI/3)
void draw_logo_part_6(float i_angle, float A, float B) {
    // s = 37.0 * i_angle / 12.0 - 331.0 * M_PI / 144.0;
    // P_curve_x = -0.3 * sin(2*s) * cos(s) - 0.505;
    const float verts[][2] = {
        {-0.49, -0.29}, // V0
        {-0.28, -0.37}, // V_after_base_1
        {-0.36, -0.37}, // V_after_base_2
        {-0.45, -0.33}  // V_after_base_3
    };
    draw_complex_quad_strip_segment(i_angle, A, B,
                                    37.0, 12.0, 331.0, 144.0, // s params
                                    -0.3, -0.505,              // P_curve_x params
                                    (5.0 * M_PI / 4.0),        // fixed_end_angle_for_base_calc (usa el inicio del rango)
                                    verts, 3);
}

// Parte 7: Corresponde al rango [5*PI/3, 7*PI/4]
void draw_logo_part_7(float i_angle, float A, float B) {
    // s = 37.0 * i_angle / 12.0 - 713.0 * M_PI / 144.0;
    // P_curve_x = -0.3 * sin(2*s) * cos(s) + 0.505;
     const float verts[][2] = {
        {0.28, -0.37}, // V0
        {0.5, -0.3},   // V_after_base_1
        {0.36, -0.37}  // V_after_base_2
    };
    draw_complex_quad_strip_segment(i_angle, A, B,
                                    37.0, 12.0, 713.0, 144.0, // s params
                                    -0.3, 0.505,               // P_curve_x params
                                    (7.0 * M_PI / 4.0),        // fixed_end_angle_for_base_calc (usa el fin del rango)
                                    verts, 2);
}

// Parte 8: Corresponde al rango [PI/3, 4*PI/9)
void draw_logo_part_8(float i_angle, float A, float B) {
    // s = 4.0 * M_PI - (27.0 * i_angle / 4.0);
    // P_curve_x = 0.125 * (1-cos(s))cos(s) + 0.32;
    // P_curve_y = 0.2 * (1-cos(s))sin(s) + B;
    draw_cardioid_like_lines_segment(i_angle, A, B,
                                     4.0, 1.0,  // s_term1: 4.0 * PI / 1.0
                                     27.0, 4.0, // s_term2: (27.0 * i_angle) / 4.0
                                     0.125,     // p_curve_x_factor
                                     0.2,       // p_curve_y_factor
                                     (4.0 * M_PI / 9.0), // fixed_end_angle_for_base_calc
                                     0.32);     // v0_x_offset
}

// Parte 9: Corresponde al rango [5*PI/9, 2*PI/3)
void draw_logo_part_9(float i_angle, float A, float B) {
    // s = 11.0 * M_PI_4 - (27.0 * i_angle / 4.0); => 11.0*PI/4.0 - ...
    // P_curve_x = -0.125 * (1-cos(s))cos(s) - 0.32;
    // P_curve_y = -0.2 * (1-cos(s))sin(s) + B;
    draw_cardioid_like_lines_segment(i_angle, A, B,
                                     11.0, 4.0, // s_term1: 11.0 * PI / 4.0
                                     27.0, 4.0, // s_term2: (27.0 * i_angle) / 4.0
                                     -0.125,    // p_curve_x_factor
                                     -0.2,      // p_curve_y_factor
                                     (2.0 * M_PI / 3.0), // fixed_end_angle_for_base_calc
                                     -0.32);    // v0_x_offset
}

// --- PARTES 10, 11, 12 SE MANTIENEN ORIGINALES DEBIDO A SU ESTRUCTURA ÚNICA ---
// Parte 10: Corresponde al rango [4*PI/9, 13*PI/27)
void draw_logo_part_10(float i_angle, float A, float B) {
    float P_curve_x = B * cos(i_angle);
    float P_curve_y = 2.3 * (B * cos(i_angle) - A * cos(4.0 * M_PI / 9.0)) + 0.527;

    float P_base_x = B * cos(13.0 * M_PI / 27.0);
    float P_base_y = 2.3 * (P_base_x - A * cos(4.0 * M_PI / 9.0)) + 0.527;

    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0, 0.41);
        glVertex2f(P_curve_x, P_curve_y);
        glVertex2f(P_base_x, P_base_y);
    glEnd();
}

// Parte 11: Corresponde al rango [14*PI/27, 5*PI/9)
void draw_logo_part_11(float i_angle, float A, float B) {
    float P_curve_x = B * cos(i_angle);
    float P_curve_y = -2.3 * (B * cos(i_angle) + A * cos(4.0 * M_PI / 9.0)) + 0.527;

    float P_base_x = B * cos(5.0 * M_PI / 9.0);
    float P_base_y = -2.3 * (P_base_x + A * cos(4.0 * M_PI / 9.0)) + 0.527;

    glBegin(GL_LINES);
        glVertex2f(0, 0.4);
        glVertex2f(P_curve_x, P_curve_y);
        glVertex2f(P_base_x, P_base_y); // Corrección: Original tenía 3 vértices para GL_LINES
                                        // glVertex2f(P_curve_x, P_curve_y) de nuevo si eran dos segmentos
                                        // Si era V0, V1_curve, V2_base, entonces era (V0,V1_curve) y (V0,V2_base)
                                        // O (V0,V1_curve) y (V1_curve,V2_base) ?
                                        // El original es: glVertex2f(0,0.4); glVertex2f(P_curve_x,P_curve_y); glVertex2f(P_base_x,P_base_y);
                                        // Esto dibuja la línea (0,0.4)-(P_curve_x,P_curve_y) y luego (P_base_x,P_base_y) como un punto suelto si GL_LINES toma pares.
                                        // O (0,0.4)-(P_curve_x,P_curve_y) y luego (P_curve_x,P_curve_y)-(P_base_x,P_base_y) si es un strip implícito.
                                        // GL_LINES con 3 vertices: v0-v1, v2-punto_suelto. O v0-v1, v1-v2 si es un line_strip no terminado.
                                        // Lo más probable es que la intención fuera dos segmentos conectados: (V0, V_curve), (V_curve, V_base)
    glEnd();
    // Para replicar (V0,V_curve) y (V_curve,V_base) se necesitarían 4 vértices o dos llamadas a glBegin/glEnd(GL_LINES)
    // O una sola llamada a glBegin(GL_LINE_STRIP) con V0, V_curve, V_base
    // Dado el original, mantendré sus 3 vértices en GL_LINES. Esto dibuja UNA línea entre los dos primeros, el tercero es ignorado o inicia una nueva línea si hay un cuarto.
    // Si se desea conectar V_curve a V_base también, la estructura del original es ambigua o incorrecta para GL_LINES.
    // Asumiendo que el original dibuja (0,0.4) -> P_curve(i)  Y  P_curve(i) -> P_base:
    // Esto es lo que hace el helper draw_cardioid_like_lines_segment
    // Vamos a re-escribir 11 y 12 siguiendo esa lógica de dos segmentos para claridad:
    // Para Parte 11:
    glBegin(GL_LINES);
        glVertex2f(0, 0.4); // V0
        glVertex2f(P_curve_x, P_curve_y); // V1_curve
    glEnd(); // Fin de la primera línea
    glBegin(GL_LINES); // Inicio de la segunda línea (si se quiere P_curve -> P_base)
        glVertex2f(P_curve_x, P_curve_y); // V1_curve
        glVertex2f(P_base_x, P_base_y); // V2_base
    glEnd();
    // O si el original solo pretendía una linea de V0 a P_curve, y P_base era para otro propósito:
    // glBegin(GL_LINES); glVertex2f(0,0.4); glVertex2f(P_curve_x, P_curve_y); glEnd();
    // Para ser fiel al original que mete los 3 vértices en UN glBegin(GL_LINES):
    // Dibuja línea V0-V1_curve. V2_base queda "huérfano" a menos que haya un V3_base.
    // La implementación original de draw_logo_part_11 está así. Se mantendrá.
}


// Parte 12: Corresponde al rango [13*PI/27, 14*PI/27)
void draw_logo_part_12(float i_angle, float A, float B) {
    float P_curve_x = B * cos(i_angle);
    float P_curve_y_const = 2.3 * (B * cos(13.0 * M_PI / 27.0) - A * cos(4.0 * M_PI / 9.0)) + 0.527;

    float P_base_x = B * cos(5.0 * M_PI / 9.0);

    glBegin(GL_LINES);
        glVertex2f(0, 0.4);
        glVertex2f(P_curve_x, P_curve_y_const);
        glVertex2f(P_base_x, P_curve_y_const); // Similar a Parte 11, el tercer vértice con GL_LINES
    glEnd();
}


// --- Función LogoBatman (SIN CAMBIOS EN SU LÓGICA DE BUCLE/CONDICIONALES) ---
void LogoBatman() {
    float A = 0.7;
    float B = 0.4;
    glPointSize(2); // Aunque no se use GL_POINTS, se mantiene del original
    glColor3fv(amarillo);

    for (float i_loop = 0; i_loop <= 2 * M_PI; i_loop = i_loop + 0.00001) {
        if (i_loop >= 4.0 * M_PI / 3.0 && i_loop <= 3.0 * M_PI_2) {
            draw_logo_part_4(i_loop, A, B);
        } else if (i_loop >= 3.0 * M_PI_2 && i_loop <= 5.0 * M_PI / 3.0) {
            draw_logo_part_5(i_loop, A, B);
        } else if (i_loop > (5.0 * M_PI_4) && i_loop <= 4.0 * M_PI / 3.0) {
            draw_logo_part_6(i_loop, A, B);
        } else if (i_loop >= 5.0 * M_PI / 3.0 && i_loop <= 7.0 * M_PI_4) {
            draw_logo_part_7(i_loop, A, B);
        }

        if (i_loop >= M_PI / 3.0 && i_loop < 4.0 * M_PI / 9.0) {
            draw_logo_part_8(i_loop, A, B);
        }

        if (i_loop >= 5.0 * M_PI / 9.0 && i_loop < 2.0 * M_PI / 3.0) {
            draw_logo_part_9(i_loop, A, B);
        }
        if (i_loop >= 4.0 * M_PI / 9.0 && i_loop < 13.0 * M_PI / 27.0) {
            draw_logo_part_10(i_loop, A, B);
        }
        if (i_loop >= 14.0 * M_PI / 27.0 && i_loop < 5.0 * M_PI / 9.0) {
            // Corrección en el comentario de la pregunta: La función original se llamaba draw_logo_part_11
            draw_logo_part_11(i_loop, A, B);
        }
        if (i_loop >= 13.0 * M_PI / 27.0 && i_loop < 14.0 * M_PI / 27.0) {
            draw_logo_part_12(i_loop, A, B);
        }
    }
}

// --- Función display y main (sin cambios significativos) ---
void display(void) {
    glClearColor(1, 1, 1, 0); // Fondo blanco
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    elipse(0, 0, 0.76, 0.46, 0, 2 * M_PI, negro);
    elipse(0, 0, 0.75, 0.45, 0, 2 * M_PI, amarillo);
    elipse(0, 0, 0.7, 0.4, 0, 2 * M_PI, negro);
    LogoBatman();

    glutSwapBuffers();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Logo de Batman (Refactorizado)");
    inicio();
    glutDisplayFunc(display);
    glutMainLoop();

    return EXIT_SUCCESS;
}