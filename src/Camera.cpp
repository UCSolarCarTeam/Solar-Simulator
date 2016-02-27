#include "Camera.h"

Camera::Camera(const glm::vec3 pos, float fov, float aspect, float zNear, float zFar)
{
	perspective_ = glm::perspective(fov, aspect, zNear, zFar);
	position_ = pos;
	forward_ = glm::vec3(0, 0, 1); //hardcode axis
	up_ = glm::vec3(0, 1, 0); //define up as positive y-axis

}

glm::mat4 Camera::getViewProjection() const
{
	return perspective_ * glm::lookAt(position_, position_ + forward_, up_);
}
