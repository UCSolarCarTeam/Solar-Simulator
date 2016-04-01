#include <gtest/gtest.h>
#include <gmock/gmock.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "../../src/Data/Transform.h"

class TransformTest : public ::testing::Test {
protected:
    Transform* transform_;

    virtual void SetUp() {
        glm::vec3 position = glm::vec3(1.0f, 1.0f, 1.0f);
        glm::vec3 rotation = glm::vec3(1.0f, 1.0f, 1.0f);
        glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
        transform_ = new Transform(position, rotation, scale); 
    }

    virtual void TearDown() {
        delete transform_;
    }
};

TEST_F(TransformTest, setGetPositionTest) {
    glm::vec3 expectedPosition = glm::vec3(1.0f, 2.0f, 3.0f);

    transform_->setPos(expectedPosition);
    const glm::vec3* actualPosition = transform_->getPos();
    EXPECT_EQ(actualPosition->x, expectedPosition.x);
    EXPECT_EQ(actualPosition->y, expectedPosition.y);
    EXPECT_EQ(actualPosition->z, expectedPosition.z);
}

TEST_F(TransformTest, setGetRotationTest) {
    glm::vec3 expectedRotation = glm::vec3(4.0f, 5.0f, 6.0f);

    transform_->setRot(expectedRotation);
    const glm::vec3* actualRotation = transform_->getRot();
    EXPECT_EQ(actualRotation->x, expectedRotation.x);
    EXPECT_EQ(actualRotation->y, expectedRotation.y);
    EXPECT_EQ(actualRotation->z, expectedRotation.z);
}

TEST_F(TransformTest, setGetScaleTest) {
    glm::vec3 expectedScale = glm::vec3(7.0f, 8.0f, 9.0f);

    transform_->setScale(expectedScale);
    const glm::vec3* actualScale = transform_->getScale();
    EXPECT_EQ(actualScale->x, expectedScale.x);
    EXPECT_EQ(actualScale->y, expectedScale.y);
    EXPECT_EQ(actualScale->z, expectedScale.z);
}
