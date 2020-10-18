#include "../../include/Resources/Material.hpp"

Material::Material(Texture* diffuseTexture, Texture* normalTexture, Texture* specularTexture, Shader* shader)
    : usesTextures{true}, diffuseTexture{diffuseTexture}, normalTexture{normalTexture}, specularTexture{specularTexture}, shader{shader} {
}

Material::Material(Texture* diffuseTexture, Texture* specularTexture, Shader* shader)
    : usesTextures{true}, diffuseTexture{diffuseTexture}, normalTexture{nullptr}, specularTexture{specularTexture}, shader{shader} {
}

Material::Material(glm::vec3 diffuseColor, glm::vec3 specularColor, Shader* shader)
    : usesTextures{false}, diffuseColor{diffuseColor}, specularColor{specularColor}, shader{shader} {
}

void Material::use() {
    if (usesTextures) {
        bool useNormalMap = normalTexture;
        shader->upload("useNormalMap", useNormalMap);

        diffuseTexture->bind(GL_TEXTURE_2D);
        shader->upload("material.diffuse", 0);
        specularTexture->bind(GL_TEXTURE_2D, 2);
        shader->upload("material.specular", 2);

        if (useNormalMap) {
            normalTexture->bind(GL_TEXTURE_2D, 1);
            shader->upload("material.normal", 1);
        }
    }
    else {
        shader->upload("material.diffuse", diffuseColor);
        shader->upload("material.specular", specularColor);
    }
}
