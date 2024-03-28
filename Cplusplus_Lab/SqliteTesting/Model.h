//
//  Model.h
//  CPP
//
//  Created by CHAIN on 2024/3/27.
//

#ifndef Model_h
#define Model_h

#include <string>

enum class ColumnType {
    INTEGER,
    TEXT,
    REAL,
    BLOB
};

class Model {
public:
    struct ColumnInfo {
        std::string name;
        ColumnType type;
        std::string extra;
        std::string value;
        ColumnInfo(const std::string& n, ColumnType t, const std::string& e = "")
            : name(n), type(t), extra(e) {}
    };
    
    virtual std::string TableName() const = 0;
    //virtual std::string PrimaryKey() const = 0;
    virtual std::vector<ColumnInfo> Columns() const = 0;
    virtual std::vector<std::string> ColumnValues() const = 0;
    //virtual std::string ForeignKeyConstraint() const = 0;
};

#endif /* Model_h */
