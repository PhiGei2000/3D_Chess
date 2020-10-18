#pragma once
#include "../Resources/Geometry.hpp"
#include "../Resources/Material.hpp"

#include <glm/glm.hpp>
#include <vector>

struct MeshComponent {
    Geometry* geometry;
    Material* material;

    inline MeshComponent(Geometry* geometry, Material* material)
        : geometry{geometry}, material{material} {
    }
};
