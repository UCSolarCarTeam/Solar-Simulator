#ifndef TRANSFORM_H
#define TRANSFORM_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Transform
{
public:
    Transform(const glm::vec3& position = glm::vec3(),
              const glm::vec3& rotation = glm::vec3(),
              const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
        : position_(position)
        , rotation_(rotation)
        , scale_(scale)
    { }

    virtual ~Transform();
    Transform(const Transform&) = delete;
    void operator=(const Transform&) = delete;


    inline glm::mat4 getModel() const
    {
        glm::mat4 posMatrix = glm::translate(position_); //convert transformations into matrix
        glm::mat4 scaleMatrix = glm::scale(scale_);
        glm::mat4 rotXMatrix = glm::rotate(rotation_.x, glm::vec3(1, 0, 0));
        glm::mat4 rotYMatrix = glm::rotate(rotation_.y, glm::vec3(0, 1, 0));
        glm::mat4 rotZMatrix = glm::rotate(rotation_.z, glm::vec3(0, 0, 1));
        glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;
        return (posMatrix * rotMatrix * scaleMatrix);
    }

    inline glm::vec3* getPos() { return &position_; }
    inline glm::vec3* getRot() { return &rotation_; }
    inline glm::vec3* getScale() { return &scale_; }

    inline void setPos(glm::vec3& position) { position_ = position; }
    inline void setRot(glm::vec3& rotation) { rotation_ = rotation; }
    inline void setScale(glm::vec3& scale) { scale_ = scale; }

private:
    glm::vec3 position_;
    glm::vec3 rotation_;
    glm::vec3 scale_;
};

#endif
