#pragma once

#include <string>
#include <GL/glew.h>
#include "../Data/ImageData.h"

class Texture
{
public:
    Texture(ImageData& textureData);
    void Bind(unsigned int unit);
    virtual ~Texture();
    Texture(const Texture& other) = delete;
    void operator=(const Texture& other) = delete;

private:
    GLuint texture_;
};


