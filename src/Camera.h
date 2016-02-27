#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera
{
public:
	Camera(const glm::vec3 pos, float fov, float aspect, float zNear, float zFar);
	glm::mat4 getViewProjection() const;
private:
	glm::mat4 perspective_;
	glm::vec3 position_;
	glm::vec3 forward_;
	glm::vec3 up_;
};

#endif
