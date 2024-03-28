#pragma once

#include <string>
#include <vector>
#include "../Json/json.hpp"

using json = nlohmann::json;

namespace MulitJson {

	struct Action
	{
		int id = 0;
		std::string name = "action";
	};
	void from_json(const json& j, Action& data) {
		j.at("name").get_to(data.name);
		j.at("id").get_to(data.id);
	}
	void to_json(json& j, const Action& data) {
		j = json{ {"id", data.id},
				  {"name", data.name} };
	}

	struct DeviceConfig
	{
		int id = 0;
		std::string name = "default";
		std::map<std::string, Action> command = { {Action().name, Action()} };
	};
	void from_json(const json& j, DeviceConfig& data) {
		j.at("name").get_to(data.name);
		j.at("id").get_to(data.id);
		j.at("command").get_to(data.command);
	}
	void to_json(json& j, const DeviceConfig& data) {
		j = json{ {"id", data.id},
				  {"name", data.name},
				  {"command", data.command} };
	}

	struct Application
	{
		int id = 0;
		std::string name = "App01";
		DeviceConfig config = DeviceConfig();
	};
	void from_json(const json& j, Application& data) {
		j.at("name").get_to(data.name);
		j.at("id").get_to(data.id);
		j.at("config").get_to(data.config);
	}
	void to_json(json& j, const Application& data) {
		j = json{ {"id", data.id},
				  {"name", data.name},
				  {"config", data.config} };
	}

	struct Profile
	{
		int id = 0;
		std::string name = "profile01";
		std::map<std::string, Application> applications = { {Application().name, Application()}};
	};
	void from_json(const json& j, Profile& data) {
		j.at("name").get_to(data.name);
		j.at("id").get_to(data.id);
		j.at("applications").get_to(data.applications);
	}
	void to_json(json& j, const Profile& data) {
		j = json{ {"id", data.id},
				  {"name", data.name},
				  {"applications", data.applications} };
	}

	struct DeviceData
	{
		int id = 0;
		std::string name = "AAAAAAA";
		std::map<std::string, Profile> profiles = {{Profile().name, Profile()}};
	};
	void from_json(const json& j, DeviceData& data) {
		j.at("name").get_to(data.name);
		j.at("id").get_to(data.id);
		j.at("profiles").get_to(data.profiles);
	}
	void to_json(json& j, const DeviceData& data) {
		j = json{ {"id", data.id},
				  {"name", data.name},
				  {"profiles", data.profiles} };
	}


}


