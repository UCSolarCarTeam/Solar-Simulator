#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "ObjectLoader.h"
#include "Mesh.h"

/**
 * Here is a short list of features a real function would provide :
 *  - Binary files. Reading a model should be just a few memcpy's away, not parsing a file at runtime. In short : OBJ is not very great.
 *  - Animations & bones (includes bones weights)
 *  - Multiple UVs
 *  - All attributes should be optional, not "forced"
 *  - More stable. Change a line in the OBJ file and it crashes.
 *  - More secure. Change another line and you can inject code.
 *  - Loading from memory, stream, etc
 */

int loadObject(const char* path,
               std::vector<glm::vec3>& out_vertices,
               std::vector<glm::vec3>& out_normals)
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
        return -1;
    }
    int whileLoops = 0;
    int commentLines = 0;
    for (;;)
    {
        char lineHeader[128];
        int res = fscanf(file, "%s", lineHeader);// read the first word of the line
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
                return -1;
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
    for ( unsigned int i = 0; i < vertexIndices.size(); i++ ) // For each vertex get indices of attributes
    {
        unsigned int vertexIndex = vertexIndices[i];
        unsigned int normalIndex = normalIndices[i];

        glm::vec3 vertex = temp_vertices[vertexIndex - 1]; // Get the attributes thanks to the index
        glm::vec3 normal = temp_normals[normalIndex - 1];

        // Put the attributes in buffers
        out_vertices.push_back(vertex); // Put the attributes in buffers
    }
    std::cout << "The .obj file was loaded successfully!" << std::endl;
    return vertexIndices.size();
}

