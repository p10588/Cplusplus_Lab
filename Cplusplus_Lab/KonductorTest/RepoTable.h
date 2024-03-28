#pragma once

#include <json.hpp>

using json = nlohmann::json;

template<typename T>
class IDataTable
{
protected:
	virtual void Add(const T& data) = 0;
	virtual void Get(int id) = 0;
	virtual void Update(int id, T newData) = 0;
	virtual void Delete(int id) = 0;
	virtual void List() = 0;
	virtual void ListbyId(int id) = 0;
};

template<typename T>
class FileTable : public IDataTable<T>
{
public:
	FileTable(json db);
	~FileTable();

	void Add(const T& data) override;
	void Get(int id) override;
	void Update(int id, T newData) override;
	void Delete(int id) override;
	void List() override;
	void ListbyId(int id) override;

private:
	json _db;
	void CreateTable(std::string tableName);
	void Save();
};

/*
template<typename T>
class SqliteTable : public IDataTable<T>
{
public:
	SqliteTable(sqlite3* db);
	~SqliteTable();

	void Add(const T& data)override;
	void Get(int id) override;
	void Update(int id, T newData) override;
	void Delete(int id) override;
	void List() override;
	void ListbyId(int id) override;

private:
	sqlite3* _db;
	const char* _tableName;
	std::vector<char*> columes;
	void CreateTable(std::string tableName) override;
};
*/

