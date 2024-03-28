#pragma once

#include <string>
#include <odb/core.hxx>
//#include<odb/database.hxx>
#include <odb/schema-catalog.hxx>
//#include <odb/sqlite/database.hxx>

#pragma db model version(1, 1)

#pragma db object
    class person
    {
    public:
        person(const std::string& first,
            const std::string& last,
            unsigned short age)
            : first_(first), last_(last), age_(age) {
        }

        const std::string&
            first() const {
            return first_;
        }

        const std::string&
            last() const {
            return last_;
        }

        unsigned short
            age() const {
            return age_;
        }

        void
            age(unsigned short age) {
            age_ = age;
        }

    private:
        friend class odb::access;

        person() {}

#pragma db id auto
        unsigned long id_;

        std::string first_;
        std::string last_;
        unsigned short age_;
    };
    /*
    void TestODBMain() {
        std::unique_ptr<odb::sqlite::database> db(
            new odb::sqlite::database("AAAAA.db", SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE));

        odb::transaction t(db->begin());

        odb::schema_catalog::create_schema(*db);
        t.commit();
    }*/

