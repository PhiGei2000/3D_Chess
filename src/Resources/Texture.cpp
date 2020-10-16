#include "../../include/Resources/Texture.hpp"

#include <SOIL/SOIL.h>

Texture::Texture(const std::string& filename) {    
    unsigned char* data = SOIL_load_image(filename.c_str(), &m_width, &m_height,&m_channels, SOIL_LOAD_RGB);

    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);    

    SOIL_free_image_data(data);
}

Texture::~Texture() {
    glDeleteTextures(1, &m_texture);
}

void Texture::bind(unsigned int target, unsigned int offset) const {
    glActiveTexture(GL_TEXTURE0 + offset);
    glBindTexture(target, m_texture);    
}
