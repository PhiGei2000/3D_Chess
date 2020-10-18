#include "../../include/Utility/Utility.hpp"

namespace Utility {
glm::vec3 getVec3(const nlohmann::json& node) {
    return glm::vec3{
        node[0].get<float>(),
        node[1].get<float>(),
        node[2].get<float>()};
}
}