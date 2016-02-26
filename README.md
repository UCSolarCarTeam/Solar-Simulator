# Solar-Simulator

This program takes in a 3D-Model of a car from Solidworks, the program then simulates solar intensity on the model from different angles to determine the efficiency of the solar cell arrangement.

## Meshlab Instructions 

Meshlab is used to convert STL files to OBJ files.

Install meshlab on ubuntu using the following command:
	`sudo apt-get install meshlab`

Type this in command line to convert from .stl to .obj:
	`meshlabserver -i [inputlocation] -o [outputlocation]`

Example:
	`meshlabserver -i ./Materials/box.STL -o ./test.obj`

## Note 

Both glm and glew libraries have to be installed in /usr/local/include/
