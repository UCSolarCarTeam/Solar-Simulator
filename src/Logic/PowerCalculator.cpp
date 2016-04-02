#include "PowerCalculator.h"


PowerCalculator::PowerCalculator()
{
    actualPower_ = 0;
    maximumPower_ = 0;
}

float PowerCalculator::calculateTotalPower(ModelData& data, glm::vec3 & solarArray) const
{
    float angle, surfaceArea;
    float totalSurfaceArea = 0;
    float currentMax = 0;
    for (int i = 0; i < data.getSize; i += 3)
    {
        glm::vec3 normal = getNormalVector(data, i);
        
    }
    return 0.0;
}

bool PowerCalculator::isOuterTriangle(glm::vec3& normalVector) const
{
    return false;
}

glm::vec3 PowerCalculator::getNormalVector(ModelData& data, int triangleIndex) const
{
    return glm::vec3();
}
