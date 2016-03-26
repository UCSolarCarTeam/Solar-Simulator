#include "Utilities.h"



Utilities::Utilities()
{
}

float Utilities::getGreatestValue(const glm::vec3 * verticesArray, unsigned int size)
{
    float greatestValue = 0;
    for (unsigned int i = 0; i < size; i++)
    {
        if (glm::abs(verticesArray[i].x) > greatestValue)
        {
            greatestValue = glm::abs(verticesArray[i].x);
        }
        if (glm::abs(verticesArray[i].y) > greatestValue)
        {
            greatestValue = glm::abs(verticesArray[i].y);
        }
        if (glm::abs(verticesArray[i].z) > greatestValue)
        {
            greatestValue = glm::abs(verticesArray[i].z);
        }
    }
    return greatestValue;
}


Utilities::~Utilities()
{
}
