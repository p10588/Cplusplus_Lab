#pragma once

#include "FileIO.h"
#include "DataModel.h"

namespace MulitJson {


	class Settings
	{
	public:
		static Settings& GetInstance() {
			static Settings instance;
			return instance;
		}

		void Initalize(std::vector<std::string> deviceNames) {
			std::string folder = "DevicesJSON";
			for (const auto& deviceName : deviceNames) {
				_devices.emplace(deviceName, deviceName + ".json");
			}
			this->isInitalized = true;
		}

		bool GetFile(std::string deviceId, FileIO<DeviceData>& data) {
			if (!this->isInitalized) {
				std::cerr << " Settings is Uninitalized " << std::endl;
				return false;
			}
			auto it = _devices.find(deviceId);
			if (it != _devices.end()) {
				data = it->second;
				return true;
			}else{
				std::cerr << "File for device ID " << deviceId << " not found" << std::endl;
				return false;
			}

		}

	private:

		std::map<std::string, FileIO<DeviceData>> _devices;
		bool isInitalized = false;

		void GetDeviceSetting() {

		}


		Settings(){ // Private constructor to prevent instantiation
			
			/*if (DEVICE_TYPE == DeviceTypeConfig::KB) {
				settingFileIO = new FileIO<DeviceData>("KbSettingsExample.json", this->cache);
			}
			else if (DEVICE_TYPE == DeviceTypeConfig::TB) {
				settingFileIO = new FileIO<Setting_v2>("TbSettingsExample.json", this->cache);
			}
			else {
				throw std::runtime_error("Unsupported type for FileRepo constructor");
			}*/
		}
		~Settings() { }
		Settings(const Settings&) = delete; // Delete copy constructor
		Settings& operator=(const Settings&) = delete; // Delete copy assignment operator
	};


	void MultiJsonTest() {
		std::vector<std::string> deviceNames = {
		"AAAAAA", "BBBBBB"
		};
		Settings* settings = &Settings::GetInstance();
		settings->Initalize(deviceNames);

	}
}
