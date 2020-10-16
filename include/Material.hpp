#pragma once
#include "Texture.hpp"

struct Material {
    Texture *diffuse;
    Texture *normal;
    Texture *specular;    
};

