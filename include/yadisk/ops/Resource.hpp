#ifndef RESOURCE_HPP
#define RESOURCE_HPP

using namespace std;

#include <nlohmann/json.hpp>
using nlohmann::json;

namespace yadisk
{
	namespace ops
	{
		class Resource
		{
		public:

			json data;

			Resource(const json& input);

			Resource(Resource* input);

			auto operator=(const json& input) -> Resource&;

			auto operator=(const Resource& input) -> Resource&;

			auto operator==(const Resource& input) -> bool;

			auto operator==(const json& input) -> bool;

			auto operator()(const string& field) -> json&;

			auto at(int32_t index) -> json&;

			auto erase(int32_t index) -> void;

			auto total() -> int32_t;

			~Resource();

		protected:

			auto remove_dirs() -> void;
		};
	}
}

#endif
