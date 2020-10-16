#pragma once
#include "Texture.hpp"
#include "Shader.hpp"

struct Material {
    Texture* diffuse;
    Texture* normal;
    Texture* specular;

    Shader* shader;

    Material(Texture* diffuse, Texture* normal, Texture* specular, Shader* shader);
};
