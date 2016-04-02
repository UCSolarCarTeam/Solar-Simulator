#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "../Data/ModelData.h"

class PowerCalculator
{
public:
	double calculateTotalPower(ModelData& data, glm::vec3& solarArray) const;
	bool isOuterTriangle(glm::vec3& normalVector) const;
	glm::vec3 getNormalVector(ModelData& data, int triangleIndex) const;
private:

};

