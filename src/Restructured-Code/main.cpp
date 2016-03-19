#include "InitSDL.h"
#include "Window.h"
#include "ObjectLoader.h"



int main(int argc, char **argv)
{
	Window window (800, 600, "Solar Simulator");
	InitSDL InitSDL();
	ObjectLoader objectLoader();

    if (!objectLoader.loadObject("samples/test.obj")
    {
        exit(EXIT_FAILURE);
    }
    const ModelData* objectData = objectLoader.getModel();

    //TODO
    float scale = 1 / (getGreatestValue(&(objectData->getPos())[0], objectData->getSize()));

    std::cout << "The greatest value is " << scale << std::endl;
    std::cout << "Number of faces: " << (objectData.getSize() + 1) / 3 << std::endl;
    Shader shader("./shaders/basicShader");
    Mesh mesh(objectData);
    Texture texture("./textures/bricks.jpg");
    Transform transform;

    float counter = 0.0f;

    transform.getScale()->x = 1 / (scale);
    transform.getScale()->y = 1 / (scale);
    transform.getScale()->z = 1 / (scale);

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