#include "../../include/Resources/ResourceManager.hpp"
#include "../../include/Components/MeshComponent.hpp"
#include "../../include/Resources/Geometry.hpp"
#include "../../include/Resources/Material.hpp"
#include "../../include/Resources/Shader.hpp"
#include "../../include/ObjLoader.hpp"

#include <fstream>
#include <nlohmann/json.hpp>

Resource::Resource()
    : m_type(typeid(void*)),
      m_data(nullptr) {
}

template <typename T>
Resource::Resource(T* value)
    : m_type{typeid(T)}, m_data{(void*)value} {
}

Resource::~Resource() {
    // delete m_data;
}

template <typename T>
T* Resource::getValue() const {
    if (m_type == typeid(T)) {
        return reinterpret_cast<T*>(m_data);
    }
    else {
        return nullptr;
    }
}

std::map<std::string, Resource> ResourceManager::m_resources;

template <typename T>
void ResourceManager::addResource(const std::string& id, const T* resource) {
    m_resources[id] = Resource(resource);
}

template <typename T>
T* ResourceManager::getResource(const std::string& resourceId) {
    if (!m_resources.contains(resourceId)) {
        return nullptr;
    }

    const Resource& resource = m_resources[resourceId];
    return resource.getValue<T>();
}

void ResourceManager::init() {
    std::ifstream fs("Resources/resources.json");

    nlohmann::json json;
    json << fs;

    const auto& textures = json["textures"];
    for (const auto& texture : textures) {
        std::string id = texture["id"];
        std::string filename = texture["filename"];

        m_resources.emplace(id, Resource(new Texture("Resources/" + filename)));
    }

    const auto& shaders = json["shaders"];
    for (const auto& shader : shaders) {
        std::string id = shader["id"];
        std::string vert = shader["vertex"];
        std::string frag = shader["fragment"];

        if (shader.contains("geometry")) {
            std::string geom = shader["geometry"];
            m_resources.emplace(id, Resource(new Shader("Resources/" + vert, "Resources/" + frag, "Resources/" + geom)));
        }
        else {
            m_resources.emplace(id, Resource(new Shader("Resources/" + vert, "Resources/" + frag)));
        }
    }

    const auto& materials = json["materials"];
    for (const auto& material : materials) {
        std::string id = material["id"];
        std::string diffuse = material["diffuse"];
        std::string normal = material["normal"];
        std::string specular = material["specular"];
        std::string shader = material["shader"];

        m_resources.emplace(id, Resource(new Material(
                                    ResourceManager::getResource<Texture>(diffuse),
                                    ResourceManager::getResource<Texture>(normal),
                                    ResourceManager::getResource<Texture>(specular),
                                    ResourceManager::getResource<Shader>(shader))));
    }

    const auto& models = json["models"];
    for (const auto& model : models) {
        std::string id = model["id"];
        std::string material = model["material"];
        std::string filename = model["filename"];

        const Geometry* geometry = Utility::ObjLoader::loadObj("Resources/" + filename);
        MeshComponent* mesh = new MeshComponent();
        mesh->data.emplace_back(geometry, ResourceManager::getResource<Material>(material));

        m_resources.emplace(id, mesh);
    }
}

template void ResourceManager::addResource<Geometry>(const std::string&, const Geometry*);
template void ResourceManager::addResource<MeshComponent>(const std::string&, const MeshComponent*);
template void ResourceManager::addResource<Shader>(const std::string&, const Shader*);
template void ResourceManager::addResource<Material>(const std::string&, const Material*);

template Geometry* ResourceManager::getResource<Geometry>(const std::string&);
template MeshComponent* ResourceManager::getResource<MeshComponent>(const std::string&);
template Shader* ResourceManager::getResource<Shader>(const std::string&);
template Material* ResourceManager::getResource<Material>(const std::string&);
