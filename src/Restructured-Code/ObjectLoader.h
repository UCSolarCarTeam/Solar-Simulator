#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <vector>
#include "ModelData.h"

#include <glm/glm.hpp>


class ObjectLoader
{
public:
	ObjectLoader();
	const ModelData* getModel();
	bool loadObject(const char* path, ModelData& data);
	ObjectLoader(const ObjectLoader&) = delete;
    void operator=(const ObjectLoader&) = delete;

private:
	ModelData * data_;
};

#endif
