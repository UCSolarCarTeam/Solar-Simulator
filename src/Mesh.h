#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "ModelData.h"

class Mesh
{
public:
    Mesh(const ModelData& modelData);
    virtual ~Mesh();
    Mesh(const Mesh&) = delete;
    void operator=(const Mesh&) = delete;
    void Draw();

private:
    enum
    {
        POSITION_VB,
        TEXCOORD_VB,
        NORMAL_VB,
        INDEX_VB,
        NUM_BUFFERS
    };
    GLuint vertexArrayObject_;
    GLuint vertexArrayBuffers_[NUM_BUFFERS];
    unsigned int drawCount_;
};


