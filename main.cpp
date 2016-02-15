#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "display.h"
#include "mesh.h"
#include "shader.h"
#include "transform.h"


int main(int argc, char **argv)
{
	Display display (800, 600, "Solar Simulator");
	Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0)), //OpenGL coordinates are from -1 to 1
						 Vertex(glm::vec3(0, 0.5, 0)),
						 Vertex(glm::vec3(0.5, -0.5, 0)),
						Vertex(glm::vec3(-0.5, -0.5, 0.5)),
						Vertex(glm::vec3(0, 0.5, 0.5)),
						Vertex(glm::vec3(0.5, -0.5, 0.5))};

	unsigned int indices[] = { 0, 1 , 2, 3, 4, 5};

	Shader shader("./res/basicShader");
	Mesh mesh (vertices, sizeof(vertices)/sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]));
	Transform transform;

	float counter = 0.0f;

	while(!display.IsClosed())
	{
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);
		transform.GetRot()->y = counter; //rotate about the y-axis
		shader.Bind();
		shader.Update(transform);
		mesh.Draw();
		display.Update();
		counter += 0.0002f;
	}

	return 0;
}