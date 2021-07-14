
// Library includes //
#include <glew.h>

// Engine includes //
#include "shader.hpp"
#include "texture.hpp"

Texture::~Texture() {
    glDeleteTextures(1, &textureNum);
}

void Texture::Load(string textureName_) {
    textureName = textureName_;
    textureNum = Texture::LoadDDS("data/textures/" + textureName);
    textureId = glGetUniformLocation(Shader::GetProgram(), "myTextureSampler");
    hasBeenSet = true;
}

void Texture::Display() {
    if (!hasBeenSet) return;

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureNum);
    glUniform1i(textureId, 0);
}

string Texture::GetTextureName() const {
    return textureName;
}

GLuint Texture::GetTextureNum() const {
    return textureNum;
}

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII
GLuint Texture::LoadDDS(string imagepath) {
    unsigned char header[124];

    FILE *fp;

      // Opening the file
    fp = fopen(imagepath.c_str(), "rb");
    if (fp == nullptr)
        return 0;

      // Making sure it is a dds
    char filecode[4];
    fread(filecode, 1, 4, fp);
    if (strncmp(filecode, "DDS ", 4) != 0) {
        fclose(fp);
        return 0;
    }

      // Getting the surface description
    fread(&header, 124, 1, fp); 

    unsigned int height      = *(unsigned int*)&(header[8 ]);
    unsigned int width         = *(unsigned int*)&(header[12]);
    unsigned int linearSize     = *(unsigned int*)&(header[16]);
    unsigned int mipMapCount = *(unsigned int*)&(header[24]);
    unsigned int fourCC      = *(unsigned int*)&(header[80]);

    unsigned char * buffer;
    unsigned int bufsize;

    bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
    buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
    fread(buffer, 1, bufsize, fp);

      // Close the file
    fclose(fp);

    unsigned int components  = (fourCC == FOURCC_DXT1) ? 3 : 4; 
    unsigned int format;
    switch(fourCC) { 
        case FOURCC_DXT1: 
            format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT; 
            break; 
        case FOURCC_DXT3: 
            format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT; 
            break; 
        case FOURCC_DXT5: 
            format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT; 
            break; 
        default: 
            free(buffer); 
            return 0; 
    }

    GLuint textureID;
    glGenTextures(1, &textureID);

    glBindTexture(GL_TEXTURE_2D, textureID);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);	
    
    unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16; 
    unsigned int offset = 0;

    for (unsigned int level = 0; level < mipMapCount && (width || height); ++level) { 
        unsigned int size = ((width+3)/4)*((height+3)/4)*blockSize; 
        glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,  
            0, size, buffer + offset); 
     
        offset += size; 
        width  /= 2; 
        height /= 2; 

        if(width < 1) width = 1;
        if(height < 1) height = 1;

    } 

    free(buffer); 

    return textureID;
}