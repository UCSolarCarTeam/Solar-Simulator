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

float getGreatestValue(glm::vec3* verticesArray, unsigned int size);

int main(int argc, char **argv)
{
    Display display (800, 600, "Solar Simulator");
	ModelData objectData = ModelData();
	loadObject("samples/test2.obj", objectData);
	std::cout << "Size outside of loadobject: " << objectData.getPos()->size() << std::endl;
	unsigned int numVertices = objectData.getPos()->size();
	std::cout << numVertices << std::endl;
	std::vector <glm::vec3> * temp = objectData.getPos();
	glm::vec3* verticesArray = &(*temp)[0];
	glm::vec3* normalsArray = &(*objectData.getNormal())[0];
	glm::vec2* texArray = &(*objectData.getTexCoord())[0];

    unsigned int* indices = new unsigned int [numVertices];
    for (unsigned int i = 0; i < numVertices; i++)
    {
        indices[i] = i;
    }

    float scale = getGreatestValue(verticesArray, numVertices);

    std::cout << "The greatest value is " << scale << std::endl;
    std::cout << "Number of faces: " << (numVertices + 1) / 3 << std::endl;
    Shader shader("./shaders/basicShader");
    Mesh mesh(verticesArray, numVertices, indices, (numVertices + 1) / 3, normalsArray);
	Texture texture("./textures/bricks.jpg");
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
       // transform.getRot()->x = counter;

        shader.Bind();
        shader.Update(transform);
		texture.Bind(0);
        mesh.Draw();

        display.Update();
        counter += 0.0002f;
    }

    delete[] indices;
    return 0;
}

float getGreatestValue(glm::vec3* verticesArray, unsigned int size)
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
