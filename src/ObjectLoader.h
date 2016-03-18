#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <vector>
class ModelData;

#include <glm/glm.hpp>

bool loadObject(const char* path, ModelData& data);

#endif
