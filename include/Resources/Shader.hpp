#pragma once

#include <gl/glew.h>
#include <glm/glm.hpp>
#include <map>
#include <string>

struct Material;
struct DirectionalLight;

class Shader {
  private:
    unsigned int m_program;    
    std::map<std::string, unsigned int> m_locations;

    unsigned int loadShader(const std::string& filename, unsigned int shaderType) const;
    unsigned int getLocation(const std::string& location);

  public:
    Shader(const std::string& vertShader, const std::string& fragShader, const std::string& geometryShader = "");

    void bind() const;    

    void upload(const std::string& location, const bool& data);
    void upload(const std::string& location, const int& data);
    void upload(const std::string& location, const float& data);
    void upload(const std::string& location, const glm::vec2& data);
    void upload(const std::string& location, const glm::vec3& data);
    void upload(const std::string& location, const glm::vec4& data);
    void upload(const std::string& location, const glm::mat4& data);
    void upload(const std::string& location, const DirectionalLight& light);
};