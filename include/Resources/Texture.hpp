#pragma once

#include <GL/glew.h>
#include <string>

class Texture {
  private:
    GLuint m_texture;
    int m_width;
    int m_height;
    int m_channels;

  public:
    Texture(const std::string &filename);
    ~Texture();

    void bind(unsigned int target = GL_TEXTURE_2D, unsigned int offset = 0) const;
};
