#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct CameraComponent {
  private:
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

  public:
    float distance = 5;
    float phi = 0;
    float theta = 45;
    float fov = 60;

    glm::vec3 getPosition() const;

    glm::vec3 getUpVector() const;

    void updateViewMatrix();

    void updateProjectionMatrix(const float width, const float height);

    const glm::mat4& getViewMatrix() const;
    const glm::mat4& getProjectionMatrix() const;
};