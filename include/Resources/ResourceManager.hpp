#pragma once

#include <map>
#include <nlohmann/json.hpp>
#include <string>
#include <typeindex>
#include <typeinfo>

class Resource {
  private:
    std::type_index m_type;
    void* m_data;

  public:
    Resource();
    template <typename T>
    Resource(T* value);
    ~Resource();

    template <typename T>
    T* getValue() const;    
};

class ResourceManager {
  private:
    static std::map<std::string, Resource> m_resources;

    static void loadTextures(const nlohmann::json& textureArray);
    static void loadShaders(const nlohmann::json& shadersArray);
    static void loadMaterials(const nlohmann::json& materialsArray);
    static void loadModels(const nlohmann::json& modelsArray);
    static void loadObjects(const nlohmann::json& objectsArray);

  public:
    template <typename T>
    static void addResource(const std::string& resouceId, const T* resource);

    template <typename T>
    static T* getResource(const std::string& resourceId);

    bool contains(const std::string& resourceId) const;

    static void init();
};