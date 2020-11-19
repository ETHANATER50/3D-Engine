#include "pch.h"
#include "Json.h"
#include <istreamwrapper.h>

namespace ew {
	namespace json {
		bool load(const std::string& filename, rapidjson::Document& document) {
			bool success = false;
			std::ifstream stream(filename);
			ASSERT_MSG(stream.good(), ("Error file not loaded: " + filename));
			if (stream.is_open()) {
				rapidjson::IStreamWrapper istream(stream);
				document.ParseStream(istream);
				success = document.IsObject();
				ASSERT_MSG(success, ("Error invalid json file: " + filename));
			}
			return success;
		}

		bool get(const rapidjson::Value& value, const std::string& name, int& data) {
			auto iter = value.FindMember(name.c_str());
			if (iter == value.MemberEnd()) {
				return false;
			}

			auto& property = iter->value;
			if (!property.IsInt()) {
				return false;
			}

			data = property.GetInt();
			return true;
		}

		bool get(const rapidjson::Value& value, const std::string& name, float& data) {
			auto iter = value.FindMember(name.c_str());
			if (iter == value.MemberEnd()) {
				return false;
			}

			auto& property = iter->value;
			if (!property.IsNumber()) {
				return false;
			}

			data = property.GetFloat();
			return true;
		}

		bool get(const rapidjson::Value& value, const std::string& name, bool& data) {
			auto iter = value.FindMember(name.c_str());
			if (iter == value.MemberEnd()) {
				return false;
			}

			auto& property = iter->value;
			if (!property.IsBool()) {
				return false;
			}

			data = property.GetBool();
			return true;
		}

		bool get(const rapidjson::Value& value, const std::string& name, std::string& data) {
			auto iter = value.FindMember(name.c_str());
			if (iter == value.MemberEnd()) {
				return false;
			}

			auto& property = iter->value;
			if (!property.IsString()) {
				return false;
			}

			data = property.GetString();
			return true;
		}

		bool get(const rapidjson::Value& value, const std::string& name, Vector2& data) {
			auto iter = value.FindMember(name.c_str());
			if (iter == value.MemberEnd()) {
				return false;
			}

			auto& property = iter->value;
			if (!property.IsArray() || property.Size() != 2) {
				return false;
			}

			for (rapidjson::SizeType i = 0; i < 2; i++) {
				if (!property[i].IsNumber()) {
					return false;
				}
			}

			data.x = property[0].GetFloat();
			data.y = property[1].GetFloat();

			return true;
		}

		bool get(const rapidjson::Value& value, const std::string& name, Color& data) {
			auto iter = value.FindMember(name.c_str());
			if (iter == value.MemberEnd()) {
				return false;
			}

			auto& property = iter->value;
			if (!property.IsArray() || property.Size() != 4) {
				return false;
			}

			for (rapidjson::SizeType i = 0; i < 4; i++) {
				if (!property[i].IsNumber()) {
					return false;
				}
			}

			data.r = property[0].GetFloat();
			data.g = property[1].GetFloat();
			data.b = property[2].GetFloat();
			data.a = property[3].GetFloat();
			return true;
		}

		bool get(const rapidjson::Value& value, const std::string& name, SDL_Rect& data) {
			auto iter = value.FindMember(name.c_str());
			if (iter == value.MemberEnd()) {
				return false;
			}

			auto& property = iter->value;
			if (!property.IsArray() || property.Size() != 4) {
				return false;
			}

			for (rapidjson::SizeType i = 0; i < 4; i++) {
				if (!property[i].IsNumber()) {
					return false;
				}
			}

			data.x = property[0].GetInt();
			data.y = property[1].GetInt();
			data.w = property[2].GetInt();
			data.h = property[3].GetInt();
			return true;
		}

		bool get(const rapidjson::Value& value, const std::string& name, std::vector<std::string>& data) {
			auto iter = value.FindMember(name.c_str());
			if (iter == value.MemberEnd()) {
				return false;
			}

			auto& property = iter->value;
			if (!property.IsArray()) {
				return false;
			}

			for (rapidjson::SizeType i = 0; i < property.Size(); i++) {
				if (property[i].IsString()) {
					data.push_back(property[i].GetString());
				}
			}
			return true;
		}

		bool get(const rapidjson::Value& value, const std::string& name, std::vector<int>& data) {
			auto iter = value.FindMember(name.c_str());
			if (iter == value.MemberEnd()) {
				return false;
			}

			auto& property = iter->value;
			if (!property.IsArray()) {
				return false;
			}

			for (rapidjson::SizeType i = 0; i < property.Size(); i++) {
				if (property[i].IsInt()) {
					data.push_back(property[i].GetInt());
				}
			}
			return true;
		}

	}
}
