#pragma once
#include "pch.h"

namespace ew {
	class Model
	{
	public:
		static bool load(const std::string& filename, 
			std::vector<glm::vec3>& positions, 
			std::vector<glm::vec3>& normals, 
			std::vector<glm::vec2>& texcoords);

	};

}

