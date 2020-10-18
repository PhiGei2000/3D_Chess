#include "../../include/Resources/ResourceManager.hpp"
#include "../../include/Components/MeshComponent.hpp"
#include "../../include/Resources/Geometry.hpp"
#include "../../include/Resources/Material.hpp"
#include "../../include/Resources/Shader.hpp"
#include "../../include/Utility/ObjLoader.hpp"

#include <fstream>
#include <iostream>

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

void ResourceManager::loadTextures(const nlohmann::json& textures) {
    for (const auto& texture : textures) {
        std::string id = texture["id"];
        std::string filename = texture["filename"];

        m_resources.emplace(id, Resource(new Texture("Resources/" + filename)));
    }
}

void ResourceManager::loadShaders(const nlohmann::json& shaders) {
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
}

void ResourceManager::loadMaterials(const nlohmann::json& materials) {
    for (const auto& material : materials) {
        std::string id = material["id"];
        std::string type = material["type"];
        std::string shader = material["shader"];

        if (type == "texture") {
            std::string diffuse = material["diffuse"];
            std::string specular = material["specular"];
            if (material.contains("normal")) {
                std::string normal = material["normal"];

                m_resources.emplace(id, Resource(new Material(getResource<Texture>(diffuse),
                                                              getResource<Texture>(normal),
                                                              getResource<Texture>(specular),
                                                              getResource<Shader>(shader))));
            }
            else {
                m_resources.emplace(id, Resource(new Material(getResource<Texture>(diffuse),                                                              
                                                              getResource<Texture>(specular),
                                                              getResource<Shader>(shader))));
            }            
        }
        else if (type == "color") {
            const auto& diffuseNode = material["diffuse"];
            const auto& specularNode = material["specular"];
            glm::vec3 diffuse, specular;
            for (int i = 0; i < 3; i++) {
                diffuse[i] = diffuseNode[i].get<float>();
                specular[i] = specularNode[i].get<float>();
            }

            m_resources.emplace(id, Resource(new Material(diffuse, specular,
                                                          getResource<Shader>(shader))));
        }
        else {
            std::cout << "Unknown material type: \"" << type << "\"" << std::endl;
        }
    }
}

void ResourceManager::loadModels(const nlohmann::json& models) {
    for (const auto& model : models) {
        std::string id = model["id"];
        std::string filename = model["filename"];

        Geometry* geo = Utility::ObjLoader::loadObj("Resources/" + filename);
        addResource(id, geo);
    }
}

void ResourceManager::loadObjects(const nlohmann::json& objects) {
    for (const auto& object : objects) {
        std::string id = object["id"];
        std::string material = object["material"];
        std::string model = object["model"];

        addResource(id, new MeshComponent(getResource<Geometry>(model), getResource<Material>(material)));
    }
}

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
    loadTextures(textures);

    const auto& shaders = json["shaders"];
    loadShaders(shaders);

    const auto& materials = json["materials"];
    loadMaterials(materials);

    const auto& models = json["models"];
    loadModels(models);

    const auto& objects = json["objects"];
    loadObjects(objects);
}

bool ResourceManager::contains(const std::string& resourceId) const {
    return m_resources.contains(resourceId);
}

template void ResourceManager::addResource<Geometry>(const std::string&, const Geometry*);
template void ResourceManager::addResource<MeshComponent>(const std::string&, const MeshComponent*);
template void ResourceManager::addResource<Shader>(const std::string&, const Shader*);
template void ResourceManager::addResource<Material>(const std::string&, const Material*);

template Geometry* ResourceManager::getResource<Geometry>(const std::string&);
template MeshComponent* ResourceManager::getResource<MeshComponent>(const std::string&);
template Shader* ResourceManager::getResource<Shader>(const std::string&);
template Material* ResourceManager::getResource<Material>(const std::string&);
