#pragma once
#include "Geometry.hpp"
#include "Material.hpp"

#include <glm/glm.hpp>
#include <vector>

class Mesh {
  private:
    std::vector<std::pair<const Geometry*, const Material*>> m_data;

  public:
    void addGeometry(const Geometry* geometry, const Material* material);

    void render() const;
};
