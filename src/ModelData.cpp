#include "ModelData.h"
#include <iostream>
ModelData::ModelData(std::vector<glm::vec3>* pos, std::vector<glm::vec2>* textureCoord, std::vector<glm::vec3>* normal)
{
	this->position_ = pos;
	this->texCoord_ = textureCoord;
	this->normal_ = normal;
	this->numVertices_ = pos->size();
}

ModelData::ModelData()
{

}

const std::vector<glm::vec3>& ModelData::getPos()
{
	return *position_;
}

const std::vector<glm::vec2>& ModelData::getTexCoord()
{
	return *texCoord_;
}

const std::vector<glm::vec3>& ModelData::getNormal()
{
	return *normal_;
}
const std::vector<unsigned int>& ModelData::getIndices()
{
	return *indices_;
}
unsigned int ModelData::getSize()
{
	return numVertices_;
}
void ModelData::setSize(unsigned int pos)
{
	this->numVertices_ = pos;
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

void ModelData::setIndices(std::vector<unsigned int>* indicies)
{
	this->indices_ = indicies;
}
