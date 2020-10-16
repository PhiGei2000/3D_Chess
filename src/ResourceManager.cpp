#include "../include/ResourceManager.hpp"

Resource::Resource()
    : m_type(typeid(void*)), m_data(nullptr) {
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

#include "../include/Mesh.hpp"
#include "../include/Shader.hpp"
#include "../include/Material.hpp"
#include "../include/Geometry.hpp"

template void ResourceManager::addResource<Geometry>(const std::string&, const Geometry*);
template void ResourceManager::addResource<Mesh>(const std::string&, const Mesh*);
template void ResourceManager::addResource<Shader>(const std::string&, const Shader*);
template void ResourceManager::addResource<Material>(const std::string&, const Material*);

template Geometry* ResourceManager::getResource<Geometry>(const std::string&);
template Mesh* ResourceManager::getResource<Mesh>(const std::string&);
template Shader* ResourceManager::getResource<Shader>(const std::string&);
template Material* ResourceManager::getResource<Material>(const std::string&);
