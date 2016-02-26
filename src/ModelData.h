#ifndef MODELDATA_H
#define MODELDATA_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

class ModelData
{
public:
	ModelData(const std::vector<glm::vec3> &pos, const std::vector<glm::vec2> &textureCoord, const std::vector<glm::vec3> &normal);
	ModelData();
	std::vector<glm::vec3>* ModelData::getPos();
	std::vector<glm::vec2>* ModelData::getTexCoord();
	std::vector<glm::vec3>* ModelData::getNormal();
	void ModelData::setPos(std::vector<glm::vec3> & pos);
	void ModelData::setTexCoord(std::vector<glm::vec2> & texCoord);
	void ModelData::setNormal(std::vector<glm::vec3> & normal);
	
private:
	std::vector<glm::vec3> position_;
	std::vector<glm::vec2> texCoord_;
	std::vector<glm::vec3> normal_;
};

#endif