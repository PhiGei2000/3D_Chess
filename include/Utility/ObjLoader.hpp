#pragma once
#include <string>
#include <glm/glm.hpp>
#include <array>

class Geometry;

namespace Utility {
	class ObjLoader {
	private:
		static glm::vec3 parseVec3(const std::string& str);
		static glm::vec2 parseVec2(const std::string& str);

		static std::array<std::tuple<int, int, int>, 3> parseFace(const std::string& str);        		

      public:
		static Geometry* loadObj(const std::string& filename);
	};
};

