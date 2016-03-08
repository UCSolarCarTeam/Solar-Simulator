#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <GL/glew.h>

#include "Transform.h"

class Shader
{
public:
    Shader(const std::string& fileName);
    virtual ~Shader();
    Shader(const Shader&) = delete;
    void operator=(const Shader&) = delete;

    void Bind();
    void Update(const Transform& transform);

private:
    static const unsigned int NUM_SHADERS = 2;
	static const unsigned int NUM_UNIFORMS = 2;

    std::string LoadShader(const std::string& fileName);
    void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
    GLuint CreateShader(const std::string& text, unsigned int type);

    GLuint program_;
    GLuint shaders_[NUM_SHADERS];
    GLuint uniforms_[NUM_UNIFORMS];
};

#endif
