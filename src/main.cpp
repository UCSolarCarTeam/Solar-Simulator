#include "Window.h"
#include "FileLoader.h"
#include <iostream>
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "ModelData.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

float getGreatestValue(const glm::vec3* verticesArray, unsigned int size);

int main(int argc, char **argv)
{
    Window window (800, 600, "Solar Simulator");
    FileLoader fileLoader;

    if (!fileLoader.loadObject("samples/test.obj"))
    {
        exit(EXIT_FAILURE);
    }
    const ModelData* objectData = fileLoader.getModel();

    float scale = (getGreatestValue(&(objectData->getPos())[0], objectData->getSize()));

    std::cout << "The greatest value is " << scale << std::endl;
    std::cout << "Number of faces: " << (objectData->getSize() + 1) / 3 << std::endl;

    std::string vertexShader = fileLoader.loadShader("./shaders/basicShader.vs");
    std::string fragmentShader = fileLoader.loadShader("./shaders/basicShader.fs");

    Shader shader(vertexShader, fragmentShader);
    Mesh mesh(*objectData);
    Texture texture("./textures/bricks.jpg");
    Transform transform;

    float counter = 0.0f;

    transform.setScale(1 / scale);

    while (!window.IsClosed())
    {
        window.Clear(0.0f, 0.0f, 0.0f, 1.0f);

        transform.getRot()->y = counter; //rotate about the y-axis
        transform.getRot()->z = counter;

        shader.Bind();
        shader.Update(transform);
        texture.Bind(0);
        mesh.Draw();

        window.Update();
        counter += 0.0002f;
    }

    return 0;
}

float getGreatestValue(const glm::vec3* verticesArray, unsigned int size)
{
    float greatestValue = 0;
    for (unsigned int i = 0; i < size; i++)
    {
        if (glm::abs(verticesArray[i].x) > greatestValue)
        {
            greatestValue = glm::abs(verticesArray[i].x);
        }
        if (glm::abs(verticesArray[i].y) > greatestValue)
        {
            greatestValue = glm::abs(verticesArray[i].y);
        }
        if (glm::abs(verticesArray[i].z) > greatestValue)
        {
            greatestValue = glm::abs(verticesArray[i].z);
        }
    }
    return greatestValue;
}