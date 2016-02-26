#ifndef MODELDATA_H
#define MODELDATA_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

class ModelData
{
public:
	ModelData(std::vector<glm::vec3>* pos, std::vector<glm::vec2>* textureCoord, std::vector<glm::vec3>* normal);
	ModelData();
	std::vector<glm::vec3>& getPos();
	std::vector<glm::vec2>& getTexCoord();
	std::vector<glm::vec3>& getNormal();
	void setPos(std::vector<glm::vec3>* pos);
	void setTexCoord(std::vector<glm::vec2>* texCoord);
	void setNormal(std::vector<glm::vec3>* normal);
	
private:
	std::vector<glm::vec3>* position_;
	std::vector<glm::vec2>* texCoord_;
	std::vector<glm::vec3>* normal_;
};

#endif