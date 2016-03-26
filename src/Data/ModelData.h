#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

class ModelData
{
public:
	ModelData(std::vector<glm::vec3>* pos, std::vector<glm::vec2>* textureCoord, std::vector<glm::vec3>* normal);
	ModelData();
	const std::vector<glm::vec3>& getPos() const;
	const std::vector<glm::vec2>& getTexCoord() const;
	const std::vector<glm::vec3>& getNormal() const;
	const std::vector<unsigned int>& getIndices() const;
	unsigned int getSize() const;
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

