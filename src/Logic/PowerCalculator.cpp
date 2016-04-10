#include "PowerCalculator.h"
#include <iostream>

PowerCalculator::PowerCalculator() //0.2264916W 100% power
{
    actualPower_ = 0;
    maximumPower_ = 0;
    irradiance_ = 1;
}

float PowerCalculator::calculateTotalPower(ModelData& data, glm::vec3 & solarArray) const
{
    float angle, surfaceArea;
    float totalSurfaceArea = 0;
    float currentMax = 0;
    float actualPower = 0; //TODO
    float maxPower = 0;
    glm::vec3 nSolar = glm::normalize(solarArray);
    for (int i = 0; i < data.getSize(); i += 3)
    {
        glm::vec3 normal = getNormalVector(data, i); 
        normal = glm::normalize(normal);
        angle = glm::acos(glm::dot(normal, nSolar)); 
        if (isOuterTriangle(normal))
        {
            surfaceArea = calculateSurfaceArea(data, i);
            totalSurfaceArea += surfaceArea;
            currentMax = calculateMaxPower(surfaceArea);
            maxPower += currentMax;
            actualPower += calculatePowerUsingMax(angle, currentMax);
        }
    }
    float percentPower = (actualPower / maxPower) * 100;
    actualPower *= 0.239f;
    maxPower *= 0.239f;
    std::cout << "Surface area is  " << totalSurfaceArea << std::endl;
    std::cout << "Total power has been calculated to be " << actualPower << std::endl;
    std::cout << "Maximum power has been calculated to be  " << maxPower << std::endl;
    std::cout << "Percentage power has been calculated to be  " << percentPower << std::endl;
    return actualPower;
}

bool PowerCalculator::isOuterTriangle(glm::vec3& normalVector) const
{
    float dot = glm::dot(glm::vec3(0, 1, 0), normalVector);
    float angle = glm::acos(dot);
    if (angle >= 1.57079) //angle >=90
        return false;
    return true;
}

glm::vec3 PowerCalculator::getNormalVector(ModelData& data, int triangleIndex) const
{
    glm::vec3 p1 = data.getPos().at(triangleIndex);
    glm::vec3 s1 = data.getPos().at(triangleIndex + 1) - p1;
    glm::vec3 s2 = data.getPos().at(triangleIndex + 2) - p1;
    return glm::cross(s1, s2);
}

float PowerCalculator::calculateSurfaceArea(ModelData & data, int triangleIndex) const
{
    glm::vec3 p1 = data.getPos().at(triangleIndex);
    glm::vec3 s1 = p1 - data.getPos().at(triangleIndex + 1);
    glm::vec3 s2 = p1 - data.getPos().at(triangleIndex + 2);
    glm::vec3 v = glm::cross(s1, s2);
    return (glm::length(v) * 0.5f / 1000);
}

float PowerCalculator::calculateMaxPower(float& surfaceArea) const
{
    return (surfaceArea * irradiance_);
}

float PowerCalculator::calculatePowerUsingMax(float& angle, float& maxPower) const
{
    if (angle >= 1.5708)
        return 0;
    return ((glm::cos(angle) * maxPower));
}
