//
//  DataModel.h
//  CPP
//
//  Created by CHAIN on 2024/3/27.
//
#ifndef DataModel_h
#define DataModel_h

#include <string>
#include <typeinfo>

#include "Model.h"

class DeviceData : public Model{
public:

    DeviceData(){}
    DeviceData(std::string name){
        this->_name = name;
    }
    DeviceData(int id, std::string name){
        this->_id = id;
        this->_name = name;
    }
    
    std::string TableName() const override { return typeid(this).name(); }
    std::vector<ColumnInfo> Columns() const override {
        return {
            ColumnInfo("id", ColumnType::INTEGER, "PRIMARY KEY AUTOINCREMENT NOT NULL"),
            ColumnInfo("name", ColumnType::TEXT, "NOT NULL")
        };
    }
    std::vector<std::string> ColumnValues() const override {
        return {std::to_string(_id), _name};
    }

    int Id(){return this->_id;}
    std::string Name(){return this->_name;}
    
private:
    int _id;
    std::string _name;

};

#endif /* DataModel_h */
