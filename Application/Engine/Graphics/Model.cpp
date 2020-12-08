#include "pch.h"
#include "Model.h"
#include <sstream>

namespace ew {
	bool Model::load(const std::string& filename, std::vector<glm::vec3>& positions, std::vector<glm::vec3>& normals, std::vector<glm::vec2>& texcoords)
	{
		std::vector<glm::vec3> model_positions; 
		std::vector<glm::vec3> model_normals; 
		std::vector<glm::vec2> model_texcoords; 
		std::ifstream fStream(filename, std::ios::binary); 
		
		if (!fStream.is_open()) { 
			SDL_Log("Error opening model file: %s", filename.c_str()); 
			return false; 
		}

		std::string line;
		while (std::getline(fStream, line)) {
			if (line.substr(0, 2) == "v ") {
				std::istringstream sStream(line.substr(2));
				glm::vec3 position;
				sStream >> position.x;
				sStream >> position.y;
				sStream >> position.z;
				model_positions.push_back(position);
			}

			else if (line.substr(0, 3) == "vn ") {
				std::istringstream sStream(line.substr(3));
				glm::vec3 normal;
				sStream >> normal.x;
				sStream >> normal.y;
				sStream >> normal.z;
				model_normals.push_back(normal);
			}

			else if (line.substr(0, 3) == "vt ") {
				std::istringstream sStream(line.substr(3));
				glm::vec2 uv;
				sStream >> uv.x;
				sStream >> uv.y;
				model_texcoords.push_back(uv);
			}

			else if (line.substr(0, 2) == "f ") {
				std::istringstream stream(line.substr(2));
				std::string str;
				while (std::getline(stream, str, ' ')) {
					std::istringstream stream(str);
					std::string indexString; size_t i = 0;
					unsigned int index[3] = { 0, 0, 0 }; // position, texcoord, normal

					while (std::getline(stream, indexString, '/')) {
						if (!indexString.empty()) {
							std::istringstream indexStream{ indexString };
							indexStream >> index[i];
						}i++;
					}
					if (index[0]) {
						glm::vec3 position = model_positions[index[0] - 1];
						positions.push_back(position);
					}
					if (index[1]) {
						glm::vec3 position = model_positions[index[1] - 1];
						positions.push_back(position);
					}
					if (index[2])
					{
						glm::vec3 position = model_positions[index[2] - 1];
						positions.push_back(position);
					}
				}
			}
		}
		fStream.close();
		return true;
	}
}