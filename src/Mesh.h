#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <glm/glm.hpp>

class Mesh
{
public:
    Mesh(glm::vec3* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
    virtual ~Mesh();
    Mesh(const Mesh&) = delete;
    void operator=(const Mesh&) = delete;

    void Draw();

private:
    enum
    {
        POSITION_VB,
        INDEX_VB,
        NUM_BUFFERS
    };
    GLuint vertexArrayObject_;
    GLuint vertexArrayBuffers_[NUM_BUFFERS];
    unsigned int drawCount_;
};

#endif
