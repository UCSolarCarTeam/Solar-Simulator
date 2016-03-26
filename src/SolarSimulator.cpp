#include "SolarSimulator.h"
#include "Window.h"
#include "FileLoader.h"
#include "ImageData.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "ModelData.h"
#include "Utilities.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <iostream>


SolarSimulator::SolarSimulator()
{
}

void SolarSimulator::run()
{
    Window window(800, 600, "Solar Simulator");
    FileLoader fileLoader;
    ModelData objectData;
    if (!fileLoader.loadObject(objectData, "samples/test.obj"))
    {
        exit(EXIT_FAILURE);
    }
    Utilities utilities;
    float scale = (utilities.getGreatestValue(&(objectData.getPos())[0], objectData.getSize()));

    std::cout << "The greatest value is " << scale << std::endl;
    std::cout << "Number of faces: " << (objectData.getSize() + 1) / 3 << std::endl;

    std::string vertexShader = fileLoader.loadShader("./shaders/basicShader.vs");
    std::string fragmentShader = fileLoader.loadShader("./shaders/basicShader.fs");
    Shader shader(vertexShader, fragmentShader);

    Mesh mesh(objectData);

    ImageData textureData;
    fileLoader.loadTextures(textureData, "./textures/bricks.jpg");
    Texture texture(textureData);

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
}


SolarSimulator::~SolarSimulator()
{
}
