//
//  Settings_v2.h
//  CPP
//
//  Created by CHAIN on 2024/3/27.
//

#ifndef Settings_v2_h
#define Settings_v2_h

#include "sqlite3.h"

#include "SqliteTable.h"
#include "DataModel.h"

class Settings_v2{

public:
    static Settings_v2& GetInstance() {
        static Settings_v2 instance;
        return instance;
    }
    
    Settings_v2(const Settings_v2&) = delete;
    Settings_v2& operator=(const Settings_v2&) = delete;
    
private:
    sqlite3* _db;
    SqliteTable* _devices;
    
    sqlite3* ConnectToDb(){
        sqlite3* db;
        int rc = sqlite3_open("/Volumes/Chain/Xcode project/CPP/example.db", &db);
        if (rc != SQLITE_OK) {
            std::cerr << "Can't open database: " << sqlite3_errmsg(this->_db) << std::endl;
            return nullptr;
        } else {
            std::cout << "Database opened successfully" << std::endl;
            return db;
        }
    }
    
    Settings_v2(){
        this->_db = this->ConnectToDb();
        
        if(!this->_db)
            return;
        
        this->_devices = new SqliteTable(this->_db, DeviceData());
        //this->_devices->Insert(DeviceData("AAAAAA"));
        auto data = DeviceData(1, "CCCCCC");
        this->_devices->Update(data);
        this->_devices->RemoveById(data);
    }
    
    ~Settings_v2(){
        sqlite3_close(this->_db);
        delete this->_devices;
    }
};

#endif /* Settings_v2_h */
