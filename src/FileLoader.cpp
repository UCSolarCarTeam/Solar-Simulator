#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

#include <glm/glm.hpp>

#include "FileLoader.h"
#include "Mesh.h"
#include "stb_image.h"


FileLoader::FileLoader()
{
    data_ = new ModelData();
}

const ModelData* FileLoader::getModel()
{
    return data_;
}

/**
 * Here is a short list of features a real function would provide :
 *  - Binary files. Reading a model should be just a few memcpy's away, not parsing a file at runtime. In short : OBJ is not very great.
 *  - Multiple UVs
 *  - All attributes should be optional, not "forced"
 *  - More stable. Change a line in the OBJ file and it crashes.
 *  - More secure. Change another line and you can inject code.
 *  - Loading from memory, stream, etc
 */
bool FileLoader::loadObject(const char* path)
{
    std::cout << "Loading OBJ file " << path << "..." << std::endl;

    std::vector<unsigned int> vertexIndices, normalIndices;
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec3> temp_normals;

    FILE* file = fopen(path, "r");
    if ( file == NULL )
    {
        std::cout << "Error! Unable to open file. Please check that the correct directory has been specified." << std::endl;
        getchar();
        return false;
    }
    int whileLoops = 0;
    int commentLines = 0;
    for (;;)
    {
        char lineHeader[128];
        int res = fscanf(file, "%127s", lineHeader);// read the first word of the line
        whileLoops++;
        if (res == EOF) {
            break; // EOF = End Of File. Quit the loop.
        } // else : parse lineHeader
        if ( strcmp( lineHeader, "v" ) == 0 )
        {
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
            temp_vertices.push_back(vertex);
        }
        else if ( strcmp( lineHeader, "vn" ) == 0 )
        {
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
            temp_normals.push_back(normal);
        }
        else if ( strcmp( lineHeader, "f" ) == 0 )
        {
            unsigned int vertexIndex[3], normalIndex[3];
            int numbersRead = fscanf(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2] );
            if (numbersRead != 6)
            {
                std::cout << "The file could not be read by our parser! Try exporting with other options." << std::endl;
                std::cout << "The loop ran: " << whileLoops << " times" << std::endl;
                std::cout << "Commented lines: " << commentLines << std::endl;
                return false;
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
        }
        else // Probably a comment, eat up the rest of the line
        {
            char garbageBuffer[500];
            fgets(garbageBuffer, 500, file);
            commentLines++;
        }
    }
	std::vector <glm::vec3>* out_vertices = new std::vector <glm::vec3> ();
	std::vector <glm::vec2>* out_texCoords = new std::vector <glm::vec2> ();
	std::vector <glm::vec3>* out_normals = new std::vector <glm::vec3> ();
    for ( unsigned int i = 0; i < vertexIndices.size(); i++ ) // For each vertex get indices of attributes
    {
        unsigned int vertexIndex = vertexIndices[i];
        unsigned int normalIndex = normalIndices[i];

        out_vertices->push_back(temp_vertices[vertexIndex - 1]); // Get the attributes thanks to the index
		out_normals->push_back(temp_normals[normalIndex - 1]);
		out_texCoords->push_back(glm::vec2(0.2, 0.2)); //Set the texture coordinate to an arbitrary value
    }
	data_->setPos(out_vertices);// Put the attributes in buffers
	data_->setNormal(out_normals);
	data_->setTexCoord(out_texCoords);
	data_->setSize(data_->getPos().size());

    std::vector<unsigned int>* indices = new std::vector<unsigned int>();  
    for (unsigned int i = 0; i < data_->getSize(); i++)
    {
        indices->push_back(i);
    }
    data_->setIndices(indices);

    std::cout << "The .obj file was loaded successfully!" << std::endl;
    return true;
}

std::string FileLoader::loadShader(const std::string & fileName)
{
    std::ifstream file;
    file.open((fileName).c_str());

    std::string output;
    std::string line;

    if (file.is_open())
    {
        while (file.good())
        {
            getline(file, line);
            output.append(line + "\n");
        }
    }
    else
    {
        std::cerr << "Unable to load shader: " << fileName << std::endl;
    }

    return output;
}

bool FileLoader::loadTextures(ImageData& data, const std::string& fileName)
{
    data.setImageData(stbi_load(fileName.c_str(), data.getWidth(), data.getHeight(), data.getNumComponents(), 4));
    if (data.getImageData() == NULL)
    {
        std::cerr << "Error! Texture failed to load for texture: " << fileName << std::endl;
        return false;
    }
    return true;
}

FileLoader::~FileLoader()
{

}