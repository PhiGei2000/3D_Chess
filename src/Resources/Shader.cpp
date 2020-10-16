#include "../../include/Resources/Shader.hpp"
#include "../../include/Resources/Material.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const std::string& vertShaderFilename, const std::string& fragShaderFilename, const std::string& geomShaderFilename) {
    unsigned int vertShader = loadShader(vertShaderFilename, GL_VERTEX_SHADER);
    unsigned int fragShader = loadShader(fragShaderFilename, GL_FRAGMENT_SHADER);
    unsigned int geomShader;
    if (geomShaderFilename != "") {
        geomShader = loadShader(geomShaderFilename, GL_GEOMETRY_SHADER);
    }

    m_program = glCreateProgram();
    glAttachShader(m_program, vertShader);
    glAttachShader(m_program, fragShader);

    if(geomShaderFilename != "") {
        glAttachShader(m_program, geomShader);
    }

    glLinkProgram(m_program);

    int success;
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(m_program, 512, NULL, infoLog);
        std::cout << "Shader linking failed:\n"
                  << infoLog << std::endl;
    }

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    if(geomShaderFilename != "") {
        glDeleteShader(geomShader);
    }
}

unsigned int Shader::loadShader(const std::string& filename, unsigned int type) const {
    std::ifstream file{filename};

    std::stringstream ss;
    ss << file.rdbuf();

    std::string shaderSource = ss.str();
    const char* shaderCode = shaderSource.c_str();

    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderCode, NULL);
    glCompileShader(shader);

    int success;
    glGetProgramiv(shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        char info[512];
        glGetProgramInfoLog(shader, 512, NULL, info);

        std::cout << "Shader compilation failed:\n"
                  << info << std::endl;
    }

    return shader;
}

unsigned int Shader::getLocation(const std::string& location) {
    if(m_locations.contains(location)) {
        return m_locations[location];
    }
    else {
        unsigned int loc = glGetUniformLocation(m_program, location.c_str());
        m_locations[location] = loc;
        return loc;
    }
}

void Shader::bind() const {
    glUseProgram(m_program);
}

void Shader::upload(const std::string& name, const bool& data) {
    unsigned int location = getLocation(name);
    glUniform1i(location, data);
}

void Shader::upload(const std::string& name, const int& data) {
    unsigned int location = getLocation(name);
    glUniform1i(location, data);
}

void Shader::upload(const std::string& name, const float& data) {
    unsigned int location = getLocation(name);
    glUniform1f(location, data);
}

void Shader::upload(const std::string& name, const glm::vec2& data) {
    unsigned int location = getLocation(name);
    glUniform2f(location, data.x, data.y);
}

void Shader::upload(const std::string& name, const glm::vec3& data) {
    unsigned int location = getLocation(name);
    glUniform3f(location, data.x, data.y, data.z);
}

void Shader::upload(const std::string& name, const glm::vec4& data) {
    unsigned int location = getLocation(name);
    glUniform4f(location, data.x, data.y, data.z, data.w);
}

void Shader::upload(const std::string& name, const glm::mat4& data) {
    unsigned int location = getLocation(name);
    glUniformMatrix4fv(location, 1, false, glm::value_ptr(data));
}

void Shader::upload(const std::string& name, const Material& data, int textureOffset) {
    data.diffuse->bind(GL_TEXTURE_2D, textureOffset);
    data.normal->bind(GL_TEXTURE_2D, textureOffset + 1);
    data.specular->bind(GL_TEXTURE_2D, textureOffset + 2);

    upload(name + ".diffuse", textureOffset);
    upload(name + ".normal", textureOffset + 1);
    upload(name + ".specular", textureOffset + 2);
}