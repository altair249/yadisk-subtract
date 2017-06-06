#include "yadisk/ops/Resource.hpp"

using nlohmann::json;

void to_json(json& j, const yadisk::ops::Resource& r) {
	j = r.data;
}

void from_json(const json& j, yadisk::ops::Resource& r) {
	r.data = j;
}

yadisk::ops::Resource::Resource(const json& input)
{
	data = input;
	remove_dirs();
}

yadisk::ops::Resource::Resource(Resource *input)
{
	data = input->data;
}

auto yadisk::ops::Resource::operator=(const json& input) -> Resource&
{
	data = input;
	remove_dirs();
	return *this;
}

auto yadisk::ops::Resource::operator=(const Resource& input) -> Resource&
{
	data = input.data;
	return *this;
}

auto yadisk::ops::Resource::operator==(const Resource& input) -> bool
{
	if (data == input.data)
		return true;
	else
		return false;
}

auto yadisk::ops::Resource::operator==(const json& input) -> bool
{
	if (data == input)
		return true;
	else
		return false;
}

auto yadisk::ops::Resource::operator()(const string& a) -> json&
{
	return data[a];
}

auto yadisk::ops::Resource::at(int32_t index) -> json&
{
	return data["_embedded"]["items"][index];
}

auto yadisk::ops::Resource::erase(int32_t index) -> void
{
	data["_embedded"]["total"] = total() - 1;
	data["_embedded"]["items"].erase(index);
}

auto yadisk::ops::Resource::total() -> int32_t
{
	return data["_embedded"]["total"].get<int32_t>();
}

yadisk::ops::Resource::~Resource()
{
	data.clear();
}

auto yadisk::ops::Resource::remove_dirs() -> void
{
	for (int32_t i = 0; i < total(); i++)
		if (at(i)["type"].get<string>() == "dir") {
			erase(i);
			i--;
		}
}
