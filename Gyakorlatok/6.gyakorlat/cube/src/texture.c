#include <GL/gl.h>
#include <stdlib.h>

GLuint create_checker_texture(int width, int height)
{
    unsigned char* data = malloc(width * height * 3);
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            int offset = (y*width + x)*3;
            int c = ((x/8 + y/8) % 2) * 255;
            data[offset+0] = c; // R
            data[offset+1] = c; // G
            data[offset+2] = c; // B
        }
    }
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
    free(data);
    return tex;
}