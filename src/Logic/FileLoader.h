#pragma once

#include <vector>
#include "../Data/ModelData.h"
#include "../Data/ImageData.h"
#include <string>
#include <glm/glm.hpp>


class FileLoader
{
public:
    FileLoader();
    bool loadObject(ModelData& data, const char* path);
    bool loadTextures(ImageData& data, const std::string& fileName);
    std::string loadShader(const std::string& fileName);

    FileLoader(const FileLoader&) = delete;
    void operator=(const FileLoader&) = delete;
    virtual ~FileLoader();
private:
};


