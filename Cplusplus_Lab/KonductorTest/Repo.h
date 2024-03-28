#pragma once

#include <json.hpp>
#include <string>
#include <fstream>
#include <iostream>

//#include "sqlite/sqlite3.h"
#include "RepoData.h"
#include "RepoTable.h"

using json = nlohmann::json;

class IRepo
{
public:

	virtual void AddDevice() = 0;
	/*
	virtual Setting_v2<KBDeviceConfig> GetKBSettings() = 0;
	virtual void SetKBSettings(Setting_v2<KBDeviceConfig> newData) = 0;
	virtual Setting_v2<TBDeviceConfig> GetTBSettings() = 0;
	virtual void SetTBSettings(Setting_v2<TBDeviceConfig> newData) = 0;

	//profile 
	virtual bool CreateProfile(std::string deviceId, unsigned profileId, const char* name, int duplicateId) = 0;
	*/
	/*
public:
	//Notification
	virtual void SetNotification() = 0;
	virtual void GetNotification() = 0;

	//Applications
	virtual void GetAllApps() = 0;
	virtual void SetApp() = 0;
	virtual void AddApp(const ApplicationConfig_v2 data) = 0;
	virtual void DeleteApp() = 0;

	//Device & DeviceSetting
	virtual void GetAllDevices() = 0;
	virtual void GetDevice() = 0;
	virtual void RenameDevice() = 0;
	
	virtual void ResetDevice() = 0;
	virtual void DeleteDevice() = 0;

	//DeviceConfig
	virtual void UpdateCurDeviceConfig() = 0;
	virtual void GetCurDeviceConfig() = 0;
	virtual void UpdateDeviceConfig() = 0;
	virtual void GetDeviceConfig() = 0;

	//Profile
	virtual nlohmann::json GetProfiles(std::string deviceId)  = 0;
	virtual bool ResetProfile(std::string deviceId, unsigned profileId) = 0;
	virtual bool CreateProfile(std::string deviceId, unsigned profileId, const char* name, int duplicateId) = 0;
	virtual bool DeleteProfile(std::string deviceId, unsigned profileId, const char* name) = 0;
	virtual bool SaveProfile(std::string deviceId, unsigned profileId, const char* name, const char* identifier) = 0;
	virtual bool SetProfile(std::string deviceId, unsigned profileId) = 0;

	//Macro
	virtual nlohmann::json GetMacros(std::string deviceId) = 0;
	virtual bool deleteMacro(std::string deviceId, int macroid) = 0;
	virtual std::string getMacroName(std::string deviceId, int index) = 0;
	virtual nlohmann::json saveMacros(std::string deviceId, nlohmann::json j) = 0;

	//Global Setting
	virtual void GetGolbalSetting() = 0;
	virtual void SetGlobalSetting() = 0;
*/
};

/*
template <typename T>
class SqliteRepo : public IRepo
{
public:
	static SqliteRepo& GetInstance();

	IDataTable<ProfileConfig_v2>* GetProfileConfigTable() { return this->_profileConfigs; }
	IDataTable<ApplicationConfig_v2>* GetApplicationConfigTable() { return this->_applicationConfigs; }
	IDataTable<DeviceData>* GetDeviceTable() { return this->_devices; }
	IDataTable<T>* GetDeviceConfigTable() { return this->_deviceConfigs; }

	//Notification
	void SetNotification() {};
	void GetNotification() {};

	//Applications
	void GetAllApps() {};
	void SetApp() {};
	void AddApp(const ApplicationConfig_v2 data);
	void DeleteApp() {};

	//Device & DeviceSetting
	void GetAllDevices() {};
	void GetDevice() {};
	void RenameDevice() {};
	void AddDevice() {};
	void ResetDevice() {};
	void DeleteDevice() {};

	//DeviceConfig
	void UpdateCurDeviceConfig() {};
	void GetCurDeviceConfig() {};
	void UpdateDeviceConfig() {};
	void GetDeviceConfig() {};

	//Profile
	nlohmann::json GetProfiles(std::string deviceId) { return NULL; };
	bool ResetProfile(std::string deviceId, unsigned profileId) { return false; };
	bool CreateProfile(std::string deviceId, unsigned profileId, const char* name, int duplicateId) { return false; };
	bool DeleteProfile(std::string deviceId, unsigned profileId, const char* name) { return false; };
	bool SaveProfile(std::string deviceId, unsigned profileId, const char* name, const char* identifier) { return false; };
	bool SetProfile(std::string deviceId, unsigned profileId) { return false; };

	//Macro
	nlohmann::json GetMacros(std::string deviceId) { return NULL; };
	bool deleteMacro(std::string deviceId, int macroid) { return false; };
	std::string getMacroName(std::string deviceId, int index) { return 0; };
	nlohmann::json saveMacros(std::string deviceId, nlohmann::json j) { return NULL; };

	//Global Setting
	void GetGolbalSetting() {};
	void SetGlobalSetting() {};

private:
	const char* PATH = "example.db";

	sqlite3* _db;
	SqliteTable<ProfileConfig_v2<T>>* _profileConfigs;
	SqliteTable<ApplicationConfig_v2<T>>* _applicationConfigs;
	SqliteTable<DeviceData>* _devices;
	SqliteTable<T>* _deviceConfigs;
	SqliteTable<GlobalSetting>*  _globalSetting;

	sqlite3* TryConnectToDB(const char* path);

	SqliteRepo();  // Private constructor to prevent instantiation
	~SqliteRepo();
	SqliteRepo(const SqliteRepo&) = delete; // Delete copy constructor
	SqliteRepo& operator=(const SqliteRepo&) = delete; // Delete copy assignment operator
};
*/

template<typename T>
class FileIO
{
public:
	FileIO(const std::string fileName, T& cacheData);
	bool Save(T& data);
private:
	std::string _fileName;
	bool TryGetFileOrCreate(T& data);
	bool ReadFile(T& data);
	bool WriteFile(T& data);
};

class FileRepo : public IRepo//Setting
{
public:
	static FileRepo& GetInstance();

private:
	
	FileIO<Setting_v2>* settingFileIO;
	Setting_v2 cache;

	void GetDeviceConfig(int deviceid, int pid, int aid) {
		//auto DeviceConfig = cache.kbDevices[deviceid][pid][aid][ButtonCofig];
		
	}

	void AddDevice();

	FileRepo(); // Private constructor to prevent instantiation
	~FileRepo();
	FileRepo(const FileRepo&) = delete; // Delete copy constructor
	FileRepo& operator=(const FileRepo&) = delete; // Delete copy assignment operator

};






