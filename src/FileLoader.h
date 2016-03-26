#pragma once

#include <vector>
#include "ModelData.h"
#include <string>
#include <glm/glm.hpp>


class FileLoader
{
public:
    FileLoader();
	const ModelData* getModel();
	bool loadObject(const char* path);
    std::string loadShader(const std::string& fileName);

    FileLoader(const FileLoader&) = delete;
    void operator=(const FileLoader&) = delete;
    virtual ~FileLoader();

private:
	ModelData * data_;
};


