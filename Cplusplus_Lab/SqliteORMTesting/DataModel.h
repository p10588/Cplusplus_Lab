#pragma once

#include <string>
#include <vector>
#include <odb/core.hxx>

	#pragma db object 
	struct Action
	{
		int id = 0;
		std::string name = "action";
	};

	#pragma db object 
	struct Application
	{
		#pragma db id 
		int id = 0;
		std::string name = "App01";
		std::string path = "";
	};

	#pragma db object 
	struct DeviceConfig
	{
	#pragma db id 
		int id = 0;
		std::string name = "default";
		Application* application;
		std::vector<Action> commends;
	};

	#pragma db object 
	struct Profile
	{
		#pragma db id auto
		int id = 0;
		std::string name = "profile01";
		std::vector<DeviceConfig> configs;
	};



	#pragma db object 
	struct DeviceData
	{ 
		#pragma db id auto
		int id = 0;
		std::string name = "AAAAAAA";
		std::vector<Profile> profiles;
	};




