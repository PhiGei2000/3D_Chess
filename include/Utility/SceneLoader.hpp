#pragma once
#include <nlohmann/json.hpp>
#include <entt/entt.hpp>

namespace Utility {
    class SceneLoader {
        private:
          static void loadObject(entt::registry& registry, const nlohmann::json& object);
          
          public:
            static void loadScene(const std::string& filename, entt::registry& registry);
    };
}