#include <iostream>

#include "Shader.h"

Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader)
{
    program_ = glCreateProgram();
    shaders_[0] = CreateShader(vertexShader, GL_VERTEX_SHADER);
    shaders_[1] = CreateShader(fragmentShader, GL_FRAGMENT_SHADER);

    for (unsigned int i = 0; i < NUM_SHADERS; i++)
    {
        glAttachShader(program_, shaders_[i]);
    }

    glBindAttribLocation(program_, 0, "position");
    glBindAttribLocation(program_, 1, "texCoord");
    glBindAttribLocation(program_, 2, "normal");

    glLinkProgram(program_);
    CheckShaderError(program_, GL_LINK_STATUS, true, "Error: Program linking failed:");

    glValidateProgram(program_);
    CheckShaderError(program_, GL_LINK_STATUS, true, "Error: Program is invalid");

    uniforms_[TRANSFORM_U] = glGetUniformLocation(program_, "transform");//gain access to transform uniform
    uniforms_[LIGHTVECTOR_U] = glGetUniformLocation(program_, "lightVector");
}

Shader::~Shader()
{
    for (unsigned int i = 0; i < NUM_SHADERS; i++)
    {
        glDetachShader(program_, shaders_[i]);
        glDeleteShader(shaders_[i]);
    }
    glDeleteProgram(program_);
}

GLuint Shader::CreateShader(const std::string& text, unsigned int type)
{
    GLuint shader = glCreateShader(type);

    if (shader == 0)
    {
        std::cerr << "Error: Shader creation failed!" << std::endl;
    }

    const GLchar* shaderSourceStrings[1];
    GLint shaderSourceStringLengths[1];

    shaderSourceStrings[0] = text.c_str(); //change to c string
    shaderSourceStringLengths[0] = text.length();

    glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
    glCompileShader(shader);

    CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed: ");

    return shader;
}


void Shader::Bind()
{
    glUseProgram(program_);
}

void Shader::Update(const Transform& transform)
{
    glm::mat4 model = transform.getModel();
    glUniformMatrix4fv(uniforms_[0], 1, GLU_FALSE, &model[0][0]);
    glUniform3f(uniforms_[1], 0.0f, 0.0f, 1.0f); //specify light direction here

}

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
    GLint success = 0;
    GLchar error[1024] = { 0 };

    if (isProgram)
    {
        glGetProgramiv(shader, flag, &success);
    }
    else
    {
        glGetShaderiv(shader, flag, &success);
    }

    if (success == GL_FALSE)
    {
        if (isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);

        std::cerr << errorMessage << ": '" << error << "'" << std::endl;
    }
}
