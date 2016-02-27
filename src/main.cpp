#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Display.h"
#include "Mesh.h"
#include "ObjectLoader.h"
#include "Shader.h"
#include "Transform.h"
#include "texture.h"
#include "ModelData.h"
#include "Camera.h"

float getGreatestValue(const glm::vec3* verticesArray, unsigned int size);

int main(int argc, char **argv)
{
    Display display (800, 600, "Solar Simulator");
	ModelData objectData = ModelData();
	loadObject("samples/test2.obj", objectData);

	std::vector<unsigned int>* indices = new std::vector<unsigned int>(); 
    for (unsigned int i = 0; i < objectData.getSize(); i++)
    {
		indices->push_back(i);
    }
	objectData.setIndices(indices);
    float scale = getGreatestValue(&(objectData.getPos())[0], objectData.getSize());

    std::cout << "The greatest value is " << scale << std::endl;
    std::cout << "Number of faces: " << (objectData.getSize() + 1) / 3 << std::endl;
    Shader shader("./shaders/basicShader");
    Mesh mesh(objectData);
	Texture texture("./textures/bricks.jpg");
	Camera camera(glm::vec3(0, 0, -3), 70.0f, display.getWidth() / display.getHeight(), 0.01f, 1000.0f); //specify number of units to move camera back and FOV 
	Transform transform;

    float counter = 0.0f;

    transform.getScale()->x = 1 / (scale);
    transform.getScale()->y = 1 / (scale);
    transform.getScale()->z = 1 / (scale);

    while (!display.IsClosed())
    {
        display.Clear(0.0f, 0.0f, 0.0f, 1.0f);

        transform.getRot()->y = counter; //rotate about the y-axis
        //transform.getRot()->z = counter;
        //transform.getRot()->x = counter;

        shader.Bind();
		texture.Bind(0);
        shader.Update(transform, camera);
        mesh.Draw();

        display.Update();
        counter += 0.0002f;
    }

    delete[] indices;
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
