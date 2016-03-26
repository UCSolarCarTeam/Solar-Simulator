#pragma once

#include <string>
#include <GL/glew.h>

class Texture
{
public:
    Texture(const std::string& fileName);
    void Bind(unsigned int unit);
    virtual ~Texture();
    Texture(const Texture& other) = delete;
    void operator=(const Texture& other) = delete;

private:
    GLuint texture_;
};


