#include "stdafx.h"

#include <iostream>
#include <iomanip>
#include <fstream>

#include "Repo.h"
#include "KBDeviceConfig.h"
#include "TBDeviceConfig.h"

/*
#pragma region SqliteRepo<T>

template<typename T>
SqliteRepo<T>& SqliteRepo<T>::GetInstance() {
    static SqliteRepo<T> instance;
    return instance;
}

template<typename T>
void SqliteRepo<T>::AddApp(const ApplicationConfig_v2 data) {
    this->_applicationConfigs->Add(data);
}

template<typename T>
SqliteRepo<T>::SqliteRepo() {
    this->_db = TryConnectToDB(this->PATH);
    this->_profileConfigs = new SqliteTable<ProfileConfig_v2>(this->_db);
    this->_applicationConfigs = new SqliteTable<ApplicationConfig_v2>(this->_db);
    this->_devices = new SqliteTable<DeviceData>(this->_db);
    this->_deviceConfigs = new SqliteTable<T>(this->_db);
    this->_globalSetting = new SqliteTable<GlobalSetting>(this->_db);
}

template<typename T>
SqliteRepo<T>::~SqliteRepo() {
    sqlite3_close(this->_db);
    delete this->_db;
}

template<typename T>
sqlite3* SqliteRepo<T>::TryConnectToDB(const char* path) {
    sqlite3* db = nullptr;
    // Open the SQLite database file
    int rc = sqlite3_open(this->PATH, &db);
    if (rc != SQLITE_OK) {
        // Throw an exception if the connection fails
        throw std::runtime_error("Failed to connect to the database");
    }
    return db;
}

template class SqliteRepo<DeviceConfig_v2<KBDeviceConfig>>;
template class SqliteRepo<DeviceConfig_v2<TBDeviceConfig>>;

#pragma endregion
*/


#pragma region FileIO
template<typename T>
FileIO<T>::FileIO(const std::string fileName, T& cacheData) {
    this->_fileName = fileName;
    this->TryGetFileOrCreate(cacheData);
}

template<typename T>
bool FileIO<T>::Save(T& data) {
    if (this->WriteFile(data)) {
        return true;
    }
    return false;
}

template<typename T>
bool FileIO<T>::ReadFile(T& data) {

    std::ifstream infile(this->_fileName);
    if (infile.is_open()) {
        json j;
        infile >> j;
        infile.close();
        data = j;
        return true;
    }
    else {
        std::cerr << "Unable to open file for reading: " << this->_fileName << std::endl;
        return false;
    }
}

template<typename T>
bool FileIO<T>::WriteFile(T& data) {
    std::ofstream outfile(this->_fileName);

    json j = data;

    if (outfile.is_open()) {
        outfile << j.dump(4);
        outfile.close();
        std::cout << "JSON data written to file: " << this->_fileName << std::endl;
        return true;
    }
    else {
        std::cerr << "Unable to open file for writing: " << this->_fileName << std::endl;
        return false;
    }
}

template<typename T>
bool FileIO<T>::TryGetFileOrCreate(T& data) {
    if (this->ReadFile(data))
        return true;

    T newData;
    if (this->WriteFile(newData)) { //create default value;
        
        data = newData;
        return true;
    }else
        return false;

}
template class FileIO<Setting_v2>;
#pragma endregion

#pragma region FileRepo<T>

FileRepo& FileRepo::GetInstance() {
    static FileRepo instance;
    return instance;
}
/*
template<typename T>
Setting_v2<KBDeviceConfig> FileRepo<T>::GetSettings() {
    return this->cache;
}

template<typename T>
void FileRepo<T>::SetSettings(Setting_v2<KBDeviceConfig> newData) {
    this->cache = newData;
    this->settingFileIO->Save(this->cache);
}

bool FileRepo::CreateProfile(std::string deviceId, unsigned profileId, const char* name, int duplicateId) {
    return false;
}*/

void FileRepo::AddDevice() {

}

FileRepo::FileRepo() {
    if (DEVICE_TYPE == DeviceTypeConfig::KB) {
        settingFileIO = new FileIO<Setting_v2>("KbSettingsExample.json", this->cache);
    }else if (DEVICE_TYPE == DeviceTypeConfig::TB) {
        settingFileIO = new FileIO<Setting_v2>("TbSettingsExample.json", this->cache);
    }else{
        throw std::runtime_error("Unsupported type for FileRepo constructor");
    }
} 

FileRepo::~FileRepo() { 
    delete settingFileIO; 
}


#pragma endregion

