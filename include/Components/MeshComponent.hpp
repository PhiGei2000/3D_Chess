#pragma once
#include "../Resources/Geometry.hpp"
#include "../Resources/Material.hpp"

#include <glm/glm.hpp>
#include <vector>

struct MeshComponent {
    std::vector<std::pair<const Geometry*, const Material*>> data;
};
