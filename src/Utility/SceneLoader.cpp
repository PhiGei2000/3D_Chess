#include "../../include/Utility/SceneLoader.hpp"

#include "../../include/Components/Components.hpp"
#include "../../include/Resources/ResourceManager.hpp"
#include "../../include/Utility/Utility.hpp"

#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Utility {

void SceneLoader::loadObject(entt::registry& registry, const nlohmann::json& objectNode) {
    entt::entity entity = registry.create();
    if (objectNode.contains("transformation")) {
        const auto& node = objectNode["transformation"];

        TransformationComponent transform;
        if (node.contains("position")) {
            transform.position = getVec3(node["position"]);
        }

        if (node.contains("rotation")) {
            glm::vec3 axis = getVec3(node["rotation"]["axis"]);
            float angle = node["rotation"]["angle"].get<float>();

            transform.rotation = glm::angleAxis(glm::radians(angle), glm::normalize(axis));
        }

        if (node.contains("scale")) {
            transform.scale = getVec3(node["scale"]);
        }

        registry.emplace<TransformationComponent>(entity, transform);
    }

    if (objectNode.contains("mesh")) {
        std::string mesh = objectNode["mesh"];

        registry.emplace<MeshComponent>(entity, *ResourceManager::getResource<MeshComponent>(mesh));
    }
}

void SceneLoader::loadScene(const std::string& filename, entt::registry& registry) {
    nlohmann::json j;

    std::ifstream fs("Resources/" + filename);
    j << fs;

    fs.close();

    const auto& objectsNode = j["objects"];
    for (const auto& object : objectsNode) {
        loadObject(registry, object);
    }
}
} // namespace Utility