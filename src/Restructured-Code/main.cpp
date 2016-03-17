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
    const ModelData* data = objectData.getModel();

    //TODO
    scale = 1 / (getGreatestValue(&(objectData->getPos())[0], objectData->getSize()));

    std::cout << "The greatest value is " << scale << std::endl;
    std::cout << "Number of faces: " << (objectData.getSize() + 1) / 3 << std::endl;
}