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
	const std::vector<glm::vec3>& getPos();
	const std::vector<glm::vec2>& getTexCoord();
	const std::vector<glm::vec3>& getNormal();
	const std::vector<unsigned int>& getIndices();
	unsigned int getSize();
	void setSize(unsigned int size);
	void setPos(std::vector<glm::vec3>* pos);
	void setTexCoord(std::vector<glm::vec2>* texCoord);
	void setNormal(std::vector<glm::vec3>* normal);
	void setIndices(std::vector<unsigned int>* indicies);
	virtual ~ModelData();
private:
	std::vector<glm::vec3>* position_;
	std::vector<glm::vec2>* texCoord_;
	std::vector<glm::vec3>* normal_;
	std::vector<unsigned int>* indices_;
	unsigned int numVertices_;
};

#endif