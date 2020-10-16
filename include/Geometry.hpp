#pragma once

#include <vector>

struct Vertex;

class Geometry {
  private:
    unsigned int m_vao, m_vbo, m_ebo;

    int m_drawCount;

    void initBuffers();

  public:
    Geometry();
    ~Geometry();

    void draw() const;

    void updateBuffers(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
};
