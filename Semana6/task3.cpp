// Nombre: Diego A. Espinoza

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
#define PI 3.141592f




float amarillo[3]     = {1, 1, 0},
      rojo[3]         = {1, 0, 0}, 
      verde[3]        = {0, 1, 0}, 
      azul[3]         = {0, 0, 1},
      cyan[3]         = {0, 1, 1},
      magenta[3]      = {1, 0, 1},
      blanco[3]       = {1, 1, 1},
      gris[3]         = {0.5f, 0.5f, 0.5f},
      naranja[3]      = {1, 0.647f, 0},
      rosa[3]         = {1, 0.75f, 0.8f},
      marron[3]       = {0.6f, 0.3f, 0},
      verde_oscuro[3] = {0, 0.5f, 0},
      azul_oscuro[3]  = {0, 0, 0.5f},
      aqua[3]         = {0, 1, 0.5f},
      crema[3]        = {1, 0.9, 0.8},
      negro[3]        = {0,0,0};

void elipse(
        float cx, float cy,
        float rx, float ry,
        float *RGB1, float *RGB2,
        float w=1.0f)
    {
        int segments = 100; 

        glColor3fv(RGB1);   
    
        glBegin(GL_TRIANGLE_FAN);
        for (int i = 0; i < segments; i++) {
            float theta = 2.0f * PI * float(i) / float(segments);
    
            float x = rx * cosf(theta);
            float y = ry * sinf(theta); 
    
            glVertex2f(x + cx, y + cy);
        }
        glEnd(); 

        glColor3fv(RGB2);   
            glLineWidth(w);

        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < segments; i++) {
            float theta = 2.0f * PI * float(i) / float(segments);
    
            float x = rx * cosf(theta);
            float y = ry * sinf(theta); 
    
            glVertex2f(x + cx, y + cy);
        }
        glEnd(); 
    }

void LogoBatman()
{ float A=0.7;
  float B=0.4;
  float s=0;
  glPointSize(2);
  glBegin(GL_POLYGON);
  glColor3f(0,0,0);
    for (float i = 0; i <= 2*M_PI; i = i + 0.009)
        {
            if ( i >=0 && i < M_PI/3){
                glVertex2f(0,0);
                glVertex2f(A*cos(i) , B*sin(i) );
                                glVertex2f(0,0);

                
            }
              
            else if ( i >=2*M_PI/3 && i <5*M_PI_4)
            { 
                glVertex2f(A*cos(i) , B*sin(i));
            }
            /*
            else if ( i >=7*M_PI_4 && i < 2*M_PI)
            {glVertex2f(A*cos(i) , B*sin(i));
            }


            else if (i >= 4*M_PI/3 && i< 3*M_PI_2)
                { s=69.0*M_PI_4/4 - i*15/8;
                    glVertex2f(A/2*sin(2*s)*cos(s) , A/2*sin(2*s)*sin(s) - B);
                }

            else if (i >= 3*M_PI_2 && i<5*M_PI/3)
                { s=53.0*M_PI_4/4 - i*15/8;
                    glVertex2f(A/2*sin(2*s)*cos(s) , A/2*sin(2*s)*sin(s) - B);
                }
            else if (i > (5*M_PI_4) && i<4*M_PI/3)
                { s=37.0*i/12 - 331.0*M_PI/144;
                    glVertex2f(-0.3*sin(2*s)*cos(s)-0.505, A/2*sin(2*s)*sin(s) - B);
                }
                else if (i >= 5*M_PI/3 && i<=7*M_PI_4)
                { s=37.0*i/12 - 713*M_PI/144;
                    glVertex2f(-0.3*sin(2*s)*cos(s)+0.505, A/2*sin(2*s)*sin(s) - B);
                }

           if ( i >= M_PI/3 && i < 4*M_PI/9)
                { s= 4.0*M_PI - 27.0*i/4;
                  glVertex2f(0.125*(1-cos(s))*cos(s) + 0.32 , 0.2*(1-cos(s))*sin(s)+B);
                }
            if ( i >=5*M_PI/9 && i < 2*M_PI/3)
                { s= 11.0*M_PI_4 - 27.0*i/4;
                  glVertex2f(-0.125*(1-cos(s))*cos(s) - 0.32 , -0.2*(1-cos(s))*sin(s)+ B );
                }

            if ( i >= 4*M_PI/9 && i < 13.0*M_PI/27)
                {glVertex2f(B*cos(i) , 2.3*(B*cos(i)-A*cos(4.0*M_PI/9)) + 0.527);
                }

            if ( i >= 14.0*M_PI/27 && i < 5*M_PI/9)
                { glVertex2f(B*cos(i) , -2.3*(B*cos(i)+A*cos(4.0*M_PI/9)) + 0.527);
                }
           if ( i >= 13.0*M_PI/27 && i < 14.0*M_PI/27)
                { glVertex2f(B*cos(i), 2.3*(B*cos(13.0*M_PI/27) - A*cos(4.0*M_PI/9)) + 0.527);
                } */
        }


  glEnd();

}

void display(void)
{
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

   elipse(0,0,0.75,0.45,amarillo,negro,5);
   LogoBatman();

   glutSwapBuffers();

}


void inicio()
{   
    int a = 1;
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