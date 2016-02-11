#include <iostream>
#include <GL/glew.h>
#include "display.h"
#include "mesh.h"

int main()
{
	Display display (800, 600, "Solar Simulator");
	Vertex vertices[] = {Vertex(glm::vec3(-0.5, -0.5, 0)), //OpenGL coordinates are from -1 to 1
						 Vertex(glm::vec3(0, 0.5, 0)),
						 Vertex(glm::vec3(0.5, -0.5, 0))}

	Mesh mesh (vertices, sizeOf(vertices)/sizeof(vertices[0]));
	while(!display.isClosed())
	{
		display.Clear(0, 0f, 0.15f, 0.3f, 1.0f)
		mesh.Draw();
		display.Update();
	}

	return 0;
}