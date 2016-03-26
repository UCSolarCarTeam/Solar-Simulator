#include "Texture.h"
#include <iostream>


Texture::Texture(ImageData& textureData)
{
    glGenTextures(1, &texture_);
    glBindTexture(GL_TEXTURE_2D, texture_);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, *(textureData.getWidth()), *(textureData.getHeight()), 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData.getImageData());

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
