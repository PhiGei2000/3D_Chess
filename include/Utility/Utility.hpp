#pragma once

#include <nlohmann/json.hpp>
#include <glm/glm.hpp>

namespace Utility {
glm::vec3 getVec3(const nlohmann::json& node);
}