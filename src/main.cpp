#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "display.h"
#include "mesh.h"
#include "shader.h"
#include "transform.h"
#include "objectLoader.h"
#include <vector>

float getGreatestValue(glm::vec3 * verticesArray, unsigned int size);

int main(int argc, char **argv)
{
	Display display (800, 600, "Solar Simulator");

	/*glm::vec3 verticesArray[] = { (glm::vec3(-0.5, -0.5, 0)), //OpenGL coordinates are from -1 to 1
						 (glm::vec3(0, 0.5, 0)),
						 (glm::vec3(0, -0.5, 0)),
						(glm::vec3(-0.5, -0.5, 0.5)),
						(glm::vec3(0, 0.5, 0.5)),
						(glm::vec3(0.5, -0.5, 0.5))};

	unsigned int indices[] = { 0, 1 , 2, 3, 4, 5};*/
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals; // Won't be used at the moment.
	unsigned int numVertices = loadObject("test2.obj", vertices, normals);
	glm::vec3 * verticesArray = &vertices[0];
	unsigned int * indices = new unsigned int[numVertices];
	for (unsigned int i = 0; i < numVertices; i++)
	{
		indices[i] = i;
	}
	/*for (int i = 0; i < numVertices; i++)
	{
		printf("Vertex %d: %f %f %f\n", i, verticesArray[i].x, verticesArray[i].y, verticesArray[i].z);
	}*/

	float scale = getGreatestValue(verticesArray, numVertices);

	printf("The greatest value is %f \n", scale);
	printf("Number of faces: %d\n", ((numVertices + 1)/3));
	Shader shader("./res/basicShader");
	Mesh mesh(verticesArray, numVertices, indices, (numVertices + 1)/3);
	Transform transform;

	float counter = 0.0f;

	transform.GetScale()->x = 1 / (scale);
	transform.GetScale()->y = 1 / (scale);
	transform.GetScale()->z = 1 / (scale);

	while(!display.IsClosed())
	{
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);
		
		transform.GetRot()->y = counter; //rotate about the y-axis
		transform.GetRot()->z = counter;
		transform.GetRot()->x = counter;
		
		shader.Bind();
		shader.Update(transform);
		mesh.Draw();

		/*glPointSize(10);
		glBegin(GL_POINTS);
		glVertex3f(1, 0, 0);
		glVertex3f(0, 1, 0);
		glVertex3f(0, 0, 1);
		glEnd();*/

		display.Update();
		counter += 0.0002f;
	}

	return 0;
}

float getGreatestValue(glm::vec3 * verticesArray, unsigned int size)
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