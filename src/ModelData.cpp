#include "ModelData.h"
#include <iostream>
ModelData::ModelData(std::vector<glm::vec3>* pos, std::vector<glm::vec2>* textureCoord, std::vector<glm::vec3>* normal)
{
	this->position_ = pos;
	this->texCoord_ = textureCoord;
	this->normal_ = normal;
}

ModelData::ModelData()
{

}

std::vector<glm::vec3>& ModelData::getPos()
{
	return *position_;
}

std::vector<glm::vec2>& ModelData::getTexCoord()
{
	return *texCoord_;
}

std::vector<glm::vec3>& ModelData::getNormal()
{
	return *normal_;
}

void ModelData::setPos(std::vector<glm::vec3>* pos)
{
	this->position_ = pos;
}
void ModelData::setTexCoord(std::vector<glm::vec2>* texCoord)
{
	this->texCoord_ = texCoord;
}
void ModelData::setNormal(std::vector<glm::vec3>* normal)
{
	this->normal_ = normal;
}
