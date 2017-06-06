#include <iostream>
#include <fstream>
using namespace std;

#include <curl/curl.h>
#include <url/params.hpp>
#include <url/path.hpp>
#include <nlohmann/json.hpp>

#include "yadisk/ops/Tree.hpp"
#include "yadisk/ops/subtract.hpp"

template <class Stream>
auto read(char * ptr, size_t size, size_t count, void * userdata) -> size_t {

	auto stream = reinterpret_cast<Stream *>(userdata);
	auto byte_count = count * size;
	stream->read(ptr, byte_count);
	return stream->fail() ? 0 : byte_count;
}

template <class Stream>
auto write(char * ptr, size_t size, size_t count, void * userdata) -> size_t {

	auto stream = reinterpret_cast<Stream *>(userdata);
	auto byte_count = count * size;
	stream->write(ptr, byte_count);
	return stream->fail() ? 0 : byte_count;
}

json get_json(string token, string path)
{
	CURL * curl = curl_easy_init();
	if (!curl) return json();

	string url = "https://cloud-api.yandex.net/v1/disk/resources?path=" + path + "&limit=1000";

	struct curl_slist *header_list = nullptr;
	string auth_header = "Authorization: OAuth " + token;
	header_list = curl_slist_append(header_list, auth_header.c_str());

	stringstream response;
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write<stringstream>);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);

	auto response_code = curl_easy_perform(curl);

	curl_slist_free_all(header_list);
	curl_easy_cleanup(curl);

	if (response_code != CURLE_OK) return json();

	return json::parse(response);
}

void recursive_add(Tree& input, string path, yadisk::ops::Node* parent = NULL)
{
	json data = get_json("AQAAAAAXlDhiAARYfyTaNPh53U0uevKqq7pyw", path);
	Resource rsc(data);

	yadisk::ops::Node* node = input.add_child(rsc, parent);

	for (int32_t i = 0; i < data["_embedded"]["total"].get<int32_t>(); i++)
		if (data["_embedded"]["items"][i]["type"].get<string>() == "dir") {
			if (path[path.size() - 1] == '/')
				recursive_add(input, path + data["_embedded"]["items"][i]["name"].get<string>(), node);
			else
				recursive_add(input, path + "/" + data["_embedded"]["items"][i]["name"].get<string>(), node);
		}

}

int main()
{
	Tree tree1;
	Tree tree2;

	recursive_add(tree1, "/");
	recursive_add(tree2, "/Музыка");

	Tree sub(Operations::subtract(tree1, tree2));

	json flat1 = tree1.flat_list();
	json flat2 = tree2.flat_list();
	json flat3 = sub.flat_list();

	cout << "FLAT TREE1:" << endl;
	for (int32_t i = 0; i < flat1.size(); i++) {
		cout << flat1[i]["path"] << endl;
	}

	cout << endl << "FLAT TREE2:" << endl;
	for (int32_t i = 0; i < flat2.size(); i++) {
		cout << flat2[i]["path"] << endl;
	}

	cout << endl << "FLAT SUB:" << endl;
	for (int32_t i = 0; i < flat3.size(); i++) {
		cout << flat3[i]["path"] << endl;
	}

	cout << "yandex-subtract project" << endl;
	return 0;
}
