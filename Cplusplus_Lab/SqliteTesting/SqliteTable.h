//
//  SqliteTable.h
//  CPP
//
//  Created by CHAIN on 2024/3/27.
//

#ifndef SqliteTable_h
#define SqliteTable_h

#include "sqlite3.h"
#include "DataModel.h"

class SqliteTable{
   
public:
    
    SqliteTable(sqlite3* db, const Model& model){
        this->_db = db;
        this->CreateTable(model);
    }
    
    void CreateTable(const Model& model) {
        if (!tableExists(model.TableName())) {
            char* errMsg = nullptr;
            std::string sql = "CREATE TABLE " + model.TableName() + " (";
            std::vector<Model::ColumnInfo> columns = model.Columns();
            for (size_t i = 0; i < columns.size(); ++i) {
                sql += columns[i].name + " " + columnTypeToString(columns[i].type) + " " + columns[i].extra;
                sql += (i < columns.size() - 1 ? ", " : "");
            }
            sql += ");";
            int rc = sqlite3_exec(this->_db, sql.c_str(), nullptr, 0, &errMsg);
            if (rc != SQLITE_OK) {
                std::cerr << "SQL error: " << errMsg << std::endl;
                sqlite3_free(errMsg);
                throw std::runtime_error("Failed to create table");
            }
            std::cout << "Table created successfully" << std::endl;
        } else {
            std::cout << "Table already exists" << std::endl;
        }
    }
    
    void Insert(const Model& model) {
        std::string sql = "INSERT INTO " + model.TableName() + " (";
        
        std::vector<Model::ColumnInfo> columns = model.Columns();
        for (size_t i = 1; i < columns.size(); ++i) {
            sql += columns[i].name + (i < columns.size() - 1 ? ", " : "");
        }
        
        sql += ") VALUES (";
        for (size_t i = 1; i < columns.size(); ++i) {
            sql += "?"; // 使用参数占位符
            sql += (i < columns.size() - 1 ? ", " : "");
        }
        sql += ");";
        
        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(this->_db, sql.c_str(), -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << sqlite3_errmsg(this->_db) << std::endl;
            throw std::runtime_error("Failed to prepare statement");
        }

        for (int i=1; i<columns.size(); i++) {
            DeviceData::ColumnInfo info = columns[i];
            std::string value = model.ColumnValues()[i];
            bindValue(stmt, i, info.type, value);
        }

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            std::cerr << "SQL error: " << sqlite3_errmsg(this->_db) << std::endl;
            sqlite3_finalize(stmt);
            throw std::runtime_error("Failed to execute statement");
        }

        sqlite3_finalize(stmt);
        std::cout << "Data inserted successfully" << std::endl;
    }
    
    
    std::vector<Record> QueryAll(const Model& model) {
            std::vector<Model> result;

            std::string sql = "SELECT * FROM TableName;";
            sqlite3_stmt* stmt;
            int rc = sqlite3_prepare_v2(this->_db, sql.c_str(), -1, &stmt, nullptr);
            if (rc != SQLITE_OK) {
                handleError("Failed to prepare statement for query");
            }

            // 执行查询
            while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
                Model data;
                data.id = sqlite3_column_int(stmt, 0);
                const unsigned char* value = sqlite3_column_text(stmt, 1);
                data.value = reinterpret_cast<const char*>(value);
                result.push_back(record);
            }

            if (rc != SQLITE_DONE) {
                handleError("Failed to execute query statement");
            }

            sqlite3_finalize(stmt);
            return result;
        }
    
    std::vector<Model> SelectById(const int id) {
        std::vector<Model> result;
        std::string sql = "SELECT * FROM " + tableName + (condition.empty() ? "" : " WHERE " + condition) + ";";
        return result;
    }

    
    void Update(const Model& model) {
        std::string sql = "UPDATE " + model.TableName() + " SET ";
        std::vector<Model::ColumnInfo> columns = model.Columns();
        for (size_t i = 1; i < columns.size(); ++i) {
            sql += columns[i].name + " = ?";
            sql += (i < columns.size() - 1 ? ", " : "");
        }
        
        sql += " WHERE " + columns[0].name + " = " + model.ColumnValues()[0];

        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(this->_db, sql.c_str(), -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << sqlite3_errmsg(this->_db) << std::endl;
            throw std::runtime_error("Failed to prepare statement");
        }

        for (int i = 1; i < columns.size(); i++) {
            Model::ColumnInfo info = columns[i];
            std::string value = model.ColumnValues()[i];
            bindValue(stmt, i, info.type, value);
        }
        
        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            std::cerr << "SQL error: " << sqlite3_errmsg(this->_db) << std::endl;
            sqlite3_finalize(stmt);
            throw std::runtime_error("Failed to execute statement");
        }

        sqlite3_finalize(stmt);
        std::cout << "Data updated successfully" << std::endl;
    }

    void RemoveById(const Model& model) {
        std::string sql = "DELETE FROM " + model.TableName();
        
        sql += " WHERE id = " + model.ColumnValues()[0];
        
        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(this->_db, sql.c_str(), -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << sqlite3_errmsg(this->_db) << std::endl;
            throw std::runtime_error("Failed to prepare statement");
        }

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            std::cerr << "SQL error: " << sqlite3_errmsg(this->_db) << std::endl;
            sqlite3_finalize(stmt);
            throw std::runtime_error("Failed to execute statement");
        }

        sqlite3_finalize(stmt);
        std::cout << "Data removed successfully" << std::endl;
    }
    
    
    
private:
    sqlite3* _db;
    
    bool tableExists(const std::string& tableName) {
        char* errMsg = nullptr;
        std::string sql = "SELECT count(*) FROM sqlite_master WHERE type='table' AND name='" + tableName + "';";
        int count = 0;
        int rc = sqlite3_exec(this->_db, sql.c_str(), [](void* countPtr, int argc, char** argv, char** colName) {
            int* count = static_cast<int*>(countPtr);
            *count = std::stoi(argv[0]);
            return 0;
        }, &count, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
            throw std::runtime_error("Failed to check if table exists");
        }
        return count > 0;
    }

    std::string columnTypeToString(ColumnType type) {
        switch (type) {
            case ColumnType::INTEGER: return "INTEGER";
            case ColumnType::TEXT: return "TEXT";
            case ColumnType::REAL: return "REAL";
            case ColumnType::BLOB: return "BLOB";
            default: return "";
        }
    }
    
    void bindValue(sqlite3_stmt* stmt, int index, ColumnType type, const std::string& value) {
        int rc;
        switch (type) {
            case ColumnType::INTEGER:
                rc = sqlite3_bind_int(stmt, index, std::stoi(value));
                break;
            case ColumnType::TEXT:
                rc = sqlite3_bind_text(stmt, index, value.c_str(), -1, SQLITE_STATIC);
                break;
            case ColumnType::REAL:
                rc = sqlite3_bind_double(stmt, index, std::stod(value));
                break;
            case ColumnType::BLOB:
                rc = sqlite3_bind_blob(stmt, index, value.c_str(), value.size(), SQLITE_STATIC);
                break;
            default:
                throw std::invalid_argument("Invalid column type");
        }
        if (rc != SQLITE_OK) {
            throw std::runtime_error("Failed to bind value to statement");
        }
    }
    
    template<typename T>
    void mapRowToModel(sqlite3_stmt* stmt, const std::vector<std::string>& columnNames, T& model) {
        std::apply([&stmt](auto&&... args) {
            ((std::get<decltype(args)::value - 1>(args) = getColumnValue<decltype(args)>(stmt, decltype(args)::value - 1)), ...);
        }, std::make_tuple(std::make_pair(&T::id, "id"), std::make_pair(&T::name, "name"), std::make_pair(&T::value, "value")));
    }
    
    void handleError(const std::string& errorMsg) {
        std::cerr << "Error: " << errorMsg << std::endl;
        sqlite3_close(this->_db);
        throw std::runtime_error(errorMsg);
    }
};


#endif /* SqliteTable_h */
