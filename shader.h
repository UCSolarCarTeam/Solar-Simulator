#ifndef SHADER_H
#define SHADER_H

#include <string>
#incldue <GL/glew.h>

class Shader
{
public:
	Shader(const std::string&, fileName);
	void Bind();
	virtual Shader();
protected:
private:
	Shader(const Shader& other) {}
	void operator=(const Shader other) {}
};

#endif