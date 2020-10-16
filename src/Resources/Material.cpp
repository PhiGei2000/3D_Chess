#include "../../include/Resources/Material.hpp"

Material::Material(Texture* diffuse, Texture* normal, Texture* specular, Shader* shader)
    : diffuse{diffuse}, normal{normal}, specular{specular}, shader{shader} {
}
