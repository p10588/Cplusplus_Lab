#pragma once

#include <string>
#include <fstream>

#include "../Json/json.hpp"

using json = nlohmann::json;

namespace MulitJson {
	template<typename T>
	class FileIO
	{
	public:
		
		FileIO(const std::string fileName) {
			this->_fileName = fileName;
			this->TryGetFileOrCreate(this->_cache);
		}

		T GetData() {
			return this->_cache;
		}

		void SetData(T data) {
			
			auto backup = this->_cache;

			this->_cache = data;
			if (this->WriteFile(data)) {
				return true;
			}
			else { //rollback cache
				this->_cache = backup;
				return false;
			}
			
		}

		/*bool Save(T& data) {
			if (this->WriteFile(data)) {
				return true;
			}
			return false;
		}*/


	private:
		std::string _fileName;
		T _cache;
		bool TryGetFileOrCreate(T& data) {
			if (this->ReadFile(data))
				return true;

			T newData;
			if (this->WriteFile(newData)) { //create default value;

				data = newData;
				return true;
			}
			else
				return false;

		}

		bool ReadFile(T& data) {

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

		bool WriteFile(T& data) {
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
	};
}
