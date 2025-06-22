#ifndef IMG_H
#define IMG_H

#include <GL/glut.h>

unsigned char* loadBMP(const char* filename, int& width, int& height);
void crearTexture(const char* filename, GLuint& textureID);

#endif 
