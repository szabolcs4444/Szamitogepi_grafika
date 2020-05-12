#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glut.h>

typedef GLubyte Pixel[4];

/**
 * Load texture from file and returns with the texture name.
 */
GLuint load_texture(char* filename);
GLuint load_fust(char* filename);

#endif /* TEXTURE_H */

