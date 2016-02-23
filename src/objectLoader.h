#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

int loadObject(
	const char * path, 
	std::vector<glm::vec3> & out_vertices,
	std::vector<glm::vec3> & out_normals
);


#endif
