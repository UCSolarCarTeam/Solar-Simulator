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

ModelData::~ModelData()
{
    delete position_; //These vectors are allocated in ObjectLoader::loadObject(const char* path)
    delete texCoord_;
    delete normal_;
}

const std::vector<glm::vec3>& ModelData::getPos() const
{
	return *position_;
}

const std::vector<glm::vec2>& ModelData::getTexCoord() const
{
	return *texCoord_;
}

const std::vector<glm::vec3>& ModelData::getNormal() const
{
	return *normal_;
}
const std::vector<unsigned int>& ModelData::getIndices() const
{
	return *indices_;
}
unsigned int ModelData::getSize() const
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
