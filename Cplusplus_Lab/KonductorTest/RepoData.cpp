#include "stdafx.h"

#include "RepoData.h"
#include <KBDeviceConfig.h>
#include <TBDeviceConfig.h>

#pragma region DeviceConfig_v2


void from_json(const json& j, KBDeviceConfig& data) {
	j.at("id").get_to(data.id);
	j.at("name").get_to(data.name);
	j.at("applicationId").get_to(data.applicationId);
	j.at("pid").get_to(data.pid);
}
void to_json(json& j, const KBDeviceConfig& data) {
	j = json{ {"id", data.id},
			  {"applicationId", data.applicationId} };
	j["pid"] = data.pid;
	j["name"] = data.name;
}

void from_json(const json& j, TBDeviceConfig& data) {
	j.at("id").get_to(data.id);
	j.at("name").get_to(data.name);
	j.at("applicationId").get_to(data.applicationId);
	j.at("pid").get_to(data.pid);
	j.at("metaData").get_to(data.metaData);
}
void to_json(json& j, const TBDeviceConfig& data) {
	j = json{ {"id", data.id},
			  {"applicationId", data.applicationId} };
	j["pid"] = data.pid;
	j["name"] = data.name;
	j["metaData"] = data.metaData;
}

// DeviceData_v2
template<typename T1>
void from_json(const json& j, DeviceData_v2<T1>& data) {
	j.at("name").get_to(data.name);
	j.at("id").get_to(data.id);
}

template<typename T1>
void to_json(json& j, const DeviceData_v2<T1>& data) {
	j = json{ {"id", data.id},
			  {"name", data.name} };
}
template class DeviceData_v2<KBDeviceConfig>;
template class DeviceData_v2<TBDeviceConfig>;



//NotificationStatus
void from_json(const json& j, NotificationsStatus_v2& data) {
	j.at("isMicNotificationOn").get_to(data.isMicNotificationOn);
	j.at("isProfileNotificationOn").get_to(data.isProfileNotificationOn);
	j.at("isLayoutNotification").get_to(data.isLayoutNotification);
	j.at("isLowBetteryNotificationOn").get_to(data.isLowBetteryNotificationOn);
}
void to_json(json& j, const NotificationsStatus_v2& data) {
	j = json{ {"isMicNotificationOn", data.isMicNotificationOn},
			  {"isProfileNotificationOn", data.isProfileNotificationOn},
			  {"isLayoutNotification", data.isLayoutNotification},
			  {"isLowBetteryNotificationOn", data.isLowBetteryNotificationOn} };
}


//GlobalSetting
void from_json(const json& j, GlobalSetting& data) {
	j.at("platform").get_to(data._platform);
	j.at("timestamp").get_to(data._timestamp);
	j.at("versionMajor").get_to(data._versionMajor);
	j.at("versionMinor").get_to(data._versionMinor);
	j.at("trayIcon").get_to(data._trayIcon);
	j.at("notificationsStatus").get_to(data._notificationsStatus);

}
void to_json(json& j, const GlobalSetting& data) {
	j = json{ {"notificationsStatus", data._notificationsStatus},
			  {"platform", data._platform},
			  {"timestamp", data._timestamp},
			  {"versionMajor", data._versionMajor},
			  {"versionMinor", data._versionMinor},
			  {"trayIcon", data._trayIcon} };
}


//Setting

void from_json(const json& j, Setting_v2& data) {
	int version = DATA_VERSION;
	j.at("version").get_to(version);
	j.at("metaData").get_to(data.metaData);
	j.at("globalSetting").get_to(data.globalSetting);
	j.at("deviceType").get_to(data.deviceType);
	if(data.deviceType == DeviceTypeConfig::KB)
		j.at("devices").get_to(data.kbDevices);
	else if (data.deviceType == DeviceTypeConfig::TB)
		j.at("devices").get_to(data.tbDevices);
	//j.at("devices").get_to(data.devices);
}
void to_json(json& j, const Setting_v2& data) {
	
	json deviceDataJson = "";

	if (DEVICE_TYPE == DeviceTypeConfig::KB) {
		deviceDataJson = data.kbDevices;
	}else if (DEVICE_TYPE == DeviceTypeConfig::TB) {
		deviceDataJson = data.tbDevices;
	}
	
	j = json{ {"version", data.version},
			  {"metaData", data.metaData},
			  {"globalSetting", data.globalSetting},
			  {"devices", deviceDataJson} };

}


#pragma endregion
