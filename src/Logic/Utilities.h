#pragma once
#include <glm/glm.hpp>

class Utilities
{
public:
    Utilities();
    float getGreatestValue(const glm::vec3* verticesArray, unsigned int size);
    ~Utilities();
};

