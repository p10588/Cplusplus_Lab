#include "stdafx.h"

#include <string>
#include <vector>
#include <typeinfo>
#include <iostream>
#include <fstream>
#include <json.hpp>

//#include "sqlite/sqlite3.h"
#include "RepoTable.h"
#include <RepoData.h>
//#include <DeviceBase.h>
#include <KBDeviceConfig.h>
#include <TBDeviceConfig.h>

/*
#pragma region SqliteTable
template<typename T>
SqliteTable<T>::SqliteTable(sqlite3* db) {
    this->_db = db;
    this->_tableName = typeid(T).name();
    this->CreateTable(std::string(this->_tableName));
}

template<typename T>
SqliteTable<T>::~SqliteTable() {
    this->_db = nullptr;
    this->_tableName = nullptr;
}

template<typename T>
void SqliteTable<T>::Add(const T& data) { //override

    char* errorMessage;
    const char* insertSQL = "INSERT INTO users (name, age) VALUES ('John', 30);";

    int rc = sqlite3_exec(this->_db, insertSQL, nullptr, 0, &errorMessage);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }
}

template<typename T>
void SqliteTable<T>::Get(int id) { //override
}

template<typename T>
void  SqliteTable<T>::Update(int id, T newData) { //override

    char* errorMessage;
    const char* updateSQL = "UPDATE users SET age = 31 WHERE name = 'John';";

    int rc = sqlite3_exec(this->_db, updateSQL, nullptr, 0, &errorMessage);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }

}

template<typename T>
void  SqliteTable<T>::Delete(int id) { //override

    char* errorMessage;
    const char* deleteSQL = "DELETE FROM users WHERE id = 'John';";

    int rc = sqlite3_exec(this->_db, deleteSQL, nullptr, 0, &errorMessage);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }
}

template<typename T>
void SqliteTable<T>::List() { //override

    char* errorMessage;
    std::stringstream selectSQL;
    selectSQL << "SELECT * FROM " << this->_tableName << "; ";

    int rc = sqlite3_exec(this->_db, selectSQL.str().c_str(), [](void* data, int argc, char** argv, char** azColName *) -> int {
        // Callback function to process each row of the result set
        for (int i = 0; i < argc; ++i) {
            std::cout << argv[i] << " ";
        }
        std::cout << std::endl;
        return 0;
    }, nullptr, &errorMessage);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }
}

template<typename T>
void  SqliteTable<T>::ListbyId(int id) { //override
}

template<typename T>
void SqliteTable<T>::CreateTable(std::string tableName) { //private
    char* errorMessage;
    const char* createTableSQL = "CREATE TABLE IF NOT EXISTS users (" 
                                 "id INTEGER PRIMARY KEY AUTOINCREMENT," 
                                 "name TEXT NOT NULL," 
                                 "age INTEGER NOT NULL);";

    int rc = sqlite3_exec(this->_db, createTableSQL, nullptr, 0, &errorMessage);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }
}
template class SqliteTable<ProfileConfig_v2>;
template class SqliteTable<ApplicationConfig_v2>;
template class SqliteTable<DeviceData>;
template class SqliteTable<DeviceConfig_v2<KBDeviceConfig>>;
template class SqliteTable<DeviceConfig_v2<TBDeviceConfig>>;
template class SqliteTable<GlobalSetting>;

#pragma endregion
*/

#pragma region FileTable

template <typename T>
FileTable<T>::FileTable(json db) {
    this->_db = db;
}

template<typename T>
FileTable<T>::~FileTable() {

}

template<typename T>
void FileTable<T>::Add(const T& data) { //override
}

template<typename T>
void FileTable<T>::Get(int id) { //override
}

template<typename T>
void FileTable<T>::Update(int id, T newData) { //override
}

template<typename T>
void FileTable<T>::Delete(int id) { //override
}

template<typename T>
void FileTable<T>::List() { // override
}

template<typename T>
void FileTable<T>::ListbyId(int id) { // override
}

template<typename T>
void FileTable<T>::CreateTable(std::string tableName) { //override private
}

template<typename T>
void FileTable<T>::Save() {
}

//template class FileTable<DeviceData_v2<KBDeviceConfig>>;
//template class FileTable<DeviceData_v2<TBDeviceConfig>>;

template class FileTable<ProfileConfig_v2<KBDeviceConfig>>;
template class FileTable<ProfileConfig_v2<TBDeviceConfig>>;
template class FileTable<ApplicationConfig_v2<KBDeviceConfig>>;
template class FileTable<ApplicationConfig_v2<TBDeviceConfig>>;

//template class FileTable<DeviceConfig_v2<KBDeviceConfig>>;
//template class FileTable<DeviceConfig_v2<TBDeviceConfig>>;
template class FileTable<GlobalSetting>;

#pragma endregion
