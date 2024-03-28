#pragma once

#include <iostream>
#include <memory>

#include "person.hxx"
#include "person-odb.hxx"

#include <odb/database.hxx>
#include <odb/sqlite/database.hxx>
#include <odb/schema-catalog.hxx>
#include <odb/query.hxx>
#include <odb/statement.hxx>
#include <odb/result.hxx>
#include <odb/transaction.hxx>
#include <odb/connection.hxx>
#include <odb/sqlite/connection.hxx>
#include <odb/sqlite/transaction.hxx>
//#include "DataModel.h"




	
	class SettingsSQL
	{
	public:
		static SettingsSQL& GetInstance() {
			static SettingsSQL instance;
			return instance;
		}
		

	private:
		SettingsSQL() {

			std::unique_ptr<odb::sqlite::database> db(
				new odb::sqlite::database("AAAAA.db", SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE));

			odb::transaction t(db->begin());

			odb::schema_catalog::create_schema(*db);

			t.commit();

			odb::transaction t1(db->begin());

			person person1("Alice", "A", 30);
			db->persist(person1);

			person person2("Bob", "B", 35);
			db->persist(person2);

			t1.commit();

		}
		~SettingsSQL() {}
		SettingsSQL(const SettingsSQL&) = delete; // Delete copy constructor
		SettingsSQL& operator=(const SettingsSQL&) = delete; // Delete copy assignment operator

	};

	void TestODBMain() {
		std::cout << " TEST ODB MAIN" << std::endl;
		SettingsSQL* settings = &SettingsSQL::GetInstance();
	}

