#include "Texture.h"
#include <iostream>


Texture::Texture(const std::string& fileName)
{
    int width, height, numComponents; //load textures into these variables
    unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);

    if (imageData == NULL)
    {
        std::cerr << "Error! Texture failed to load for texture: " << fileName << std::endl;
    }

    glGenTextures(1, &texture_);
    glBindTexture(GL_TEXTURE_2D, texture_);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

    stbi_image_free(imageData);

}

void Texture::Bind(unsigned int unit)
{
    if (unit < 0 || unit > 31)
    {
        std::cerr << "Error! Invalid texture selected!" << std::endl;
    }
    glActiveTexture(GL_TEXTURE0 + unit); //set active texture
    glBindTexture(GL_TEXTURE_2D, texture_);
}

Texture::~Texture()
{
    glDeleteTextures(1, &texture_);
}
