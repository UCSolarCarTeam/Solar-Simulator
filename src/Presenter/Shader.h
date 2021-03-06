#pragma once

#include <string>

#include <GL/glew.h>

#include "../Data/Transform.h"

class Shader
{
public:
    Shader(const std::string& vertexShader, const std::string& fragmentShader);
    virtual ~Shader();
    Shader(const Shader&) = delete;
    void operator=(const Shader&) = delete;

    void Bind();
    void Update(const Transform& transform);

private:
    static const unsigned int NUM_SHADERS = 2;

    void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
    GLuint CreateShader(const std::string& text, unsigned int type);

    enum
    {
        TRANSFORM_U,
        LIGHTVECTOR_U,
        NUM_UNIFORMS
    };

    GLuint program_;
    GLuint shaders_[NUM_SHADERS];
    GLuint uniforms_[NUM_UNIFORMS];
};


