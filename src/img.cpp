#include <stdlib.h>
#include <math.h>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <GL/glut.h>


// Función para cargar imágenes BMP
unsigned char* loadBMP(const char* filename, int& width, int& height) {
    FILE* file = fopen(filename, "rb");

    if (!file) {
        std::cout << "No existe el archivo: " << filename << std::endl;
        return nullptr;
    }

    // Ir al byte 18 para leer el width y height
    fseek(file, 18, SEEK_SET);
    fread(&width, sizeof(int), 1, file);
    fread(&height, sizeof(int), 1, file);

    // Ir al offset 54 para empezar a leer los datos de los píxeles
    fseek(file, 54, SEEK_SET);

    int imageSize = width * height * 3; // 3 bytes por píxel (RGB)
    unsigned char* data = new unsigned char[imageSize];

    fread(data, 1, imageSize, file);

    // Revertir los valores de color para que OpenGL use el formato RGB
    for(int i = 0; i < imageSize; i += 3) {
        std::swap(data[i], data[i + 2]); // Intercambiar R y B
    }

    fclose(file); // Cerrar el archivo

    return data;
}

// Función para crear la textura
void crearTexture(const char* filename, GLuint& textureID) {
    int width, height;

    unsigned char* data = loadBMP(filename, width, height);

    if (!data) return;

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    delete[] data; // Liberar la memoria de los datos de la imagen
}

