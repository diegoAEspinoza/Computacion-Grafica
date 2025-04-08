/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

static int slices = 16;
static int stacks = 16;

/* GLUT callback Handlers */

static void resize(int width, int height)
{
    // Calcula el aspect ratio (relación de aspecto) de la ventana
    const float ar = (float) width / (float) height;

    // Establece el viewport para cubrir toda la ventana
    glViewport(0, 0, width, height);

    // Configura la matriz de proyección
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Define la proyección en perspectiva usando frustum
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    // Configura la matriz de modelo y vista
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void display(void)
{
    // Obtiene el tiempo transcurrido desde el inicio de la ejecución en segundos
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    // Calcula el ángulo de rotación en función del tiempo (gira 90 grados por segundo)
    const double a = t * 90.0;

    // Limpia el buffer de color y el buffer de profundidad
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Establece el color de los objetos en rojo
    glColor3d(1, 0, 0);

    // Dibuja una esfera sólida en la parte superior izquierda
    glPushMatrix();
        glTranslated(-2.4, 1.2, -6);  // Posiciona la esfera
        glRotated(60, 1, 0, 0);       // Aplica una rotación inicial
        glRotated(a, 0, 0, 1);        // Rota sobre el eje Z en función del tiempo
        glutSolidSphere(1, slices, stacks); // Dibuja una esfera sólida
    glPopMatrix();

    // Dibuja un cono sólido en la parte superior central
    glPushMatrix();
        glTranslated(0, 1.2, -6);
        glRotated(60, 1, 0, 0);
        glRotated(a, 0, 0, 1);
        glutSolidCone(1, 1, slices, stacks); // Dibuja un cono sólido
    glPopMatrix();

    // Dibuja un toroide sólido en la parte superior derecha
    glPushMatrix();
        glTranslated(2.4, 1.2, -6);
        glRotated(60, 1, 0, 0);
        glRotated(a, 0, 0, 1);
        glutSolidTorus(0.2, 0.8, slices, stacks); // Dibuja un toroide sólido
    glPopMatrix();

    // Dibuja una esfera de líneas en la parte inferior izquierda
    glPushMatrix();
        glTranslated(-2.4, -1.2, -6);
        glRotated(60, 1, 0, 0);
        glRotated(a, 0, 0, 1);
        glutWireSphere(1, slices, stacks); // Dibuja una esfera en modo wireframe
    glPopMatrix();

    // Dibuja un cono de líneas en la parte inferior central
    glPushMatrix();
        glTranslated(0, -1.2, -6);
        glRotated(60, 1, 0, 0);
        glRotated(a, 0, 0, 1);
        glutWireCone(1, 1, slices, stacks); // Dibuja un cono en modo wireframe
    glPopMatrix();

    // Dibuja un toroide de líneas en la parte inferior derecha
    glPushMatrix();
        glTranslated(2.4, -1.2, -6);
        glRotated(60, 1, 0, 0);
        glRotated(a, 0, 0, 1);
        glutWireTorus(0.2, 0.8, slices, stacks); // Dibuja un toroide en modo wireframe
    glPopMatrix();

    // Intercambia los buffers para mostrar la escena renderizada
    glutSwapBuffers();
}

// Funcion de LLaves
static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        // Si se presiona la tecla 'Esc' (código 27) o la tecla 'q', se cierra la aplicación
        case 27 :
        case 'q':
            exit(0);
            break;

        // Si se presiona la tecla '+', se incrementan las variables slices y stacks
        // Esto aumenta la resolución de los objetos 3D (hace que tengan más detalles)
        case '+':
            slices++;
            stacks++;
            break;

        // Si se presiona la tecla '-', se reducen slices y stacks, pero no por debajo de 3
        // Esto evita que los objetos se vuelvan demasiado simples o desaparezcan
        case '-':
            if (slices > 3 && stacks > 3)
            {
                slices--;
                stacks--;
            }
            break;
    }

    // Indica a OpenGL que debe volver a renderizar la escena con los nuevos valores
    glutPostRedisplay();
}


static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */

int main(int argc, char *argv[])
{
    // Inicializa GLUT y procesa los argumentos de la línea de comandos
    glutInit(&argc, argv);
    
    // Configura el tamaño inicial de la ventana
    glutInitWindowSize(640, 480);
    
    // Define la posición inicial de la ventana en la pantalla
    glutInitWindowPosition(10, 10);
    
    // Establece el modo de visualización con:
    // - `GLUT_RGB` → Usa el modelo de color RGB
    // - `GLUT_DOUBLE` → Habilita el doble buffer para una animación más fluida
    // - `GLUT_DEPTH` → Activa el buffer de profundidad para el manejo de la oclusión
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    // Crea una ventana con el título "GLUT Shapes"
    glutCreateWindow("GLUT Shapes");

    // Configura las funciones de GLUT
    glutReshapeFunc(resize);   // Función que se ejecuta cuando la ventana cambia de tamaño
    glutDisplayFunc(display);  // Función encargada de renderizar la escena
    glutKeyboardFunc(key);     // Función para manejar las entradas del teclado
    glutIdleFunc(idle);        // Función de animación (se ejecuta cuando el programa está inactivo)

    // Configuración del color de fondo (blanco)
    glClearColor(1, 1, 1, 1);

    // Habilita el culling (oculta las caras traseras de los objetos para optimizar el renderizado)
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // Habilita el test de profundidad para el correcto orden de los objetos en 3D
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Habilita la iluminación
    glEnable(GL_LIGHT0);         // Activa la fuente de luz 0
    glEnable(GL_NORMALIZE);      // Normaliza las normales (importante cuando hay escalado)
    glEnable(GL_COLOR_MATERIAL); // Permite que el color del material sea afectado por la luz
    glEnable(GL_LIGHTING);       // Activa el sistema de iluminación

    // Configura las propiedades de la luz 0
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);  // Luz ambiental
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);  // Luz difusa
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular); // Luz especular
    glLightfv(GL_LIGHT0, GL_POSITION, light_position); // Posición de la luz

    // Configura las propiedades del material de los objetos
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess); // Brillo del material

    // Inicia el bucle principal de GLUT (se ejecuta indefinidamente hasta que se cierre la ventana)
    glutMainLoop();

    return EXIT_SUCCESS; // Termina el programa correctamente
}
