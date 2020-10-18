#pragma once
#include "Shader.hpp"
#include "Texture.hpp"

class Material {
  public:
    Texture* diffuseTexture;
    Texture* normalTexture;
    Texture* specularTexture;

    Shader* shader;

    bool usesTextures;

    glm::vec3 diffuseColor;
    glm::vec3 specularColor;

    Material(Texture* diffuseTexture, Texture* normalTexture, Texture* specularTexture, Shader* shader);
    Material(Texture* diffuseTexture, Texture* specularTexture, Shader* shader);
    Material(glm::vec3 diffuseColor, glm::vec3 specularColor, Shader* shader);

    void use();    
};
