#pragma once
#include <json.hpp>
#include <string>
#include <map>

//#include "TBDeviceConfig.h"
//#include "KBDeviceConfig.h"

using json = nlohmann::json;

#pragma region Struct JSON DATA

#define DATA_VERSION 1;
#define UNSUPPORTED_VALUE "UNSUPPORTED";

struct KBDeviceConfig
{
public:
	int id;
	int applicationId;
	int pid = 1;
	std::string name = "KBDeviceConfig";
	//BUTTON_ACTION_TABLE _actions;
	//std::vector<SnippetString> _snippets;
};
void from_json(const json& j, KBDeviceConfig& data);
void to_json(json& j, const KBDeviceConfig& data);


class TBDeviceConfig
{

public:
	int id;
	int applicationId;
	int pid = 2;
	std::string name = "TBDeviceConfig";
	std::string metaData = "AAAAAA";
	//Pointer _pointer;
	//Scroll _scroll;
	//BUTTON_ACTION_TABLE _actions;

	//std::vector<SnippetString> _snippets;
};
void from_json(const json& j, TBDeviceConfig& data);
void to_json(json& j, const TBDeviceConfig& data);


template<typename T3>
struct ApplicationConfig_v2
{
public:
	int id;
	std::string name = "*";
	//DEVICECONFIG_MAP<T3> deviceConfigs;
};
template<typename T3>
using APPLICATION_MAP = std::map<std::string, ApplicationConfig_v2<T3>>;


template<typename T2>
struct ProfileConfig_v2
{
public:
	int id;
	bool isSave;
	std::string name = "default";
	APPLICATION_MAP<T2> applications;
};
template<typename T2>
using PROFILECONFIG_MAP = std::map<std::string, ProfileConfig_v2<T2>>;


template<typename T1>
struct DeviceData_v2
{
public:
	std::string id = "****";
	std::string name = "****";

	PROFILECONFIG_MAP<T1> profiles;
};
template<typename T1>
void from_json(const json& j, DeviceData_v2<T1>& data);
template<typename T1>
void to_json(json& j, const DeviceData_v2<T1>& data);
template<typename T1>
using DEVICEDATA_MAP = std::map<std::string, DeviceData_v2<T1>>;


struct NotificationsStatus_v2
{
public:
	bool isMicNotificationOn = true;
	bool isProfileNotificationOn = true;
	bool isLayoutNotification = true;
	bool isLowBetteryNotificationOn = true;
};
void from_json(const json& j, NotificationsStatus_v2& data);
void to_json(json& j, const NotificationsStatus_v2& data);


struct GlobalSetting
{
public:
	NotificationsStatus_v2 _notificationsStatus;
	std::string _platform = "";
	time_t _timestamp = std::time(nullptr);
	unsigned _versionMajor = 0;
	unsigned _versionMinor = 0;
	bool _trayIcon = false;
};
void from_json(const json& j, GlobalSetting& data);
void to_json(json& j, const GlobalSetting& data);


struct Setting_v2{
public:
	int version = DATA_VERSION;
	std::string metaData = "";
	DeviceTypeConfig deviceType = DEVICE_TYPE;
	GlobalSetting globalSetting;
	DEVICEDATA_MAP<TBDeviceConfig> tbDevices;
	DEVICEDATA_MAP<KBDeviceConfig> kbDevices;
};
void from_json(const json& j, Setting_v2& data);
void to_json(json& j, const Setting_v2& data);

/*
template<typename T>
void to_json(json& j, DeviceConfig_v2<T> const& settings);

template<typename T>
void from_json(json const& j, DeviceConfig_v2<T>& settings);

template<typename T>
void to_json(json& j, ApplicationConfig_v2<T> const& settings);

template<typename T>
void from_json(json const& j, ApplicationConfig_v2<T>& settings);

template<typename T>
void to_json(json& j, ProfileConfig_v2<T> const& settings);

template<typename T>
void from_json(json const& j, ProfileConfig_v2<T>& settings);

template<typename T>
void to_json(json& j, DeviceData_v2<T> const& settings);

template<typename T>
void from_json(json const& j, DeviceData_v2<T>& settings);
*/
#pragma endregion

/*
#pragma region NO SQL Data

class DeviceData
{
public:
	std::string id;
	std::string name;
};

class ProfileData
{
public:
	int id;
	std::string name = "default";
	int deviceId;
	int version;
};

class ProfileAppRelationData
{
	int id;
	int profildId;
	int appId;
};

class ApplicationData
{
public:
	int id;
	std::string name = "*";
	int version;
};

template<typename T>
class DeviceConfigData
{
public:
	DeviceConfigData(T deviceConfig);
	~DeviceConfigData();
	int id;
	int applicationId;
	int deviceId;
	T deviceConfig;
};

#pragma endregion
*/


