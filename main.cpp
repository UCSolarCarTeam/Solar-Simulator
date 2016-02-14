#include <iostream>
#include <GL/glew.h>
#include "display.h"
#include "mesh.h"
#include "shader.h"

int main(int argc, char **argv)
{
	Display display (800, 600, "Solar Simulator");
	Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0)), //OpenGL coordinates are from -1 to 1
						 Vertex(glm::vec3(0, 0.5, 0)),
						 Vertex(glm::vec3(0.5, -0.5, 0)) };

	Shader shader("./res/basicShader");
	Mesh mesh (vertices, sizeof(vertices)/sizeof(vertices[0]));
	while(!display.IsClosed())
	{
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);
		shader.Bind();
		mesh.Draw();
		display.Update();
	}

	return 0;
}